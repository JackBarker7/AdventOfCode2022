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

int main()
{
    fstream Input("input.txt");
    string line{};
    const long to_check{2000000}; // line to check for no beacon locations
    // const long to_check {10};

    // store positions as complex numbers x+iy
    vector<CMPLX> sensors{};
    vector<CMPLX> beacons{};

    // holds all intervals where there is no beacon
    vector<interval> no_beacons{};

    // holds locations of all beacons and sensors with y=to_check
    set<long> danger_points{};

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
        if (beacon.imag() == to_check)
        {
            danger_points.insert(beacon.real());
        }
        if (sensor.imag() == to_check)
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

        if (dist>abs(sensor.imag()-to_check))
        {
            // x location - (distance-y difference between sensor and check line)
            long dx{abs((dist - abs(sensor.imag() - to_check)))};

            interval nb{sensor.real() - dx, sensor.real() + dx};
            no_beacons.push_back(nb);
        }
        
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

    // now go through unions and remove points that we know have beacons in them
    for (size_t i{}; i < unions.size(); ++i)
    {
        for (auto beacon : danger_points)
        {
            if (unions[i].start < beacon && unions[i].end > beacon)
            {
                interval new_int{beacon + 1, unions[i].end};
                unions.push_back(new_int);
                unions[i].end = beacon - 1;
            }
        }
    }

    // go through unions and sum up their sizes
    long sum{0};
    for (auto u : unions)
    {
        sum += 1 + u.end - u.start;
    }

    std::cout << sum;
}