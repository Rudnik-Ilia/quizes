#pragma once

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

