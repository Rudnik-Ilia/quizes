#include <iostream>
#include <unordered_set>
#include <vector>
#define SIZE (4) 

using namespace std;

void BackTrack(int row, int N, vector<string> &board, vector<vector<string>> &result, unordered_set<int> &row, unordered_set<int> &asc,  unordered_set<int> &desc)
{
    if(row == N)
    {
        return;
    }
    for(int i = 0; i < board[row].size() - 1; ++i)
    {
        int asc_idx = row + i;
        int desc_idx = row - i;

        if()
        {
            

            std::cout << row << ' ' << i << std::endl;

            vertical.insert(i);
            asc.insert(asc_idx);
            desc.insert(desc_idx);

            BackTrack(row + 1, N, board, result, row, asc, desc);

          

            vertical.erase(i);
            asc.erase(asc_idx);
            desc.erase(desc_idx);
        }
    }
}

void MainFunc(int N, vector<string>&board, )
{
    unordered_set<int> row;
    unordered_set<int> asc;
    unordered_set<int> desc;


    BackTrack(0, N, board, row, asc, desc);

}


int main()
{
    vector<vector<char>> mat(SIZE);

    for (int i = 0; i < SIZE; ++i)
    {
        mat[i].resize(SIZE, '.');
    }

    MainFunc(4, mat);

    return 0;
}