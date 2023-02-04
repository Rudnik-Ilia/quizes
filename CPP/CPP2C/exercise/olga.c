/*
# Title : CPP2C
# Author : Olga
# Reviewer : Ilia
# Review status : Sent to reviewer
# Data : 01.02.2022
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TEMPLATE_MAX(T) T max_##T(T a, T b){ return a > b ? a : b;} 
TEMPLATE_MAX(int)

static int s_count = 0;

/****** PublicTransport CLASS ******/
typedef struct public_transport public_transport_t;
typedef struct vtable_pt
{
    void (*func_dtor)(public_transport_t*);
    void (*func_cctor)(public_transport_t*, public_transport_t*);
    void (*func_display)(public_transport_t*);
}vtable_pt_t;

void PTCtor(public_transport_t *obj);
void PTDtor(public_transport_t *obj);
void PTCctor(public_transport_t *obj1, public_transport_t *obj2);
void PTDisplay(public_transport_t *obj1);

vtable_pt_t vptr_pt = {PTDtor, PTCctor, PTDisplay};

struct public_transport
{
    vtable_pt_t *pt_table;
    int m_license_plate;
};

static int GetID(public_transport_t *obj)
{
    return obj->m_license_plate;
}

static void PTPrintCount()
{   
    printf("s_count: %d\n", s_count);     
}

void PTCtor(public_transport_t *obj)
{
    obj->pt_table = &vptr_pt;
    obj->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor()%d\n", obj->m_license_plate);
}

void PTDtor(public_transport_t *obj)
{
    --s_count;
    printf("PublicTransport::Dtor()%d\n", obj->m_license_plate);
}

void PTCctor(public_transport_t *obj1, public_transport_t *obj2)
{
    obj1->pt_table = obj2->pt_table;
    obj1->m_license_plate = ++s_count;
    printf("PublicTransport::CCtor() %d\n", obj1->m_license_plate);  
}

void PTDisplay(public_transport_t *obj1)
{
    printf("PublicTransport::display(): %d\n", obj1->m_license_plate);     
}

/****** Minibus CLASS ******/
typedef struct minibus minibus_t;
typedef struct vtable_minibus
{
    void (*func_dtor)(minibus_t *);
    void (*func_cctor)(minibus_t *, minibus_t *);
    void (*func_display)(minibus_t*);
    void (*func_wash)(minibus_t*, int);
}vtable_minibus_t;

void MinibusCtor(minibus_t *obj);
void MinibusDtor(minibus_t *obj);
void MinibusCctor(minibus_t *obj1, minibus_t *obj2);
void MinibusDisplay(minibus_t *obj1);
void MinibusWash(minibus_t *obj, int minutes);

vtable_minibus_t vptr_minibus = {MinibusDtor, MinibusCctor, MinibusDisplay, MinibusWash};

struct minibus
{
    vtable_minibus_t *minibus_table;
    int m_license_plate;
    int m_num_seats;
};

void MinibusCtor(minibus_t *obj)
{
    PTCtor((public_transport_t*)obj);
    obj->minibus_table = &vptr_minibus;
    obj->m_num_seats = 20;
    puts("Minibus::Ctor()");
}

void MinibusDtor(minibus_t *obj)
{
    puts("Minibus::Dtor()");
    PTDtor((public_transport_t*)obj);
}

void MinibusCctor(minibus_t *obj1, minibus_t *obj2)
{
    PTCctor((public_transport_t*)obj1, (public_transport_t*)obj2);    
    obj1->m_num_seats = obj2->m_num_seats;
}

void MinibusDisplay(minibus_t *obj1)
{
    printf("Minibus::display() ID:%d", GetID((public_transport_t*)obj1));
    printf(" num seats:%d\n",obj1->m_num_seats);
}

void MinibusWash(minibus_t *obj, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, GetID((public_transport_t*)obj));
}

/****** Taxi CLASS ******/
typedef struct taxi taxi_t;
typedef struct vtable_taxi
{
    void (*func_dtor)(taxi_t *);
    void (*func_cctor)(taxi_t *, taxi_t *);
    void (*func_display)(taxi_t*);
}vtable_taxi_t;

void TaxiCtor(taxi_t *obj);
void TaxiDtor(taxi_t *obj);
void TaxiCctor(taxi_t *obj1, taxi_t *obj2);
void TaxiDisplay(taxi_t *obj1);

vtable_taxi_t vptr_taxi = {TaxiDtor, TaxiCctor, TaxiDisplay};

struct taxi
{
    vtable_taxi_t *taxi_table;
    int m_license_plate;
};

void TaxiCtor(taxi_t *obj)
{
    PTCtor((public_transport_t*)obj);
    obj->taxi_table = &vptr_taxi;
    puts("Taxi::Ctor()");
}

void TaxiDtor(taxi_t *obj)
{
    puts("Taxi::Dtor()");
    PTDtor((public_transport_t*)obj);    
}

