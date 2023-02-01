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
    void (*PublicTransportDtor) (struct PublicTransport* pub_trans);
    void (*display) (struct PublicTransport* pub_trans); 
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
    void (*MinibusWash) (int minutes, struct Minibus* this);
    void (*MinibusDisplay) (struct Minibus* this); 
    void (*MinibusDtor) (struct Minibus* this); 
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
    void (*TaxiDsplay)(struct Taxi* this);
    void (*TaxiDtor)(struct Taxi* this);
};


void TaxtDisplay(struct Taxi* this);
void TaxiDtor(struct Taxi* this);

struct SpecialTaxi
{
    struct Taxi taxiBase;
};

struct SpecialTaxiPtr
{
    void (*SpecialTaxiDisplay)(struct SpecialTaxi* this);
    void (*SpecialTaxiDtor)(struct SpecialTaxi* this);
};

void SpecialTaxiDisplay(struct SpecialTaxi* this);
void SpecialTaxiDtor(struct SpecialTaxi* this);