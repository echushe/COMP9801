#pragma once
#include <string>
#include <vector>
#include <iostream>

typedef unsigned char byte;
typedef long long int lint;

class Integer
{
private:
    lint m_sign;
    std::vector<byte> m_data;

public:
    Integer();

    Integer(lint in, lint len = 8);

    Integer(const std::vector<byte> & bytes, lint sign = 1);

    Integer(const Integer & other);

    Integer(Integer && other);

    Integer & operator = (const Integer & other);

    Integer & operator = (Integer && other);

public:

    lint sign() const
    {
        return this->m_sign;
    }

    void set_sign(lint s)
    {
        this->m_sign = s;
    }


public:
    /*
    Bitwise calculation
    */


public:

    Integer& operator = (lint other);

    Integer& operator ++ ();

    Integer operator ++ (int);

    Integer& operator -- ();

    Integer operator -- (int);

    Integer& operator += (const Integer & itg);

    Integer& operator -= (const Integer & itg);

    Integer& operator *= (const Integer & itg);

    Integer& operator /= (const Integer & itg);

    Integer& operator <<= (lint bits);

    Integer& operator >>= (lint bits);

    //Implicitely convert to a C++ integer
    explicit operator lint () const;

    lint to_raw_int() const;

public:
    ~Integer();

    /*
    Friend members
    */
    friend std::ostream & operator << (std::ostream & os, const Integer & itg);
    
    friend Integer operator << (const Integer & itg, lint bits);

    friend Integer operator >> (const Integer & itg, lint bits);

    friend Integer operator * (const Integer & left, const Integer & right);

public:

    Integer& sum_with(const Integer & other);

    Integer& sub_with(const Integer & other);
    
    bool abs_less(const Integer & other) const;

    Integer abs() const;

    bool is_zero() const;

    bool abs_equals(const Integer & other) const;

    lint size();

    Integer & resize(lint len);

private:

    Integer truncate(lint front, lint tail) const;

    static Integer multiply(const Integer & left, const Integer & right);

    static Integer shift_left_allow_expansion(const Integer & itg, lint bits);
};


std::ostream & operator << (std::ostream& os, const Integer & itg);

Integer operator << (const Integer & itg, lint bits);

Integer operator >> (const Integer & itg, lint bits);

Integer operator + (const Integer & left, const Integer & right);

Integer operator - (const Integer & left, const Integer & right);

Integer operator * (const Integer & left, const Integer & right);

inline Integer operator / (const Integer & left, const Integer & right);

bool operator == (const Integer & left, const Integer & right);

bool operator != (const Integer & left, const Integer & right);

bool operator < (const Integer & left, const Integer & right);

bool operator > (const Integer & left, const Integer & right);





