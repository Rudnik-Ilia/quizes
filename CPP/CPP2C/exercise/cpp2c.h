#pragma once

typedef struct PublicTransportPtr BaseClassPtr;
typedef struct MinibusPtr MinPtr;
typedef struct TaxiPtr TaxPrtr;

struct PublicTransport
{
    struct PublicTransportPtr* _vptr;
    int m_license_plate;
};

struct PublicTransportPtr
{
    void (*Dtor) (struct PublicTransport* pub_trans);
    void (*Display) (struct PublicTransport* pub_trans); 
};

void PublicTransportDtor(struct PublicTransport* this);
void display(struct PublicTransport* this);

struct Minibus
{
    struct PublicTransport publicBase;
    int m_numSeats;    
};

struct MinibusPtr
{
    void (*Dtor) (struct Minibus* this); 
    void (*Display) (struct Minibus* this); 
    
    void (*MinibusWash) (int minutes, struct Minibus* this);
};

void MinibusDtor(struct Minibus* this);
void MinibusWash(int min, struct Minibus* this);
void MinibusDisplay(struct Minibus* this);

struct Taxi
{
    struct PublicTransport publicBase;
};

struct TaxiPtr
{
    void (*Dtor)(struct Taxi* this);
    void (*Display)(struct Taxi* this);
};

void TaxtDisplay(struct Taxi* this);
void TaxiDtor(struct Taxi* this);

struct SpecialTaxi
{
    struct Taxi taxiBase;
};

struct SpecialTaxiPtr
{
    void (*Dtor)(struct SpecialTaxi* this);
    void (*Display)(struct SpecialTaxi* this);
};

void SpecialTaxiDisplay(struct SpecialTaxi* this);
void SpecialTaxiDtor(struct SpecialTaxi* this);


struct PublicConvoy
{
    struct PublicTransport publicBase;
    struct PublicTransport *m_ptr1;
	struct PublicTransport *m_ptr2;
    struct Minibus m_m;
    struct Taxi m_t;
};


struct PublicConvoyPtr
{
    void (*const Dtor)(struct PublicConvoy *const);
	void (*const Display)(struct PublicConvoy *const);
};


void PublicConvoyDtor(struct PublicConvoy* this);
void PublicConvoyDisplay(struct PublicConvoy *this);