#include "BigReal.h"

bool BigReal::checkValidInput(const std::string& input) {
    if(input.size() == 1 && !isdigit(input[0])) return false;
    std::regex reg("[+-]?[0-9]*[.]?[0-9]*");
    return regex_match(input, reg);
}

void BigReal::deleteZerosFromFractionPart() {
    deque<int> wholeNumber = this->decimalNumber.getWholeNumber();
    int mxdel = min(this->decimalPointPosition, (int)wholeNumber.size()) - 1;
    while (mxdel && wholeNumber.size() != 1 && !wholeNumber.back()){
        wholeNumber.pop_back();
        this->decimalPointPosition--;
        mxdel--;
    }
    this->decimalNumber.setWholeNumber(wholeNumber);
}

void BigReal::zeros_after_dpp() {
    deque<int> decimal = this->decimalNumber.getWholeNumber();
    while (this->decimalPointPosition > decimal.size()+1)
        decimal.push_front(0);
    this->decimalNumber.setWholeNumber(decimal);
}

void BigReal::addZerosToFractionPart(BigReal &realNumber, int times) {
    deque<int> wholeNumber = realNumber.decimalNumber.getWholeNumber();
    for (int i = 0; i < times; ++i) {
        wholeNumber.push_back(0);
    }
    realNumber.decimalNumber.setWholeNumber(wholeNumber);
}

void BigReal::equalFractionPartLength(BigReal &firstNumber, BigReal &secondNumber) {
    if(firstNumber.decimalPointPosition < secondNumber.decimalPointPosition){
        addZerosToFractionPart(firstNumber, secondNumber.decimalPointPosition-firstNumber.decimalPointPosition);
        firstNumber.decimalPointPosition = secondNumber.decimalPointPosition;
    } else if(firstNumber.decimalPointPosition > secondNumber.decimalPointPosition){
        addZerosToFractionPart(secondNumber, firstNumber.decimalPointPosition-secondNumber.decimalPointPosition);
        secondNumber.decimalPointPosition = firstNumber.decimalPointPosition;
    }
}

void BigReal::setNum(string realNumber) {
    string wholeNumber;
    if(!checkValidInput(realNumber)){
        wholeNumber = "0";
        this->decimalPointPosition = 1;
    }
    else{
        int length = realNumber.length();
        int point = find(realNumber.begin(), realNumber.end(), '.') - realNumber.begin();
        if(point==length){
            wholeNumber = realNumber;
            this->decimalPointPosition = 1;
        } else{
            wholeNumber=realNumber.substr(0, point);
            wholeNumber+=realNumber.substr(point+1);
            this->decimalPointPosition = length-point;
        }
    }
    this->decimalNumber = Bigint(wholeNumber);
    this->zeros_after_dpp();
}

BigReal::BigReal(double realNumber) {
    string wholeNumber = to_string(realNumber);
    setNum(wholeNumber);
}

BigReal::BigReal(std::string realNumber) {
    setNum(realNumber);
    this->deleteZerosFromFractionPart();
}

BigReal::BigReal(const BigReal &other) {
    this->decimalPointPosition = other.decimalPointPosition;
    this->decimalNumber = other.decimalNumber;
}

BigReal::BigReal(BigReal &&anotherReal) noexcept {
    this->decimalPointPosition = anotherReal.decimalPointPosition;
    this->decimalNumber = anotherReal.decimalNumber;
}

BigReal &BigReal::operator=(BigReal &other) {
    this->decimalPointPosition = other.decimalPointPosition;
    this->decimalNumber = other.decimalNumber;
    return *this;
}

BigReal &BigReal::operator=(BigReal &&anotherReal) noexcept {
    this->decimalPointPosition = anotherReal.decimalPointPosition;
    this->decimalNumber = anotherReal.decimalNumber;
    return *this;
}

bool BigReal::operator<(BigReal anotherReal) {
    BigReal first = *this;
    BigReal second = anotherReal;
    equalFractionPartLength(first, second);
    return first.decimalNumber < second.decimalNumber;
}

bool BigReal::operator>(BigReal anotherReal) {
    BigReal first = *this;
    BigReal second = anotherReal;
    equalFractionPartLength(first, second);
    return first.decimalNumber > second.decimalNumber;
}

bool BigReal::operator==(BigReal anotherReal) {
    BigReal first = *this;
    BigReal second = anotherReal;
    equalFractionPartLength(first, second);
    return first.decimalNumber == second.decimalNumber;
}

BigReal BigReal::operator+(BigReal &other) {
    BigReal first = *this;
    BigReal second = other;
    equalFractionPartLength(first, second);
    first.decimalNumber = first.decimalNumber + second.decimalNumber;
    first.deleteZerosFromFractionPart();
    first.zeros_after_dpp();
    return first;
}

BigReal BigReal::operator-(BigReal &other) {
    BigReal first = *this;
    BigReal second = other;
    equalFractionPartLength(first, second);
    first.decimalNumber = first.decimalNumber - second.decimalNumber;
    first.deleteZerosFromFractionPart();
    first.zeros_after_dpp();
    return first;
}

ostream& operator << (ostream& out, BigReal num){
    num.deleteZerosFromFractionPart();
    num.zeros_after_dpp();
    deque<int> wholenumber = num.decimalNumber.getWholeNumber();
    if(!(num.decimalNumber.getSign()))
        out << '-';
    if(num.decimalPointPosition!=wholenumber.size()+1) {
        for (int i = 0; i <= wholenumber.size() - num.decimalPointPosition; ++i) {
            out << wholenumber[i];
        }
    }
    else
        out << '0';
    out << '.';
    for (int i = wholenumber.size()-num.decimalPointPosition+1 ; i < wholenumber.size(); ++i) {
        out << wholenumber[i];
    }
    if(wholenumber.size()==1 || num.decimalPointPosition == 1)
        out << 0;
    return out;
}

bool BigReal::sign() {
    return decimalNumber.getSign();
}

int BigReal::size() {
    return decimalNumber.size();
}

