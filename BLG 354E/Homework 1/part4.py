# Fatih Baskın
# 150210710

import matplotlib.pyplot as plt
import numpy as np


# Functions for H1(w) and H2(w)
def H1(w):
    coefficient = 10
    nominator = (1 + (1j * w) / 1)
    denominator = (1 + (1j * w) / 10) * (1 + (1j * w) / 10)
    return coefficient * (nominator / denominator)


def H2(w):
    coefficient = 1
    nominator = 1
    denominator = (1 + (1j * w) / 10)
    return coefficient * (nominator / denominator)


# Functions for magnitude and phase response
def magnitude_response(Hw):
    return np.abs(Hw)


def phase_response(Hw):
    return np.angle(Hw)


# Generate omegas
omegas = np.logspace(-2, 3, 1000)

# Calculate H1(w), H2(w) and H1(w) . H2(w)
H1s = [H1(omega) for omega in omegas]
H2s = [H2(omega) for omega in omegas]
H1H2s = [H1(omega) * H2(omega) for omega in omegas]

# Calculate magnitude responses for H1(w), H2(w) and H1(w) . H2(w)
H1_magnitudes = [magnitude_response(H1(omega)) for omega in omegas]
H2_magnitudes = [magnitude_response(H2(omega)) for omega in omegas]
H1H2_magnitudes = [magnitude_response(H1(omega) * H2(omega)) for omega in omegas]

# Turn magnitudes to dB
H1_magnitudes_dB = 20 * np.log10(H1_magnitudes)
H2_magnitudes_dB = 20 * np.log10(H2_magnitudes)
H1H2_magnitudes_dB = 20 * np.log10(H1H2_magnitudes)

# Plot the magnitude response
plt.figure(figsize=(20, 10))
plt.plot(omegas, H1_magnitudes_dB, label='|H1(w)|')
plt.plot(omegas, H2_magnitudes_dB, label='|H2(w)|')
plt.plot(omegas, H1H2_magnitudes_dB, label='|H1(w) . H2(w)|')
plt.grid(True)
plt.xscale('log')
plt.xlabel('Frequency (rad/s)')
plt.ylabel('Magnitude (dB)')
plt.title('Magnitude Response')
plt.legend()
plt.savefig('part4_magnitude_response.png')

# Calculate phase responses for H1(w), H2(w) and H1(w) . H2(w)
H1_phases = [phase_response(H1(omega)) for omega in omegas]
H2_phases = [phase_response(H2(omega)) for omega in omegas]
H1H2_phases = [phase_response(H1(omega) * H2(omega)) for omega in omegas]

# Plot the phase response
plt.figure(figsize=(20, 10))
plt.plot(omegas, H1_phases, label='Phase of H1(w)')
plt.plot(omegas, H2_phases, label='Phase of H2(w)')
plt.plot(omegas, H1H2_phases, label='Phase of H1(w) . H2(w)')
plt.xscale('log')
plt.xticks(np.logspace(-2, 3, 6), ['0.01', '0.1', '1', '10', '100', '1000'])
plt.yticks(np.linspace(-np.pi, np.pi/2, 7), ['-pi', '-3pi/4', '-pi/2', '-pi/4', '0', 'pi/4', 'pi/2'])
plt.grid(True)
plt.xlabel('Frequency (rad/s)')
plt.ylabel('Phase (radians)')
plt.title('Phase Response')
plt.legend()
plt.savefig('part4_phase_response.png')
