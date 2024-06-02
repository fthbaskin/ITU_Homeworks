# Fatih Baskın
# 150210710

from network_simulation.datagram import Datagram
from network_simulation.datagram_generator import DatagramGenerator, DatagramGeneratorType
from network_simulation.router import Router, RouterStrategy
from enum import Enum
import time as Time
import numpy as np
import matplotlib.pyplot as plt


class Network:
    def __init__(self, total_burst_rate: int, queue_capacity: int, strategy: RouterStrategy, service_type: DatagramGeneratorType, num_input_ports: int, num_output_ports: int, average_bit_rate: int = None, constant_bit_rate: int = None):
        self.start_time = None
        self.service_type = service_type
        self.strategy = strategy
        self.num_input_ports = num_input_ports
        self.num_output_ports = num_output_ports
        self.average_bit_rate = average_bit_rate
        self.constant_bit_rate = constant_bit_rate
        # Create a router with the given total burst rate and strategy
        self.router = Router(total_burst_rate, strategy)
        # Add output ports to the router
        for i in range(num_output_ports):
            self.router.add_output_port(i, np.random.randint(low=1, high=(2*num_output_ports)), queue_capacity)
        # Add datagram generators to the network
        self.datagram_generators = []
        for i in range(num_input_ports):
            self.datagram_generators.append(DatagramGenerator(i, i, service_type, average_bit_rate, constant_bit_rate))

    def _generate_datagrams(self):
        for generator in self.datagram_generators:
            output_port = generator.destination_port
            available_capacity = self.router.available_data_in_queue(output_port)
            if DatagramGeneratorType.ABR == generator.generator_type:
                datagram = generator.generate_datagram(Time.time(), available_capacity)
            elif DatagramGeneratorType.CBR == generator.generator_type and available_capacity >= self.constant_bit_rate:
                datagram = generator.generate_datagram(Time.time())
            elif DatagramGeneratorType.VBR == generator.generator_type and available_capacity >= self.average_bit_rate:
                datagram = generator.generate_datagram(Time.time())
            else:
                datagram = None
            if datagram is not None:
                self.router.receive_datagram(datagram)

    def _send_data(self):
        self.router.send_data()

    def _save_statistics(self, start_time: Time):
        self.router.save_datagram_statistics(start_time)

    def simulate(self, duration: int):
        print("Simulation is starting.")
        self.start_time = Time.time()
        while Time.time() - self.start_time < duration:
            print("Time: ", Time.time() - self.start_time)
            self._generate_datagrams()
            self._send_data()
            self._save_statistics(self.start_time)
            Time.sleep(0.1)
        print("Simulation is over.")

    def _plot_troughputs_per_port(self, start_time: Time):
        ports_data = self.router.get_average_troughputs_per_port(start_time)

        for port, data in ports_data.items():
            times = [troughput[1] for troughput in data]
            data = [troughput[0] for troughput in data]
            plt.plot(times, data, label=f"Port {port}")
        plt.xlabel("Time (s)")
        plt.ylabel("Troughput (bit/s)")
        plt.legend()
        plt.savefig("troughputs_per_port.png")
        plt.show()

    def _plot_total_troughput(self, start_time: Time):
        troughputs = self.router.get_average_troughputs(start_time)
        times = [troughput[1] for troughput in troughputs]
        data = [troughput[0] for troughput in troughputs]
        plt.plot(times, data)
        plt.xlabel("Time (s)")
        plt.ylabel("Total Troughput (bit/s)")
        plt.savefig("total_troughput.png")
        plt.show()

    def _log_datagrams(self):
        with open("datagrams.log", "w") as file:
            file.write("Sent Datagrams\n")
            for datagram in self.router.sent_datagrams:
                file.write(str(datagram) + "\n")

            file.write("In Queue Datagrams\n")
            for port in self.router.output_queues:
                file.write(f"Port {port} Datagrams\n")
                for datagram in self.router.output_queues[port]:
                    file.write(str(datagram) + "\n")

    def _plot_datagram_statistics_per_port(self):
        print("Showing datagram statistics for each port.")
        data = self.router.port_datagram_statistics
        time = [stat[0] for stat in data]
        ports_data = [stat[1] for stat in data]

        # Turn list of dictionaries into dictionary of lists
        ports_data_dict = {port: [] for port in range(self.num_output_ports)}
        for port_data in ports_data:
            for port, stats in port_data.items():
                ports_data_dict[port].append(stats)

        # Plot the average queue time for each port
        for port, stats in ports_data_dict.items():
            queue_times = [stat[0] for stat in stats]
            if len(queue_times) != len(time):
                queue_times = [0 for _ in time]
            plt.plot(time, queue_times, label=f"Port {port} Queue Time")
        plt.xlabel("Time (s)")
        plt.ylabel("Average Queue Time (s)")
        plt.legend()
        plt.savefig("queue_times_per_port.png")
        plt.show()

        # Plot the average response time for each port
        for port, stats in ports_data_dict.items():
            response_times = [stat[1] for stat in stats]
            if len(response_times) != len(time):
                response_times = [0 for _ in time]
            plt.plot(time, response_times, label=f"Port {port} Response Time")
        plt.xlabel("Time (s)")
        plt.ylabel("Average Response Time (s)")
        plt.legend()
        plt.savefig("response_times_per_port.png")
        plt.show()

        # Plot the average waiting time for each port
        for port, stats in ports_data_dict.items():
            waiting_times = [stat[2] for stat in stats]
            if len(waiting_times) != len(time):
                waiting_times = [0 for _ in time]
            plt.plot(time, waiting_times, label=f"Port {port} Waiting Time")
        plt.xlabel("Time (s)")
        plt.ylabel("Average Waiting Time (s)")
        plt.legend()
        plt.savefig("waiting_times_per_port.png")
        plt.show()

    def _plot_datagram_statistics(self):
        data = self.router.all_datagram_statistics
        time = [stat[0] for stat in data]
        stats = [stat[1] for stat in data]
        # Plot the average queue time for the whole network
        queue_times = [stat[0] for stat in stats]
        plt.plot(time, queue_times, label="Average Queue Time")
        response_times = [stat[1] for stat in stats]
        plt.plot(time, response_times, label="Average Response Time")
        waiting_times = [stat[2] for stat in stats]
        plt.plot(time, waiting_times, label="Average Waiting Time")
        plt.legend()
        plt.xlabel("Time (s)")
        plt.ylabel("Average Time Elapsed (s)")
        plt.savefig("network_statistics.png")
        plt.show()

    def statistics(self, start_time: Time):
        print("Showing troughputs per port and total troughput.")
        self._plot_troughputs_per_port(start_time)
        self._plot_total_troughput(start_time)
        print("Logging datagrams.")
        self._log_datagrams()
        print("Statistics (average queue time, average response time, average waiting time) for each port:")
        self._plot_datagram_statistics_per_port()
        print("Average queue time, average response time, average waiting time:")
        self._plot_datagram_statistics()
