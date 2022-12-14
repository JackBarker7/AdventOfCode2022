#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <algorithm>

std::fstream Input("input.txt");
std::string line{};

struct monkey
{
    std::deque<double> items = {}; // so we have pop_front() method
    char operation = '+'; // options are '+', '*', '^'
    double op_amt = 0;      // value for rhs of operation (n/a for '^')

    int test = 0;      // divisibility test number
    int test_true = 0; // where to throw if test is true
    int test_false = 0;

    size_t inspections = 0;
};

void parse_monkey(std::vector<monkey> &monkeys)
{
    monkey new_monkey{};

    // get the items
    std::getline(Input, line);

    const int first_char{18}; // char at which items begin
    int start{first_char};
    int end{first_char};

    while (end != std::string::npos)
    {
        end = line.find_first_of(',', start);
        new_monkey.items.push_back(std::stol(line.substr(start, start - end)));
        start = end + 2;
    }

    // get the operation type and number
    std::getline(Input, line);

    if (line[25] == 'o')
        new_monkey.operation = '^';
    else
    {
        new_monkey.operation = line[23];
        new_monkey.op_amt = std::stol(line.substr(25));
    }

    // get divisibility test
    std::getline(Input, line);
    new_monkey.test = std::stoi(line.substr(21));

    // get true and false results
    std::getline(Input, line);
    new_monkey.test_true = std::stoi(line.substr(29));
    std::getline(Input, line);
    new_monkey.test_false = std::stoi(line.substr(30));

    monkeys.push_back(new_monkey);
}

double get_worry(monkey monk)
{
    switch (monk.operation)
    {
    case '+':
        return std::floor((monk.op_amt + monk.items[0])/3.);
        break;

    case '*':
        return std::floor((monk.op_amt * monk.items[0])/3.);
        break;

    case '^':
        return std::floor((std::pow(monk.items[0], 2))/3.);
        break;
    default:
        break;
    }
    return 0.;
}

int main()
{

    // parse all the monkeys
    std::vector<monkey> monkeys{};
    while (std::getline(Input, line))
    {
        parse_monkey(monkeys);
        std::getline(Input, line);
    }

    // perform the operations
    const int rounds{20};
    for (int i{}; i < rounds; ++i)
    {
        for (auto &monk : monkeys)
        {
            while (monk.items.size() > 0)
            {
                double new_worry{get_worry(monk)};
                monk.inspections ++;
                if (((long)new_worry) % monk.test == 0)
                {
                    monkeys[monk.test_true].items.push_back(new_worry);
                }
                else
                {
                    monkeys[monk.test_false].items.push_back(new_worry);
                }
                monk.items.pop_front();
            }
        }
    }
    size_t max_inspections[2] {0};
    for (auto monk: monkeys)
    {
        if (monk.inspections > max_inspections[0])
        {
            max_inspections[0] = monk.inspections;
        }
    }
    for (auto monk: monkeys)
    {
        if ((monk.inspections > max_inspections[1]) && (monk.inspections != max_inspections[0]))
        {
            max_inspections[1] = monk.inspections;
        }
    }

    std::cout << max_inspections[0]*max_inspections[1];

}