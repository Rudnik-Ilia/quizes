#ifndef __ILRD_RD132_COMPLEX_H__
#define __ILRD_RD132_COMPLEX_H__

#include <iostream>
#include <cmath> 

namespace ilrd
{

    class ComplexNum
    {
    public:
        inline explicit ComplexNum(double r_ = 0.0, double i_ = 0.0);

        // auto generated CCtor Dtor assignment

        // Getters
        inline double GetReal() const;
        inline double GetImag() const;

        // Setters
        inline void SetReal(double real_);
        inline void SetImag(double imag_);

        // Binary arithmetic operator
        inline ComplexNum &operator+=(const ComplexNum &other_);
        inline ComplexNum &operator-=(const ComplexNum &other_);
        inline ComplexNum &operator*=(const ComplexNum &other_);
        inline ComplexNum &operator/=(const ComplexNum &other_);

    private:
        double m_real;
        double m_imag;
    }; //end of class ComplexNum
            // Math operators
        inline ComplexNum operator+(const ComplexNum &lhs_, const ComplexNum &rhs_);
        inline ComplexNum operator-(const ComplexNum &lhs_, const ComplexNum &rhs_);
        inline ComplexNum operator/(const ComplexNum &lhs_, const ComplexNum &rhs_);
        inline ComplexNum operator*(const ComplexNum &lhs_, const ComplexNum &rhs_);

        // // Comparison operators
        inline bool operator==(const ComplexNum &lhs_, const ComplexNum &rhs_);
        inline bool operator!=(const ComplexNum &lhs_, const ComplexNum &rhs_);

        // // stream
        inline std::ostream &operator<<(std::ostream &os_, const ComplexNum &rhs_);
        inline std::istream &operator>>(std::istream &is_, ComplexNum &rhs_);
} // end namespace ilrd


#include "com.hpp"


#endif // __ILRD_RD132_COMPLEX_H__