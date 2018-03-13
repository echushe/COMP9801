#include "Integer.h"
#include <bitset>

Integer::Integer()
    :
    m_sign{ 1 }
{}

Integer::Integer(lint in, lint len)
    :
    m_sign{ in > 0 ? 1 : -1 }
{
    this->m_data.resize(static_cast<size_t>(len));

    in *= this->m_sign;

    lint size = sizeof(lint);

    lint sub = len - size;
    lint one = 1;
    lint base = one << 8;

    for (lint i = len - 1; i >= sub && i >= 0; --i)
    {
        this->m_data[i] = static_cast<byte>(in % base);
        in >>= 8;
    }
    for (lint i = sub - 1; i >= 0; --i)
    {
        this->m_data[i] = 0;
    }
}


Integer::Integer(const std::vector<byte>& bytes, lint sign)
    :
    m_sign{ sign },
    m_data{ bytes }
{}


Integer::Integer(const Integer & other)
    :
    m_sign{ other.m_sign },
    m_data{ other.m_data }
{}


Integer::Integer(Integer && other)
    :
    m_sign{ other.m_sign },
    m_data{ std::move(other.m_data) }
{}


Integer & Integer::operator = (const Integer & other)
{
    this->m_sign = other.m_sign;
    this->m_data = other.m_data;

    return *this;
}


Integer & Integer::operator = (Integer && other)
{
    this->m_sign = other.m_sign;
    this->m_data = std::move(other.m_data);

    return *this;
}


Integer & Integer::operator = (lint other)
{
    if (other > 0)
    {
        this->m_sign = 1;
    }
    else
    {
        this->m_sign = -1;
        other *= -1;
    }

    this->m_data.resize(sizeof(lint));

    lint one = 1;
    lint base = one << 8;

    for (lint i = sizeof(lint) - 1; i >= 0; --i)
    {
        this->m_data[i] = static_cast<byte>(other % base);
        other >>= 8;
    }

    return *this;
}


Integer & Integer::operator ++ ()
{
    *this += Integer{ 1, static_cast<lint>(this->m_data.size()) };
    return *this;
}


Integer Integer::operator ++ (int)
{
    Integer to_return{ *this };
    *this += Integer{ 1, static_cast<lint>(this->m_data.size()) };

    return to_return;
}


Integer & Integer::operator -- ()
{
    *this -= Integer{ 1, static_cast<lint>(this->m_data.size()) };
    return *this;
}


Integer Integer::operator -- (int)
{
    Integer to_return{ *this };
    *this -= Integer{ 1, static_cast<lint>(this->m_data.size()) };

    return to_return;
}


Integer & Integer::operator += (const Integer & itg)
{
    *this = *this + itg;

    return *this;
}


Integer & Integer::operator -= (const Integer & itg)
{
    *this = *this - itg;

    return *this;
}


Integer & Integer::operator *= (const Integer & itg)
{
    *this = *this * itg;

    return *this;
}


Integer & Integer::operator <<= (lint bits)
{
    lint len = this->m_data.size();
    bits %= len * 8;
    if (bits < 0)
    {
        bits += len * 8;
    }

    lint bytes = bits / 8;
    lint re_bits = bits % 8;

    // Move the bytes first
    lint sub = len - bytes;
    if (bytes > 0)
    {
        if (sub <= 0)
        {
            for (lint i = 0; i < len; ++i)
            {
                this->m_data[i] = 0;
            }

            return *this;
        }

        for (lint i = 0; i < sub; ++i)
        {
            this->m_data[i] = this->m_data[i + bytes];
        }
        for (lint i = sub; i < len; ++i)
        {
            this->m_data[i] = 0;
        }
    }

    // Move the residual of bits
    if (re_bits)
    {
        byte bits_to_move;
        for (lint i = 0; i < sub; ++i)
        {
            if (i < sub - 1)
            {
                bits_to_move = this->m_data[i + 1];
                bits_to_move >>= 8 - re_bits;
            }
            else
            {
                bits_to_move = 0;
            }

            this->m_data[i] <<= re_bits;
            this->m_data[i] += bits_to_move;
        }
    }

    return *this;
}



