# Fatih Baskın
# 150210710

import numpy as np
from enum import Enum
from simulation.tcp_simulation import TCPSimulation
from simulation.tcp_congestion_states import TCPCongestionState
import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
from PIL import Image, ImageTk

# TCP metrics class that represents the metrics of the TCP simulation
time = []
cwnd = []
ssthresh = []
troughput = []
goodput = []
events = []
last_seq_sent = []
last_ack_received = []
# TCP simulation constants
pOISSON = 1
rTT = 0.1
# TCP simulation object
tcp_simulation = TCPSimulation(pOISSON, rTT)
tcp_iteration = 0

# Iterate the simulation for a single step


def iterate_simulation(canvas1: FigureCanvasTkAgg, canvas2: FigureCanvasTkAgg, ax1: plt.Axes, ax2: plt.Axes, text_area: tk.Text, image_area: tk.Frame):
    # Return cwnd, sstresh, throughput, goodput, last_seq_sent, last_ack_received, event
    # return self.server.cwnd, self.server.ssthresh, throughput, goodput, ret_last_seq_sent, self.server.last_ack_received, event.name
    Icwnd, Isstresh, Ithroughput, Igoodput, Ilast_seq_sent, Ilast_ack_received, Ievent = tcp_simulation.sim_iteration()
    global tcp_iteration, rTT
    time.append(tcp_iteration*rTT)
    tcp_iteration += 1
    cwnd.append(Icwnd)
    ssthresh.append(Isstresh)
    troughput.append(Ithroughput / 1024)  # Convert to KB
    goodput.append(Igoodput / 1024)  # Convert to KB
    last_seq_sent.append(Ilast_seq_sent)
    last_ack_received.append(Ilast_ack_received)
    events.append(Ievent)
    # Only keep the last 20 elements
    if len(time) > 20:
        time.pop(0)
        cwnd.pop(0)
        ssthresh.pop(0)
        troughput.pop(0)
        goodput.pop(0)
        last_seq_sent.pop(0)
        last_ack_received.pop(0)
        events.pop(0)
    # Update the widgets
    update_diagrams(canvas1, canvas2, ax1, ax2)
    update_text(text_area)
    update_sequence(image_area)


# Update the sequence diagram of the main window
def update_sequence(image_area: tk.Frame):
    LOST_ACK = 'lost_ack.png'
    TRIPLE_DOUBLE_ACK = 'triple_ack.png'
    SLOW_START = 'slow_start.png'
    ACK = 'regular.png'
    TIMEOUT = 'timeout.png'
    PATH_TO = 'diagrams/'
    global events, tcp_simulation
    # Clear the image area
    for widget in image_area.winfo_children():
        widget.destroy()

    if events[-1] == "ACK":
        if tcp_simulation.server.congestion_state == TCPCongestionState.SLOW_START:
            img = Image.open(PATH_TO + SLOW_START)
        else:
            img = Image.open(PATH_TO + ACK)
    elif len(events) >= 3 and events[-1] == "DOUBLE_ACK" and events[-2] == "DOUBLE_ACK" and events[-3] == "DOUBLE_ACK":
        img = Image.open(PATH_TO + TRIPLE_DOUBLE_ACK)
    elif events[-1] == "DOUBLE_ACK":
        img = Image.open(PATH_TO + LOST_ACK)
    else:
        img = Image.open(PATH_TO + TIMEOUT)

    img = img.resize((500, 500), Image.BICUBIC)
    img = ImageTk.PhotoImage(img)
    panel = tk.Label(image_area, image=img)
    panel.image = img
    panel.pack(side="top", fill="both", expand="yes")


# Update the text area of the main window
def update_text(text_area: tk.Text):
    # Add the last element to the text area
    text_area.config(state=tk.NORMAL)
    # Write the time
    text_area.insert(tk.END, "Time: " + str(time[-1]) + "\n")
    # Write the performance metrics
    text_area.insert(tk.END, f"  CWND: {cwnd[-1]} sstresh: {ssthresh[-1]} troughput: {troughput[-1]} goodput: {goodput[-1]}\n")
    # Write the last sequence number and last ack received
    text_area.insert(tk.END, f"  Last Seq Sent: {last_seq_sent[-1]} Last Ack Received: {last_ack_received[-1]}\n")
    # Write TCP congestion state
    global tcp_simulation
    text_area.insert(tk.END, f"  Congestion Avoidance State: {tcp_simulation.server.congestion_state.name}\n")
    # Write the last event
    if events[-1] == "ACK":
        text_area.insert(tk.END, "  Event: ACK ")
    elif len(events) >= 3 and events[-1] == "DOUBLE_ACK" and events[-2] == "DOUBLE_ACK" and events[-3] == "DOUBLE_ACK":
        text_area.insert(tk.END, "  Event: TRIPLE_DOUBLE_ACK (lost packet)")
    elif events[-1] == "DOUBLE_ACK":
        text_area.insert(tk.END, "  Event: LOST ACK")
    else:
        text_area.insert(tk.END, "  Event: TIMEOUT (premature timeout)")
    text_area.insert(tk.END, "\n")
    text_area.config(state=tk.DISABLED)
    text_area.see(tk.END)


