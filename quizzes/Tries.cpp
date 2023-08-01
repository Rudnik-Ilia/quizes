#include <iostream>
#include <map>
#include <vector>

class Node
{
    public:
        Node(bool end): is_end(end)
        {}
        ~Node(){}
        bool is_end;
        std::map<char, Node *> m_map;
};

class Tries
{
    public:
        Tries() : m_root(new Node(0)){}
        ~Tries(){}

        void Insert(std::string str)
        {
            Node * iter = m_root;

            for(size_t i = 0; i < str.size();)
            {
                if(iter->m_map[str[i]])
                {  
                    while(iter->m_map[str[i]])
                    {
                        iter = iter->m_map[str[i]];
                        ++i;
                    }
                }
                else
                {
                    iter->m_map[str[i]] = new Node(0);
                    iter = iter->m_map[str[i]];
                    ++i;
                }
            }
            iter->is_end = 1;
        }

        void Show(std::string str, Node *root)
        {
            
        }

        void Aux(std::string str, Node *root)
        {
          
        }

        size_t Len()
        {
            // return m_root->m_map['s']->m_map.size();
            // return m_root->m_map['s']->m_map['e']->m_map['a']->m_map['m'];
            return m_root->m_map['s']->m_map['o']->m_map['u']->m_map['l']->m_map.size();

        }

    private:
        Node * m_root;
};



int main()
{
    std::string word = "se";
    std::vector<std::string> arr({"seam", "soul", "seed", "see", "sick"});
    
    Tries tries;
    tries.Insert(arr[0]);
    tries.Insert(arr[1]);
    tries.Insert(arr[2]);
    tries.Insert(arr[3]);
    tries.Insert(arr[4]);

    std::cout << tries.Len() << std::endl;









    return 0;
}