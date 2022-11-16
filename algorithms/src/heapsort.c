


#include <stdio.h>



void heapify(int[], int, int);
void heapsort(int[], int);
void printarray(int[], int);
void scanarray(int[], int);
void swap(int *, int *);

int main()
{
    int a[50];
    int n;
    printf("Enter no. of elements : ");
    scanf("%d", &n);
    scanarray(a, n);
    printarray(a, n);
    
    heapsort(a, n);
    
    printf("\nAfter sorting:\n");
    printarray(a, n);
    
    return 0;
}

void scanarray(int a[], int n)
{
    int i;
    printf("Enter %d elements :\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
}
void printarray(int a[], int n)
{
    int i;
    printf("The array is :\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t", a[i]);
    }
}


void heapify(int a[], int n, int i)
{
    int largest = i;   /* largest element index */
    int l = 2 * i + 1; /* left element index */
    int r = 2 * i + 2; /* right element index */

    if (l < n && a[l] > a[largest])
    {
        largest = l;
    }
    if (r < n && a[r] > a[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}
void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
void heapsort(int a[], int n)
{
    int i;
    for (i = (n / 2) - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }
    for (i = n - 1; i >= 0; i--)
    {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}


