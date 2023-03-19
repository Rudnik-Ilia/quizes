#include <iostream>
using std::cout;
using std::endl;

#include "Dispatcher.hpp"

using namespace ilrd;

void Foo(const int &x, const int &y)
{
    cout << "SUMM: "<< x + y << endl;
}

void Bar(const int &x, const int &y)
{
    cout << "DIV: "<< x - y << endl;
}

class DataModel
{
    public:
        void ChangeState(int x, int y)
        {
            pos_x = x;
            pos_y = y;

            Notify(x, y);
        }

        void Notify(int x, int y)
        {
            m_disp.Dispatch(x, y);
        }

        Dispatcher<int, int> m_disp;
    private:
        int pos_x{0};
        int pos_y{0};
};


class ViewWindow
{
    public:
        ViewWindow(DataModel &model) : m_model(model), func(Foo)
        {
            model.m_disp.Subscribe(func);
        }

    private:
       DataModel &m_model;
       Callback<int, int> func;
};


class ControlWindow
{
    public:
        ControlWindow(DataModel &model) : m_model(model){}
         
        void SetState(int x, int y)
        {
            m_model.ChangeState(x, y);
        }

    private:
       DataModel &m_model;

};

int main()
{
    // Dispatcher<int, int> disp;
    std::function<void(const int&, const int&)> wrap1 = Foo;
    std::function<void(const int&, const int&)> wrap2 = Bar;

    Callback<int, int> summ(wrap1);
    Callback<int, int> dev(wrap2);

    // disp.Subscribe(summ);
    // disp.Subscribe(dev);
    // disp.Dispatch(10,9);
    // disp.Unsubscribe(dev);
    // disp.Dispatch(10,9);

    DataModel model;

    ControlWindow control(model);

    ViewWindow view(model);


    control.SetState(9,9);

    





    return 0;
}
