# Fatih Baskın
# 150210710


from network_simulation.datagram import Datagram
from enum import Enum
import time as Time
import numpy as np


class DatagramGeneratorType(Enum):
    CBR = 1
    VBR = 2
    ABR = 3


class DatagramGenerator:
    def __init__(self, source_port: int, destination_port, generator_type: DatagramGeneratorType,
                 average_bit_rate: int = None, constant_bit_rate: int = None):
        self.source_port = source_port
        self.destination_port = destination_port
        self.generator_type = generator_type
        self.average_bit_rate = average_bit_rate
        self.constant_bit_rate = constant_bit_rate
        self.current_datagram_number = 0
        self.last_datagram_time = Time.time()
        self.last_datagram_size = 0

    def set_bit_rate(self, average_bit_rate: int, constant_bit_rate: int = None):
        self.average_bit_rate = average_bit_rate
        self.constant_bit_rate = constant_bit_rate

    def set_mode(self, generator_type: DatagramGeneratorType, average_bit_rate: int = None, constant_bit_rate: int = None):
        self.generator_type = generator_type
        self.set_bit_rate(average_bit_rate, constant_bit_rate)

    def generate_datagram(self, queue_time: Time, available_capacity: int = None) -> Datagram:
        if self.generator_type == DatagramGeneratorType.CBR:
            return self._generate_cbr_datagram(queue_time)
        elif self.generator_type == DatagramGeneratorType.VBR:
            return self._generate_vbr_datagram(queue_time)
        elif self.generator_type == DatagramGeneratorType.ABR:
            return self._generate_abr_datagram(queue_time, available_capacity)
        else:
            raise ValueError("Unknown generator type")

    def _create_datagram(self, data_length: int, queue_time: Time) -> Datagram:
        datagram = Datagram(self.source_port, self.destination_port, self.current_datagram_number, data_length, queue_time)
        # update the last datagram time and size
        self.current_datagram_number += 1
        self.last_datagram_time = queue_time
        self.last_datagram_size = data_length
        return datagram

    def _generate_cbr_datagram(self, queue_time: Time):
        # do necessary checks for the bit rate
        if self.constant_bit_rate is None:
            raise ValueError("Constant bit rate must be provided for CBR")
        # do necessary calculations for the current datagram
        time_difference = Time.time() - self.last_datagram_time
        # calculate the supposed data length
        data_length = int(self.constant_bit_rate * time_difference)
        # generate a datagram with the calculated data length
        datagram = self._create_datagram(data_length, queue_time)
        return datagram

    def _generate_vbr_datagram(self, queue_time: Time):
        # do necessary checks for the bit rate limits
        if self.average_bit_rate is None:
            raise ValueError("Average bit rate must be provided for VBR")
        # do necessary calculations for the current datagram
        current_required_bit_rate = np.random.poisson(self.average_bit_rate)
        time_difference = Time.time() - self.last_datagram_time
        # calculate the supposed data length
        data_length = int(current_required_bit_rate * time_difference)
        # generate a datagram with the calculated data length
        datagram = self._create_datagram(data_length, queue_time)
        return datagram

    def _generate_abr_datagram(self, queue_time: Time, data_length: int = None):
        # do necessary checks for the data length
        if data_length is None:
            raise ValueError("Data length must be provided for ABR")
        # do necessary calculations for the current datagram
        time_difference = Time.time() - self.last_datagram_time
        # calculate the supposed data length
        data_length = int(data_length * time_difference)
        # generate a datagram with the provided data length
        datagram = self._create_datagram(data_length, queue_time)
        return datagram
