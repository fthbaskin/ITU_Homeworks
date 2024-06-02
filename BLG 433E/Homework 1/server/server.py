# Fatih Baskın
# 150210710

from socket import *
from select import *
import dotenv
import os
import json
from enum import Enum
import time
import datetime
import threading


# Enum to represent the response types to the client
class ResponseType(Enum):
    SUCCESS = 1
    ERROR = 2
    INFO = 3


# This class is used to represent a response from the server to a client
# The response is in JSON format, and the class is used to create the JSON
class ServerResponse:
    def __init__(self, client_id: str, response_type: int, response_data: str):
        self.client_id = client_id
        self.response_type = response_type
        self.response_data = response_data

    def __str__(self) -> str:
        return f'Client {self.client_id} response: {self.response}'

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
    def __init__(self, request_json):
        request_dict = json.loads(request_json)
        self.client_id = str(request_dict['client_id'])
        self.request_type = int(request_dict['type'])
        self.request_data = str(request_dict['data'])

    def __str__(self) -> str:
        return f"ClientRequest(type={self.request_type}, client_id={self.client_id}, data={self.request_data})"

    def to_json(self) -> str:
        return json.dumps({
            'client_id': self.client_id,
            'type': self.request_type,
            'data': self.request_data
        })


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


# For file handling
class FileHandler:
    def __init__(self, file_path, record_file_path, record_file_name):
        self.file_path = file_path
        self.record_file_path = record_file_path
        self.record_file_name = record_file_name

    def get_absolute_path_client(self, client_id: str) -> str:
        return os.path.join(self.file_path, client_id + ".txt")

    def get_absolute_path_record(self) -> str:
        return os.path.join(self.record_file_path, self.record_file_name)

    def read_file(self, client_id: str) -> str:
        file_absolute_path = self.get_absolute_path_client(client_id)
        try:
            with open(file_absolute_path, 'r') as file:
                return file.read()
        except Exception as e:
            print(f"Error reading file: {e}")
            return None

    def write_file(self, client_id: str, data: str) -> bool:
        file_absolute_path = self.get_absolute_path_client(client_id)
        try:
            with open(file_absolute_path, 'w') as file:
                # Write the data
                file.write(data)
                return True
        except Exception as e:
            print(f"Error writing file: {e}")
            return False

    def delete_file(self, client_id: str) -> bool:
        file_absolute_path = self.get_absolute_path_client(client_id)
        try:
            os.remove(file_absolute_path)
            return True
        except Exception as e:
            print(f"Error removing file: {e}")
            return False

    def create_record_file(self) -> bool:
        try:
            with open(self.get_absolute_path_record(), 'w') as file:
                json.dump({}, file)
                return True
        except Exception as e:
            print(f"Error creating record file: {e}")
            return False

    def read_record_file(self) -> dict:
        try:
            with open(self.get_absolute_path_record(), 'r') as file:
                return json.load(file)
        except Exception as e:
            print(f"Error reading record file: {e}")
            return None

    def write_record_file(self, data: dict) -> bool:
        if not data:
            return False

        try:
            with open(self.get_absolute_path_record(), 'w') as file:
                json.dump(data, file)
                return True
        except Exception as e:
            print(f"Error writing record file: {e}")
            return False

    def update_record_file(self, client_id: str) -> bool:
        client_record = self.read_record_file()

        if not client_record:
            if not self.create_record_file():
                return False
            client_record = {}

        client_record[client_id] = TimeConverter.get_time()
        return self.write_record_file(client_record)

    def update_files(self, treshold: int = 900) -> bool:
        to_be_updated = {}

        record_file = self.read_record_file()

        if record_file is None:
            return False

        current_time = TimeConverter.get_epoch()

        # Find the files to be updated
        for client_id, last_edit_time in record_file.items():
            last_edit_epoch = TimeConverter.convert_time_to_epoch(last_edit_time)
            if current_time - last_edit_epoch > treshold:
                to_be_updated[client_id] = last_edit_time

        for client_id, last_edit_time in to_be_updated.items():
            # Read the files
            file_content = self.read_file(client_id)
            if file_content is None:
                print(f"Error reading file of client {client_id}")
                continue
            file_content_lines = file_content.split("\n")
            # Update the time stamp
            file_content_lines[0] = 'Last updated: ' + TimeConverter.get_time()
            new_file_content = "\n".join(file_content_lines)

            # Write the files
            if not self.write_file(client_id, new_file_content):
                print(f"Error writing file of client {client_id}")
                continue

            # No need to roll back, if there was an error while updating the record file
            # in the next step, the file will be updated again
            if self.update_record_file(client_id):
                print(f"File of client {client_id} updated.")