Integer & Integer::operator >>= (lint bits)
{
    lint len = this->m_data.size();
    bits %= len * 8;
    if (bits < 0)
    {
        bits += len * 8;
    }

    lint bytes = bits / 8;
    lint re_bits = bits % 8;

    // Move the bytes first
    if (bytes > 0)
    {
        if (len <= bytes)
        {
            for (lint i = 0; i < len; ++i)
            {
                this->m_data[i] = 0;
            }

            return *this;
        }

        for (lint i = len - 1; i >= bytes; --i)
        {
            this->m_data[i] = this->m_data[i - bytes];
        }
        for (lint i = bytes - 1; i >= 0; --i)
        {
            this->m_data[i] = 0;
        }
    }

    // Move the residual of bits
    if (re_bits > 0)
    {
        byte bits_to_move;
        for (lint i = len - 1; i >= bytes; --i)
        {
            if (i > bytes)
            {
                bits_to_move = this->m_data[i - 1];
                bits_to_move <<= 8 - re_bits;
            }
            else
            {
                bits_to_move = 0;
            }

            this->m_data[i] >>= re_bits;
            this->m_data[i] += bits_to_move;
        }
    }

    return *this;
}



Integer::operator lint() const
{
    lint len = this->m_data.size();
    lint size = sizeof(lint);
    lint ret = 0;

    if (size <= len)
    {
        ret = this->m_data[len - size];
        if (ret > 127)
        {
            ret &= 127;
        }

        for (lint i = 1; i < size; ++i)
        {
            ret *= 256;
            ret += this->m_data[len - size + i];
        }
    }
    else
    {
        for (lint i = 0; i < len; ++i)
        {
            ret *= 256;
            ret += this->m_data[i];
        }
    }

    ret *= this->m_sign;

    return ret;
}



lint Integer::to_raw_int() const
{
    return this->operator std::streamoff();
}



Integer::~Integer()
{}



Integer & Integer::sum_with(const Integer & other)
{
    byte m = 0;

    if (other.m_data.size() > this->m_data.size())
    {
        this->resize(other.m_data.size());
    }

    lint len = this->m_data.size();
    lint offset = len - other.m_data.size();

    for (lint i = len - 1; i >= 0; --i)
    {
        lint sum;
        if (i >= offset)
        {
            sum = this->m_data[i] + other.m_data[i - offset] + m;
        }
        else
        {
            sum = this->m_data[i] + m;
        }

        if (sum > 255)
        {
            m = 1;
            this->m_data[i] = static_cast<byte>(sum - 256);
        }
        else
        {
            m = 0;
            this->m_data[i] = static_cast<byte>(sum);
        }
    }

    if (1 == m)
    {
        this->resize(len + 1);
        this->m_data[0] = 1;
    }

    return *this;
}



Integer & Integer::sub_with(const Integer & other)
{
    byte m = 0;

    if (other.m_data.size() > this->m_data.size())
    {
        this->resize(other.m_data.size());
    }

    lint len = this->m_data.size();
    lint offset = len - other.m_data.size();

    for (lint i = len - 1; i >= 0; --i)
    {
        lint sub;
        if (i >= offset)
        {
            sub = this->m_data[i] - other.m_data[i - offset] - m;
        }
        else
        {
            sub = this->m_data[i] - m;
        }

        if (sub < 0)
        {
            m = 1;
            this->m_data[i] = static_cast<byte>(sub + 256);
        }
        else
        {
            m = 0;
            this->m_data[i] = static_cast<byte>(sub);
        }
    }

    return *this;
}



bool Integer::abs_less(const Integer & other) const
{
    if (other.m_data.size() < this->m_data.size())
    {
        lint len = this->m_data.size();
        lint sub = len - other.m_data.size();

        for (lint i = 0; i < sub; ++i)
        {
            if (this->m_data[i] > 0)
            {
                return false;
            }
        }

        for (lint i = sub; i < len; ++i)
        {
            if (this->m_data[i] < other.m_data[i - sub])
            {
                return true;
            }
            else if (this->m_data[i] > other.m_data[i - sub])
            {
                return false;
            }
        }
    }
    else if (other.m_data.size() > this->m_data.size())
    {
        lint len = other.m_data.size();
        lint sub = len - this->m_data.size();

        for (lint i = 0; i < sub; ++i)
        {
            if (other.m_data[i] > 0)
            {
                return true;
            }
        }

        for (lint i = sub; i < len; ++i)
        {
            if (this->m_data[i - sub] < other.m_data[i])
            {
                return true;
            }
            else if (this->m_data[i - sub] > other.m_data[i])
            {
                return false;
            }
        }
    }
    else
    {
        lint len = this->m_data.size();

        for (lint i = 0; i < len; ++i)
        {
            if (this->m_data[i] < other.m_data[i])
            {
                return true;
            }
            else if (this->m_data[i] > other.m_data[i])
            {
                return false;
            }
        }
    }

    return false;
}



