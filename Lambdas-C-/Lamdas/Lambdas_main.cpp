/* \file Lambdas_main.cpp
*  \autor Soohwan Kim
*  \date 2021-11-22
*  \copyright 2021
* 
* Lambda Expression demo

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <chrono>
#include <array>
using namespace std;

//option 1
//double g_start = -1;
//double f() {
//	return g_start += 2;
//}
//option 2

double f() {
	static double g_start = -1;
	return g_start += 2;
}
int main() {
	vector<double> v(10);
	//option 1...
	//v.push_back(0);
	//v.push_back(1);
	//v.push_back(2);
	//v.push_back(3);
	//v.push_back(4);
	//......

	//option 2: little typos, logical errors, type conversion warnings...
	/*for (size_t i = 0; i < v.size(); ++i) {
		v[i] = i;
	}*/

	//option 3 C++ 98...
	/*std::generate(begin(v), end(v), f);*/
	// ... 'f' is defined away from the call
	// ... users a global variable or, static function variable( wastes space for the duration of the program)
	// ... either leaves a name in the global space, or cannot be restarted (if static)

	//option 4...
	//struct ramp {
	//	double x = -1;
	//	double operator()(void) { return x += 2; } // functors allow objects to be called like a function
	//} localRamp;
	//generate(begin(v), end(v), localRamp);
	//// ... a lot of typing
	//// ... added a local variable, that we won't use past the 'generate'
	//// ... the type 'ramp' is now hanging around.


	//LAMBDAS(since c++11)
	//==============================================================
	/*double start = -1;
	generate(begin(v), end(v), [&start]() {return start += 2.0; });*/
	//[&start] is the 'capture' which gives access to the local variable 'start'
	//and that access is by reference.
	//the 'lambdas' maybe constexpr'd, inlined at the descretion of the complier

	generate(begin(v), end(v), [start=-1.0]() mutable {return start += 2.0; });
	// no local variable, classes, etc.
	// everything 'baked-in' at the point of the call.
	// nothing 'leaks' forward

	//simplest lambdas
	auto foo = [] { return 42; };
	//[] is the lambda capture, it introduces the lambda function 
	//return type is the automatically deduced ( in this case integer)
	//{ } is the function body
	//no parameter list is required to be written if you don't have arguments/parameters
	//'foo' is called a 'closure', and can only be declared with 'auto'
	cout << foo() << endl;
	//lambdas are called just like functions.
	//this one complies to a 'constexpr'
	cout << endl;

	//lambda with an argument list...

	auto print = [](double x) {cout << x << endl; };
	print(1.2);
	for_each(begin(v), end(v), print);
	/*Expands to :
	* void for_each(vector<double>::iterator b,vector<double>::iterator e, func print){
	*	while(b!=e)
	*		print(*b++);
	* }
	* 
	* further expanded to:
	* double* b = begin(v); // placed in a CPU register
	* double* e = end(v);   // placed in a CPU register
	* while(b!=e)
	*	cout << *b++ << endl;
	*/
	cout << endl;


	//adding a custom return type
	transform(begin(v), end(v), begin(v),
		[](double i) -> double {if (i < 7)return -1; else return i; }
	);

	//'->double' indicates that we want the lambda to return a double(therefore non-doubles will be cast)


	//with a capture
	double limit = 10.0;
	cout << "# > " << limit << " = " << 
		count_if(begin(v), end(v),
			/*[=](double x) -> bool {return x > limit; }*/
			[limit](double x) -> bool {return x > limit; }
			) << endl;

	// [=] tells the lambda it can read any variable visible to the local scope
	// [limit] tells the lambda it can read the local variable 'limit' but no other
	// multiple variables can be captured with a comma-separated list e.g. [foo,bar]


	// writeable captures
	v[0] = v[1] = 1;
	size_t i = 1;
	auto fib = [i, &v]() mutable { ++i; return v[i - 2] + v[i - 1]; };
	generate(begin(v) + 2, end(v), fib);
	for_each(begin(v), end(v), print);
	//[i,&v] i is passed-by-constant-value from the local scope, 'v' is passed by reference
	//'mutable' strips the 'constant' from 'i'
	//fills a vector with fibonacci values.



	//Can we make 'print' more generic?
	for_each(begin(v), end(v), [](decltype(*begin(v)) x) { cout << x << endl; });
	// '(decltype(*begin(v)) x)' == parameter hell?
	// decltype --> the declaration type of its parameter
	// the datatype of 'x' is the same as the datatype of whatever is returned from when you de-reference
	// whatever is returned by 'begin(v)'
	// decltype parameters allow the lambda type to match the vector's value_type ( whatever it turns out to be).


	// C++ 14 - lambdas are now genecric
	auto generic_square = [](auto a) {return a * a; };
	cout << generic_square(4) << ', ' << generic_square(3.4) << endl;

	std::iota(begin(v), end(v), 1); // starting with '1', assigns the value to the first element fo the range, then increments. ( enum )
	sort(begin(v), end(v), [](auto lhs, auto rhs) { return lhs > rhs; });
	for_each(begin(v), end(v), [](auto e) {cout << e << " "; });

	//Extended captures(C++ 14)
	auto timer = [val = std::chrono::system_clock::now()]{ return std::chrono::system_clock::now() - val; };
	//'val' initialized once
	cout << endl << timer().count() << endl;
	cout << "Do something" << endl;
	cout << timer().count() << endl;

	//a better fill using extended capture
	generate(begin(v), end(v), [n = -1.0]() mutable {return n += 2.0; });

	//C++ 17 - lambdas can be constexpr
	constexpr auto csquare = [](auto n) {return n * n; };
	constexpr array arr{ csquare(1), csquare(2), csquare(3) };

	//C++ 20(work-in-progress for VC++) adding constexpr algorithms that mix with constexpr lambdas and dynamic containers like vector.
	
	//More C++20
	auto equalArbitary = [](auto lhs, auto rhs) {return lhs == rhs; };

	bool b = equalArbitary(4, true); // warning from inside the lambdas: mixing int and bool is unsafe.

	//force th be the same
	auto equalConvertable = [](auto lhs, decltype(lhs) rhs) {return lhs == rhs; };
	b = equalConvertable(4, true); // good! force rhs type to match lhs type ==> the bool is implicitly cast to an int
			// 'b' == false since true casts to integer '1' which is not equal to integer 4

	b = equalConvertable(true, 4); // good! force rhs type to match lhs type ==> the bool is implicitly cast to an int
			// 'b' == 'true' since integer '4' casts to bool 'true' which is a match.

	//templated lambdas!
	auto equalMatched = []<typename T>(T lhs, T rhs) { return lhs = rhs; };
	//b = equalMatched(4, true); // error, types don't match
	b = equalMatched(4, 42); // good, types matchj




	return 0;
}