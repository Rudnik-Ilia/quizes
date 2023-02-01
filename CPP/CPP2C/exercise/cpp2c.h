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