class RequestHandler:
    def __init__(self, file_path, record_file_path, record_file_name):
        self.fileHandler = FileHandler(file_path, record_file_path, record_file_name)

    def handle_request(self, client_request: str) -> ServerResponse:
        # Client request comes as a string, so we need to parse it to a ClientRequest object
        try:
            request = ClientRequest(client_request)
        except Exception as e:
            print(f"Error parsing client request: {e}")
            return ServerResponse(None, ResponseType.ERROR.value, "Invalid request format, please send a valid JSON request.")

        # Check the request type
        if request.request_type == RequestType.READ.value:
            return self.handle_read(request)
        elif request.request_type == RequestType.WRITE.value:
            return self.handle_write(request)
        else:
            return ServerResponse(request.client_id, ResponseType.ERROR.value, "Invalid request type, please send a valid request type.")

    def handle_read(self, request: ClientRequest) -> ServerResponse:
        print("Handling read request of client: ", request.client_id)
        read_file = self.fileHandler.read_file(request.client_id)
        if read_file:
            return ServerResponse(request.client_id, ResponseType.SUCCESS.value, read_file)
        else:
            return ServerResponse(request.client_id, ResponseType.ERROR.value, "Error reading file.")

    def handle_write(self, request: ClientRequest) -> ServerResponse:
        print("Handling write request of client: ", request.client_id)
        # Try to write the file
        if self.fileHandler.write_file(request.client_id, request.request_data):
            # Try to update the record file
            if self.fileHandler.update_record_file(request.client_id):
                return ServerResponse(request.client_id, ResponseType.SUCCESS.value, "File updated successfully.")
            else:
                # Rollback the file write
                self.fileHandler.delete_file(request.client_id)
                return ServerResponse(request.client_id, ResponseType.ERROR.value, "Error writing file.")
        else:
            return ServerResponse(request.client_id, ResponseType.ERROR.value, "Error writing file.")


