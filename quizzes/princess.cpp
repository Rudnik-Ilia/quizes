#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

int calculateMinimumHP(vector<vector<int>>& dungeon) 
{
    int m = dungeon.size();
    int n = dungeon[0].size();

    vector<vector<int>> dp(m, vector<int>(n, INT_MAX));

    dp[m-1][n-1] = 1;
    
    for (int i = m-1; i >= 0; i--)
    {
        for (int j = n-1; j >= 0; j--) 
        {
            if (i < m-1) {
                dp[i][j] = min(dp[i][j], dp[i+1][j] - dungeon[i][j]);
            }
            if (j < n-1) {
                dp[i][j] = min(dp[i][j], dp[i][j+1] - dungeon[i][j]);
            }
          
            dp[i][j] = max(dp[i][j], 1);
        }
    }
    return dp[0][0];
}


int main() {

    vector<vector<int>> dungeon = {{-2,-5,3},{-5,-10,1},{10,30,-6}};
    cout << calculateMinimumHP(dungeon) << endl; // Expected output: 7

    return 0;
}
