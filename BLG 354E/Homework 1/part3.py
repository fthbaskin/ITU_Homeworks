# Fatih Baskın
# 150210710

import numpy as np
import soundcard as sc
import pyautogui as pg
from time import sleep

# Grid of the map, 0 is free space, 1 is obstacle
grid = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
]

# Constants, start and end points
WIN_POINT = (3, 9)
START_POINT = (5, 2)

# Enums, directions
UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3
NOWHERE = -1

# Enums, key presses
UP_KEY = 'w'
RIGHT_KEY = 'd'
DOWN_KEY = 's'
LEFT_KEY = 'a'

# Times for distance calculation
# Note: times are in seconds, and are approximate (room for error)
TIME_FULL = 1.8
TIME_TRY = 0.62
TIME_SYNC = 0.15
TIME_WAIT = 0.3
TIME_START = 5


# Coordinate calculation
def up_coord(coord):
    return (coord[0] - 1, coord[1])


def right_coord(coord):
    return (coord[0], coord[1] + 1)


def down_coord(coord):
    return (coord[0] + 1, coord[1])


def left_coord(coord):
    return (coord[0], coord[1] - 1)


# Enums, sound detection
SOUND_DANGER = 1
SOUND_SAFE = 0

SAMPLE_RATE = 148000
NUM_SAMPLES = 1000000

STD_TRESH = 0.7


# Sound detection
def detect_sound():
    microphones = sc.all_microphones(include_loopback=True)
    mic = microphones[1]  # Bluetooth headstet loopback
    with mic.recorder(samplerate=SAMPLE_RATE) as mic:
        data = mic.record(numframes=NUM_SAMPLES)

    # reduce the data to one channel
    data = data[:, 0]

    # Take the STD
    data_std = np.std(data)

    # STD of square wave is higher than triangle wave
    if data_std > STD_TRESH:
        return SOUND_DANGER

    return SOUND_SAFE


# key press
def key_press(key, duration):
    pg.keyDown(key)
    sleep(duration)
    pg.keyUp(key)


# evaluate coordinatesd
def evaluate_coord(coord):
    if coord[0] < 0 or coord[0] > 6 or coord[1] < 0 or coord[1] > 10:
        return False
    return grid[coord[0]][coord[1]] == 0


# mark obstacle
def mark_obstacle(coord):
    grid[coord[0]][coord[1]] = 1


# try and move
def try_move(move_dir, back_dir, move_coord, curr_coord):
    # check if the move is valid
    if not evaluate_coord(move_coord):
        return False

    # wait for a bit
    sleep(TIME_WAIT)

    # move to 1/3 of the way
    key_press(move_dir, TIME_TRY)
    verdict = detect_sound()

    if verdict == SOUND_SAFE:
        # If safe, move to the full way
        # mark current position as obstacle
        grid[curr_coord[0]][curr_coord[1]] = 1
        key_press(move_dir, TIME_FULL - TIME_TRY)
        return True
    else:
        # If danger, move back
        key_press(back_dir, TIME_TRY)
        # mark tried position as obstacle
        grid[move_coord[0]][move_coord[1]] = 1
        return False


# game loop
sleep(TIME_START)  # wait for the game to start
# move to start point
key_press(DOWN_KEY, TIME_SYNC)
# wait for a bit
sleep(TIME_WAIT)
# start moving
current_pos = START_POINT
while True:
    # check if we reached the end
    if current_pos == WIN_POINT:
        print("Reached the end")
        break

    # calculate coordinates
    up_coord_pos = up_coord(current_pos)
    down_coord_pos = down_coord(current_pos)
    right_coord_pos = right_coord(current_pos)
    left_coord_pos = left_coord(current_pos)

    # try up
    print("trying up")
    if try_move(UP_KEY, DOWN_KEY, up_coord_pos, current_pos):
        current_pos = up_coord_pos
        continue

    # try right
    print("trying right")
    if try_move(RIGHT_KEY, LEFT_KEY, right_coord_pos, current_pos):
        current_pos = right_coord_pos
        continue

    # try down
    print("trying down")
    if try_move(DOWN_KEY, UP_KEY, down_coord_pos, current_pos):
        current_pos = down_coord_pos
        continue

    # try left
    print("trying left")
    if try_move(LEFT_KEY, RIGHT_KEY, left_coord_pos, current_pos):
        current_pos = left_coord_pos
        continue
