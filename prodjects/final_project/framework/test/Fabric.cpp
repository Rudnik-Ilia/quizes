#include <iostream>

using namespace std;


class IProduction
{
    public:
    virtual void Release() = 0;
   
};

class Car: public IProduction
{
    public:
    void Release()
    {
        cout << "CAR" << endl;
    }
};

class Truck: public IProduction
{
    public:
    void Release()
    {
        cout << "TRUCK" << endl;
    }
};

class IWorkShop
{
    public:
    virtual IProduction* create() = 0;
};


class CarShop: public IWorkShop
{
    public: 
    IProduction* create()
    {
        return new Car();
    }
};

class TruckShop: public IWorkShop
{
    public: 
    IProduction* create()
    {
        return new Truck();
    }
};




int main()
{
    IProduction *vechle;
    IWorkShop* Creator;


    Creator = new CarShop();
    vechle = Creator->create();
    vechle->Release();


    Creator = new TruckShop();
    vechle = Creator->create();
    vechle->Release();



    return 0;
}



