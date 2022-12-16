import os
from typing import Union
from functools import cmp_to_key
from copy import deepcopy

os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open("input.txt", "r") as f:
    lines = [line.strip() for line in f.readlines()]


def compare(pair1: list[Union[int, list]], pair2: list[Union[int, list]]) -> bool:
    """
    Compares 2 packets, returns True if left is smaller than right

    Modified from puzzle 1 as I was changing the original packets list unexpectedly
    """
    while True:
        # check if one of the lists is empty
        if len(pair1) == 0 and len(pair2) != 0:
            return True
        elif len(pair1) != 0 and len(pair2) == 0:
            return False

        # now apply other rules
        if type(pair1[0]) == int and type(pair2[0]) == int:
            # both ints
            # if they are equal, continue, otherwise return True if left is smaller than right
            if pair1[0] != pair2[0]:
                return pair1[0] < pair2[0]
            else:
                return compare(deepcopy(pair1)[1:], deepcopy(pair2)[1:])
        elif type(pair1[0]) == list and type(pair2[0]) == list:
            # both lists

            # first, check if lists are empty
            if len(pair1[0]) == 0 and len(pair2[0]) == 0:
                return compare(deepcopy(pair1)[1:], deepcopy(pair2)[1:])
            elif len(pair1[0]) == 0 and len(pair2[0]) != 0:
                return True
            elif len(pair1[0]) != 0 and len(pair2[0]) == 0:
                return False
            else:
                # compare first elements of both lists
                try:
                    return compare(deepcopy(pair1)[0], deepcopy(pair2)[0])
                except IndexError:
                    # lists were exhasted, compare next elements
                    return compare(deepcopy(pair1)[1:], deepcopy(pair2)[1:])
        elif type(pair1[0]) == int and type(pair2[0]) == list:
            # first is int, second is list
            pair1[0] = [pair1[0]]
            return compare(deepcopy(pair1), deepcopy(pair2))
        elif type(pair1[0]) == list and type(pair2[0]) == int:
            # first is list, second is int
            pair2[0] = [pair2[0]]
            return compare(deepcopy(pair1), deepcopy(pair2))


# get all the packets in list format
packets = []
for i in range(int((len(lines) + 1) / 3)):
    packets.extend([eval(lines[3 * i]), eval(lines[3 * i + 1])])

# add divider packets
packets.append([[2]])
packets.append([[6]])


packets = sorted(packets, key=cmp_to_key(lambda a, b: -1 if compare(a, b) else 1))

# find location of divider packets
loc1 = packets.index([[2]]) + 1
loc2 = packets.index([[6]]) + 1

print(loc1 * loc2)
