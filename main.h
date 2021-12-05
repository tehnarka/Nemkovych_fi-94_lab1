#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

string hex_to_bin(const char& hex_numeric) {
    char lowercase_hex = tolower(hex_numeric);
    string binary_num;
    int num = 0;
    if (isdigit(lowercase_hex))
    {
        num = atoi(&lowercase_hex);
    }
    else
    {
        num = lowercase_hex - 87;

    }
    binary_num = bitset<4>(num).to_string();
    if (binary_num.size() > 4)
    {
        binary_num.erase(0, binary_num.size() - 5);
    }

    return binary_num;
}


class LongNum
{
public:
    //LAB 1
    LongNum(const string& hex = "0");
    LongNum(size_t size);
    //+
    LongNum LongAdd(LongNum B) const;
    //-
    LongNum LongSub(LongNum B) const;
    //*
    LongNum LongMulOneDigit(const char& b) const;
    //*
    LongNum LongMul(LongNum B) const;
    // /
    LongNum LongDiv(LongNum B) const;
    //mod
    LongNum LongMod(LongNum B) const;
    //>, <, ==
    int LongCmp(LongNum B) const;
    // <<
    LongNum LongShiftDigitsToHigh(size_t count_of_bits) const;
    // >>
    LongNum LongShiftDigitsToSmall(size_t count_of_bits) const;
    //^
    LongNum LongPower(const LongNum& B) const;
    //^
    LongNum LongPowerOneDigit(size_t b) const;

    //LAB 2
    LongNum GCD(LongNum B);
    LongNum LCM(const LongNum& B);
    LongNum BarrettReduction(LongNum n, LongNum mu);
    LongNum LongModPowerBarrett(const LongNum& B, const LongNum& N);
    //+ mod
    LongNum LongAddMod(const LongNum& B, LongNum N);
    //- mod
    LongNum LongSubMod(const LongNum& B, LongNum N);
    //* mod
    LongNum LongMulMod(const LongNum& B, LongNum N);
    const string& GetBin() const noexcept;
    string GetHex() const noexcept;

private:
    friend void SameCountsOfBits(LongNum& A, LongNum& B);
    friend void ClearZerosInbegining(LongNum& A);
    string number;
};

const string& LongNum::GetBin() const noexcept {
    return number;
}

string bin_to_hex(const string& bin) {
    stringstream res;
    bitset<8> set(bin);
    res << hex << set.to_ulong();
    return res.str();
}

string LongNum::GetHex() const noexcept {
    string bin = number;
    while (bin.size() % 4 != 0)
    {
        bin.insert(bin.begin(), '0');
    }

    string hex;
    hex.reserve(bin.size() / 4);

    string bin_buf;
    for (size_t i = 0; i < bin.size(); i += 4)
    {
        bin_buf = bin.substr(i, 4);
        hex += bin_to_hex(bin_buf);
    }

    return hex;
}

void SameCountsOfBits(LongNum& A, LongNum& B) {
    if (A.number.size() > B.number.size())
    {
        B.number.insert(0, string(A.number.size() - B.number.size(), '0'));
    }
    else
    {
        A.number.insert(0, string(B.number.size() - A.number.size(), '0'));
    }
}

void ClearZerosInbegining(LongNum& A) {
    A.number.erase(A.number.begin(), find(A.number.begin(), A.number.end() - 1, '1'));
}

LongNum::LongNum(const string& hex) {
    number.reserve(hex.size() * 4);
    for (const auto& c : hex)
    {
        number += hex_to_bin(c);
    }

}

LongNum::LongNum(size_t n)
    :number(n, '0')
{
}

LongNum LongNum::LongAdd(LongNum B) const {
    LongNum A = *this;
    SameCountsOfBits(A, B);
    LongNum C(A.number.size());
    bool carry = 0;
    char a_i, b_i;
    for (size_t i = A.number.size(); i > 0; i--)
    {
        a_i = A.number[i - 1];
        b_i = B.number[i - 1];
        auto temp = a_i - '0';
        temp += b_i - '0';
        temp += carry;
        C.number[i - 1] = (temp & 1) + '0';
        carry = temp >> 1;
    }

    if (carry == 1)
    {
        C.number.insert(C.number.begin(), '1');
    }

    return C;
}

