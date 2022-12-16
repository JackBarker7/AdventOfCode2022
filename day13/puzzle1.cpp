#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

bool compare(std::string item1, std::string item2)
{
    
}



int main()
{
    std::fstream Input("example.txt");
    std::string line{};

    std::vector<std::array<std::string, 2>> pairs {};

    std::string item1{};
    std::string item2{};
    while (std::getline(Input, line))
    {
        item1 = line;
        std::getline(Input, line);
        item2 = line;
        std::getline(Input, line);
        pairs.push_back(std::array<std::string, 2>({item1, item2}));
    }
    for (auto pair: pairs)
    {
        
    }
    std::cout << "done";
}
