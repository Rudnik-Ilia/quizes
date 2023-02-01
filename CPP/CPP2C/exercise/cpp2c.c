#include <stdio.h>
#include <stdlib.h>
#include "cpp2c.h"
#define max_func(t1, t2) ((t1 > t2) ? t1 : t2)
static int s_count;




/*********PUBLIC**************************************************************/

// struct PublicTransportPtr
// {
//     void (*PublicTransportDtor) (struct PublicTransport* pub_trans);
//     void (*display) (struct PublicTransport* pub_trans); 
// };

// struct PublicTransport
// {
//     struct PublicTransportPtr* _vptr;
//     int m_license_plate;
// };

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

// struct MinibusPtr
// {
//     void (*MinibusDisplay) (struct Minibus* this); 
//     void (*MinibusWash) (int minutes, struct Minibus* this);
//     void (*MinibusDtor) (struct Minibus* this); 
// };

// struct Minibus
// {
//     struct PublicTransport publicBase;
//     int m_numSeats;    
// };

struct MinibusPtr Minibus_vtable = 
{
    &MinibusWash,
    &MinibusDisplay,
    &MinibusDtor
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

// struct TaxiPtr
// {
//     void (*TaxiDsplay)(struct Taxi* this);
//     void (*TaxiDtor)(struct Taxi* this);
// };

// struct Taxi
// {
//     struct PublicTransport publicBase;
// };

struct TaxiPtr Taxi_vtable = 
{
    &TaxtDisplay,
    &TaxiDtor
};

struct Taxi TaxiCtor(struct Taxi* this)
{
    PublicTransportCtor(&this->publicBase);
    this->publicBase._vptr = (BaseClassPtr *)&Taxi_vtable;
    printf("Taxi::Ctor()\n");
    return *this;
}
struct Taxi TaxiCopyCtor(struct Taxi* this, struct Taxi* other_)
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

// struct SpecialTaxiPtr
// {
//     void (*SpecialTaxiDisplay)(struct SpecialTaxi* this);
//     void (*SpecialTaxiDtor)(struct SpecialTaxi* this);
// };

// struct SpecialTaxi
// {
//     struct Taxi taxiBase;
// };

struct SpecialTaxiPtr SpecialTaxi_vtable =
{
    &SpecialTaxiDisplay,
    &SpecialTaxiDtor
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
    a->_vptr->display(a);
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
    // PublicTransportCtor(&p);
    struct Minibus ret;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    ((MinPtr *)(ret.publicBase._vptr))->MinibusDisplay(&ret);
    PublicTransportCopyCtor(&p, &ret.publicBase);
    MinibusDtor(&ret);
    return p;
}

void taxi_display(struct Taxi* s)
{
    ((TaxPrtr *)(s->publicBase._vptr))->TaxiDsplay(s);
}


int main()
{
    struct Minibus m;
    MinibusCtor(&m);
    Minibus_print_info(&m);

    struct PublicTransport p;
    p = Public_print_info(3);
    p._vptr->display(&p);
    PublicTransportDtor(&p);

    // MinibusCtor(&m);
    // struct Taxi t;
    // TaxiCtor(&t);
    // PublicTransportCtor(&p);
    
    printf("___________________\n");
    struct PublicTransport * arr[3] = 
    {
        malloc(sizeof(struct Minibus)),
        malloc(sizeof(struct Taxi)),
        malloc(sizeof(struct Minibus))
    };
    printf("___________________\n");

    MinibusCtor((struct Minibus *)arr[0]);
    TaxiCtor((struct Taxi *)arr[1]);
    MinibusCtor((struct Minibus *)arr[2]);


    for (int i = 0; i < 3; ++i) {
        arr[i]->_vptr->display(arr[i]);
    }

    for (int i = 0; i < 3; ++i) {

        arr[i]->_vptr->PublicTransportDtor(arr[i]);
        free(arr[i]);
    }
    // struct PublicTrasport arr2[3];
	// struct Minibus mm;
	// MinibusCtor(&mm);
	// PublicCCtor(&arr2[0] , &m.public_obj);
	// MinibusDtor(&mm);
    













    // struct PublicTransport p;
    // PublicTransportCtor(&p);
    // p._vptr->display(&p);

    // MinibusCtor(&m);
    // MinibusDisplay(&m);

    // struct Taxi t;
    // TaxiCtor(&t);
    // TaxtDisplay(&t);

    // struct SpecialTaxi st;
    // SpecialTaxiCtor(&st);
    // SpecialTaxiDisplay(&st);


    // PublicTransport_print_info(&p);
    // print_info();
    // Minibus_print_info(&m);

    // taxi_display(&t);






    return 0;
}