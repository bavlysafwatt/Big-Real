#include "Bigint.h"
#include<bits/stdc++.h>

bool Bigint::isValidInt(const string &intNumber){
    int start = 0;
    if(intNumber[0] == '+' || intNumber[0] == '-')
        start = 1;
    for (int i = start; i < intNumber.length() ; ++i) {
        if(intNumber[i] < '0' || intNumber[i] > '9'){
            this->sign = 1;
            this->wholeNumber = {0};
            return false;
        }
    }
    return true;
}

void Bigint::equalNumberLength(Bigint& a, Bigint& b){
    int dif = abs((int)a.wholeNumber.size() - (int)b.wholeNumber.size());
    if(a.wholeNumber.size() < b.wholeNumber.size())
        for (int i = 0; i < dif; ++i)
            a.wholeNumber.push_front(0);
    else
        for (int i = 0; i < dif; ++i)
            b.wholeNumber.push_front(0);
}

void Bigint::deleteZerosFromLeft() {
    while (this->wholeNumber.size() > 1 && !this->wholeNumber.front())
        this->wholeNumber.pop_front();
}

void Bigint::setNumber(const std::string &number) {
    bool is_valid = isValidInt(number);
    if(!is_valid)
        return;
    int start = 0;
    if(number[0] == '+') this->sign = true, start++;
    else if(number[0] == '-') this->sign = false, start++;
    else this->sign = true;
    for (int i = start; i < number.length() ; ++i) {
        this->wholeNumber.push_back(number[i]-'0');
    }
    deleteZerosFromLeft();
}

Bigint::Bigint(const int &number) {
    string nstring = to_string(number);
    setNumber(nstring);
}

Bigint::Bigint(const std::string &number) {
    setNumber(number);
}

Bigint::Bigint(const Bigint &anotherReal) {
    *this = anotherReal;
}

Bigint::Bigint(Bigint &&anotherNumber) noexcept {
    *this = anotherNumber;
}

Bigint &Bigint::operator=(const Bigint &anotherNumber) {
    this->wholeNumber = anotherNumber.wholeNumber;
    this->sign = anotherNumber.sign;
    return *this;
}

Bigint &Bigint::operator=(Bigint &&anotherNumber) noexcept {
    this->wholeNumber = anotherNumber.wholeNumber;
    this->sign = anotherNumber.sign;
    return *this;
}

void Bigint::setWholeNumber(deque<int> &anotherWholeNumber) {
    this->wholeNumber = move(anotherWholeNumber);
}

deque<int> Bigint::getWholeNumber() const {
    return this->wholeNumber;
}

void Bigint::clear() {
    wholeNumber.clear();
    this->sign = true;
}

bool Bigint::getSign() const {
    return this->sign;
}

bool Bigint::operator==(Bigint anotherReal) {
    return this->sign == anotherReal.sign && this->wholeNumber == anotherReal.wholeNumber;
}

ostream& operator << (ostream& out, Bigint num){
    if(!num.getSign()) cout << '-';
    for (auto& val : num.getWholeNumber()) {
        out << val;
    }
    cout << endl;
    return out;
}

bool Bigint::isSmallerThan(const Bigint &secondNumber) {
    if(this->wholeNumber.size() != secondNumber.wholeNumber.size())
        return this->wholeNumber.size() < secondNumber.wholeNumber.size();
    int size = this->wholeNumber.size();
    for (int i = 0; i < size ; ++i) {
        if(this->wholeNumber[i] == secondNumber.wholeNumber[i]) continue;
        return this->wholeNumber[i] < secondNumber.wholeNumber[i];
    }
    return false;
}

bool Bigint::isGreaterThan(const Bigint &secondNumber) {
    if(this->wholeNumber.size() != secondNumber.wholeNumber.size())
        return this->wholeNumber.size() > secondNumber.wholeNumber.size();
    int size = this->wholeNumber.size();
    for (int i = 0; i < size ; ++i) {
        if(this->wholeNumber[i] == secondNumber.wholeNumber[i]) continue;
        return this->wholeNumber[i] > secondNumber.wholeNumber[i];
    }
    return false;
}

bool Bigint::operator<(Bigint anotherReal) {
    if(this->sign != anotherReal.sign)
        return this->sign < anotherReal.sign;
    if(!this->sign){
        return this->isGreaterThan(anotherReal);
    } else{
        return this->isSmallerThan(anotherReal);
    }
}

bool Bigint::operator>(Bigint anotherReal) {
    if(this->sign != anotherReal.sign)
        return this->sign > anotherReal.sign;
    if(!this->sign){
        return this->isSmallerThan(anotherReal);
    } else{
        return this->isGreaterThan(anotherReal);
    }
}

void Bigint::doSummation(Bigint &a) {
    equalNumberLength(*this, a);
    int pos = this->wholeNumber.size()-1;
    while (pos >= 0){
        this->wholeNumber[pos]+=a.wholeNumber[pos];
        if(this->wholeNumber[pos] >= 10){
            this->wholeNumber[pos]%=10;
            if(pos-1 >= 0)
                this->wholeNumber[pos-1]++;
            else
                this->wholeNumber.push_front(1);
        }
        pos--;
    }
}

void Bigint::doSubtraction(Bigint &a) {
    if(this->wholeNumber < a.wholeNumber) swap(this->wholeNumber, a.wholeNumber);
    int position = (int)this->wholeNumber.size() - 1;
    while (position >= 0)
    {
        this->wholeNumber[position] = this->wholeNumber[position] - a.wholeNumber[position];
        if(this->wholeNumber[position] < 0)
        {
            if(position)
            {
                this->wholeNumber[position-1]--;
                this->wholeNumber[position] += 10;
            }
        }
        position --;
    }
}

Bigint Bigint::operator+(Bigint other) {
    equalNumberLength(*this, other);
    Bigint tmp("");
    tmp = *this;
    equalNumberLength(tmp, other);
    if(this->sign == other.sign){
        tmp.doSummation(other);
    }
    else{
        if(other.isGreaterThan(tmp))
            tmp.sign = other.sign;
        tmp.doSubtraction(other);
    }
    tmp.deleteZerosFromLeft();
    return tmp;
}

Bigint Bigint::operator-(Bigint other) {
    other.sign = !other.sign;
    return (*this+other);
}

int Bigint::size() {
    return wholeNumber.size();
}