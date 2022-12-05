#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main() {
    std::ifstream Input ("input.txt");
    std::string line{};

    long total{0};

    while(std::getline(Input, line)){
        int theirs {static_cast<int>(line[0]-'A')+1};
        int mine {static_cast<int>(line[2]-'X')+1};
        // shift so that 1=Rock, 2=Paper, 3=Scissors

        if (theirs == mine){
            // draw; add 3 plus the score from the choice
            total += 3 + mine;
        }
        else if(theirs%3 == mine-1){
            // win; add 6 plus choice
            total += 6 + mine;
        }
        else{
            // loss; add choice
            total += mine;
        }
    }
    std::cout << total;

}