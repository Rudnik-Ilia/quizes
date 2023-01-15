#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

// #include <stdio.h>

    enum E
    {
        AA, BB, CC ,DD
    };

    enum E2
    {
        TT, KK
    };
  
    enum E s;
    enum E q;
    enum E u;
    bool b3;




    // typedef struct List {


    // }List_t;

    // typedef struct Person{
    //     int age;
    // } Person_t;

    // void foo(List_t* ll, int key, int age)
    // {
    //     // void *vv = ll_find(ll, key);
    //     void *vv;
    //     // Person_t *p = (Person_t *)ll;

    //     Person_t *p = static_cast<Person_t *>(ll);

    //     // p->age = age;
    // }

    void Default_f(int x,  int y = 1, int a = 2 )
    {
        std::cout << x << y << a << std::endl;
      
    }

    void Foo(int *x)
    {
        std::cout << x << std::endl;
    }
    void Foo(float x)
    {
         std::cout << x << std::endl;
    }
    void Foo(unsigned char x)
    {
         std::cout << x << std::endl;

    }
    void Foo(char x)
    {
         std::cout << x << std::endl;

    }
    void Foo(void* x)
    {
         std::cout << x << std::endl;

    }


    // void invoke_method(char *lib, char *method, int x, int y)
    // {
    //     void *dl_handle;
    //     int (*func)(int, int);
    //     char *error;
    
    //     dl_handle = dlopen(lib, RTLD_LAZY);
    //     if (!dl_handle) {
    //         std::cout << "ERROR1" << std::endl;
    //         return;
    //     }

        
    //     *(void**)&func = dlsym(dl_handle, method);
    //     error = dlerror();
    //     if (error != NULL) {
    //         std::cout << "ERROR2" << std::endl;
    //         return;
    //     }

    
    //     std::cout << (*func)(x,y) << std::endl;

        
    //     dlclose( dl_handle );

    // return;
    // }

int main()
{   
    // int const*(*const  f)(int*) = foo;
    
  
    // std::cout << s << std::endl;
    // std::cout << q << std::endl;
    // std::cout << u << std::endl;

    // enum E e = (E)2;
    // enum E2 e2 = (E2)AA;
    // // dd dd;

    // // ++e;

    // int i = e;
    // ++i;
    // std::cout << i << std::endl;


    
    // bool b1 = true;
    // bool b2 ;

    // int i = b1;
    // long l = 100;
    // i = 7; 
    // b2 = i != 0;
  
    
    // std::cout << sizeof(b1) << std::endl;
    // std::cout << sizeof(b2) << std::endl;
    // std::cout << b2 << std::endl;
    // std::cout << sizeof(i) << std::endl;
    // std::cout << sizeof(l) << std::endl;
    

    // const int a = 0;
    // const int *pa = &a;

    // int *p = const_cast<int*>(pa);
    // *p = 1;  // undefined behavior ??
    // std::cout << a << *p; 

    // std::cout << Foo() << std::endl;

    // for(int i = 0; i < 10; ++i){
    //     int a = 0;

    //     std::cout << a+i << std::endl;
    // }

    // void *v = new int(50);
    // void *x = (int*)malloc(4);
    // *(int*)x = 40;

    // std::cout << *(int*)v << std::endl;
    // std::cout << *(int*)x << std::endl;

    // free(x);
    // delete (int*)v;
    // free(x);

    // long *p = new(std::nothrow) long[10];

    // if(NULL == p){
    //     std::cout << "!!!!" << std::endl;
    // }

    // int *a = new int(0);

    // free(a);

    // int i = 0;

    // std:: cout << "fjkdf" << i << std:: endl;
    // std:: cin >> i;
    // std:: cerr << "Hhhjdhc" << i;

    // Default_f();
    // Default_f(7);
    // Default_f(7,7);

    //   int i = 1;
    //   int *ptr = NULL;

    //    Foo(NULL);
    //    Foo(static_cast<void>(NULL));
    //    Foo(8.0f);
    //    Foo(static_cast<char>('i'));
//    invoke_method("./libaddsub.so", "_Z3Subii", 99, 3);
   
    return 0;
}


int  Foo(){
    return 1;
}