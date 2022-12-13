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

    // position is represented as x+iy
    cmplx head{0, 0};
    cmplx tail{0, 0};

    // set of complex numbers to hold all positions visited by tail.
    // set is used as it only allows unique elements
    std::vector<cmplx> visited{};
    visited.push_back(tail);

    while (std::getline(Input, line))
    {
        // get translation
        cmplx dir{dirs[line[0]]};
        cmplx trans{dir * std::stol(line.substr(line.find_first_of("1234567890")))};

        // perform the movements
        for (int i{static_cast<int>(std::abs(trans))}; i > 0; --i)
        {
            head += dir;
            cmplx diff{head - tail};
            if ((std::real(diff) == 0) || (std::imag(diff) == 0))
            {
                // same x or y coordinate
                tail += (diff) / cmplx(2, 0);
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
                tail += cmplx(std::real(diff) / std::abs(std::real(diff)), std::imag(diff) / std::abs(std::imag(diff)));
            }
            if (!contains(visited, tail))
            {
                visited.push_back(tail);
            }
            trans -= dir;
        }
    }
    std::cout << visited.size();
}