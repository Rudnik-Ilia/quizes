#include <stdio.h>

int main()
{
    int bytes = 0;
    int i = 0;
    FILE *file = fopen("ATM", "r+b");
    if(NULL == file)
    {
        printf("ERROR");
    };
    unsigned char code_74 = 0x74;
    unsigned char code_05 = 0x05;

    unsigned char code_75 = 0x75;
    unsigned char code_af = 0xaf;
   
    size_t code_big = 0x0000000007c94e6a;

    unsigned char code_c9 = 0xc9;
    unsigned char code_c3 = 0xc3;
   
 
    /*SWAP OPCODES***************************************/
    fseek(file, 0x000887, SEEK_SET);
    bytes =  fwrite(&code_74, sizeof(code_74), 1, file);
    fseek(file, 0x000888, SEEK_SET);
    bytes =  fwrite(&code_05, sizeof(code_05), 1, file);


    fseek(file, 0x0008a3, SEEK_SET);
    bytes =  fwrite(&code_75, sizeof(code_75), 1, file);
    fseek(file, 0x0008a4, SEEK_SET);
    bytes =  fwrite(&code_af, sizeof(code_af), 1, file);

    /*REPLASE original hash*********************************/
    fseek(file, 0x00087c, SEEK_SET);
    bytes =  fwrite(&code_big, sizeof(code_big), 1, file);




    fseek(file, 0x0008a5, SEEK_SET);
    bytes =  fwrite(&code_c9, sizeof(code_c9), 1, file);
    fseek(file, 0x0008a6, SEEK_SET);
    bytes =  fwrite(&code_c3, sizeof(code_c3), 1, file);

    // fseek(file, 0x00087e, SEEK_SET);
    // bytes =  fwrite(&code_01, sizeof(code_01), 1, file) ;


    printf("bytes: %d\n", bytes);
    fclose(file);
    return 0;
}