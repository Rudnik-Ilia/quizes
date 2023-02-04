#include <stdio.h>
#include <stdlib.h>
#include "cpp2c.h"
#define max_func(t1, t2) ((t1 > t2) ? t1 : t2)
static int s_count;


/*********PUBLIC**************************************************************/

struct PublicTransportPtr PublicTransport_vtable =
{
    &PublicTransportDtor,
    &display
};

/******/

struct PublicTransport PublicTransportCtor(struct PublicTransport* this)
{
    this->_vptr = &PublicTransport_vtable;
    this->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
    return *this;

};


void PublicTransportDtor(struct PublicTransport* this)
{
    this->_vptr = &PublicTransport_vtable;
    --s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
    
}


struct PublicTransport PublicTransportCopyCtor(struct PublicTransport* this, struct PublicTransport* other_ )
{
    this->_vptr = &PublicTransport_vtable;
    this->m_license_plate = ++s_count;
    printf("PublicTransport::CCtor()%d\n", this->m_license_plate);
    return *this;
}

void display(struct PublicTransport* this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void print_count()
{
    printf("s_count:  %d\n", s_count);
}

int get_id(struct PublicTransport* this)
{
    return this->m_license_plate;
}

/*********MINIBUS*************************************************************/

struct MinibusPtr Minibus_vtable = 
{
    &MinibusDtor,
    &MinibusDisplay,
    &MinibusWash
};

struct Minibus MinibusCtor(struct Minibus* this)
{
    PublicTransportCtor(&this->publicBase);
    this->publicBase._vptr = (BaseClassPtr *)&Minibus_vtable;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
    return *this;
}

struct Minibus MinibusCopyCtor(struct Minibus* this, struct Minibus* other_)
{
    PublicTransportCopyCtor(&this->publicBase, &other_->publicBase);
	this->publicBase._vptr = (BaseClassPtr *)&Minibus_vtable;
	printf("Minibus::CCtor()\n");
	this->m_numSeats = other_->m_numSeats;
	return *this;
}

void MinibusDtor(struct Minibus* this)
{
    this->publicBase._vptr = (BaseClassPtr *)&Minibus_vtable;
	printf("Minibus::Dtor()\n");
	PublicTransportDtor(&this->publicBase);
}

void MinibusWash(int min, struct Minibus* this) 
{
     printf("Minibus::wash(%d) ID: %d \n", min, get_id((struct PublicTransport*)this));
}

void MinibusDisplay(struct Minibus* this)
{
    printf("Minibus::display() ID: %d ", get_id((struct PublicTransport*)this));
    printf("num seats: %d\n", this->m_numSeats);
}

/*********TAXI****************************************************************/


struct TaxiPtr Taxi_vtable = 
{
    &TaxiDtor,
    &TaxtDisplay
};

struct Taxi TaxiCtor(struct Taxi* this)
{
    PublicTransportCtor(&this->publicBase);
    this->publicBase._vptr = (BaseClassPtr *)&Taxi_vtable;
    printf("Taxi::Ctor()\n");
    return *this;
}
struct Taxi TaxiCopyCtor(struct Taxi* this, struct Taxi *other_)
{
    PublicTransportCopyCtor(&this->publicBase, &other_->publicBase);
    this->publicBase._vptr = (BaseClassPtr *)&Taxi_vtable;
    printf("Taxi::CCtor()\n");
    return *this;
}

void TaxiDtor(struct Taxi* this)
{
    this->publicBase._vptr = (BaseClassPtr *)&Taxi_vtable;
    printf("Taxi::Dtor()\n");
    PublicTransportDtor(&this->publicBase);
}

void TaxtDisplay(struct Taxi* this)
{
    printf("Taxi::display() ID: %d\n", get_id(&this->publicBase));
}

/*********SPECIAL TAXI********************************************************/


struct SpecialTaxiPtr SpecialTaxi_vtable =
{
    &SpecialTaxiDtor,
    &SpecialTaxiDisplay
};

struct SpecialTaxi SpecialTaxiCtor(struct SpecialTaxi* this)
{
    TaxiCtor(&this->taxiBase);
    this->taxiBase.publicBase._vptr = (BaseClassPtr *)&SpecialTaxi_vtable;
    printf("SpecialTaxi::Ctor()\n");
    return *this;
}

struct SpecialTaxi SpecialTaxiCopyCtor(struct SpecialTaxi* this, struct SpecialTaxi other_)
{
    TaxiCopyCtor(&this->taxiBase, &other_.taxiBase);
    this->taxiBase.publicBase._vptr = (BaseClassPtr *)&SpecialTaxi_vtable;
    printf("SpecialTaxi::CCtor()\n");
    return *this;
}

void SpecialTaxiDtor(struct SpecialTaxi* this)
{
    this->taxiBase.publicBase._vptr = (BaseClassPtr *)&SpecialTaxi_vtable;
    printf("SpecialTaxi::Dtor()\n");
    TaxiDtor(&this->taxiBase);
}

void SpecialTaxiDisplay(struct SpecialTaxi* this)
{
    printf("SpecialTaxi::display() ID: %d \n", get_id(&this->taxiBase.publicBase));
}

/***********************************************************************/

void PublicTransport_print_info(struct PublicTransport *a)
{
    a->_vptr->Display(a);
}

void print_info()
{
    print_count();
}

void Minibus_print_info(struct Minibus *m)
{
    ((MinPtr *)(m->publicBase._vptr))->MinibusWash(3, m);
}

struct PublicTransport Public_print_info(int i)
{
    struct PublicTransport p;
    struct Minibus ret;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    ((MinPtr *)(ret.publicBase._vptr))->Display(&ret);
    PublicTransportCopyCtor(&p, &ret.publicBase);
    MinibusDtor(&ret);
    return p;
}

void taxi_display(struct Taxi* s)
{
    ((TaxPrtr *)(s->publicBase._vptr))->Display(s);
}
/**********************************/

// struct PublicConvoy
// {
//     struct PublicTransport publicBase;
//     struct PublicTrasport *m_ptr1;
// 	struct PublicTrasport *m_ptr2;
//     struct Minibus m_m;
//     struct Taxi m_t;
// };


// struct PublicConvoyPtr
// {
//     void (*const Dtor)(struct PublicConvoy *const);
// 	    void (*const Display)(struct PublicConvoy *const);
// };

struct PublicConvoyPtr PublicConvoy_vtable = 
{
    &PublicConvoyDtor,
	&PublicConvoyDisplay
};

struct PublicConvoy PublicConvoyCtor(struct PublicConvoy* this)
{
    PublicTransportCtor(&this->publicBase);
    this->publicBase._vptr = (BaseClassPtr *)&PublicConvoy_vtable;

    this->m_ptr1 = malloc(sizeof(struct Minibus));
    MinibusCtor((struct Minibus*)this->m_ptr1);

    this->m_ptr2 = malloc(sizeof(struct Taxi));
    TaxiCtor((struct Taxi*)this->m_ptr2);

    MinibusCtor(&this->m_m);
    TaxiCtor(&this->m_t);

    return *this;
}

struct PublicConvoy PublicConvoyCopyCtor(struct PublicConvoy* this, struct PublicConvoy* other_)
{
    PublicTransportCopyCtor(&this->publicBase, &other_->publicBase);
    this->publicBase._vptr = (BaseClassPtr *)&PublicConvoy_vtable;

    this->m_ptr1 = malloc(sizeof(struct Minibus));
    MinibusCtor((struct Minibus*)this->m_ptr1);

    this->m_ptr2 = malloc(sizeof(struct Taxi));
    TaxiCtor((struct Taxi*)this->m_ptr2);

    MinibusCopyCtor(&this->m_m, &other_->m_m);
    TaxiCopyCtor(&this->m_t, &other_->m_t);
    
    return *this;
}

void PublicConvoyDtor(struct PublicConvoy* this)
{
    this->publicBase._vptr = (BaseClassPtr *)&PublicConvoy_vtable;

    this->m_ptr1->_vptr->Dtor(this->m_ptr1);
    free(this->m_ptr1);

    this->m_ptr2->_vptr->Dtor(this->m_ptr2);
    free(this->m_ptr2);

	TaxiDtor(&this->m_t);
	MinibusDtor(&this->m_m);

	PublicTransportDtor(&this->publicBase);
}

void PublicConvoyDisplay(struct PublicConvoy *this)
{   
	this->m_ptr1->_vptr->Display(this->m_ptr1);
	this->m_ptr2->_vptr->Display(this->m_ptr2);

	MinibusDisplay(&this->m_m);
	TaxtDisplay(&this->m_t);
}


int main()
{
    struct Minibus m;
    MinibusCtor(&m);
    Minibus_print_info(&m);

    struct PublicTransport p;
    
    p = Public_print_info(3);
    p._vptr->Display(&p);
    PublicTransportDtor(&p);

    struct PublicTransport *arr[3] = 
    {
        malloc(sizeof(struct Minibus)),
        malloc(sizeof(struct Taxi)),
        malloc(sizeof(struct Minibus))
    };

    MinibusCtor((struct Minibus *)arr[0]);
    TaxiCtor((struct Taxi *)arr[1]);
    MinibusCtor((struct Minibus *)arr[2]);


    for (int i = 0; i < 3; ++i) {
        arr[i]->_vptr->Display(arr[i]);
    }

    for (int i = 0; i < 3; ++i) {

        arr[i]->_vptr->Dtor(arr[i]);
        free(arr[i]);
    }

    struct PublicTransport arr2[3];

	struct Minibus mm;
	MinibusCtor(&mm);
	PublicTransportCopyCtor(&arr2[0] , &m.publicBase);
	MinibusDtor(&mm);
    
    struct Taxi t;
	TaxiCtor(&t);
	PublicTransportCopyCtor(&arr2[1], &t.publicBase);
	TaxiDtor(&t);

    PublicTransportCtor(&arr2[2]);

	for(int i = 0; i < 3; ++i)
	{
		display(&arr2[i]);
	}
	
	PublicTransport_print_info(&arr2[0]);
	print_count();
	struct Minibus m2;
	MinibusCtor(&m2);
	print_count();


    struct Minibus arr3[4];
	for(int i = 0; i < 4; ++i)
	{
		MinibusCtor(&arr3[i]);
	}

    struct Taxi *arr4 = malloc(sizeof(struct Taxi) * 4);
	for (int i = 0; i < 4; ++i)
	{
		TaxiCtor(&arr4[i]);
	}
	for(int i = 3; i >=0; --i)
	{
		TaxiDtor(&arr4[i]);
	}
	free(arr4);

    printf("%d\n",max_func(1, 2));
	printf("%d\n",max_func(1, 2.0));

    struct SpecialTaxi st;
	SpecialTaxiCtor(&st);
	struct Taxi tempp;
	TaxiCopyCtor(&tempp, &st.taxiBase);
	TaxtDisplay(&tempp);
	TaxiDtor(&tempp);


    struct PublicConvoy *ts1 = malloc(sizeof(struct PublicConvoy));
	PublicConvoyCtor(ts1);

    struct PublicConvoy *ts2 = malloc(sizeof(struct PublicConvoy));
	PublicConvoyCopyCtor(ts2, ts1);
	ts1->publicBase._vptr->Display((struct PublicTransport*)ts1);
	ts2->publicBase._vptr->Display((struct PublicTransport*)ts2);
	PublicConvoyDtor(ts1);
	free(ts1);



    ts2->publicBase._vptr->Display((struct PublicTransport*)ts2);
	PublicConvoyDtor(ts2);
	free(ts2);

	SpecialTaxiDtor(&st);

	for(int i = 3; i >= 0; --i)
	{
		MinibusDtor(&arr3[i]);
	}

	MinibusDtor(&m2);
	PublicTransportDtor(&arr2[2]);
	PublicTransportDtor(&arr2[1]);
	PublicTransportDtor(&arr2[0]);
	MinibusDtor(&m); 




    return 0;
}