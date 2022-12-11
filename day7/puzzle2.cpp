#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

// rather than messing about with streams, we read all the lines into a vector
std::vector<std::string> lines{};

size_t total{}; // final answer

const size_t disk_space{70000000};
const size_t needed_space{30000000};

struct dir
{
    std::string name = "";
    size_t size = 0;
    dir *parent = nullptr;
    std::unordered_map<std::string, dir *> subdirs;
};

dir *new_node(std::string name, dir *parent)
{
    dir *temp = new dir;
    temp->name = name;
    temp->parent = parent;
    return temp;
}

void parse(int &inst_no, dir *&current, std::vector<dir *> &filetree)
{
    std::string line{lines[inst_no]};
    if (line[0] == '$')
    {
        // command. options are "cd" or "ls"
        std::string command{line.substr(2, 2)};
        if (command == "cd")
        {
            std::string loc{line.substr(5)};
            if (loc == "..")
            {
                current = current->parent; // equivalent to (*current).parent
            }
            else
            {
                current = current->subdirs[loc]; // cd into new dir
            }
            inst_no += 1;
            return;
        }
        else
        {
            // command = ls

            // keep parsing lines until we find another command

            while (inst_no < lines.size() - 1)
            {
                inst_no += 1;

                line = lines[inst_no];
                // check if next line is a command
                if (line[0] == '$')
                {
                    return;
                }

                // parse new line
                if (line.substr(0, 3) == "dir")
                {
                    // new line is of form dir xyz. create a new dir and add it to the filesystem
                    std::string name{line.substr(4)};

                    filetree.push_back(new_node(name, current));
                    current->subdirs.insert({name, filetree.back()});
                }
                else
                {
                    // new line is a file
                    // get the number part, convert to an integer

                    int new_size{stoi(line.substr(0, line.find_first_of(' ')))};

                    // and update the size of the directory
                    current->size += new_size;
                }
            }
            inst_no = lines.size();
        }
    }
}

void dir_sizes(dir *node)
{
    // traverse file tree using post-order method (bottom-up), and correct the size of each directory to
    // include the sizes of its child directories
    // going bottom-up ensures all child files are included

    for (auto &subdir : node->subdirs)
    {
        dir_sizes(subdir.second);
        node->size += subdir.second->size;
    }
}

int main()
{

    std::fstream Input("input.txt");
    std::string line{};

    while (std::getline(Input, line))
    {
        lines.push_back(line);
    }

    // filetree is a vector of dirs, each pointing to each other to form a tree
    std::vector<dir *> filetree{};

    // create parent dir, whose parent is a nullptr

    filetree.push_back(new_node("", nullptr));

    auto current{filetree[0]}; // directory we are currently in during parsing
    int instruction_no{1};     // current line to parse

    // iterate through instructions, and parse them 1-by-1
    while (instruction_no < lines.size())
    {
        parse(instruction_no, current, filetree);
    }

    // correct all the dir sizes based on the size of subdirs
    dir_sizes(filetree[0]);

    // now, find the smallest directory to be deleted that gives the required free space
    size_t free_space{disk_space - (filetree[0]->size)};

    size_t min_delete{needed_space - free_space};

    size_t current_del{filetree[0]->size};

    size_t space{current_del};
    for (auto *item : filetree)
    {
        size_t space{item->size};

        if ((space > min_delete) && (space < current_del))
        {
            current_del = space;
        }
    }
    std::cout << current_del;
}