#include <stdio.h>
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
    this->publicBase._vptr = &PublicTransport_vtable;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
    return *this;

}
struct Minibus MinibusCopyCtor(struct Minibus* this, struct Minibus* other_)
{
    PublicTransportCopyCtor(&this->publicBase, &other_->publicBase);
	this->publicBase._vptr = NULL;
	printf("Minibus::CCtor()\n");
	this->m_numSeats = other_->m_numSeats;
	return *this;
}

void MinibusDtor(struct Minibus* this)
{
    printf("Minibus::Dtor()\n");
}

void MinibusWash(int min, struct Minibus* this) 
{
     printf("Minibus::wash(%d) ID: %d \n", min, get_id((struct PublicTransport*)this));
}
void MinibusDisplay(struct Minibus* this)
{
    printf("Minibus::display() ID: %d\n", get_id((struct PublicTransport*)this));
    printf("num seats: %d\n", this->m_numSeats);
}

/*********TAXI****************************************************************/

struct TaxiPtr
{
    
};

struct Taxi
{
    struct PublicTransportPtr* _vptr;
};


/*********SPECIAL TAXI********************************************************/

struct SpecialTaxiPtr
{

};

struct SpecialTaxi
{
    struct PublicTransportPtr* _vptr;
};




int main()
{
   struct PublicTransport p;
   PublicTransportCtor(&p);
   p._vptr->display(&p);


   struct Minibus m;
   MinibusCtor(&m);
   MinibusDisplay(&m);






    return 0;
}