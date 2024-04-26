#include <iostream>
#include <vector>

class O1Array
{

public:
    O1Array(int size)
    {
        arr.resize(size, 0);
        isSet = false;
    }

    int getValue(int index)
    {
        if (index >= 0 && index < arr.size())
        {
            if (isSet)
            {
                return valueToSet;
            }
            else
            {
                return arr[index];
            }
        }
        return -1;
    }

    void setValue(int index, int value)
    {
        if (index >= 0 && index < arr.size())
        {
            arr[index] = value;
            isSet = false;
        }
    }

    void setAllValues(int value)
    {
        valueToSet = value;
        isSet = true;
    }

private:
    std::vector<int> arr;
    int valueToSet;
    bool isSet;
};

int main()
{
    O1Array arr(5);
    arr.setValue(0, 1);
    arr.setValue(1, 2);
    arr.setValue(2, 3);
    arr.setValue(3, 4);

    std::cout << "Before setting all values to 10:" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << arr.getValue(i) << " ";
    }

    std::cout << std::endl;

    arr.setAllValues(10);

    std::cout << "After setting all values to 10:" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << arr.getValue(i) << " ";
    }
    std::cout << std::endl;
    arr.setValue(3, 4);
    for (int i = 0; i < 5; ++i)
    {
        std::cout << arr.getValue(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
