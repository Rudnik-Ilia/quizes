#include <iostream>
#include <map>
#include <vector>

#define CAS(ptr, oldone, newone)  __sync_bool_compare_and_swap(ptr, oldone, newone)

template<class K, class V>
class WRRMMap
{
    public:
        std::map<K,V> *m_pMap;
        std::vector<std::map<K,V> *> rlist;


        static void Retire(std::map<K,V> * pOld)
        {
            rlist.push_back(pOld);
        }
};

class HPRecType
{
    public:
        void * pHazard;

        static HPRecType *Head()
        {
            return pHead;
        }

        static HPRecType *Acquire()
        {
            HPRecType *p = pHead;

            for( ;p ;p->pNext)
            {
                if(p->active || !CAS(&p->active, 0, 1))
                {
                    continue;
                }
                return p;
            }

            int oldLen;

            do
            {
               oldLen = listLen;
            } while (!CAS(&listLen, oldLen, oldLen + 1));

            HPRecType * pnew= new HPRecType;

            pnew->active = 1;
            pnew->pHazard = 0;

            HPRecType * old;
            do
            {
                old = pHead; 
                pnew->pNext = old;

            } while (!CAS(&pHead, old, pnew));
            
            return pnew;
        }

        static void Release(HPRecType * p)
        {
            p->pHazard = 0;
            p->active = 1;
        }


    private:
        HPRecType * pNext;
        int active;
        static HPRecType * pHead;
        static int listLen;
};





int main()
{
    int arr[] = {1,2,3,4};

    for(size_t i = 0; i < 5; ++i)
    {
        std::cout << arr[i] << std::endl;
        if(arr[i] == 1)
        {
            continue;
        }
        return 0;
    }
    


    return 0;
}