Integer Integer::abs() const
{
    Integer to_return{ *this };
    to_return.m_sign = 1;

    return to_return;
}



bool Integer::is_zero() const
{
    lint len = this->m_data.size();

    for (lint i = 0; i < len; ++i)
    {
        if (this->m_data[i] != 0)
        {
            return false;
        }
    }

    return true;
}



bool Integer::abs_equals(const Integer & other) const
{
    if (other.m_data.size() < this->m_data.size())
    {
        lint len = this->m_data.size();
        lint sub = len - other.m_data.size();

        for (lint i = 0; i < sub; ++i)
        {
            if (this->m_data[i] > 0)
            {
                return false;
            }
        }

        for (lint i = sub; i < len; ++i)
        {
            if (this->m_data[i] != other.m_data[i - sub])
            {
                return false;
            }
        }
    }
    else if (other.m_data.size() > this->m_data.size())
    {
        lint len = other.m_data.size();
        lint sub = len - this->m_data.size();

        for (lint i = 0; i < sub; ++i)
        {
            if (other.m_data[i] > 0)
            {
                return false;
            }
        }

        for (lint i = sub; i < len; ++i)
        {
            if (this->m_data[i - sub] != other.m_data[i])
            {
                return false;
            }
        }
    }
    else
    {
        lint len = this->m_data.size();

        for (lint i = 0; i < len; ++i)
        {
            if (this->m_data[i] != other.m_data[i])
            {
                return false;
            }
        }
    }

    return true;
}


lint Integer::size()
{
    return this->m_data.size();
}


Integer Integer::truncate(lint front, lint tail) const
{
    Integer to_return;
    to_return.m_sign = this->m_sign;
    to_return.m_data.resize(tail - front + 1);

    for (lint i = front; i <= tail; ++i)
    {
        to_return.m_data[i - front] = this->m_data[i];
    }

    return to_return;
}


Integer Integer::multiply(
    const Integer & left, const Integer & right)
{
    if (left.m_data.size() <= 1 && right.m_data.size() <= 1)
    {
        byte l, r;
        unsigned short int multi;
        
        if (left.m_data.size() > 0)
        {
            l = left.m_data[0];
        }
        else
        {
            l = 0;
        }

        if (right.m_data.size() > 0)
        {
            r = right.m_data[0];
        }
        else
        {
            r = 0;
        }

        multi = l * r;

        return Integer{ multi, 2 };
    }


    lint len;
    if (left.m_data.size() > right.m_data.size())
    {
        len = left.m_data.size();
    }
    else
    {
        len = right.m_data.size();
    }

    if (len % 2 != 0)
    {
        ++len;
    }

    Integer l_left{ left };
    Integer l_right{ right };

    l_left.resize(len);
    l_right.resize(len);

    Integer A1 = l_left.truncate(0, len / 2 - 1);
    Integer A0 = l_left.truncate(len / 2, len - 1);

    Integer B1 = l_right.truncate(0, len / 2 - 1);
    Integer B0 = l_right.truncate(len / 2, len - 1);

    Integer U = A0 + A1;
    Integer V = B0 + B1;

    Integer X = multiply(A0, B0);
    Integer W = multiply(A1, B1);
    Integer Y = multiply(U, V);

    lint bits = len * 8;
    return Integer::shift_left_allow_expansion(W, bits) + 
        Integer::shift_left_allow_expansion(Y - X - W, bits / 2) + X;
}


Integer Integer::shift_left_allow_expansion(const Integer & itg, lint bits)
{
    lint len = itg.m_data.size();

    lint affected_bytes = bits / 8;
    if (bits % 8 != 0)
    {
        ++affected_bytes;
    }

    Integer expanded{ itg };

    lint index = 0;
    while (index < len && expanded.m_data[index] == 0)
    {
        ++index;
    }

    if (index < len && index < affected_bytes)
    {
        expanded.resize(len + affected_bytes - index);
    }
    
    return expanded <<= bits;
}
 
 
 
