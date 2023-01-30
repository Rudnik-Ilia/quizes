#include <iostream>

class B
{
    public:
        static int count;
        B() 
        {
            std::cout <<  ++count << std::endl;
        }
        ~B() 
        {
            std::cout <<  ++count << std::endl;
        }
        int x;
        int y;
    
};
int B::count = 0;

int main()
{
	B arr1[100];
	B *arr2 = new B[100];
	delete[] arr2;

	return 0;
}