#include <iostream>
#include <vector>
#include <numeric>

int Foo(std::vector<int> &rating)
{
    std::vector<int> ans(rating.size(), 1);

    for(int i = 1; i < rating.size(); i++)
    {
        if(rating[i] > rating[i - 1])
        {
            ans[i] = ans[i - 1] + 1;
        }
    }
    for (int i = rating.size() - 2; i < rating.size(); i--)
    {
        if(rating[i] > rating[i + 1] && ans[i] <= ans[i+1])
        {
            ans[i] = ans[i + 1] + 1;
        }
    }
    
    return std::accumulate(ans.begin(), ans.end(), 0);
}


int main()
{
    std::vector<int> v({1,2,3,5,1,1,3});
    std::cout << Foo(v); 
    return 0;
}