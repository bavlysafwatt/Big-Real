#include <iostream>
#include "Bigint.h"
#include "BigReal.h"

using namespace std;

int main() {
    BigReal a("1284.0062");
    BigReal b("-547.261");
    cout << a+b << endl;
    cout << a-b << endl;
    cout << (a==b) << endl;
    cout << (a > b) << endl;
    cout << (a < b) << endl;
    return 0;
}
