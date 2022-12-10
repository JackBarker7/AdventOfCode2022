#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


std::vector<int> parse_instruction(std::string inst)
{
    // takes an instruction in text format, returns [number, start, end]
    size_t start{0};
    size_t end{0};
    char search[] {"1234567890"};
    std::vector<int> nums;
    while (end != std::string::npos)
    {
        start = inst.find_first_of(search, end); // find start of number
        end = inst.find_first_not_of(search, start); // find end of number
        nums.push_back(std::stoi(inst.substr(start, end-start)));
    }
    return nums;
}

void move_crates(int num, std::vector<char> &from, std::vector<char> &to)
{
    // this time, we move crates in the opposite order to last time
    
    for (size_t i{from.size()-num}; i<from.size(); i++)
    {
        to.push_back(from[i]);
    }
    
    from.resize(from.size()-num); // resize always removes from the end
}


int main()
{
    std::ifstream Input("input.txt");
    std::string line{};
    const int num_stacks{9};

    std::vector<char> crates[num_stacks];

    // we now need to parse

    // populate crates array

    std::getline(Input, line);
    while (line[1] != '1')
    {
        for (size_t i{}; i < num_stacks; i++)
        {
            char new_crate = line[4 * i + 1];
            if (new_crate != ' ')
            {
                crates[i].push_back(new_crate);
            }
        }
        std::getline(Input, line);
    }
    // stacks are in wrong order
    for (size_t i{0}; i<num_stacks; i++)
    {
        std::reverse(crates[i].begin(), crates[i].end());
    }
    // stacks are now populated, time to implement the instructions
    std::getline(Input, line); // advance a line to get to 1st instruction
    std::vector<int> instructions {};

    while(std::getline(Input, line))
    {
        // parse instruction and move crate
        instructions = parse_instruction(line);
        move_crates(instructions[0], crates[instructions[1]-1], crates[instructions[2]-1]);
    }

    // get crates at top of stacks
    std::string ans {};
    for (auto &stack: crates)
    {
        ans.push_back(stack.back());
    }
    std::cout << ans;

}