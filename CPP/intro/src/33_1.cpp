#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
using namespace std;

void my_terminate()
{
    cout<< "TERMINATION---------------------------------------" << endl;
    throw;
}


int main()
{
    set_terminate(my_terminate);
    // set_unexpected(my_terminate);q

    throw runtime_error("hhhh");

    return 0;
}