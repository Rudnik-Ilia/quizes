#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>

#define AMOUNT_OF_TOWER (8)

struct Tower
{
    int x;
    int y;
};

void Print(std::vector<Tower> coor)
{
    for (auto &iter : coor)
    {
        std::cout << iter.x << " : " << iter.y << std::endl;
    }
}
void PrintD(std::vector<double> coor)
{
    for (auto &iter : coor)
    {
        std::cout << iter << ' ';
    }
    std::cout << '\n';
}

int DefineFirst(double one, double two)
{
    if(one < two)
    {
        return 1;
    }
    else if(one > two)
    {
        return 2;
    }
    return 0;
}

int DefineSecond(std::vector<double> one, std::vector<double> two)
{
    int count1 = 0;
    int count2 = 0;

    if(one[0] < two[0])
    {
        size_t i = 0;
        int count  = 0;
        while(one[i] > two[0] && i < AMOUNT_OF_TOWER)
        {
            ++count1;
            ++i;
        } 
    }
    else if(one[0] > two[0])
    {
        size_t i = 0;
        int count  = 0;
        while(one[i] > two[0] && i < AMOUNT_OF_TOWER)
        {
            ++count2;
            ++i;
        } 
    }
    else
    {
        return 0;
    }

    return count1 > count2 ? 1 : 2;
}

int main()
{
    int P = 0;
    int Q = 0;

    std::cin >> P >> Q;

    std::vector<Tower> MTS(AMOUNT_OF_TOWER);
    std::vector<Tower> TELE2(AMOUNT_OF_TOWER);

    for (size_t i = 0; i < 16; ++i)
    {
        Tower tower;
        std::cin >> tower.x >> tower.y;

        if (i < 8)
        {
            MTS[i] = tower;
        }
        else
        {
            TELE2[i - 8] = tower;
        }
    }

    std::vector<double> MTS_dist{};
    std::vector<double> TELE2_dist{};

    double MAXVALUE = std::numeric_limits<double>::max();

    for (size_t i = 0; i < 8; ++i)
    {
        double distance_MTS = std::sqrt(MTS[i].x * MTS[i].x + MTS[i].y * MTS[i].y);
        double distance_TELE2 = std::sqrt(TELE2[i].x * TELE2[i].x + TELE2[i].y * TELE2[i].y);

        if(distance_MTS < (Q + P))
        {
            MTS_dist.push_back(distance_MTS);
        }
        else
        {
            MTS_dist.push_back(MAXVALUE);
        }

        if(distance_TELE2 < (Q + P))
        {
            TELE2_dist.push_back(distance_TELE2);
        }
        else
        {
            TELE2_dist.push_back(MAXVALUE);
        }
    }

    std::sort(MTS_dist.begin(), MTS_dist.end());
    std::sort(TELE2_dist.begin(), TELE2_dist.end());

    PrintD(MTS_dist);
    PrintD(TELE2_dist);

    std::cout << DefineFirst(MTS_dist[0], TELE2_dist[0]) << std::endl;
    std::cout << DefineSecond(MTS_dist, TELE2_dist) << std::endl;

    return 0;
}
