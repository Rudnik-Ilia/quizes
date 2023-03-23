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

void Faa(const int &x, const int &y)
{
    cout << "MUL: "<< x * y << endl;
}

// class DataModel
// {
//     public:
//         void ChangeState(int x, int y)
//         {
//             pos_x = x;
//             pos_y = y;

//             Notify(x, y);
//         }

//         void Notify(int x, int y)
//         {
//             m_disp.Dispatch(x, y);
//         }

//         Dispatcher<int, int> m_disp;
//     private:
//         int pos_x{0};
//         int pos_y{0};
// };

// class ViewWindow
// {
//     public:
//         ViewWindow(DataModel &model) : m_model(model), func(Foo)
//         {
//             model.m_disp.Subscribe(func);
//         }

//     private:
//        DataModel &m_model;
//        Callback<int, int> func;
// };


// class ControlWindow
// {
//     public:
//         ControlWindow(DataModel &model) : m_model(model){}
         
//         void SetState(int x, int y)
//         {
//             m_model.ChangeState(x, y);
//         }

//     private:
//        DataModel &m_model;

// };

class Subject
{
    public:
        Subject(){}
        ~Subject()
        {
            m_disp.~Dispatcher();
            cout << "Subject is destroyed!" << endl;
        }

        void ChangState(int x, int y)
        {
            m_disp.Dispatch(x, y);
            pos_x = x;
            pos_y = y;
        }

        Dispatcher<int, int> m_disp;
    private:
        int pos_x{0};
        int pos_y{0};
};


class Observer1
{
    public:
        Observer1(Subject &sub): m_func(Foo), m_subject(sub)
        {
            m_subject.m_disp.Subscribe(m_func);
            // m_subject.m_disp.~Dispatcher();
        }

        void SelfDelete()
        {
            m_subject.m_disp.Unsubscribe(m_func);
        }

        ~Observer1()
        {
            m_subject.m_disp.Unsubscribe(m_func);
        }

    private:
        Callback<int, int> m_func;
        Subject &m_subject;
};

class Observer2
{
    public:
        Observer2(Subject &sub): m_func(Faa), m_subject(sub)
        {
            m_subject.m_disp.Subscribe(m_func);
        }
        ~Observer2()
        {
            m_subject.m_disp.Unsubscribe(m_func);
        }
    private:
        Callback<int, int> m_func;
        Subject &m_subject;
};

class Observer3
{
    public:
        Observer3(Subject &sub): m_func(Bar), m_subject(sub)
        {
            m_subject.m_disp.Subscribe(m_func);
        }

        ~Observer3()
        {
           
            m_subject.m_disp.Unsubscribe(m_func);
            
        }

    private:
        Callback<int, int> m_func;
        Subject &m_subject;
};

class Changer
{
    public:
        Changer(Subject &disp): m_disp(disp){}

        void Change(int x, int y)
        {
            m_disp.ChangState(x,y);
        }

        void Delete(Callback<int, int> &some_call)
        {
            m_disp.m_disp.Unsubscribe(some_call);
        }

    private:
        Subject &m_disp;
};

int main()
{
    /***********************************************************************/
    // Dispatcher<int, int> disp;
    std::function<void(const int&, const int&)> wrap1 = Foo;
    // std::function<void(const int&, const int&)> wrap2 = Bar;
    Callback<int, int> summ(wrap1);
    // Callback<int, int> dev(wrap2);
    // disp.Subscribe(summ);
    // disp.Subscribe(dev);
    // disp.Dispatch(10,9);
    // disp.Unsubscribe(dev);
    // disp.Dispatch(10,9);
    /***********************************************************************/

    // DataModel model;
    // ControlWindow control(model);
    // ViewWindow view(model);
    // control.SetState(9,9);

    /***********************************************************************/
    {
        Subject subject;
        Observer1 obs1(subject);
        {
            Observer2 obs2(subject);
            Observer2 obs7(subject);
            Observer3 obs3(subject);
            subject.ChangState(99, 2);
            Observer3 obs6(subject);
        }
        cout << "______________________________" << endl;

        Observer2 obs4(subject);
        Observer3 obs5(subject);

        subject.ChangState(99, 2);
        cout << "______________________________" << endl;

        // subject.m_disp.~Dispatcher();

        Observer3 obs6(subject);
        subject.ChangState(9,9);
        cout << "______________________________" << endl;

        Changer changer(subject);
        changer.Change(10,10);
        cout << "______________________________" << endl;

        // changer.Delete(summ);
        obs1.SelfDelete();
        changer.Change(10,10);
        cout << "______________________________" << endl;
        changer.Change(5,9);
        cout << "______________________________" << endl;
    }
    
    return 0;
}