# Fatih Baskın
# 150210710

from enum import Enum


# TCP events are defined as an enumeration
class TCPEvent(Enum):
    ACK = 1
    DOUBLE_ACK = 2
    TIMEOUT = 4
