

/* Joses task about solgers*/
int JosesProblem(int arr[], int len);
/* print vars and their size*/
void PrintVar();

void Test_SummArray();
/* sum rows in 2d array*/
int *SummArray(int *arr, int row, int col);
/*free memory after CreateArrayFromVar*/
void FreeMemory(char **arr, int len);
/* create dinamic 2d array*/
char **CreateArrayFromVar(char *env[]);
