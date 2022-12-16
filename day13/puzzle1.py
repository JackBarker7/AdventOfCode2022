import os
from typing import Union
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open("input.txt", "r") as f:
    lines = [line.strip() for line in f.readlines()]



def compare(pair1:list[Union[int, list]], pair2:list[Union[int, list]]) -> bool:
    """
    Compares 2 packets, returns True if left is smaller than right
    """
    while True:
        # check if one of the lists is empty
        if len(pair1) == 0 and len(pair2) != 0:
            return True
        elif len(pair1) != 0 and len(pair2) == 0:
            return False

        # now apply other rules
        if (type(pair1[0])==int and type(pair2[0])==int):
            # both ints
            # if they are equal, continue, otherwise return True if left is smaller than right
            if (pair1[0]!=pair2[0]):
                return pair1[0]<pair2[0]
            else:
                return compare(pair1[1:], pair2[1:])
        elif (type(pair1[0])==list and type(pair2[0])==list):
            # both lists
            
            # first, check if lists are empty
            if (len(pair1[0])==0 and len(pair2[0])==0):
                return compare(pair1[1:], pair2[1:])
            elif (len(pair1[0])==0 and len(pair2[0])!=0):
                return True
            elif (len(pair1[0])!=0 and len(pair2[0])==0):
                return False
            else:
                # compare first elements of both lists
                try: 
                    return compare(pair1[0], pair2[0])
                except IndexError:
                    # lists were exhasted, compare next elements
                    return compare(pair1[1:], pair2[1:])
        elif (type(pair1[0])==int and type(pair2[0])==list):
            # first is int, second is list
            pair1[0] = [pair1[0]]
            return compare(pair1, pair2)
        elif (type(pair1[0])==list and type(pair2[0])==int):
            # first is list, second is int
            pair2[0] = [pair2[0]]
            return compare(pair1, pair2)


# get all the pairs in list format
pairs = []
for i in range(int((len(lines) + 1) / 3)):
    pairs.append([eval(lines[3 * i]), eval(lines[3 * i + 1])])

indices_sum = 0
for i, pair in enumerate(pairs):
    if compare(pair[0], pair[1]):
        indices_sum += i + 1

print(indices_sum)

