// Basics.cpp
//
#ifdef _WIN32
#include <crtdbg.h>  // Windows only, crt stands for C-Runtime, dbg for DeBuG library
#endif
                   
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Foo { // classes' default is private, structs' defualt is public
    //variiables in the classes, try to put _ to distinguish
    char* s_ = nullptr;             // low-level dynamic string
public:
    int i_ = 100;
    double f_ = 3.14;

    //constructors
    Foo (int i = 0, double f = 0.0, const char* s = "") : i_(i), f_(f) {
        // handle a nullptr input
        if (s == nullptr) {
            s_ = nullptr;
            return;
        }

        //measure the input string
        auto end = s;
        while (*end++); //'b' 'i' 'r' 'd' '\0' 'EOF' -> 5 times increments

        //allocate dynamic memory for that string (difference of begin and end pointers)
        s_ = new char[end - s];

        //copy into that string
        copy(s, end, s_);   // uses std::copy from <algorithm>
    }


    Foo(const Foo& original) : Foo(original.i_, original.f_, original.s_) {}; //copy destructor


    Foo(Foo&& original) noexcept : i_(original.i_), f_(original.f_), s_(original.s_) {
        original.s_ = nullptr;
    } // this is way faster.

   // Foo() = default;                // go back to creating the default constructor automatically
   // Foo() : Foo(0, 0, "") {}
   // Foo(int i) : i_(i) {}
   // Foo(int i) : Foo(i, 0, "") {}
    ~Foo() { delete[] s_; }          // destructor to save memory to avoid memory leak            // ~ bitwise negative
    //accessors
    const char* s() const { if (s_) return s_; else return "(null)"; } // inline makes it faster. Impliese inline string s() ~ 

    // operator
    Foo& operator = (const Foo& original) {

        i_ = original.i_;
        f_ = original.f_;
        delete s_;

        // handle a nullptr input
        if (original.s_ == nullptr) {
            s_ = nullptr;
            return *this;
        }

        //measure the input string
        auto end = original.s_;
        auto beg = end;
        while (*end++); //'b' 'i' 'r' 'd' '\0' 'EOF' -> 5 times increments

        //allocate dynamic memory for that string (difference of begin and end pointers)
        s_ = new char[end - beg];

        //copy into that string
        copy(beg, end, s_);   // uses std::copy from <algorith>
        return *this;
    }

    Foo& operator = (Foo&& original) noexcept {
        i_ = original.i_;
        f_ = original.f_;
        delete s_;
        s_ = original.s_;
        original.s_ = nullptr;
        return *this;
    }
};

#define PRINTFOO(obj) cout << #obj << " : integer = " << obj.i_ << " , real = " << obj.f_ <<  " , string =  \"" << obj.s() <<  "\"\n"; 

int main(){
    cout << "Demonstrate basic class encapsulation!\n";

#ifdef _WIN32
#ifdef _DEBUG // only this code runs in debug mode
    int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;                    //"a |= b"    is the same as "a = a|b"   where | is bitwise-or
    dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
    dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(dbgFlags);

    // redirect leak warnings to console as well as the debug window
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
#endif
#endif


    Foo bar;
    //bar.i_ = 42;
    //bar.f_ = 5.1;
    PRINTFOO(bar);
    
    Foo bar1(1'000'000);
    PRINTFOO(bar1);


    Foo bar2{ 43, 5.2, "bert" }; //initializer list. Has to be done in order.
    PRINTFOO(bar2);
    //{
    //     Foo bar2{ 43, 5.2, "bert" }; //initializer list. Has to be done in order.
    //    PRINTFOO(bar2);
    // }                                // in this case, bar2 memory cleans up at this point so game developer loves c++ because we can control when to clean
    Foo bar3{44, 5.3, "ernie"}; // designated initializers (from c) -> 20 can do it. Mine's 17. Dosen't need to be done in order.
    PRINTFOO(bar3);

    // It cleans up in a reverse order


    Foo copyBar = bar2;
    PRINTFOO(copyBar);              // it crashes without copy destructor on the line 38. Because destructor cannot destructs something already destructed.

    Foo moveBar = move(bar3);
    PRINTFOO(moveBar);
    PRINTFOO(bar3);

    moveBar = bar3 = bar2;
    PRINTFOO(bar2);
    PRINTFOO(bar3);
    PRINTFOO(moveBar);

    moveBar = move(bar);
    PRINTFOO(moveBar);
    PRINTFOO(bar);
}