Integer & Integer::resize(lint len)
{
    if (len <= 0)
    {
        return *this;
    }

    if (len == this->m_data.size())
    {
        return *this;
    }

    std::vector<byte> new_data;
    new_data.resize(len);

    lint old_len = this->m_data.size();
    
    if (len > old_len)
    {
        lint sub = len - old_len;
        for (lint i = 0; i < sub; ++i)
        {
            new_data[i] = 0;
        }

        for (lint i = sub; i < len; ++i)
        {
            new_data[i] = this->m_data[i - sub];
        }
    }
    else
    {
        lint sub = old_len - len;
        for (lint i = 0; i < len; ++i)
        {
            new_data[i] = this->m_data[i + sub];
        }
    }

    this->m_data = std::move(new_data);

    return *this;
}


std::ostream & operator << (std::ostream& os, const Integer & itg)
{
    lint len = itg.m_data.size();
    for (lint i = 0; i < len; ++i)
    {
        os << std::bitset<8>(itg.m_data[i]) << " ";
    }
    return os;
}



Integer operator << (const Integer & itg, lint bits)
{
    Integer copy{ itg };
    return copy <<= bits;
}



Integer operator >> (const Integer & itg, lint bits)
{
    Integer copy{ itg };
    return copy >>= bits;
}



Integer operator + (const Integer & left, const Integer & right)
{
    if (left.sign() == right.sign())
    {
        Integer sum{ left };

        return sum.sum_with(right);
    }
    else if (left.abs_less(right))
    {
        Integer sub{ right };

        return sub.sub_with(left);
    }
    else
    {
        Integer sub{ left };

        return sub.sub_with(right);
    }
}



Integer operator - (const Integer & left, const Integer & right)
{
    if (left.sign() != right.sign())
    {
        Integer sum{ left };

        return sum.sum_with(right);
    }
    else if (left.abs_less(right))
    {
        Integer sub{ right };

        sub.set_sign(sub.sign() * (-1));
        return sub.sub_with(left);
    }
    else
    {
        Integer sub{ left };

        return sub.sub_with(right);
    }
}



Integer operator * (const Integer & left, const Integer & right)
{
    Integer ret = Integer::multiply(left, right);
    ret.m_sign = left.m_sign * right.m_sign;

    return ret;
}



Integer operator / (const Integer & left, const Integer & right)
{
    return Integer(1);
}



bool operator == (const Integer & left, const Integer & right)
{
    if (left.is_zero())
    {
        if (right.is_zero())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (right.is_zero())
        {
            return false;
        }
        else if (left.sign() != right.sign())
        {
            return false;
        }
    }


    return left.abs_equals(right);
}



bool operator != (const Integer & left, const Integer & right)
{
    return !(left == right);
}



bool operator < (const Integer & left, const Integer & right)
{
    if (left.is_zero())
    {
        if (right.is_zero())
        {
            return false;
        }
        else
        {
            return static_cast<bool>(right.sign() > 0);
        }
    }
    else
    {
        if (right.is_zero())
        {
            return static_cast<bool>(left.sign() < 0);
        }
        else if (left.sign() != right.sign())
        {
            return left.sign() < right.sign();
        }
    }

    bool abs_less = left.abs_less(right);

    if (left.sign() < 0)
    {
        if (left.abs_equals(right))
        {
            return abs_less;
        }
        else
        {
            return !abs_less;
        }
    }
    else
    {
        return abs_less;
    }
}



bool operator > (const Integer & left, const Integer & right)
{
    if (left.is_zero())
    {
        if (right.is_zero())
        {
            return false;
        }
        else
        {
            return static_cast<bool>(right.sign() < 0);
        }
    }
    else
    {
        if (right.is_zero())
        {
            return static_cast<bool>(left.sign() > 0);
        }
        else if (left.sign() != right.sign())
        {
            return left.sign() > right.sign();
        }
    }

    bool abs_less = left.abs_less(right);

    if (left.sign() > 0)
    {
        if (left.abs_equals(right))
        {
            return abs_less;
        }
        else
        {
            return !abs_less;
        }
    }
    else
    {
        return abs_less;
    }
}