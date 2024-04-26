#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <mutex>
#include <set>
#include <map>
#include <cctype>

std::mutex common_vector_mutex;
int GLOBAL = 0;

struct Comparator
{
    bool operator()(const std::string& a, const std::string& b)
    {
        return GLOBAL ? a > b : a < b;
    }
};

void Split_Line(std::string& str, std::set<std::string, Comparator>& words, std::map<std::string, int>& dup_map)
{
    std::lock_guard<std::mutex> lock(common_vector_mutex);
    {  
        size_t before = 0;
        size_t after = 0;
        std::string sample;
        for(int i = 0; i < str.size(); ++i)
        { 
            if(str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == '-' || str[i] == ':')
            {
                if(sample.empty())
                {
                    continue;
                }
                before = words.size();
                words.insert(sample);
                after = words.size();
                if(before == after)
                {
                    ++dup_map[sample];
                }
                sample.clear();
            }
            else
            {
                sample.push_back(std::tolower(str[i]));
            }
        }
        if(!sample.empty())
        {
            before = words.size();
            words.insert(sample);
            after = words.size();
            if(before == after)
            {
                ++dup_map[sample];
            }
        }
    }
}

void Open_File_Read(char *path, std::set<std::string, Comparator>& words, std::map<std::string, int>& dup_map)
{
    std::ifstream in;
    in.open(path);
    std::string line;
    if(in.is_open())
    {
        [[likely]]while (std::getline(in, line))
        {
            Split_Line(line, words, dup_map);
        }   
    }
    else
    {
        [[unlikely]]std::cout << "ERROR" << std::endl;
    } 
    in.close();
    std::this_thread::yield();
}

void Open_File_Write(std::set<std::string, Comparator>& set, char delimeter)
{
    std::ofstream out;
    out.open("text.txt");

    if(out.is_open())
    {
        for(auto item : set)
        {
            out << item << delimeter << ' ';
        }
    }
    std::cout << "The file 'text.txt' has been created." << std::endl;
    out.close();
}

void Most_Often(std::map<std::string, int>& map)
{
    int value = 0;
    std::string str_value{};
    for(auto item : map)
    {
        if(item.second > value)
        {
            value = item.second;
            str_value = item.first;
        }
    }

    std::cout << "The most frequend word in all files is '" << str_value << "', count: " << value << std::endl; 
}

int main(int argc, char** argv)
{
    if(argc < 2)
    [[unlikely]]{
        [[unlikely]]std::cout << "NOT ENOUGH ARG" << std::endl;
        [[unlikely]]return -1;
    }

    std::set<std::string, Comparator> ALL_WORDS_SET;
    std::map<std::string, int> DUPLICATE_MAP;
    std::thread pool[argc - 1];
    char delimeter = ' ';
    std::string option;

    std::cout << "Enter your options: " << std::endl;
    while (true)
    {
        std::getline(std::cin, option);
        
        if(option == "go")
        {
            break;
        }
        if(option == "sort -a" || option == "sort -d")
        {
            GLOBAL = (option.back() == 'd');
        }
        if(option == "split -s" || option == "split -c" || option == "split -n")
        {
            switch (option.back())
            {
                case 's':
                    delimeter = ' ';
                    break;
                case 'c':
                    delimeter = ',';
                    break;
                case 'n':
                    delimeter = '\n';
                    break;
                default:
                    break;
            }
        }
    }
    
    for(int i = 0; i < argc - 1; ++i)
    {
        pool[i] = std::thread(&Open_File_Read, std::ref(argv[i + 1]), std::ref(ALL_WORDS_SET), std::ref(DUPLICATE_MAP));
    }

    for(int i = 0; i < argc - 1; ++i)
    {
        pool[i].join();
    }

    // for(auto item: ALL_WORDS_SET)
    // {
    //     std::cout << item << std::endl;
    // }

    // for (const auto& entry : DUPLICATE_MAP) 
    // {
    //     std::cout << entry.first << ": " << entry.second << std::endl;
    // }

    Open_File_Write(ALL_WORDS_SET, delimeter);
    Most_Often(DUPLICATE_MAP);

    return 0;
}
