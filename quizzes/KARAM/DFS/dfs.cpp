#include <iostream>
#include <vector>

const int INF = 1e9;
int count = 0;

void dfs(std::vector<std::vector<int>> &matrix, int start, std::vector<int> &visit)
{
    if(visit[start] == 1 || start > matrix.size())
    {
        return;
    }

    visit[start] = 1;

    for(int i = 0; matrix.size(); ++i)
    {
        for(int j = 0; matrix[i].size(); ++j)
        {
            if(!visit[matrix[i][j]] && j < matrix[i].size())
            {
     
                dfs(matrix, start + 1, visit);
                ++count;
            }
        }
    }
}

void PrintV(std::vector<int> &visit)
{
    for (int i : visit)
    {
        std::cout << i << " ";

    }
    std::cout << " \n";
}

int main()
{
    int count = 0;
    std::vector<std::vector<int>> matrix{{1}, {0,2}, {4,3,1}, {4,2}, {2,3}, {6,7}, {5,7}, {5,6}, {}};
    std::vector<int> visit(9, 0);

    // for(int i = 0; i < matrix.size(); ++i)
    // {
    //     if(!visit[i])
    //     {
    //         dfs(matrix, i, visit);
    //         ++count;
    //     }
    // }


    dfs(matrix, 0, visit);
    PrintV(visit);
    std::cout << count << std::endl;

    






    return 0;
}