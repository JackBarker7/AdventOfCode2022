#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <algorithm>

int has_repeat (std::deque<char> queue)
{
    // check if deque has repeat character
    for (int i{}; i<queue.size(); ++i)
    {
        for (int j{}; j<queue.size(); ++j)
        {
            if ((i!=j) && (queue[i] == queue[j]))
            {
                return true;
            }
        }
    }
    return false;
}



int main() {
    std::fstream Input("input.txt");
    std::string data {};
    std::getline(Input, data);
    
    int search_length{4}; // we only want to look for comparisons when the queue is fully populated

    // store the 4 most recent chars in a deque so that we can randomly access chars to check for common letters (not possible with queue)
    // and have pop_front (not possible with a vector)

    std::deque<char> queue {};

    for (int i{}; i<data.size(); i++)
    {
        if (queue.size()==search_length)
        {
            queue.pop_front();
        }
        queue.push_back(data[i]);

        if (!has_repeat(queue) && queue.size()==search_length)
        {
            std::cout << i+1;
            return 0;
        }

    }

    // shouldn't reach here
    std::cout << "No marker found";


}
