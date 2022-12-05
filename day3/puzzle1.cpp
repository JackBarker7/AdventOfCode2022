#include <iostream>
#include <fstream>
#include <string>

int get_priority(char item)
{
    if (std::tolower(item) == item){
        //item is lowercase
        return item-'a'+1;
    }
    else{
        // item is uppercase
        return item-'A'+27;
    }
}

char find_common (std::string stra, std::string strb){

    // finds common character in strings stra and strb
    for (auto a:stra){
        for (auto b:strb){
            if (a==b){
                return a;
            }
        }
    }
}
int main()
{
    std::ifstream Input("input.txt");

    std::string line{};


    int sum {0};

    while (std::getline(Input, line))
    {
        size_t length {std::size(line)};
        char common {find_common(line.substr(0,length/2), line.substr(length/2,length/2))};
        sum += get_priority(common);
    }
    std::cout << sum;
}