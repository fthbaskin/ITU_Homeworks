# Fatih Baskın
# 150210710

import numpy as np
from enum import Enum
from simulation.tcp_events import TCPEvent


# TCP event generator class that generates TCP events such as ACK, DOUBLE_ACK, and TIMEOUT
class TCPEventGenerator:
    def __init__(self, poission: float) -> None:
        self.poisson = poission  # Value of 1 is recommended

    # Generates a TCP event based on the Poisson distribution
    def generate_event(self) -> TCPEvent:
        # Generate a random number using the Poisson distribution
        random_number = np.random.poisson(self.poisson)
        # With the treshold values, determine the TCP event
        if random_number <= TCPEvent.ACK.value:
            return TCPEvent.ACK
        elif random_number <= TCPEvent.DOUBLE_ACK.value:
            return TCPEvent.DOUBLE_ACK
        else:
            return TCPEvent.TIMEOUT
