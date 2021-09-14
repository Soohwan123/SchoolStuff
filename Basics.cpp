// Basics.cpp
//

#include <iostream>
#include <string>
using namespace std;

class Foo { // classes' default is private, structs' defualt is public
    //variiables in the classes, try to put _ to distinguish
    string s_;
public:
    int i_;
    double f_;

    //constructors
    Foo (int i, double f) : i_(i), f_(f) {}
    Foo() = default;                // go back to creating the default constructor automatically

    //accessors
    string s() const { return s_; } // inline makes it faster. Impliese inline string s() ~ 
};

#define PRINTFOO(obj) cout << #obj << " : integer = " << obj.i_ << " , real = " << obj.f_ <<  " , string =  \"" << obj.s() <<  "\"\n"; 

int main(){
    cout << "Demonstrate basic class encapsulation!\n";

    Foo bar;
    bar.i_ = 42;
    bar.f_ = 5.1;
    PRINTFOO(bar);

    Foo bar2{43, 5.2}; //initializer list. Has to be done in order.
    PRINTFOO(bar2);

    Foo bar3{ 44, 5.3}; // designated initializers (from c) -> 20 can do it. Mine's 17. Dosen't need to be done in order.
    PRINTFOO(bar3);

}

