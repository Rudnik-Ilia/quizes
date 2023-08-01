#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRU
{
    using iter_t = list<char>::iterator;

    public:
        LRU(size_t size): m_size(size), m_list(), m_map(){}

        void Put(int key, char val)
        {
            auto item = m_map.find(key);
            if(item == m_map.end())
            {

            }

            m_list.push_front(val);
            m_map.insert({key, m_list.begin()});
            
        }

        char Get(int key)
        {
            auto item = m_map.find(key);
            auto tmp = item;

            if(item == m_map.end())
            {
                return 'X';
            }
            m_list.erase(item->second);
            m_map.erase(key);

            Put(key, *(tmp->second));
            return *(tmp->second); 
        }

    private:
        list<char> m_list;
        unordered_map<int, iter_t> m_map;
        size_t m_size;
};


int main()
{
    LRU lru(4);

    lru.Put(1, 'A');
    lru.Put(2, 'B');
    lru.Put(3, 'C');

    cout << lru.Get(1) << endl;
    cout << lru.Get(1) << endl;
    // cout << lru.Get(2) << endl;
    // cout << lru.Get(3) << endl;

    // cout << lru.Get(4) << endl;

    


    return 0;
}