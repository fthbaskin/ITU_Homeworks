# Fatih Baskın
# 150210710

import time as t


# TCP segment class that represents a TCP packet
class TCPSegment:
    def __init__(self, seq_num: int, ack_num: int, data_size: int = 1460):
        self.seq_num = seq_num
        self.ack_num = ack_num
        self.data_size = data_size
        self.segment_size = 40 + data_size  # 40 bytes for the TCP header
        self.retransmitted = False
