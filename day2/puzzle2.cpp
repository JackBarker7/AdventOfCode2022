#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main()
{

    std::ifstream Input("input.txt");
    std::string line{};

    long total{0};

    while (std::getline(Input, line))
    {
        int theirs{static_cast<int>(line[0] - 'A') + 1};

        if (line[2] == 'X')
        {
            // loss. Requirement is us%3 = them-1, so more complicated to solve for us
            if (theirs == 1)
            {
                total += 3;
            }
            else
            {
                total += theirs - 1;
            }
        }
        else if (line[2] == 'Y')
        {
            // draw
            total += 3 + theirs;
        }
        else
        {
            // win. To get our choice, solve expression in if statement in puzzle 1 for "mine"
            total += 6 + (theirs % 3) + 1;
        }
    }
    std::cout << total;
}