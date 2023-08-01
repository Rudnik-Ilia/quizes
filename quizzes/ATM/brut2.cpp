#include <iostream>
#include <cstring>

unsigned int GetHash(const char* str) {
    unsigned int hash = 123;

    while (*str) {
        hash = (hash << 5) + *str;
        str++;
    }

    return hash;
}

void generateCombinations(char* input, int pos, unsigned int targetHash, int inputLength) {
    const int ASCII_RANGE_START = 32;  // Space character
    const int ASCII_RANGE_END = 126;   // Tilde character

    if (pos == inputLength) {
        if (GetHash(input) == targetHash) {
            std::cout << "Matching input string found: " << input << std::endl;
        }
        return;
    }

    for (int i = ASCII_RANGE_START; i <= ASCII_RANGE_END; i++) {
        input[pos] = static_cast<char>(i);
        generateCombinations(input, pos + 1, targetHash, inputLength);
    }
}

void findMatchingString(unsigned int targetHash, int inputLength) {
    char* input = new char[inputLength + 1];  // Dynamic allocation of input string
    std::memset(input, 0, inputLength + 1);   // Initialize the input string with null characters

    generateCombinations(input, 0, targetHash, inputLength);

    delete[] input;  // Deallocate the memory for input string
}

int main() {
    unsigned int targetHash = 0x9bcb5a2290403b1c;

    for (int length = 14; length <= 20; length++) {
        std::cout << "Searching for input string length " << length << ":" << std::endl;
        findMatchingString(targetHash, length);
        std::cout << std::endl;
    }

    return 0;
}