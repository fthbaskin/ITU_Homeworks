# Fatih Baskın
# 150210710

import librosa
import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import soundfile as sf

# Load the audio file
AUDIO_FILE = 'part1_message.wav'
audio_samples, sampling_rate = librosa.load(AUDIO_FILE)

# Details of audio file, audio samples
print("Audio sample count:", len(audio_samples))
print("Audio sample rate:", sampling_rate)
print("Audio time lenght in seconds:", len(audio_samples) / sampling_rate)


def system_simulation(input_signal):
    # X = current input sample
    # A = X - 1/4 B + 1/8 C
    # Y = A - 7/4 B - 1/2 C
    # C = B
    # B = A

    # variables
    a = 0
    b = 0
    c = 0
    output_signal = []
    EPSILON = 0.00001

    # Loop to calculate the output signal
    for x in input_signal:
        a = x - 1/4 * b + 1/8 * c
        y = a - 7/4 * b - 1/2 * c
        c = b
        b = a
        output_signal.append(y)

    # Loop until the system converges
    while abs(a) > EPSILON or abs(b) > EPSILON or abs(c) > EPSILON:
        a = 0 - ((1/4) * b) + ((1/8) * c)
        y = a - ((7/4) * b) - ((1/2) * c)
        c = b
        b = a
        output_signal.append(y)

    return output_signal


# Then, calculate the output signal
output_signal = system_simulation(audio_samples)
# Save the output signal
sf.write('part2_output_signal.wav', output_signal, sampling_rate)

# plot the output signal
plt.figure()
plt.plot(output_signal, color='red', label='Output Signal')
plt.plot(audio_samples, color='blue', label='Input Signal')
plt.legend()
plt.title('Output / Input Signal')
plt.xlabel('Sample')
plt.ylabel('Amplitude')
plt.savefig('part2_output_signal.png')
