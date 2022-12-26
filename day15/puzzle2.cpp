// a much more efficient algorithm that actually works for the main dataset
// we only check along the line of interest
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <set>
#include <algorithm>

using namespace std;
using CMPLX = complex<long>;

struct interval
{
    long start;
    long end;
};

long distance(CMPLX pos1, CMPLX pos2)
{
    return abs(pos1.real() - pos2.real()) + abs(pos1.imag() - pos2.imag());
}

void bubble_sort(vector<interval> &arr)
{
    bool sorted{false};

    while (!sorted)
    {
        sorted = true;
        for (int i{0}; i < arr.size() - 1; ++i)
        {
            if (arr[i].start > arr[i + 1].start)
            {
                sorted = false;
                iter_swap(arr.begin() + i, arr.begin() + i + 1);
            }
        }
    }
}


long beacon_loc(vector<CMPLX> sensors, vector<CMPLX> beacons, long line, long max_search)
{
    // finds possible beacon location on a given line
    // returns x position if found, returns -1 otherwise
    
    // holds all intervals where there is no beacon
    vector<interval> no_beacons{};

    // find points on line that contain a beacon or a sensor
    set<long> danger_points {};

    for (auto beacon: beacons)
    {
        if (beacon.imag() == line)
        {
            danger_points.insert(beacon.real());
        }
    }
    for (auto sensor: sensors)
    {
        if (sensor.imag() == line)
        {
            danger_points.insert(sensor.real());
        }
    }

    for (int i{0}; i < sensors.size(); ++i)
    {
        CMPLX sensor{sensors[i]};
        CMPLX beacon{beacons[i]};

        // calculate bounds to check
        long dist{distance(sensor, beacon)};

        if (dist>abs(sensor.imag()-line))
        {
            // x location - (distance-y difference between sensor and check line)
            long dx{abs((dist - abs(sensor.imag() - line)))};

            interval nb{sensor.real() - dx, sensor.real() + dx};
            no_beacons.push_back(nb);
        }
    }

    // go through no_beacons and add points that we know are a source or a beacon
    // since these cannot contain the unknown beacon

    // now go through unions and remove points that we know have beacons in them

    for (auto beacon : danger_points)
    {
        interval bc {beacon, beacon};
        no_beacons.push_back(bc);
    }

    // we now sort our array of intervals in ascengind order by their start locations
    bubble_sort(no_beacons);

    // we now go through this array and find the union
    vector<interval> unions{no_beacons[0]};

    for (size_t i{1}; i < no_beacons.size(); ++i)
    {
        auto current{no_beacons[i]};

        if (unions.back().end < current.start)
        {
            // final interval in unions finishes before start of current
            unions.push_back(current);
        }
        else if (unions.back().end == current.start)
        {
            // final interval in unions finishes at start of current
            unions.back().end = current.end;
        }
        if (current.end > unions.back().end)
        {
            // current interval ends after end of final interval
            unions.back().end = current.end;
        }
    }

    // see if there are any possible beacon locations.
    // process:
    // check all the intervals.
    // if an iunterval ends only one before the next one starts, or its end is beyond the search area,
    // then there is not a beacon position.

    // otherwise, there is. return the tuning frequency
    for(size_t i{0}; i<unions.size()-1; ++i)
    {
        if ((!(unions[i].end + 1 == unions[i+1].start)) && (!(unions[i].end>max_search)))
        {
            return unions[i].end+1;
        }
    }
    return -1l;

}

int main()
{
    fstream Input("input.txt");
    string line{};
    const long search_size {4000000};
    //const long search_size {20};



    // store positions as complex numbers x+iy
    vector<CMPLX> sensors{};
    vector<CMPLX> beacons{};

    int start, end{0};

    while (getline(Input, line))
    {
        CMPLX sensor(
            stol(line.substr(line.find_first_of('=') + 1, line.find_first_of(',') - line.find_first_of('='))),
            stol(line.substr(line.find_first_of(',') + 4, line.find_first_of(',') - line.find_first_of(':') + 3)));
        // we will use the hacky magic number 33 to distinguish between the sensor and beacon,
        // as this works for example and real inputs. Other nearby numbers also work

        CMPLX beacon(
            stol(line.substr(line.find_first_of('=', 33) + 1, line.find_first_of(',', 33) - line.find_first_of('=', 33))),
            stol(line.substr(line.find_first_of(',', 33) + 4)));

        sensors.push_back(sensor);
        beacons.push_back(beacon);

    }

    unsigned long long xpos {0}; // turns out answer is of order 10^13
    for (size_t i{}; i<search_size; ++i)
    {
        xpos = beacon_loc(sensors, beacons, i, search_size);
        if (xpos != -1)
        {
            std::cout << xpos * 4000000ull + i;
        }
        
    }
}