void TaxiCctor(taxi_t *obj1, taxi_t *obj2)
{ 
    PTCctor((public_transport_t*)obj1, (public_transport_t*)obj2); 
    puts("Taxi::CCtor()");    
}

void TaxiDisplay(taxi_t *obj1)
{
    printf("Taxi::display() ID:%d\n", GetID((public_transport_t*)obj1));
}

/****** SpecialTaxi CLASS ******/
typedef struct special_taxi special_taxi_t;
typedef struct vtable_special_taxi
{
    void (*func_dtor)(special_taxi_t *);
    void (*func_cctor)(special_taxi_t *, special_taxi_t *);
    void (*func_display)(special_taxi_t*);
}vtable_special_taxi_t;

void SpecialTaxiCtor(special_taxi_t *obj);
void SpecialTaxiDtor(special_taxi_t *obj);
void SpecialTaxiCctor(special_taxi_t *obj1, special_taxi_t *obj2);
void SpecialTaxiDisplay(special_taxi_t *obj1);

vtable_special_taxi_t vptr_special_taxi = {SpecialTaxiDtor, SpecialTaxiCctor, SpecialTaxiDisplay};

struct special_taxi
{
    vtable_special_taxi_t *special_taxi_table;
    int m_license_plate;
};

void SpecialTaxiCtor(special_taxi_t *obj)
{
    TaxiCtor((taxi_t *)obj);
    obj->special_taxi_table = &vptr_special_taxi;
    puts("SpecialTaxi::Ctor()");
}

void SpecialTaxiDtor(special_taxi_t *obj)
{
    puts("SpecialTaxi::Dtor()");
    TaxiDtor((taxi_t *)obj);
}

void SpecialTaxiCctor(special_taxi_t *obj1, special_taxi_t *obj2)
{
    TaxiCctor((taxi_t *)obj1, (taxi_t *)obj2);
    obj1->special_taxi_table = obj2->special_taxi_table;
    puts("SpecialTaxi::CCtor()");
} 

void SpecialTaxiDisplay(special_taxi_t *obj1)
{
    printf("SpecialTaxi::display() ID:%d\n", GetID((public_transport_t*)obj1));
}

/****** PublicConvoy CLASS ******/
typedef struct public_convoy public_convoy_t;
typedef struct vtable_public_convoy
{
    void (*func_dtor)(public_convoy_t *);
    void (*func_cctor)(public_convoy_t *, public_convoy_t *);
    void (*func_display)(public_convoy_t*);
}vtable_public_convoy_t;

void PublicConvoyCtor(public_convoy_t *obj);
void PublicConvoyDtor(public_convoy_t *obj);
void PublicConvoyCctor(public_convoy_t *obj1, public_convoy_t *obj2);
void PublicConvoyDisplay(public_convoy_t *obj1);

vtable_public_convoy_t vptr_public_convoy = {PublicConvoyDtor, PublicConvoyCctor, PublicConvoyDisplay};

struct public_convoy
{
    vtable_public_convoy_t *public_convoy_table;
    int m_license_plate;
    public_transport_t *m_ptr1;
    public_transport_t *m_ptr2;
    minibus_t m_m;
    taxi_t m_t;
};

void PublicConvoyCtor(public_convoy_t *obj)
{
    PTCtor((public_transport_t*)obj);
    obj->public_convoy_table = &vptr_public_convoy;

    obj->m_ptr1 = malloc(sizeof(minibus_t));
    MinibusCtor((minibus_t *)obj->m_ptr1);

    obj->m_ptr2 = malloc(sizeof(taxi_t));
    TaxiCtor((taxi_t *)obj->m_ptr2);

    MinibusCtor(&obj->m_m);
    TaxiCtor(&obj->m_t);
    puts("PublicConvoy::Ctor()");
}

void PublicConvoyDtor(public_convoy_t *obj)
{
    MinibusDtor((minibus_t *)obj->m_ptr1);
    free(obj->m_ptr1);
    TaxiDtor((taxi_t *)obj->m_ptr2);
    free(obj->m_ptr2);   
    TaxiDtor(&obj->m_t);
    MinibusDtor(&obj->m_m);
    PTDtor((public_transport_t *)obj); 
}

void PublicConvoyCctor(public_convoy_t *obj1, public_convoy_t *obj2)
{   
    PTCctor((public_transport_t *)obj1, (public_transport_t *)obj2);
    obj1->public_convoy_table = obj2->public_convoy_table;

    MinibusCtor(&obj1->m_m);
    TaxiCtor(&obj1->m_t);

    obj1->m_ptr1 = malloc(sizeof(minibus_t));
    MinibusCtor((minibus_t *)obj1->m_ptr1);

    obj1->m_ptr2 = malloc(sizeof(taxi_t));
    TaxiCtor((taxi_t *)obj1->m_ptr2);

    puts("PublicConvoy::Cctor()");  
}
void PublicConvoyDisplay(public_convoy_t *obj1)
{
    obj1->m_ptr1->pt_table->func_display(obj1->m_ptr1);
    obj1->m_ptr2->pt_table->func_display(obj1->m_ptr2);
    obj1->m_m.minibus_table->func_display(&obj1->m_m);
    obj1->m_t.taxi_table->func_display(&obj1->m_t);
    puts("PublicConvoy::display()");
}

