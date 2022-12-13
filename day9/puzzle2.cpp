#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <unordered_map>
#include <set>

using cmplx = std::complex<long>;

// convert directions to complex numbers
std::unordered_map<char, cmplx> dirs{
    {'R', cmplx(1L, 0L)},
    {'L', cmplx(-1L, 0L)},
    {'U', cmplx(0L, 1L)},
    {'D', cmplx(0L, -1L)}};

bool contains(std::vector<cmplx> vect, cmplx test)
{
    // checks if vect contains the number test
    for (auto i: vect)
    {
        if (i==test)
        {
            return true;
        }
    }
    return false;

}

int main()
{
    std::fstream Input("input.txt");
    std::string line{};

    const int num_knots {10};

    // position is represented as x+iy
    cmplx knots[num_knots] {cmplx(0,0)};



    // set of complex numbers to hold all positions visited by tail.
    // set is used as it only allows unique elements
    std::vector<cmplx> visited{};
    visited.push_back(knots[0]);

    while (std::getline(Input, line))
    {
        // get translation
        cmplx dir{dirs[line[0]]};
        cmplx trans{dir * std::stol(line.substr(line.find_first_of("1234567890")))};

        // perform the movements
        for (int i{static_cast<int>(std::abs(trans))}; i > 0; --i)
        {
            // iterate over all knots
            for (int k{0}; k<num_knots; ++k)
            {
                if (k==0)
                {
                    // deal with head separately
                    knots[0] += dir;
                    trans -= dir;
                }
                else
                {
                    cmplx diff(knots[k-1]-knots[k]);
                    if ((std::real(diff) == 0) || (std::imag(diff) == 0))
                    {
                        // same x or y coordinate
                        knots[k] += (diff) / cmplx(2, 0);
                    }
                    else if (std::abs(diff) < 2)
                    {
                        // head and tail are either in same position or neighbouring
                        ;
                    }
                    else
                    {
                        // diagonal. add (Re(diff)/|Re(diff)| + i Im(diff)/|Im(diff)|)
                        // ie up/down 1 if x diff is +ve/-ve
                        // and right/left 1 if y diff is +ve/-ve
                        knots[k] += cmplx(std::real(diff) / std::abs(std::real(diff)), std::imag(diff) / std::abs(std::imag(diff)));
                    }
                }
            }
            if (!contains(visited, knots[num_knots-1]))
            {
                visited.push_back(knots[num_knots-1]);
            }
        }
    }
    std::cout << visited.size();
}