# This class is the Server class, which is used to create a server, and handle requests from clients
# It takes several parameters, such as the server port, server host, maximum connections, file path, record file path, and record file name
class Server:
    @property
    def SERVER_OPENING_MESSAGE(self):
        return f'''The server is ready to receive on port {self.server_port}.
Server host: {self.server_host}
Server max connections: {self.max_connections}
Press Ctrl+C to quit.'''

    def __init__(self, server_port: int, server_host: str, max_connections: int, update_timer:int, update_treshold: int, request_handler: RequestHandler):
        # Server properties
        self.server_port = server_port
        self.server_host = server_host
        self.max_connections = max_connections
        self.update_timer = update_timer
        self.update_treshold = update_treshold
        self.timer = threading.Timer(self.update_timer, self.update_handler)

        # Request handler
        self.request_handler = request_handler

        # Sockets and clients
        self.server_socket = None
        self.input_sockets = []
        self.output_sockets = []
        self.clients = {}
        self.setup()

    def setup(self):
        self.server_socket = socket(AF_INET, SOCK_STREAM)
        self.server_socket.bind((self.server_host, self.server_port))
        self.server_socket.listen(self.max_connections)
        self.server_socket.setblocking(False)  # Set non-blocking mode
        self.input_sockets.append(self.server_socket)

        print(self.SERVER_OPENING_MESSAGE)

    def update_handler(self):
        print("Updating files...")
        self.request_handler.fileHandler.update_files(server_update_treshold)
        print("Files updated.")
        # Start the timer again
        self.timer = threading.Timer(self.update_timer, self.update_handler)
        self.timer.start()

    def run(self):
        # Start the timer
        self.timer.start()

        # Event loop
        while self.input_sockets:
            readable, writable, exceptional = select(self.input_sockets, self.output_sockets, self.input_sockets)

            for incoming_socket in readable:
                self.handle_read(incoming_socket)

            for outgoing_socket in writable:
                # No need to handle write
                pass

            for exceptional_socket in exceptional:
                # Handle exceptional condition
                self.remove_socket(exceptional_socket)

    def accept_connection(self, server_socket: socket):
        client_socket, client_address = server_socket.accept()
        client_socket.setblocking(False)
        self.input_sockets.append(client_socket)
        self.clients[client_socket] = client_address
        print(f"Connection established with {str(client_address)}")
        return

    def remove_socket(self, incoming_socket: socket):
        if incoming_socket in self.output_sockets:
            self.output_sockets.remove(incoming_socket)

        if incoming_socket in self.input_sockets:
            self.input_sockets.remove(incoming_socket)

        if incoming_socket in self.clients:
            print("Connection lost with client: " + str(self.clients[incoming_socket]))
            del self.clients[incoming_socket]
        else:
            print("Connection lost with unknown client.")
        try:
            incoming_socket.close()
        except:
            pass

        return

    def handle_read(self, incoming_socket: socket):
        # Check if the incoming socket is None, and remove it
        if incoming_socket is None:
            self.remove_socket(incoming_socket)
            return

        # Check if the incoming socket is the server socket, and accept the connection
        if incoming_socket is self.server_socket:
            self.accept_connection(incoming_socket)
            return
        # Otherwise, handle the request
        else:
            self.handle_client_request(incoming_socket)
            return

    def handle_client_request(self, incoming_socket: socket):
        request = self.read_socket(incoming_socket)
        # Check if the request is not None
        if request:
            # Note: The request handler is not implemented yet
            # The request handler should be implemented to handle the request
            response = self.request_handler.handle_request(request)
            self.write_socket(incoming_socket, response.to_json())
        else:
            self.remove_socket(incoming_socket)

        return

    def read_socket(self, incoming_socket: socket) -> str:
        long_data = ''
        BUFFER_SIZE = 1024

        while (True):
            try:
                read_data = incoming_socket.recv(BUFFER_SIZE).decode('utf-8')
                long_data += read_data
                if len(read_data) < BUFFER_SIZE:
                    break
            except Exception as e:
                return None
            
        if not long_data:
            return None

        return long_data

        

    def write_socket(self, incoming_socket: socket, data: str):
        try:
            incoming_socket.send(data.encode('utf-8'))
        except:
            self.remove_socket(incoming_socket)
        return

    def close(self):
        # Cancel the timer
        self.timer.cancel()

        self.remove_socket(self.server_socket)
        for client_socket in self.input_sockets:
            self.remove_socket(client_socket)
        for client_socket in self.output_sockets:
            self.remove_socket(client_socket)
        return


# Main executable
if __name__ == '__main__':

    # Change environment to the current directory
    current_directory = os.path.dirname(os.path.abspath(__file__))
    os.chdir(current_directory)

    # Load environment variables, requres a .env file in the current directory
    env_path = os.path.join(current_directory, '.env')
    dotenv.load_dotenv(env_path)

    server_port = int(os.getenv('SERVER_PORT'))  # Server port
    server_host = os.getenv('SERVER_HOST')  # Server host
    server_max_connections = int(os.getenv('MAX_CONNECTION'))  # Maximum connections
    server_update_timer = int(os.getenv('UPDATE_TIMER'))  # Update timer for the record file (in seconds)
    server_update_treshold = int(os.getenv('UPDATE_TRESH'))  # Update treshold for the record file (in seconds)

    # Absolute path to the record file directory
    file_path = os.getenv('FILE_PATH')
    record_file_path = os.getenv('RECORD_PATH')
    record_file_name = os.getenv('RECORD_FILE')  # Record file name

    # Create a new server
    server = Server(server_port, server_host, server_max_connections, server_update_timer, server_update_treshold, RequestHandler(file_path, record_file_path, record_file_name))
    
    # Run the server
    try:
        server.run()
    except KeyboardInterrupt:
        print("Server stopped with user keyboard interrupt.")
    except Exception as e:
        print("Server stopped due to an error.")
        print(e)
    finally:
        print("Shutting down server...")
        server.close()
        print("Server shut down.")
