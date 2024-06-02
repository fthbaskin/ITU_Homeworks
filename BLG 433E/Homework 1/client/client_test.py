from socket import *
import datetime
import time
import threading
from enum import Enum
import json
import os

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
    def create_write_request(client_id:str, static_data:str) -> ClientRequest:
        timestamp = 'Last updated: ' + TimeConverter.get_time()

        big_data = '\n'.join([timestamp, static_data])

        return ClientRequest(client_id, RequestType.WRITE.value, big_data)

    @staticmethod
    def create_read_request(client_id:str) -> ClientRequest:
        return ClientRequest(client_id, RequestType.READ.value, '')

def test_client(host:str, port:int, student_id:str, static_data:str):
    client = Client()
    client.set_server(host, port)

    request = RequestFactory.create_write_request(student_id, static_data)
    first_response = client.send(request.to_json())

    request = RequestFactory.create_read_request(student_id)
    second_response = client.send(request.to_json())

    client.close()

    with open(f'server_response_{student_id}.json', 'w') as file:
        file.write(first_response)

    with open(f'student_data_{student_id}.json', 'w') as file:
        file.write(second_response)


if __name__ == '__main__':
    os.chdir(os.path.dirname(__file__))

    with open('testing_data.json') as file:
        test_params = json.load(file)

    for test in test_params["test_data"]:
        threading.Timer(5, test_client, (test_params['server_host'], int(test_params['server_port']), test['client_id'], test['static_data'],)).start()