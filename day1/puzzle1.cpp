#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream Input("input1.txt");
    int max{0};
    int count {};
    std::string line {};

    while (getline(Input, line)){
        
        if (line.empty()){
            if (count>max){
                max=count;
            }
            count = 0;
        }
        else{
            count += std::stoi(line);
            }
        
    }

    std::cout << max;
}