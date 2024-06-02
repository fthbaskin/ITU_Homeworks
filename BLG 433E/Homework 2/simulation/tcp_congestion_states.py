# Fatih Baskın
# 150210710

from enum import Enum


class TCPCongestionState(Enum):
    SLOW_START = 1
    CONGESTION_AVOIDANCE = 2
    FAST_RECOVERY = 3
    TIMEOUT = 4
