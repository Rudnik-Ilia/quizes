#include <iostream>
#include <string.h>
#include <vector>

int Find(int x, int y)
{
    if(x == 0 || y == 0)
    {
        return 0;
    }
    if(x == 1 && y == 1)
    {
        return 1;
    }
    return Find(x - 1, y) + Find(x, y - 1);
}


int Find2(int m, int n) 
{
    int i = 0;
    int j = 0;

    std::vector<std::vector<int>> arr(m, std::vector<int>(n));
  
    for(i = 0; i < n; ++i)
    {
        arr[0][i] = 1;
    }
    
    for(i = 0; i < m; ++i)
    {
        arr[i][0] = 1;
    }

    for(i = 1 ; i < m; ++i)
    {
        for(j = 1; j < n; ++j)
        {
            arr[i][j] = arr[i-1][j] + arr[i][j-1];

        }
    }

    return arr[m - 1][n - 1];

}

int main()
{
    // std::cout << Find(50, 50) << std::endl;
    std::cout << Find2(50, 50) << std::endl;
    // Find2(3, 7) ;
    return 0;
}