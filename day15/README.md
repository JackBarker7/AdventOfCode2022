# Day 15 Answer

Quick explanation of how my solution works

# Part 1

* For a given sensor-beacon combo, calcilate the distance between the sensor and the beacon

* Using this, for a given line, we can calculate an interval in space within which another beacon cannot be found

    * This is much more efficient then iterating over the whole line

* Then, find the overlaps of all these intervals. This list indicates the places where a beacon cannot be found

# Part 2

* We repeat the same process, but this time we do it over all lines in the search space

* For each line, if there is a point which is not covered by any of the intervals, we can place a beacon there. This is the answer