LongNum LongNum::LongSub(LongNum B) const {
    if (LongCmp(B) == -1)
    {
        return B.LongSub(*this);
    }

    LongNum A = *this;
    SameCountsOfBits(A, B);

    LongNum C(A.number.size());
    bool borrow = 0;
    char a_i, b_i;
    for (size_t i = A.number.size(); i > 0; i--)
    {
        a_i = A.number[i - 1];
        b_i = B.number[i - 1];
        auto temp = a_i - '0';
        temp -= b_i - '0';
        temp -= borrow;
        if (temp >= 0)
        {
            C.number[i - 1] = temp + '0';
            borrow = 0;
        }
        else
        {
            C.number[i - 1] = (2 + temp) + '0';
            borrow = 1;
        }
    }

    C.number.erase(C.number.begin(), find(C.number.begin(), C.number.end() - 1, '1'));

    return C;
}

int LongNum::LongCmp(LongNum B) const {
    LongNum A = *this;
    SameCountsOfBits(A, B);
    int64_t i = 0;

    while ((i < A.number.size()) && (A.number[i] == B.number[i]))
    {
        ++i;
    }

    //ÿêùî âîíè ð³âí³
    if (i == A.number.size())
    {
        return 0;
    }
    //ÿêùî À á³ëüøå Â
    else if (A.number[i] > B.number[i])
    {
        return 1;
    }
    //ÿêùî À ìåíøå Â
    return -1;
}

LongNum LongNum::LongMulOneDigit(const char& b) const {
    if (b == '0')
    {
        return LongNum(number.size());
    }

    return *this;
}

LongNum LongNum::LongMul(LongNum B) const {
    LongNum A = *this;
    SameCountsOfBits(A, B);
    LongNum C;
    LongNum temp;
    for (size_t i = A.number.size(); i > 0; i--)
    {
        temp = A.LongMulOneDigit(B.number[i - 1]);
        temp = temp.LongShiftDigitsToHigh(A.number.size() - i);
        C = C.LongAdd(temp);
    }

    return C;
}

LongNum LongNum::LongShiftDigitsToHigh(size_t count_of_bits) const {
    LongNum Result = *this;
    Result.number.insert(Result.number.size(), string(count_of_bits, '0'));

    return Result;
}

LongNum LongNum::LongShiftDigitsToSmall(size_t count_of_bits) const {
    LongNum Result = *this;
    Result.number.erase(Result.number.size() - count_of_bits - 1);

    return Result;
}

LongNum LongNum::LongDiv(LongNum B) const {
    LongNum A = *this;
    ClearZerosInbegining(A);
    ClearZerosInbegining(B);

    auto k = B.number.size();
    LongNum R = A;
    LongNum Q(R.number.size());
    LongNum C;
    const LongNum TwoInW("2");
    while ((R.LongCmp(B) == 1) || (R.LongCmp(B) == 0))
    {
        auto t = R.number.size();

        C = B.LongShiftDigitsToHigh(t - k);
        if (R.LongCmp(C) == -1)
        {
            --t;
            C = B.LongShiftDigitsToHigh(t - k);
        }

        R = R.LongSub(C);
        Q.number[Q.number.size() - (t - k) - 1] = '1';

    }

    return Q;

}

LongNum LongNum::LongMod(LongNum B) const {
    LongNum A = *this;
    ClearZerosInbegining(A);
    ClearZerosInbegining(B);
    auto k = B.number.size();
    LongNum R = A;
    LongNum C;
    const LongNum TwoInW("2");
    while ((R.LongCmp(B) == 1) || (R.LongCmp(B) == 0))
    {
        auto t = R.number.size();

        C = B.LongShiftDigitsToHigh(t - k);
        if (R.LongCmp(C) == -1)
        {
            --t;
            C = B.LongShiftDigitsToHigh(t - k);
        }

        R = R.LongSub(C);

    }

    return R;
}

LongNum LongNum::LongPower(const LongNum& B) const {
    LongNum C("1");
    LongNum A = *this;
    for (auto it = B.number.rbegin(); it != B.number.rend(); ++it)
    {
        if (*it == '1')
        {
            C = C.LongMul(A);
        }
        A = A.LongMul(A);

    }

    return C;
}

LongNum LongNum::LongPowerOneDigit(size_t b) const {
    LongNum C("1");
    LongNum A = *this;

    string binary_b = bitset<8>(b).to_string();

    for (auto it = binary_b.rbegin(); it != binary_b.rend(); ++it)
    {
        if (*it == '1')
        {
            C = C.LongMul(A);
        }
        A = A.LongMul(A);

    }



    return C;
}

LongNum min(const LongNum& A, const LongNum& B) {
    if (A.LongCmp(B) == -1)
    {
        return A;
    }

    return B;
}

