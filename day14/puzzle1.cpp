#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

// sand is dropped at (500,0). We do not yet know the maximum y value that we have to consider
// let's assume a grid from x=0 to x=1000, y=0 to y=500
const int num_cols{1000};
const int num_rows{500};

// y position of lowest rock.
int maxy{0};

void add_rock(std::string loc1, std::string loc2, bool (&grid)[num_rows][num_cols]);

bool fall(int (&current)[2], bool (&grid)[num_rows][num_cols]);

bool add_sand(int sand_pt[2], bool (&grid)[num_rows][num_cols]);

void display_grid(int xpts[2], int ypts[2], bool grid[num_rows][num_cols]);

int main()
{
    std::fstream Input("input.txt");
    std::string line{};

    bool grid[num_rows][num_cols]{false};

    // in our grid, false represents empty space
    // let's now populate the grid with rocks

    while (std::getline(Input, line))
    {
        int start{0};
        int end{0};
        std::vector<std::string> rocks{};
        int i{0};

        while (end != std::string::npos)
        {
            end = line.find_first_of(' ', start);
            rocks.push_back(line.substr(start, end - start));
            if (rocks.size() != 1)
            {
                add_rock(rocks[i - 1], rocks[i], grid);
            }
            ++i;
            start = line.find_first_not_of(" ->", end);
        }
    }

    // implement sand falling
    int sand_pt[2]{500, 0};
    bool reached_void{false};
    int sand_count{0};
    while (!reached_void)
    {
        reached_void = !add_sand(sand_pt, grid);
        sand_count++;
    }

    // we need to subtract one from sand count as we have also counted
    // the first grain to fall into the void
    sand_count--;
    std::cout << sand_count << std::endl;
}

void add_rock(std::string loc1, std::string loc2, bool (&grid)[num_rows][num_cols])
{
    int x1{stoi(loc1.substr(0, loc1.find_first_of(',')))};
    int y1{stoi(loc1.substr(loc1.find_first_of(',') + 1))};

    int x2{stoi(loc2.substr(0, loc2.find_first_of(',')))};
    int y2{stoi(loc2.substr(loc2.find_first_of(',') + 1))};

    if (x1 == x2)
    {
        for (int i{std::min(y1, y2)}; i <= std::min(y1, y2) + std::abs(y1 - y2); ++i)
        {
            grid[i][x1] = true;
            if (i > maxy)
            {
                maxy = i;
            }
        }
    }
    else
    {
        for (int i{std::min(x1, x2)}; i <= std::min(x1, x2) + std::abs(x1 - x2); ++i)
        {
            grid[y1][i] = true;
            if (y1 > maxy)
            {
                maxy = y1;
            }
        }
    }
}

bool fall(int (&current)[2], bool (&grid)[num_rows][num_cols])
{
    // returns true if fall succeeded
    // fall succeeded if sand was able to fall without reaching
    // the void

    // 0) Check if we have fallen into void
    if (current[1] + 1 > maxy)
    {
        current[1] += 1;
        return false;
    }
    // 1) Try to fall vertically down
    else if (!grid[current[1] + 1][current[0]])
    {
        current[1] += 1;
        return true;
    }
    // 2) Try to fall down and left
    else if (!grid[current[1] + 1][current[0] - 1])
    {
        current[1] += 1;
        current[0] -= 1;
        return true;
    }

    // 3) Try to fall down and right
    else if (!grid[current[1] + 1][current[0] + 1])
    {
        current[1] += 1;
        current[0] += 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool add_sand(int sand_pt[2], bool (&grid)[num_rows][num_cols])
{
    // adds sand. returns false if sand falls into void.

    int current[2]{sand_pt[0], sand_pt[1]};

    bool succeeded{true};
    while (succeeded)
    {
        succeeded = fall(current, grid);
    }

    if (current[1] > maxy)
    {
        return false;
    }
    else
    {
        grid[current[1]][current[0]] = true;
        return true;
    }
}

void display_grid(int xpts[2], int ypts[2], bool grid[num_rows][num_cols])
{
    for (int row{ypts[0]}; row < ypts[1]; ++row)
    {
        for (int col{xpts[0]}; col < xpts[1]; ++col)
        {
            if (grid[row][col])
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