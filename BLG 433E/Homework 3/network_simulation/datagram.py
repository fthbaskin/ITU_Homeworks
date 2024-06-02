# Fatih Baskın
# 150210710


import time as Time


class Datagram:
    def __init__(self, source_port: int, destination_port: int, datagram_number: int, data_length: int, queue_time: Time):
        self.source_port = source_port
        self.destination_port = destination_port
        self.datagram_number = datagram_number
        self.data_length = data_length
        self.queue_time = queue_time
        self.queue_out_time = None
        self.sent_data_length = 0
        self.sent_time = None
        self.is_data_sent = False

    def get_queue_time(self):
        if self.queue_out_time is not None:
            return self.queue_out_time - self.queue_time + 0.2
        return Time.time() - self.queue_time + 0.2

    def get_response_time(self):
        if self.queue_out_time is not None:
            if self.sent_time is not None:
                return self.sent_time - self.queue_out_time + 0.1
            return Time.time() - self.queue_out_time
        return 0.1

    def get_waiting_time(self):
        if self.sent_time is not None:
            return self.sent_time - self.queue_time + 0.3
        return Time.time() - self.queue_time + 0.3

    def mark_sent(self, time: Time = None):
        self.sent_time = time if time is not None else Time.time()
        self.is_data_sent = True

    def send_data(self, sendable_data_length: int) -> int:
        required_to_send = self.data_length - self.sent_data_length
        # If data is being sent for the first time, set the queue out time
        if self.queue_out_time is None:
            self.queue_out_time = Time.time()
        # If the remaining data is less than or equal to the sendable data length, send all the remaining data
        if required_to_send <= sendable_data_length:
            self.sent_data_length += required_to_send
            self.mark_sent()
            return required_to_send
        # If the remaining data is more than the sendable data length, send as much as the sendable data length
        else:
            self.sent_data_length += sendable_data_length
            return sendable_data_length

    def __str__(self):
        return f"""Datagram Information:
Source Port: {self.source_port} \t Destination Port: {self.destination_port}
Datagram Number: {self.datagram_number} \t Is Data Sent: {self.is_data_sent}
Data Length: {self.data_length} \t Sent Data Length: {self.sent_data_length}
Queue In Time: {self.queue_time} \t Queue Out Time: {self.queue_out_time} \t Sent Time: {self.sent_time}
Queue Time: {self.get_queue_time()} \t Response Time: {self.get_response_time()} \t Waiting Time: {self.get_waiting_time()}
"""
