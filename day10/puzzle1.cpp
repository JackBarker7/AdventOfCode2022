#include <iostream>
#include <fstream>
#include <string>


int main()
{
    std::fstream Input ("input.txt");
    std::string line {};

    long long reg {1};
    size_t cycle {0};
    long long count {};

    while (std::getline(Input, line))
    {
        cycle ++;
        if ((cycle+20)%40 == 0)
        {
            count += reg*cycle;
        }
        if (line.substr(0,4)=="addx")
        {
            cycle++;
            if ((cycle+20)%40 == 0)
            {
                // chance that the extra increment of an addx has taken us to a 20+40x point
                count += reg*cycle;
            }
            reg += stoi(line.substr(5));
        }
        
    }
    std::cout << count;

}