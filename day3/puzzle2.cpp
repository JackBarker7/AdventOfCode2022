#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int get_priority(char item)
{
    if (std::tolower(item) == item)
    {
        // item is lowercase
        return item - 'a' + 1;
    }
    else
    {
        // item is uppercase
        return item - 'A' + 27;
    }
}

std::string find_common(std::string stra, std::string strb)
{

    // finds common characters in strings stra and strb
    std::string common{};
    for (auto a : stra)
    {
        for (auto b : strb)
        {
            if (a == b)
            {
                common.push_back(a);
            }
        }
    }
    return common;
}
int main()
{
    std::ifstream Input("input.txt");

    std::string line{};
    std::vector<std::string> lines{};

    int sum{0};

    while (std::getline(Input, line))
    {
        lines.push_back(line);
    }

    // iterate through all sets of three lines
    for (size_t i{0}; i < std::size(lines); i += 3)
    {
        char common_char = find_common(lines[i], find_common(lines[i + 1], lines[i + 2]))[0];
        sum += get_priority(common_char);
    }

    std::cout << sum;
}