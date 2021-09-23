#include <cstdint>
#include <stdexcept>
#include <ostream>
#include <istream>

//constexpr -> tells if compiler do this once while compiling just do it and never make me do it again.

template<typename T>
constexpr T gcd(T a, T b) {
	//Euclid's method
	/*if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}*/

	/*while (b != 0) {
		a %= b;
		T t = a;
		a = b;
		b = t;
	}*/

	while (b != 0) {
		T t = b;
		b = a % b;
		a = t;
	}
	return a;

}


class bad_rational : public std::domain_error {
public:
	explicit bad_rational() : std::domain_error("bad rational : zero denominator") {}
	explicit bad_rational(char const* what) : std::domain_error(what) {}
};

class Rational {
public:
	using int_type = std::intmax_t;			// Rational::int_type is an alias for the integer type

// Attributes
private:
	int_type num;
	int_type den;

// Operations
public:
	// constructors
	// Rational() : num(0), den(1) {} //default has to be 0 always in computing system
	constexpr Rational(int_type numerator = int_type(0)) : num(numerator), den(1) {} //contains both up line and this line but don't normalize cuz denominator is 1
	constexpr Rational(int_type numerator, int_type denominator) : num(numerator), den(denominator) {
		normalize();
	}

	// accessors
	constexpr int_type numerator() const { return num; }
	constexpr int_type denominator() const { return den; }

	// mutators
	constexpr void normalize();

	//relationals
	auto operator <=> (const Rational& rhs) const {
		return num * rhs.den <=> rhs.num * den;
	}

	bool operator == (const Rational& rhs) const = default;
};

constexpr void Rational::normalize() {
	// Check for denominator of zero
	if (den == 0)
		throw bad_rational();							// in GUI they can't see so we use throw
	// reduce by Greatest Common Divisor
	auto g = gcd(num, den);
	num /= g;
	den /= g;

	// Move sign to the top
	if (den < 0) {
		num = -num;
		den = -den;
	}
}

Rational operator * (const Rational& lhs, const Rational& rhs);

std::wostream& operator << (std::wostream& ostr, const Rational& r);
std::wistream& operator >> (std::wistream& istr, Rational& r);
