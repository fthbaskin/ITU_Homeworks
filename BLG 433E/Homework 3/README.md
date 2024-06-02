# BLG 433E Homework 3

Fatih Baskın <br>
150210710

## Setup

To run the simulation, first, you need to generate a Python virtual environment. You can create one using `python -m venv .venv` and activate it. Then you should install the needed packages using `pip install -r requirements.txt`. After this is done, you can run `simulation.py` inside the Python virtual environment

## Simulation Inputs

When the simulation program is run, it asks several inputs from the console. Those are:

- Burst rate of a router port
- Queue size of a router port
- Number of ports (queues)
- Bit rate of the service
- Datagram generator type (service type)
    - CBR, VBR, ABR
- Router scheduling strategy
    - FIFO, RR, WFQ

## Simulation Outputs

- Datagrams log
- Average queue times per port
- Average response times per port
- Average waiting times per port
- General picture of waiting times, response times, queue times
- Troughput per port
- Overall troughput
