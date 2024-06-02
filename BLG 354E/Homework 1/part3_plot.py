# Fatih Baskın
# 150210710

import soundcard as sc
import numpy as np
import matplotlib.pyplot as plt
from time import sleep

SAMPLE_RATE = 148000
NUM_SAMPLES = 1000000

sleep(2)

# Sound detection
microphones = sc.all_microphones(include_loopback=True)
mic = microphones[1]  # Bluetooth headstet loopback

with mic.recorder(samplerate=SAMPLE_RATE) as mic:
    data = mic.record(numframes=NUM_SAMPLES)

# reduce the data to one channel
data = data[:, 0]

# Take the std of the data
data_std = np.std(data)

# STD of square wave is higher than triangle wave
print(data_std)

plt.plot(data)
plt.grid()
plt.xlabel("Samples")
plt.ylabel("Amplitude")
plt.title("Sound wave")
# plt.savefig("part3_triangle_wave.png")
plt.savefig("part3_square_wave.png")
