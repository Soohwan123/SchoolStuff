#include "Rational.hpp"


std::wostream& operator << (std::wostream& ostr, const Rational& r) {
	return ostr << r.numerator() << '/' << r.denominator();
}

std::wistream& operator >> (std::wistream& istr, Rational& r) {
	Rational::int_type n = 0, d = 1;
	wchar_t c = 0;

	if (istr >> n) {
		if (istr.get(c)) {
			if (c == L'/') {
				if (istr >> std::noskipws >> d) {
					try {
						r = Rational(n, d);
					}
					catch (bad_rational&) {
						try { istr.setstate(std::ios::failbit); }
						catch (...) {}
						if (istr.exceptions() & std::ios::failbit)
							throw;
					}
				}
			}
			else
				istr.setstate(std::ios::failbit);
		}
	}
	return istr;
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}
