# Fatih Baskın
# 150210710

import librosa
import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf

# Load the audio file
AUDIO_FILE = 'bayrakfm.wav'
audio_samples, sampling_rate = librosa.load(AUDIO_FILE)

# Details of audio file, audio samples
print("Audio sample count:", len(audio_samples))
print("Audio sample rate:", sampling_rate)
print("Audio time lenght in seconds:", len(audio_samples) / sampling_rate)

# Divide audio files in chunks
audio_chunks = []
for i in range(0, len(audio_samples), sampling_rate):
    audio_chunks.append(audio_samples[i:i+sampling_rate])
print("Audio is divided into chunks, number of chunks:", len(audio_chunks))

# Then, calculate FFT for each chunk
audio_chunks_fft = []
for audio_chunk in audio_chunks:
    audio_chunks_fft.append(np.fft.fft(audio_chunk))
print("FFTs are calculated for chunks, number of chunks:", len(audio_chunks_fft))

# Plot the first chunk
plt.figure(figsize=(20, 10))
plt.scatter(x=[i for i in range(0, len(audio_chunks_fft[0]))], y=audio_chunks_fft[0], s=1)
plt.title("First chunk FFT")
plt.xlabel("Frequency")
plt.yscale("log")
plt.ylabel("Magnitude(log scale)")
plt.savefig("part1_first_chunk_fft.png")

# Then, get the song and message parts from the FFT
song_chunks_fft = []
message_chunks_fft = []
for audio_chunk_fft in audio_chunks_fft:
    audio_chunk_fft_len = len(audio_chunk_fft)
    first_half = audio_chunk_fft[:audio_chunk_fft_len // 2]
    second_half = audio_chunk_fft[audio_chunk_fft_len // 2:]
    # Add padding to make the lenght of halves equal to the lenght of audio_chunk_fft
    first_half = np.pad(first_half, (0, audio_chunk_fft_len - len(first_half)), 'constant', constant_values=(0, 0))
    second_half = np.pad(second_half, (0, audio_chunk_fft_len - len(second_half)), 'constant', constant_values=(0, 0))
    # Append halves to song and message parts
    song_chunks_fft.append(first_half)
    message_chunks_fft.append(second_half)

# Then, calculate the inverse FFT for song and message parts
song_chunks = []
message_chunks = []
for song_chunk_fft in song_chunks_fft:
    song_chunks.append(np.fft.ifft(song_chunk_fft))
for message_chunk_fft in message_chunks_fft:
    message_chunks.append(np.fft.ifft(message_chunk_fft))

# Combine the song and message parts
song = np.concatenate(song_chunks)
message = np.concatenate(message_chunks)

# Save the song and message parts as audio files
sf.write("part1_song.wav", np.real(song), sampling_rate)
sf.write("part1_message.wav", np.real(message), sampling_rate)
