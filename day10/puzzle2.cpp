#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int num_rows {6};
const int num_cols {40};
const int crt_size{num_cols*num_rows};

void draw_crt(bool *crt, long long reg, int pixel_no)
{
    int line_pos {(pixel_no%40)}; // correct for fact reg number only refers to position along a crt line
    if (((line_pos - 1) <= reg) && ((line_pos + 1) >= reg))
    {
        *(crt+pixel_no) = true; // that's right, we're using pointers
    }
} 

int main()
{
    std::fstream Input("input.txt");
    std::string line{};

    long long reg{1};

    bool crt[num_cols*num_rows] {false}; // crt pixels
    int pixel_no{0};

    while (std::getline(Input, line))
    {
        // for each cycle, check whether we should draw a pixel, then move onto the next pixel.
        draw_crt(crt, reg, pixel_no);
        pixel_no++;
        if (line.substr(0, 4) == "addx")
        {
            draw_crt(crt, reg, pixel_no);
            pixel_no++;
            reg += stoi(line.substr(5));
        }
    }

    // render text
    for (int i{};i<num_rows;++i)
    {
        for (int j{}; j<num_cols; ++j)
        {
            if (crt[j+num_cols*i])
            {
                std::cout << '#';
            }
            else
            {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}