LongNum LongNum::GCD(LongNum B) {
    LongNum d("1");
    LongNum A = *this;
    const LongNum Two("2");
    const LongNum Zero("0");
    LongNum A_temp;

    while ((A.number.back() == '0') && (B.number.back() == '0'))
    {
        A = A.LongDiv(Two);
        B = B.LongDiv(Two);
        d = d.LongMul(Two);
    }

    while (A.number.back() == '0')
    {
        A = A.LongDiv(Two);
    }

    while (B.LongCmp(Zero) != 0)
    {
        while (B.number.back() == '0')
        {
            B = B.LongDiv(Two);
        }
        A_temp = A;
        A = min(A, B);
        B = A_temp.LongSub(B);
    }

    d = d.LongMul(A);

    return d;
}

LongNum LongNum::LCM(const LongNum& B) {
    return (LongMul(B)).LongDiv(GCD(B));
}

LongNum LongNum::BarrettReduction(LongNum n, LongNum mu) {
    LongNum A = *this;

    LongNum q = A.LongShiftDigitsToSmall(n.number.size() - 1);
    q = q.LongMul(mu);
    q = q.LongShiftDigitsToSmall(n.number.size() + 1);
    ClearZerosInbegining(q);
    LongNum r = q.LongMul(n);
    r = A.LongSub(r);
    ClearZerosInbegining(n);
    ClearZerosInbegining(r);
    while ((r.LongCmp(n) == 1) || (r.LongCmp(n) == 0))
    {
        r = r.LongSub(n);
    }

    return r;
}

LongNum LongNum::LongModPowerBarrett(const LongNum& B, const LongNum& N) {
    LongNum mu = LongNum("2").LongPowerOneDigit(2 * N.number.size());
    mu = mu.LongDiv(N);
    LongNum A = *this;
    LongNum C("1");
    for (auto it = B.number.rbegin(); it != B.number.rend(); ++it)
    {
        if (*it == '1')
        {
            C = (C.LongMul(A)).BarrettReduction(N, mu);
        }

        A = (A.LongMul(A)).BarrettReduction(N, mu);
    }

    return C;
}

LongNum LongNum::LongAddMod(const LongNum& B, LongNum N) {
    LongNum Sum = LongAdd(B);

    if (Sum.number.size() % 2 != 0)
    {
        Sum.number.insert(Sum.number.begin(), '0');
    }

    while (Sum.number.size() < 2 * N.number.size())
    {
        Sum.number.insert(Sum.number.begin(), '0');
    }

    while (Sum.number.size() > 2 * N.number.size())
    {
        N.number.insert(N.number.begin(), '0');
    }
    // LongNum mu = LongNum( "2" ).LongPowerOneDigit( 2 * N.number.size( ) );
    // mu = mu.LongDiv( N );
    LongNum mu = LongNum("2").LongShiftDigitsToHigh(2 * N.number.size());
    mu = mu.LongDiv(N);
    ClearZerosInbegining(mu);

    return Sum.BarrettReduction(N, mu);
}

LongNum LongNum::LongSubMod(const LongNum& B, LongNum N) {
    LongNum Sub = LongSub(B);

    if (Sub.number.size() % 2 != 0)
    {
        Sub.number.insert(Sub.number.begin(), '0');
    }

    while (Sub.number.size() < 2 * N.number.size())
    {
        Sub.number.insert(Sub.number.begin(), '0');
    }

    while (Sub.number.size() > 2 * N.number.size())
    {
        N.number.insert(N.number.begin(), '0');
    }
    LongNum mu = LongNum("2").LongShiftDigitsToHigh(2 * N.number.size());
    mu = mu.LongDiv(N);
    ClearZerosInbegining(mu);

    return Sub.BarrettReduction(N, mu);
}

LongNum LongNum::LongMulMod(const LongNum& B, LongNum N) {
    LongNum Mul = LongMul(B);

    if (Mul.number.size() % 2 != 0)
    {
        Mul.number.insert(Mul.number.begin(), '0');
    }

    while (Mul.number.size() < 2 * N.number.size())
    {
        Mul.number.insert(Mul.number.begin(), '0');
    }

    while (Mul.number.size() > 2 * N.number.size())
    {
        N.number.insert(N.number.begin(), '0');
    }
    LongNum mu = LongNum("2").LongShiftDigitsToHigh(2 * N.number.size());
    mu = mu.LongDiv(N);
    ClearZerosInbegining(mu);

    return Mul.BarrettReduction(N, mu);
}
#pragma once
