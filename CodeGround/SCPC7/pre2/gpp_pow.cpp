#include <cmath>
#include <iostream>
#include <typeinfo>     // typeid()

using namespace std;

int main()
{
    long long R = 2;
    int integer = 2;
    unsigned uinteger = 2;

    cout << typeid(pow(3+2*(R-1), 2)).name() << endl;
    cout << typeid(R).name() << endl;
    cout << typeid(integer).name() << endl;
    cout << typeid(uinteger).name() << endl;

    return 0;
}