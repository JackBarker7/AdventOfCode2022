#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> split_str(std::string input, char delim)
{
    // takes an input string, splits it at char, and returns two strings (before and after char)

    size_t split = input.find_first_of(delim);
    std::vector<std::string> rep{input.substr(0, split), input.substr(split + 1)};

    return rep;
}

std::vector<int> get_ids(std::string input)
{
    // converts string of format "id1-id2" to int vector {id1, id2}
    auto ids = split_str(input, '-');
    std::vector<int> rep{std::stoi(ids[0]), std::stoi(ids[1])};
    return rep;
}

int main()
{
    std::ifstream Input("input.txt");
    std::string line{};
    size_t count{};

    while (std::getline(Input, line))
    {
        auto assignments{split_str(line, ',')};

        auto ids_1 = get_ids(assignments[0]);
        auto ids_2 = get_ids(assignments[1]);

        if ((ids_1[0] <= ids_2[0] && ids_1[1] >= ids_2[1]) || (ids_2[0] <= ids_1[0] && ids_2[1] >= ids_1[1]))
        {
            count++;
        }
    }
    std::cout << count;
}