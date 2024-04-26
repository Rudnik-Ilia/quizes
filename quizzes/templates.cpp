#include <iostream>
#include <type_traits>


template <class T, bool>
struct Help
{
    static void ShowHelper(T const& x)
    {
        std::cout << "First: " << x << std::endl;
    }

};

template <class T>
struct Help<T, true>
{
    static void ShowHelper(T const& x)
    {
        std::cout << "First true: " << x << std::endl;
    }
};

template <class T>
struct Help<T, false>
{
    static void ShowHelper(T const& x)
    {
        std::cout << "First false: " << x << std::endl;
    }
};


template <class T>
void Show(T const& x)
{
    Help<T, std::is_pointer_v<T>>::ShowHelper(x);
}

template<typename... Args>
void Print(int Args, Args... rest)
{
    std::cout << Args << std::endl;
}


int main()
{
    int a = 1;

    int* p_a = NULL;

    p_a = &a;

    int b{1};

    Show(&a);
    Show(&b);
    Show(&p_a);

    Print(1, 2,3,4);


    return 0;
// template <class T>
// struct Help
// {
//     public:
//     static void ShowHelper<T, false>(T const& x)
//     {
//         std::cout << "First false: " << x << std::endl;
//     }
// };
}