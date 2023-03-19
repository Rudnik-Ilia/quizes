#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class IObserver
{
    public:
        virtual void Handle(double price) = 0;
};

class IObservable
{
    public:
        virtual void AddObserver(int ID, IObserver &obser) = 0;
        virtual void RemoveObserver(int ID) = 0;
        virtual void Notify() = 0;

        virtual ~IObservable(){};
};

class Publisher : public IObservable
{
    public:
        Publisher(double price): m_price(price){}

        void ChangePrice(double new_price)
        {
            m_price = new_price;
            this->Notify();

        }
        void Notify()
        {
           for(auto iter: m_allobservers)
           {
                iter.second.Handle(m_price);
           }
        }
        void AddObserver(int ID, IObserver &obser)
        {
            m_allobservers.insert({ID, obser});
        }
        void RemoveObserver(int ID)
        {
            m_allobservers.erase(ID);
        }

        ~Publisher()
        {
            this->Notify();
        }

    private:
        double m_price;
        unordered_map<int, IObserver&> m_allobservers;
};

class Subscriber1: public IObserver
{
    public:
        Subscriber1(IObservable &product, int id) : m_prod(product), m_id(id) 
        {
            m_prod.AddObserver(id, *this);
        }
        
        void Handle(double price)
        {
            if(price < 100)
            {
                cout << "TAKE ALL" << endl;
            }
        }

    private:
        IObservable &m_prod;
        int m_id;
};

class Subscriber2: public IObserver
{
    public:
        Subscriber2(IObservable &product, int id) : m_prod(product), m_id(id) 
        {
            m_prod.AddObserver(id, *this);
        }

        void Handle(double price)
        {
            if(price < 90)
            {
                cout << "TAKE ONE" << endl;
            }
        }
    private:
        IObservable &m_prod;
        int m_id;
};



int main()
{
    Publisher apple(95); 

    Subscriber1 me(apple, 33); 
    Subscriber2 group(apple, 44); 

    apple.ChangePrice(88);

  

    return 0;
}