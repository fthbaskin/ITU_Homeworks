# Fatih Baskın
# 150210710

import time as t
from enum import Enum
from simulation.tcp_segment import TCPSegment
from simulation.tcp_congestion_states import TCPCongestionState
from simulation.tcp_events import TCPEvent
from simulation.tcp_server import TCPServer
from simulation.tcp_event_generator import TCPEventGenerator
from typing import List, Tuple


# This class is responsible for simulating the TCP protocol with the given parameters
class TCPSimulation:
    def __init__(self, poission: float, rtt: float):
        self.server = TCPServer()
        self.event_generator = TCPEventGenerator(poission)
        self.received_segments = []
        self.last_ack_sent = 0
        self.rtt = rtt

    def update_parameters(self, poission: float, rtt: float) -> None:
        self.event_generator.poisson = poission
        self.rtt = rtt

    def sim_iteration(self) -> Tuple[int, int, float, float, int, int, str]:
        # Get the packets from the server
        packets = self.server.send_data()
        ret_last_seq_sent = self.server.last_seq_sent

        # Add the received packets to the received segments list
        for packet in packets:
            self.received_segments.append(packet)
        # Generate a TCP event
        event = self.event_generator.generate_event()
        # Handle the TCP event
        if event == TCPEvent.ACK:
            self._ack(packets)
        elif event == TCPEvent.DOUBLE_ACK:
            self._double_ack()
        else:
            self._timeout()
        # Calculate the throughput and goodput
        throughput = self.calculate_throughput(packets)
        goodput = self.calculate_goodput(packets)
        # Return cwnd, sstresh, throughput, goodput, last_seq_sent, last_ack_received, event, message
        return self.server.cwnd, self.server.ssthresh, throughput, goodput, ret_last_seq_sent, self.server.last_ack_received, event.name

    def _ack(self, packets: List[TCPSegment]) -> None:
        # Get the highest sequence number from the received packets
        highest_seq_num = max([packet.seq_num for packet in packets])
        # Send an ACK packet to the server
        self.server.receive_ack(highest_seq_num)
        # Update the last ACK sent
        self.last_ack_sent = highest_seq_num
        # Clear the received packets
        self.received_segments.clear()
        return

    def _timeout(self) -> None:
        # Send a timeout event to the server
        self.server._timeout()
        # Clear the received packets
        self.received_segments.clear()
        return

    def _double_ack(self) -> None:
        # Send a double ACK event to the server
        self.server.receive_ack(self.last_ack_sent)
        return

    def calculate_throughput(self, incoming_data: List[TCPSegment]) -> float:
        # Calculate the total data size of the incoming packets
        total_data_size = sum([segment.segment_size for segment in incoming_data])
        # Calculate the throughput using the total data size and the round trip time
        throughput = total_data_size / self.rtt
        return throughput

    def calculate_goodput(self, incoming_data: List[TCPSegment]) -> float:
        # Calculate the good data size of the incoming packets (excluding retransmitted packets and headers)
        total_data_size = sum([segment.data_size if segment.retransmitted == False else 0 for segment in incoming_data])
        # Calculate the goodput using the total data size and the round trip time
        goodput = total_data_size / self.rtt
        return goodput
