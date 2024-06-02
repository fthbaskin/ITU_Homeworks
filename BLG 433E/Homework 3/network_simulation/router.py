# Fatih Baskın
# 150210710


from network_simulation.datagram import Datagram
from network_simulation.datagram_generator import DatagramGenerator, DatagramGeneratorType
from enum import Enum
import time as Time


class RouterStrategy(Enum):
    FIFO = 1
    RR = 2  # Round Robin aka fair queuing
    WFQ = 3


class Router:
    def __init__(self, total_burst_rate: int, strategy: RouterStrategy):
        self.total_burst_rate = total_burst_rate
        self.strategy = strategy
        self.output_ports = []
        self.output_port_priorities = {}
        self.output_port_capacity = {}
        self.output_queues = {}
        self.output_troughputs = {}
        self.total_troughputs = []
        self.sent_datagrams = []
        self.port_datagram_statistics = []
        self.all_datagram_statistics = []

    def change_strategy(self, strategy: RouterStrategy):
        self.strategy = strategy

    def change_total_burst_rate(self, total_burst_rate: int):
        self.total_burst_rate = total_burst_rate

    def add_output_port(self, port_number: int, priority: int, capacity: int):
        self.output_ports.append(port_number)
        self.output_queues[port_number] = []
        self.output_troughputs[port_number] = []
        self.output_port_priorities[port_number] = priority
        self.output_port_capacity[port_number] = capacity

    def receive_datagram(self, datagram: Datagram):
        self.output_queues[datagram.destination_port].append(datagram)

    def _burst_data(self, port_number: int, burst_rate: int) -> int:
        total_sent_data = 0
        while len(self.output_queues[port_number]) > 0 and total_sent_data < burst_rate:
            datagram = self.output_queues[port_number][0]
            sent_data = datagram.send_data(burst_rate - total_sent_data)
            total_sent_data += sent_data
            if datagram.is_data_sent:
                self.sent_datagrams.append(datagram)
                self.output_queues[port_number].pop(0)
        self.output_troughputs[port_number].append((total_sent_data, Time.time()))
        return total_sent_data

    def send_data(self) -> int:
        if self.strategy == RouterStrategy.FIFO:
            sent_data_amount = self._send_data_fifo()
        elif self.strategy == RouterStrategy.RR:
            sent_data_amount = self._send_data_rr()
        elif self.strategy == RouterStrategy.WFQ:
            sent_data_amount = self._send_data_wfq()
        self.total_troughputs.append((sent_data_amount, Time.time()))
        return sent_data_amount

    def _send_data_fifo(self) -> int:
        # Fifo scheduling should take the earliest queued datagram
        total_sent_data = 0
        # While queues are not empty and total sent data is less than the total burst rate
        while total_sent_data < self.total_burst_rate:
            # Find the earliest queued port
            earliest_port = self._find_earliest_port()
            if earliest_port == -1:
                return total_sent_data
            # Send data to the earliest queued port
            sent_data = self._burst_data(earliest_port, self.total_burst_rate - total_sent_data)
            total_sent_data += sent_data
        return total_sent_data

    def _send_data_rr(self) -> int:
        # Send equal amount of data to each port
        total_sent_data = 0
        send_data_amount = self.total_burst_rate // len(self.output_ports)
        for port_number in self.output_ports:
            total_sent_data += self._burst_data(port_number, send_data_amount)
        return total_sent_data

    def _send_data_wfq(self):
        # Calculate the total priority
        total_sent_data = 0
        total_priority = sum(self.output_port_priorities.values())
        for port_number in self.output_ports:
            # Send data according to the priority of the port
            send_data_amount = (self.total_burst_rate * self.output_port_priorities[port_number]) // total_priority
            total_sent_data += self._burst_data(port_number, send_data_amount)
        return total_sent_data

    def _list_checker(self, list: list) -> bool:
        if list is None:
            return False
        if len(list) == 0:
            return False
        return True

    def _find_earliest_port(self) -> int:
        earliest_port = -1
        earliest_time = float('inf')
        for port_number in self.output_queues:
            if self._list_checker(self.output_queues[port_number]):
                if self.output_queues[port_number][0].queue_time < earliest_time:
                    earliest_time = self.output_queues[port_number][0].queue_time
                    earliest_port = port_number
        return earliest_port

    def available_data_in_queue(self, port: int) -> int:
        total_data_in_queue = sum([datagram.data_length - datagram.sent_data_length for datagram in self.output_queues[port]])
        return self.output_port_capacity[port] - total_data_in_queue

    def get_average_troughputs_per_port(self, start_time: Time) -> dict[int, list[tuple[float, float]]]:
        raw_data = {}
        for port in self.output_troughputs:
            raw_data[port] = self.output_troughputs[port]
        prefix_sum = {}
        for port in raw_data:
            prefix_sum[port] = []
            for i in range(len(raw_data[port])):
                if i == 0:
                    prefix_sum[port].append(raw_data[port][i])
                else:
                    prefix_sum[port].append((prefix_sum[port][i-1][0] + raw_data[port][i][0], raw_data[port][i][1]))
        troughputs = {}
        for port in prefix_sum:
            troughputs[port] = []
            for i in range(len(prefix_sum[port])):
                if prefix_sum[port][i][1] >= start_time:
                    time_fix = prefix_sum[port][i][1] - start_time
                    troughput = prefix_sum[port][i][0] / time_fix if time_fix != 0 else 1
                    troughputs[port].append((troughput, time_fix))
        return troughputs

    def get_average_troughputs(self, start_time: Time) -> list[tuple[float, float]]:
        prefix_sum = []
        for i in range(len(self.total_troughputs)):
            if i == 0:
                prefix_sum.append(self.total_troughputs[i])
            else:
                prefix_sum.append((prefix_sum[i-1][0] + self.total_troughputs[i][0], self.total_troughputs[i][1]))
        troughputs = []
        for i in range(len(prefix_sum)):
            if prefix_sum[i][1] >= start_time:
                time_fix = prefix_sum[i][1] - start_time
                troughput = prefix_sum[i][0] / time_fix if time_fix != 0 else 1
                troughputs.append((troughput, time_fix))
        return troughputs

    def save_datagram_statistics(self, start_time: Time):
        current_port_datagram_statistics = self._datagram_statistics_per_port()
        current_all_datagram_statistics = self._datagram_statistics()
        self.port_datagram_statistics.append((Time.time() - start_time, current_port_datagram_statistics))
        self.all_datagram_statistics.append((Time.time() - start_time, current_all_datagram_statistics))

    def _datagram_statistics_per_port(self) -> dict[int, tuple[float, float, float]]:
        statistics = {}
        for port in self.output_ports:
            total_queue_time = 0
            queue_count = 0
            total_response_time = 0
            response_count = 0
            total_waiting_time = 0
            waiting_count = 0
            # Get the statistics for each datagram in the queue
            for datagram in self.output_queues[port]:
                total_queue_time += datagram.get_queue_time()
                queue_count += 1
                if datagram.queue_out_time is not None:
                    total_response_time += datagram.get_response_time()
                    response_count += 1
                if datagram.is_data_sent:
                    total_waiting_time += datagram.get_waiting_time()
                    waiting_count += 1
            for sent_datagram in self.sent_datagrams:
                if sent_datagram.destination_port == port:
                    total_response_time += sent_datagram.get_response_time()
                    response_count += 1
                    total_waiting_time += sent_datagram.get_waiting_time()
                    waiting_count += 1
                    total_queue_time += sent_datagram.get_queue_time()
                    queue_count += 1

            average_queue_time = total_queue_time / queue_count if queue_count != 0 else 0
            average_response_time = total_response_time / response_count if response_count != 0 else 0
            average_waiting_time = total_waiting_time / waiting_count if waiting_count != 0 else 0
            statistics[port] = (average_queue_time, average_response_time, average_waiting_time)
        return statistics

    def _datagram_statistics(self) -> tuple[float, float, float]:
        total_queue_time = 0
        queue_count = 0
        total_response_time = 0
        response_count = 0
        total_waiting_time = 0
        waiting_count = 0

        for port in self.output_ports:
            for datagram in self.output_queues[port]:
                total_queue_time += datagram.get_queue_time()
                queue_count += 1
                if datagram.queue_out_time is not None:
                    total_response_time += datagram.get_response_time()
                    response_count += 1
                if datagram.is_data_sent:
                    total_waiting_time += datagram.get_waiting_time()
                    waiting_count += 1

        for sent_datagram in self.sent_datagrams:
            total_response_time += sent_datagram.get_response_time()
            response_count += 1
            total_waiting_time += sent_datagram.get_waiting_time()
            waiting_count += 1
            total_queue_time += sent_datagram.get_queue_time()
            queue_count += 1

        average_queue_time = total_queue_time / queue_count if queue_count != 0 else 0
        average_response_time = total_response_time / response_count if response_count != 0 else 0
        average_waiting_time = total_waiting_time / waiting_count if waiting_count != 0 else 0
        return average_queue_time, average_response_time, average_waiting_time
