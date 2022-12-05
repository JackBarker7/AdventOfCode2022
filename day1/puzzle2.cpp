#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::vector<int> min_element(std::vector<int> input)
{
    // returns vector of the form {minimum value, location}
    int min{input[0]};
    int loc{0}; // location of the min
    for (size_t i{0}; i < std::size(input); i++)
    {
        // iterate through input and find lowest value
        if (input[i] < min)
        {
            loc = i;
            min = input[i];
        }
    }
    std::vector<int> rep{min, loc};
    return rep;
}

int main()
{
    std::ifstream Input("input1.txt");
    std::vector<int> maxs{0, 0, 0};
    int count{};
    std::string line{};

    while (getline(Input, line))
    {

        if (line.empty())
        {
            // if the line is empty, a new elf has begun, so check if the calories of the previous elf is
            // one of the top 3 recorded
            auto mins = min_element(maxs); // in the form value, index
            if (count > mins[0])
            {
                maxs[mins[1]] = count;
            }
            count = 0;
        }
        else
        {
            count += std::stoi(line);
        }
    }
    // we also need to check the last elf, as this is not done automatically

    auto mins = min_element(maxs);
    std::cout << maxs[0] << maxs[1] << maxs[2] << std::endl;
    if (count > mins[0])
    {
        maxs[mins[1]] = count;
    }

    // sum values in max
    int sum{0};
    for (auto i : maxs)
    {
        sum += i;
    }
    std::cout << sum;
}