/****** GLOBAL FUNCS ******/
void PrintInfoPT(public_transport_t *a)
{
    a->pt_table->func_display(a);
}

void PrintInfo()
{
    PTPrintCount();    
}

void PrintInfoMinibus(minibus_t *m)
{
    m->minibus_table->func_wash(m, 3);
}


public_transport_t PrintInfoPT2(int i)
{
    minibus_t ret;
    public_transport_t pt;

    (void)i;

    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    ret.minibus_table->func_display(&ret);
    PTCctor(&pt, (public_transport_t *)&ret);
    pt.pt_table = &vptr_pt;
    ret.minibus_table->func_dtor(&ret);
    return pt;
}


/****** ADD FUNCS ******/
static void Taxi_Display(taxi_t *s)
{
    taxi_t s2;
    TaxiCctor(&s2, s);
    s2.taxi_table = &vptr_taxi;
    s2.taxi_table->func_display(&s2);
    s2.taxi_table->func_dtor(&s2);
}


static void InitMinibus(public_transport_t* obj)
{
    minibus_t mb;
    MinibusCtor(&mb);
    PTCctor(obj, (public_transport_t *)&mb);
    obj->pt_table = &vptr_pt;
    mb.minibus_table->func_dtor(&mb);
}

static void InitTaxi(public_transport_t* obj)
{
    taxi_t t;
    TaxiCtor(&t);
    PTCctor(obj, (public_transport_t *)&t);
    t.taxi_table->func_dtor(&t);
}


int main()
{
    int fd;
    char *name = "c.txt"; 
    
    minibus_t m;
    public_transport_t pt;

    public_transport_t *array[3];
    public_transport_t array2[3];

    minibus_t m2;

    minibus_t array3[4];
    taxi_t *array4 = NULL;

    special_taxi_t st;

    public_convoy_t *ts1;
    public_convoy_t *ts2;

    int i = 0;

     fd = open(name, O_WRONLY | O_CREAT, 0644);
    
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    if (dup2(fd, 1) == -1) {
        perror("dup2 failed"); 
        exit(1);
    } 

    MinibusCtor(&m);
    PrintInfoMinibus(&m);

    pt = PrintInfoPT2(3);
    pt.pt_table->func_display(&pt);
    pt.pt_table->func_dtor(&pt);
 
    array[0] = malloc(sizeof(minibus_t));
    array[1] = malloc(sizeof(taxi_t));
    array[2] = malloc(sizeof(minibus_t));
    MinibusCtor((minibus_t *)array[0]);
    TaxiCtor((taxi_t *)array[1]);
    MinibusCtor((minibus_t *)array[2]);

    for(; i < 3; ++i)
    {
        (array[i]->pt_table)->func_display(array[i]);
    }

    for(i = 0; i < 3; ++i)
    {
        array[i]->pt_table->func_dtor(array[i]);
        free(array[i]);
    }

    InitMinibus((public_transport_t *)&array2[0]);
    InitTaxi((public_transport_t *)&array2[1]);
    PTCtor((public_transport_t *)&array2[2]);

    for(i = 0; i < 3; ++i)
    {
        PTDisplay(&array2[i]);
    }
    PrintInfoPT(&array2[0]);

    PTPrintCount();

    MinibusCtor(&m2);
    PTPrintCount();

    for(i = 0; i < 4; ++i)
    {
        MinibusCtor(&array3[i]);
    }

    array4 = malloc(4 * sizeof(taxi_t));
    for(i = 0; i < 4; ++i)
    {
        TaxiCtor(&array4[i]);
    }   

    for(i = 3; i >= 0; --i)
    {
        TaxiDtor(&array4[i]);
    } 
    free(array4);

    printf("%d\n", max_int(1, 2));
    printf("%d\n", max_int(1, 2.0f));

    SpecialTaxiCtor(&st);

    Taxi_Display((taxi_t *)&st);

    ts1 = malloc(sizeof(public_convoy_t));
    PublicConvoyCtor(ts1);
    ts2 = malloc(sizeof(public_convoy_t));
    PublicConvoyCctor(ts2, ts1);
    ts1->public_convoy_table->func_display(ts1);
    ts2->public_convoy_table->func_display(ts2);
    PublicConvoyDtor(ts1);
    free(ts1);
    ts2->public_convoy_table->func_display(ts2);
    PublicConvoyDtor(ts2);
    free(ts2);    

    st.special_taxi_table->func_dtor(&st);

    for(i = 3; i >= 0; --i)
    {
        array3->minibus_table->func_dtor(&array3[i]);
    }

    m2.minibus_table->func_dtor(&m2);

    for(i = 2; i >= 0; --i)
    {
        PTDtor(&array2[i]);
    }

    m.minibus_table->func_dtor(&m);

     close(fd); 

    return 0;
}

