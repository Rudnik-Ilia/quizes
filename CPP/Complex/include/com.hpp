#pragma once

#include <iostream>
#include <cmath> 
#include <exception> 
#include "complex.hpp"



namespace ilrd
{

const double DELTA = 0.00005f;

inline ComplexNum::ComplexNum(double r_, double i_): m_real(r_), m_imag(i_) {}

inline void ComplexNum::SetReal(const double real_) { m_real = real_; }
inline void ComplexNum::SetImag(const double imag_) { m_imag = imag_; }
inline double ComplexNum::GetReal() const { return m_real; }
inline double ComplexNum::GetImag() const { return m_imag; }


inline ComplexNum& ComplexNum::operator+=(const ComplexNum& other)
{
    m_real += other.m_real;
    m_imag += other.m_imag;
    return *this;
}

inline ComplexNum& ComplexNum::operator-=(const ComplexNum& other)
{
    m_real -= other.m_real;
    m_imag -= other.m_imag;
    return *this;
}

inline ComplexNum& ComplexNum::operator*=(const ComplexNum& other)
{
    m_real = m_real * other.m_real - m_imag * other.m_imag;
    m_imag = m_real * other.m_real + m_imag * other.m_imag;
    return *this;
}

inline ComplexNum& ComplexNum::operator/=(const ComplexNum& other)
{   
    double new_real = (this->m_real * other.m_real + this->m_imag * other.m_imag);
    double r_d =  pow(other.m_real, 2) + pow(other.m_imag, 2);

    double new_imag = (this->m_imag * other.m_real - this->m_real * other.m_imag);
    double i_d = pow(other.m_real, 2) + pow(other.m_imag, 2);

    if(r_d == 0 || i_d == 0)
    {
        throw std::logic_error("ZERO DIVISION, SORRY, TRY IT LATER!");
    }

    this->m_real = new_real / r_d;
    this->m_imag = new_imag / i_d;

    return *this;
}

inline ComplexNum operator+(const ComplexNum &lhs_, const ComplexNum &rhs_)
{
    return ComplexNum(lhs_) += rhs_;
}
inline ComplexNum operator-(const ComplexNum &lhs_, const ComplexNum &rhs_)
{
    return ComplexNum(lhs_) -= rhs_;
}
inline ComplexNum operator*(const ComplexNum &lhs_, const ComplexNum &rhs_)
{
    return ComplexNum(lhs_) *= rhs_;
}
inline ComplexNum operator/(const ComplexNum &lhs_, const ComplexNum &rhs_)
{
    return ComplexNum(lhs_) /= rhs_;
}
inline bool operator==(const ComplexNum &lhs_, const ComplexNum &rhs_)
{
    return fabs(lhs_.GetReal() - rhs_.GetReal()) < DELTA && fabs(lhs_.GetImag() - rhs_.GetImag()) < DELTA;
}
inline bool operator!=(const ComplexNum &lhs_, const ComplexNum &rhs_)
{
    return !(lhs_ == rhs_);
}

inline std::ostream &operator<<(std::ostream &os_, const ComplexNum &rhs_)
{
    os_ << rhs_.GetReal() << ((rhs_.GetImag() < 0) ? "-": "+" )<< fabs(rhs_.GetImag()) << "i";
    return os_;
}

inline std::istream &operator>>(std::istream &is_, ComplexNum &rhs_)
{
    double real, imag;
    is_ >> real; 
    is_ >> imag; 

    rhs_.SetReal(real);
    rhs_.SetImag(imag);
    
    return is_;
}


}