# Fatih Baskın
# 150210710

import numpy as np
from matplotlib import pyplot as plt
import os


class Logger(object):
    def __new__(self):
        if not hasattr(self, 'instance'):
            self.instance = super(Logger, self).__new__(self)
            self.instance._init()
        return self.instance

    def _init(self):
        self.filename = "simulation.log"
        if os.path.exists(self.filename):
            os.remove(self.filename)
        self.file = None
        self._open()
        self._close()

    def log(self, message):
        self._open()
        self.file.write(message + '\n')
        self._close()

    def _open(self):
        self.file = open(self.filename, "a")

    def _close(self):
        self.file.close()


class Simulation(object):
    def __new__(self):
        if not hasattr(self, 'instance'):
            self.instance = super(Simulation, self).__new__(self)
        return self.instance

    @staticmethod
    def pure_aloha_simulation(num_devices: int, simulation_time: float, packet_time: float) -> tuple[list, list]:
        G = np.linspace(0, 1, 100)  # Load values
        S = []
        Logger().log("Pure ALOHA Simulation")
        for g in G:
            attempts = 0
            successful_transmissions = 0
            for t in np.arange(0, simulation_time, packet_time):
                # Generate number of packets for each device with average rate g
                packets = np.random.poisson(g, num_devices)
                # Count total number of packets
                attempts += sum(packets)
                if sum(packets) == 1:
                    successful_transmissions += 1
            S.append(g * successful_transmissions / attempts if attempts > 0 else 0)
        Logger().log("Pure ALOHA Simulation is done")
        Logger().log("--------------------")
        return G, S

    @staticmethod
    def slotted_aloha_simulation(num_devices: int, simulation_time: float, slot_time: float) -> tuple[list, list]:
        G = np.linspace(0, 1, 100)  # Load values
        S = []
        Logger().log("Slotted ALOHA Simulation")
        for g in G:
            attempts = 0
            successful_transmissions = 0
            for t in np.arange(0, simulation_time, slot_time):
                packets = np.random.poisson(g, num_devices)
                attempts += sum(packets)
                if sum(packets) == 1:
                    successful_transmissions += 1
            # Normalize throughput by dividing by the number of devices in the network and by the simulation time/slot time ratio
            # Simulation time/slot time ratio is the number of slots in the simulation time
            S.append((float(g * successful_transmissions) / (simulation_time / slot_time)))
        Logger().log("Slotted ALOHA Simulation is done")
        Logger().log("--------------------")
        return G, S

    @staticmethod
    def persistent_csma_simulation(num_devices: int, simulation_time: float, packet_time: float, persistence: float) -> tuple[list, list]:
        G = np.linspace(0, 1, 100)  # Load values
        S = []
        Logger().log(f"Persistent CSMA Simulation with persistence {persistence}")
        for g in G:
            attempts = 0
            successful_transmissions = 0
            medium_free = True
            backoff_time = 0
            for t in np.arange(0, simulation_time, packet_time):
                if backoff_time > 0:
                    backoff_time -= 1
                    continue
                packets = np.random.poisson(g, num_devices)
                attempts += sum(packets)
                if medium_free:
                    # If there is only one packet, it is successful
                    if sum(packets) > 0:
                        # If there is more than one packet, check if the medium is free with probability persistence
                        if np.random.rand() < persistence:
                            if sum(packets) == 1:
                                successful_transmissions += 1
                            medium_free = False
                        else:
                            medium_free = True
                else:
                    # Random backoff time between 1 and 10
                    backoff_time = np.random.randint(1, 10)
                    medium_free = True
            S.append((float(successful_transmissions) / (simulation_time / packet_time)))
        Logger().log(f"Persistent CSMA Simulation with persistence {persistence} is done")
        Logger().log("--------------------")
        return G, S

    @staticmethod
    def csma_cd_simulation(num_devices: int, simulation_time, packet_time) -> tuple[list, list]:
        G = np.linspace(0, 1, 100)  # Load values
        S = []
        Logger().log("CSMA/CD Simulation")
        for g in G:
            attempts = 0
            successful_transmissions = 0
            medium_free = True
            backoff_time = 0
            for t in np.arange(0, simulation_time, packet_time):
                if backoff_time > 0:
                    backoff_time -= 1
                    continue
                packets = np.random.poisson(g, num_devices)
                attempts += sum(packets)
                # If the medium is free, check if there is only one packet
                if medium_free:
                    if sum(packets) == 1:
                        # If there is only one packet, it is successful
                        successful_transmissions += 1
                        medium_free = False
                    elif sum(packets) > 1:
                        # If there is more than one packet apply random backoff time
                        backoff_time = np.random.randint(1, 10)
                        medium_free = True
                else:
                    medium_free = True  # Medium becomes free in the next time slot
            S.append((float(successful_transmissions) / (simulation_time / packet_time)))
        Logger().log("CSMA/CD Simulation is done")
        Logger().log("--------------------")
        return G, S

    def simulate_once(self, num_devices: int) -> None:
        SIM_TIME = 1000.0
        PERSISTENCE1 = 1.0
        PERSISTENCE2 = 0.5
        PACKET_TIME = 1.0
        SLOT_TIME = 1.0

        print(f"Simulation started for device count {num_devices}")
        Logger().log("####################")
        Logger().log(f"Simulation started for device count {num_devices}")

        g_pure_aloha, s_pure_aloha = Simulation.pure_aloha_simulation(num_devices, SIM_TIME, PACKET_TIME)
        g_slotted_aloha, s_slotted_aloha = Simulation.slotted_aloha_simulation(num_devices, SIM_TIME, SLOT_TIME)
        g_persistent_csma1, s_persistent_csma1 = Simulation.persistent_csma_simulation(num_devices, SIM_TIME, PACKET_TIME, PERSISTENCE2)
        g_persistent_csma2, s_persistent_csma2 = Simulation.persistent_csma_simulation(num_devices, SIM_TIME, PACKET_TIME, PERSISTENCE1)
        g_csma_cd, s_csma_cd = Simulation.csma_cd_simulation(num_devices, SIM_TIME, PACKET_TIME)

        Logger().log("Simulation is done")
        Logger().log("Saving the results to a file")

        plt.plot(g_pure_aloha, s_pure_aloha, label="Pure ALOHA")
        plt.plot(g_slotted_aloha, s_slotted_aloha, label="Slotted ALOHA")
        plt.plot(g_persistent_csma1, s_persistent_csma1, label="Persistent CSMA (p=1)")
        plt.plot(g_persistent_csma2, s_persistent_csma2, label="Persistent CSMA (p=0.5)")
        plt.plot(g_csma_cd, s_csma_cd, label="CSMA/CD")
        plt.xlabel("G")
        plt.ylabel("S")
        plt.title(f"Throughput vs Load for {num_devices} devices")
        plt.legend()
        fig_name = f"simulation_{num_devices}.png"
        plt.savefig(fig_name)
        print(f"Simulation results are saved to {fig_name}")
        # plt.show()
        plt.close()

        Logger().log("####################")
        return


def main():
    devices = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]

    for device in devices:
        Simulation().simulate_once(device)


if __name__ == '__main__':
    main()
