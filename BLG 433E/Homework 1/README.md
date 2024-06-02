# BLG 433E Computer Communications Project Assignment 1

In this assignment, we were asked to implement a server and a client program using web sockets.

## IMPORTANT! Read before running:

This code must be run with these python packages:
```
python-dotenv
```

You can automatically install these packages by running:
```
pip install -r requirements.txt
```

In the server folder, there should be a ``.env`` file, accompanying ``server.py`` for configuration for the server host system. ``.env`` file contains these fields:
```
SERVER_HOST = 'server address'
SERVER_PORT = port
MAX_CONNECTION = number of maximum connections
UPDATE_TIMER = periodic update checker timespan (seconds)
UPDATE_TRESH = file timestamp update treshold (seconds)
FILE_PATH = 'absolute path to file folder'
RECORD_FILE = 'record file name . extension'
RECORD_PATH = 'absolute path to folder containing record file'
```

The environment variables in quotes are strings and variables without quotes are integers.
