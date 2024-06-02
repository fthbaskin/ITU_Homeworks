# Fatih Baskın
# 150210710

from network_simulation.datagram import Datagram
from network_simulation.datagram_generator import DatagramGenerator, DatagramGeneratorType
from network_simulation.router import Router, RouterStrategy
from network_simulation.network import Network
import time as Time
from enum import Enum


def ask_user_simulation_parameters() -> tuple[DatagramGeneratorType, RouterStrategy, int, int, int, int]:
    print("Please enter the simulation parameters.")
    total_burst_rate = int(input("Enter the burst rate of router port: "))
    queue_size = int(input("Enter the queue size of router: "))
    num_ports = int(input("Enter the number of ports (queues): "))
    bit_rate = int(input("Enter the bit rate (for the service): "))
    datagram_generator_type = int(input("Enter the datagram generator type (1 for CBR, 2 for VBR, 3 for ABR): "))
    router_strategy = int(input("Enter the router strategy (1 for FIFO, 2 for RR, 3 for WFQ): "))
    if datagram_generator_type == 1:
        datagram_generator_type = DatagramGeneratorType.CBR
    elif datagram_generator_type == 2:
        datagram_generator_type = DatagramGeneratorType.VBR
    elif datagram_generator_type == 3:
        datagram_generator_type = DatagramGeneratorType.ABR
    else:
        raise ValueError("Unknown datagram generator type")
    if router_strategy == 1:
        router_strategy = RouterStrategy.FIFO
    elif router_strategy == 2:
        router_strategy = RouterStrategy.RR
    elif router_strategy == 3:
        router_strategy = RouterStrategy.WFQ
    else:
        raise ValueError("Unknown router strategy")
    return datagram_generator_type, router_strategy, total_burst_rate, queue_size, num_ports, bit_rate


if __name__ == "__main__":
    datagram_generator_type, router_strategy, total_burst_rate, queue_size, num_ports, bit_rate = ask_user_simulation_parameters()

    # Create a network with the given parameters
    network = Network(total_burst_rate, queue_size, router_strategy, datagram_generator_type,
                      num_ports, num_ports, bit_rate, bit_rate)
    # Simulate the network for 10 seconds
    start_time = Time.time()
    network.simulate(10)
    network.statistics(start_time)
