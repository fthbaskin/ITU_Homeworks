# Fatih Baskın
# 150210710

from simulation.tcp_segment import TCPSegment
from simulation.tcp_congestion_states import TCPCongestionState
from typing import List


# TCP server class that sends TCP packets to the client and receives ACK packets from the client
class TCPServer:
    def __init__(self) -> None:
        # Congestion control variables
        self.cwnd = 1
        self.ssthresh = 16
        self.dup_ack_count = 0
        self.congestion_state = TCPCongestionState.SLOW_START
        # Keep track of the last ACK received and the last sequence number sent
        self.last_ack_received = 0
        self.last_seq_sent = 0
        self.sent_segments = []

    # Receive an ACK packet from the client
    def receive_ack(self, ack_num: int) -> None:
        # If the ACK number is greater than the last ACK received, then the ACK is correct
        if ack_num > self.last_ack_received:
            return self._receive_correct_ack(ack_num)
        # If the ACK number is equal to the last ACK received, then the ACK is a duplicate ACK
        elif ack_num == self.last_ack_received:
            return self._receive_duplicate_ack(ack_num)
        # If the ACK number is less than the last ACK received, then the ACK is for an old segment
        else:
            return self._receive_old_ack(ack_num)

    def _receive_correct_ack(self, ack_num: int) -> None:
        # If the ACK number is equal to the last sequence number sent, then the ACK is for the last segment sent
        self.last_ack_received = ack_num
        self.dup_ack_count = 0
        # Remove the ACKed segment from the sent segments list
        self.sent_segments = [segment for segment in self.sent_segments if segment.seq_num > ack_num]
        # Update the congestion window size
        self._update_cwnd()

    # Increment the congestion window size based on the congestion control algorithm
    def _update_cwnd(self) -> None:
        if self.congestion_state == TCPCongestionState.SLOW_START:
            self.cwnd *= 2  # Exponential increase
            if self.cwnd >= self.ssthresh:
                self.congestion_state = TCPCongestionState.CONGESTION_AVOIDANCE
        elif self.congestion_state == TCPCongestionState.CONGESTION_AVOIDANCE:
            self.cwnd += 1  # Additive increase
        elif self.congestion_state == TCPCongestionState.FAST_RECOVERY:
            self.cwnd += 1  # Additive increase (bug fix)
            self.congestion_state = TCPCongestionState.CONGESTION_AVOIDANCE
        else:  # TCPCongestionState.TIMEOUT
            self.ssthresh = max(self.cwnd / 2, 2)  # Multiplicative decrease
            self.cwnd = 1
            self.congestion_state = TCPCongestionState.SLOW_START

    def _receive_duplicate_ack(self, ack_num: int) -> None:
        # If the ACK number is equal to the last sequence number sent, then the ACK is for the last segment sent
        self.dup_ack_count += 1
        if self.dup_ack_count >= 3:
            self.ssthresh = max(self.cwnd / 2, 2)
            self.cwnd = self.ssthresh + 3
            self.congestion_state = TCPCongestionState.FAST_RECOVERY

    def _receive_old_ack(self, ack_num: int) -> None:
        # If the ACK number is less than the last sequence number sent, then the ACK is for an old segment
        pass  # Do nothing, the ACK is for an old segment

    def send_data(self) -> list[TCPSegment]:
        # Send new data segments based on the tcp state
        if self.congestion_state == TCPCongestionState.SLOW_START or self.congestion_state == TCPCongestionState.CONGESTION_AVOIDANCE:
            return self._send_data_helper()
        else:
            return self._initiate_retransmission()

    def _send_data_helper(self) -> list[TCPSegment]:
        will_send_segments = []
        # It might be necessary to send old segments again
        sent_segments_size = len(self.sent_segments)
        sent_segments_idx = 0
        while len(will_send_segments) < self.cwnd:
            if sent_segments_idx < sent_segments_size and self.last_seq_sent >= self.sent_segments[sent_segments_idx].seq_num:
                # Already retranmitted, skip
                sent_segments_idx += 1
                continue
            elif sent_segments_idx < sent_segments_size:
                # Retransmit the segment
                self.sent_segments[sent_segments_idx].retransmitted = True
                will_send_segments.append(self.sent_segments[sent_segments_idx])
                sent_segments_idx += 1
            else:
                # Send a new segment
                self.last_seq_sent += 1
                will_send_segments.append(TCPSegment(self.last_seq_sent, self.last_ack_received))
                self.sent_segments.append(will_send_segments[-1])
        # Return the segments to be sent
        return will_send_segments

    def _initiate_retransmission(self) -> List[TCPSegment]:
        # To initiate retransmission, update the last_seq_sent to the last ACK received
        self.last_seq_sent = self.last_ack_received
        # Send the data with this new sequence number
        return self._send_data_helper()

    def _timeout(self) -> None:
        # Timeout occurred, update the congestion control variables
        self.congestion_state = TCPCongestionState.TIMEOUT
        # To initiate retransmission, update the last_seq_sent to the last ACK received (bug fix)
        self.last_seq_sent = self.last_ack_received
        self._update_cwnd()
