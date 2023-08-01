#include <iostream>
#include <string>

size_t GetHash(const std::string& str) 
{
    size_t hash = 123;

    for (char ch : str) 
    {
        hash = (hash << 5) + ch;
    }
    return hash;
}

unsigned int GetHash2(const char* str) {
    unsigned int hash = 123;

    while (*str) {
        hash = (hash << 5) + *str;
        str++;
    }

    return hash;
}

void CheckPassword() 
{
    char input[112];
    
    printf("Enter password: ");
    fflush(stdout);
    
    fgets(input, sizeof(input), stdin);
    
    // putchar('\n');
    
    unsigned int hash = GetHash(input);
    std::cout << std::hex << GetHash(input)<< std::endl;
    
    unsigned long long targetHash = 0x0000000007c94e6a;
    
    if (hash == targetHash) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }
}
int main() 
{
    size_t one = 0x00000000003e4a73;
    std::cout << std::hex << (GetHash("123")  ==  one )<< std::endl;
    std::cout << std::hex << (GetHash2("123        ")  ==  one )<< std::endl;

    CheckPassword();


 

    return 0;
}