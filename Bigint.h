#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include<iostream>
#include<deque>
using namespace std;

class Bigint {
private:
    bool sign;
    deque<int> wholeNumber;
    bool isValidInt(const string &intNumber);
    void equalNumberLength(Bigint& a, Bigint& b);
    void deleteZerosFromLeft();
    void doSummation(Bigint &a);
    void doSubtraction(Bigint &a);
    void setNumber(const string& number);
    bool isSmallerThan(const Bigint& secondNumber);
    bool isGreaterThan(const Bigint& secondNumber);
public:
    Bigint () = default;
    Bigint(const int& number);
    Bigint(const string& number);
    Bigint(const Bigint &anotherReal);
    Bigint(Bigint &&anotherNumber) noexcept;
    Bigint& operator= (const Bigint& anotherNumber);
    Bigint& operator= (Bigint && anotherNumber) noexcept;
    Bigint operator+ (Bigint other);
    Bigint operator- (Bigint other);
    bool operator< (Bigint anotherReal);
    bool operator> (Bigint anotherReal);
    bool operator== (Bigint anotherReal);
    friend ostream& operator << (ostream& out, Bigint num);
    void setWholeNumber(deque<int>& anotherWholeNumber);
    deque<int> getWholeNumber() const;
    void clear();
    bool getSign() const;
    int size();
};


#endif //BIGINT_BIGINT_H