# Update the metrics diagrams of the main window
def update_diagrams(canvas1: FigureCanvasTkAgg, canvas2: FigureCanvasTkAgg, ax1: plt.Axes, ax2: plt.Axes):
    ax1.clear()
    ax1.plot(time, cwnd, label="CWND")
    ax1.plot(time, ssthresh, label="SSTHRESH")
    ax1.legend()
    ax1.set_xlabel("Time (s)")
    ax1.set_ylabel("Window Size")
    ax1.set_title("TCP Metrics")
    canvas1.draw()
    canvas1.get_tk_widget().pack(side="top", fill=tk.BOTH, expand=True)

    ax2.clear()
    ax2.plot(time, troughput, label="Throughput")
    ax2.plot(time, goodput, label="Goodput")
    ax2.legend()
    ax2.set_xlabel("Time (s)")
    ax2.set_ylabel("Data (KB/s)")
    ax2.set_title("Output Metrics")
    canvas2.draw()
    canvas2.get_tk_widget().pack(side="top", fill=tk.BOTH, expand=True)


# Create the widgets of the main window
def create_widgets(root):
    # Open the frames
    sequence_frame = tk.Frame(root, width=200, height=400)
    text_frame = tk.Frame(root, width=150, height=400)
    tcp_metrics_frame = tk.Frame(root, width=200, height=400)

    # Create the widgets
    sequence_frame.grid(row=0, column=0)
    text_frame.grid(row=0, column=1)
    tcp_metrics_frame.grid(row=0, column=2)

    # Create the read-only text area on the middle frame
    text_area = tk.Text(text_frame)
    text_area.pack(side="top", fill="both", expand="yes")
    scroll = tk.Scrollbar(text_frame, orient='vertical', command=text_area.yview)
    text_area.config(state=tk.DISABLED, yscrollcommand=scroll.set)  # read-only, with scroll
    text_area.pack(side="top", fill="both", expand="yes")
    scroll.pack(side="right", fill="y")

    # Create the metrics graph on the right frame
    fig1, ax1 = plt.subplots(figsize=(6, 5))
    ax1.plot(time, cwnd, label="CWND")
    ax1.plot(time, ssthresh, label="SSTHRESH")
    ax1.legend()
    ax1.set_xlabel("Time (s)")
    ax1.set_ylabel("Window Size")
    ax1.set_title("TCP Metrics")
    canvas1 = FigureCanvasTkAgg(fig1, master=tcp_metrics_frame)
    canvas1.draw()
    canvas1.get_tk_widget().pack(side="top", fill=tk.BOTH, expand=True)

    # Create the output metrics table on the right frame
    fig2, ax2 = plt.subplots(figsize=(6, 5))
    ax2.plot(time, troughput, label="Throughput")
    ax2.plot(time, goodput, label="Goodput")
    ax2.legend()
    ax2.set_xlabel("Time (s)")
    ax2.set_ylabel("Data (KB/s)")
    ax2.set_title("Output Metrics")
    canvas2 = FigureCanvasTkAgg(fig2, master=tcp_metrics_frame)
    canvas2.draw()
    canvas2.get_tk_widget().pack(side="bottom", fill=tk.BOTH, expand=True)

    # Create new frames for buttons
    buttons_frame = tk.Frame(root, width=300, height=100)
    buttons_frame.grid(row=1, column=0, columnspan=4)

    # Create iteration button on the right bottom frame
    iteration_button = tk.Button(buttons_frame, text="Iterate", command=lambda: iterate_simulation(canvas1, canvas2, ax1, ax2, text_area, sequence_frame))
    # Create iterate 5 button on the right bottom frame to iterate 5 times
    iteration_button_multiple = tk.Button(buttons_frame, text="Iterate 5 times", command=lambda: [
                                          iterate_simulation(canvas1, canvas2, ax1, ax2, text_area, sequence_frame) for _ in range(5)])
    iteration_button.pack(side="left")
    iteration_button_multiple.pack(side="left")

    # Text area to modify the simulation parameters
    global pOISSON, rTT
    poission_label = tk.Label(buttons_frame, text="Poisson parameter: " + str(pOISSON) + "\n")
    poission_label.pack(side="left")
    poission_input = tk.Text(buttons_frame, width=3, height=1)
    poission_input.pack(side="left", fill="both", expand="yes")
    rtt_label = tk.Label(buttons_frame, text="RTT: " + str(rTT) + "\n")
    rtt_label.pack(side="left")
    rtt_input = tk.Text(buttons_frame, width=3, height=1)
    rtt_input.pack(side="left", fill="both", expand="yes")

    # Button to update the simulation parameters
    update_button = tk.Button(buttons_frame, text="Update", command=lambda: update_parameters(
        poission_input.get("1.0", "end-1c"), rtt_input.get("1.0", "end-1c"), poission_label, rtt_label))
    update_button.pack(side="left")


def update_parameters(poission: str, rtt: str, label_poission: tk.Label, label_rtt: tk.Label):
    global pOISSON, rTT, tcp_simulation
    try:
        pOISSON = float(poission)
    except:
        print("Invalid Poission parameter")
    try:
        rTT = float(rtt)
    except:
        print("Invalid RTT parameter")
    tcp_simulation.update_parameters(pOISSON, rTT)
    print("Parameters updated: Poission =", pOISSON, "RTT =", rTT)
    label_poission.config(text="Poisson parameter: " + str(pOISSON) + "\n")
    label_rtt.config(text="RTT: " + str(rTT) + "\n")


# Function that is called when the main window is closed to quit the main loop
def on_closing(root: tk.Tk):
    root.quit()
    root.destroy()


# Main function that creates the main window and runs the simulation
def main():
    # Create the main window
    root = tk.Tk()
    root.title("TCP Simulation")
    create_widgets(root)
    # Run the main loop
    root.protocol("WM_DELETE_WINDOW", lambda: on_closing(root))
    root.mainloop()
    # Print the simulation ended message when the main loop ends
    print("Simulation ended.")


# Run the main function
if __name__ == '__main__':
    main()
