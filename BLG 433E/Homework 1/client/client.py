from socket import *
import os
import json
from enum import Enum
import datetime
import time


# Static utility class to convert time to epoch and vice versa
class TimeConverter:
    @staticmethod
    def convert_time_to_epoch(time: str) -> int:
        datetime_object = datetime.datetime.strptime(time, "%Y-%m-%d %H:%M:%S")
        epoch_time = datetime_object.timestamp()
        return int(epoch_time)

    @staticmethod
    def convert_epoch_to_time(epoch: int) -> str:
        human_readable_time = datetime.datetime.fromtimestamp(epoch)
        formatted_time = human_readable_time.strftime("%Y-%m-%d %H:%M:%S")
        return formatted_time

    @staticmethod
    def get_epoch() -> int:
        return int(time.time())

    @staticmethod
    def get_time() -> str:
        return TimeConverter.convert_epoch_to_time(TimeConverter.get_epoch())


# Client-server communication is handled here
class Client:
    def __init__(self):
        self.serverName = None
        self.serverPort = None
        self.clientSocket = socket(AF_INET, SOCK_STREAM)

    def set_server(self, server_name: str, server_port: int) -> bool:
        # try to connect
        try:
            self.clientSocket.connect((server_name, server_port))
        except Exception as e:
            print(f"There was an error while connecting to {server_name}:{server_port} address: {e}")
            return False

        # If connected, set the server name and port
        self.serverName = server_name
        self.serverPort = server_port
        print(f"Connected to {server_name}:{server_port} address.")
        return True

    def close(self):
        try:
            self.clientSocket.close()
            print("Connection closed successfully.")
        except Exception as e:
            print(f"There was an error while closing the connection: {e}")

    def send(self, message: str) -> str:
        try:
            self.clientSocket.send(message.encode())
            return self.receive()
        except Exception as e:
            print(f"There was an error while sending the message: {e}")
            return None

    def receive(self) -> str:
        host_response = ''
        BUFFER_SIZE = 1024

        while True:
            try:
                response = self.clientSocket.recv(BUFFER_SIZE)
                host_response += response.decode('utf-8')            

                if len(response) < BUFFER_SIZE:
                    break
            except Exception as e:
                print(f"There was an error while receiving the message: {e}")
                return None

        # If no response, lost connection, return None
        if not host_response:
            return None

        return host_response


# Enum to represent the response types to the client
class ResponseType(Enum):
    SUCCESS = 1
    ERROR = 2
    INFO = 3


# This class is used to represent a response from the server to a client
# The response is in JSON format, and the class is used to create the JSON
class ServerResponse:
    def __init__(self, response_json: str):
        response_dict = json.loads(response_json)
        self.client_id = response_dict['client_id']
        self.response_type = response_dict['type']
        self.response_data = response_dict['data']

    def to_json(self) -> str:
        return json.dumps({
            'client_id': str(self.client_id),
            'type': int(self.response_type),
            'data': str(self.response_data)
        })


# Enum to represent the request types from the client
class RequestType(Enum):
    WRITE = 1
    READ = 2


# This class is used to represent a request from a client to the server
# The request is in JSON format, and the class is used to parse the JSON
class ClientRequest:
    def __init__(self, client_id: str, request_type: int, request_data: str):
        self.client_id = client_id
        self.request_type = request_type
        self.request_data = request_data

    def to_json(self) -> str:
        return json.dumps({
            'client_id': self.client_id,
            'type': self.request_type,
            'data': self.request_data
        })


# This class is used to create client requests
class RequestFactory:
    @staticmethod
    def create_write_request() -> ClientRequest:
        client_id = input("Enter your student ID: ")
        user_id = 'Student ID: ' + client_id

        user_name = input("Enter your name: ")
        user_name = 'Name: ' + user_name

        user_dob = input("Enter your date of birth: ")
        user_dob = 'Date of Birth: ' + user_dob

        user_city = input("Enter your city: ")
        user_city = 'City: ' + user_city

        user_data = input("Enter your reason to chose this class: ")
        user_data = 'Reason: ' + user_data

        timestamp = 'Last updated: ' + TimeConverter.get_time()

        big_data = '\n'.join([timestamp, user_id, user_name, user_dob, user_city, user_data])

        return ClientRequest(client_id, RequestType.WRITE.value, big_data)

    @staticmethod
    def create_read_request() -> ClientRequest:
        client_id = input("Enter your student ID: ")
        return ClientRequest(client_id, RequestType.READ.value, '')


# User command line interface (CLI) is handled here
class CLIrequest:
    def __init__(self):
        self.client = Client()
        self.ask_server_info()

    def ask_server_info(self):
        server_name = input("Enter the server address: ")
        server_port = int(input("Enter the server port: "))
        while not self.client.set_server(server_name, server_port):
            print("Invalid server address. Please try again.")
            server_name = input("Enter the server name: ")
            server_port = int(input("Enter the server port: "))
        print("Server address set successfully.")

    def run(self):
        while True:
            print("1. Write to the server")
            print("2. Read from the server")
            print("3. Exit")
            choice = int(input("Enter your choice: "))

            if choice == 1:
                self.write_path()

            elif choice == 2:
                self.read_path()

            elif choice == 3:
                self.client.close()
                print("Goodbye!")
                break
            else:
                print("Invalid choice. Please try again.")

    def write_path(self):
        try:
            request = RequestFactory.create_write_request()
            response = self.client.send(request.to_json())

            if response is not None:
                server_response = ServerResponse(response)
                print(f"Server response: {server_response.response_data}")
            else:
                print("No response from the server.")

        except Exception as e:
            print(f"An error occurred: {e}")

    def read_path(self):
        try:
            request = RequestFactory.create_read_request()
            response = self.client.send(request.to_json())

            if response is not None:
                server_response = ServerResponse(response)
                if server_response.response_type == ResponseType.SUCCESS.value:
                    with open(f"{server_response.client_id}.txt", "w") as file:
                        file.write(server_response.response_data)
                    write_location = os.path.join(os.getcwd(), server_response.client_id + ".txt")
                    print(f"Written requested file to {write_location} successfully.")
                else:
                    print(f"Did not receive data, server respponse: {server_response.response_data}")
            else:
                print("No response from the server.")

        except Exception as e:
            print(f"An error occurred: {e}")


if __name__ == '__main__':
    # Change environment to the current directory
    current_directory = os.path.dirname(os.path.abspath(__file__))
    os.chdir(current_directory)

    # Create a CLI request object and run it
    cli = CLIrequest()
    try:
        cli.run()
    except KeyboardInterrupt:
        print("Closing application with keyboard interrupt!")
        cli.client.close()
        print("Goodbye!")
    except Exception as e:
        print(f"An error occurred: {e}")
        cli.client.close()
        print("Goodbye!")
        