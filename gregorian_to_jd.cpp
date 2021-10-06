/*	Gregorian_to_jd.cpp

	Calendar library Gregorian conversion implementations.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.09.26
	Updated: for C++ 20

Version 2019-09-11
	Updated: for C++ 17

Version 2013-09-17
	Initial release

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include "gregorian.hpp"
#include <cassert>


/*!	Convert a Proleptic Gregorian Calendar date to a Julian Day Number
	\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
	\param month [in] 1..12
	\param day [in] 1..31
	*/
namespace detail {
	/**	Real-number implementation. */
	jd_t greg2jd_real(year_t year, month_t month, day_t dayOfMonth) {
		long long y = year - 1;
		return
			GREGORIAN_EPOCH - 1
			+ 365 * y
			+ floor(y / 4.0)
			- floor(y / 100.0)
			+ floor(y / 400.0)
			+ floor(((367.0 * month - 362.0) / 12.0)
				+ ((month <= 2)
					? 0
					: (is_gregorian_leapyear(year) ? -1 : -2)))
			+ dayOfMonth;
	}

	/*	Integer implementation (wikipedia) */
	constexpr jd_t greg2jd_integer(year_t year, month_t month, day_t day) {
		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;
		return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;
	}
}
jd_t gregorian_to_jd(year_t year, month_t month, day_t day) {
	assert(year > -4800 && "Minimum year is 4800 BCE");
	assert(month >= 1 && "Minimum month is January = 1");
	assert(month <= 12 && "Maximum month is December = 12");
	assert(day >= 1 && "Minimum day is 1");
	assert(day <= 31 && "Maximum day is 31");
	assert(detail::greg2jd_integer(year, month, day) == detail::greg2jd_real(year, month, day));
	return detail::greg2jd_integer(year, month, day);
}


namespace detail {
	/*!	Convert a Julian Day Number to the Proleptic Gregorian Calendar
		\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
		\param month [in] 1..12
		\param day [in] 1..31
	*/
	void jd_to_gregorian_real(jd_t jd, year_t& year, month_t& month, day_t& day) {
		assert(jd >= -31738.5 && "Minimum convertible date not provided.");
		using namespace utility;

		double wjd, depoch, quadricent, dqc, cent, dcent, quad, dquad, yindex, yearday, leapadj;
		wjd = floor(jd - 0.5) + 0.5;
		depoch = wjd - GREGORIAN_EPOCH;
		quadricent = floor(depoch / 146097.0);
		dqc = mod(depoch, 146097.0);
		cent = floor(dqc / 36524.0);
		dcent = mod(dqc, 36524);
		quad = floor(dcent / 1461.0);
		dquad = mod(dcent, 1461.0);
		yindex = floor(dquad / 365.0);
		year = (year_t)floor((quadricent * 400.0) + (cent * 100.0) + (quad * 4.0) + yindex);
		if (!((cent == 4.0) || (yindex == 4.0)))
			++year;

		yearday = wjd - gregorian_to_jd(year, 1, 1);
		leapadj = ((wjd < gregorian_to_jd(year, 3, 1)) ? 0 : (is_gregorian_leapyear(year) ? 1 : 2));
		month = static_cast<month_t>(floor((((yearday + leapadj) * 12) + 373) / 367));
		day = static_cast<day_t>((wjd - gregorian_to_jd(year, month, 1)) + 1);
	}

	// integer implementation
	inline void jd_to_gregorian_integer(jd_t jd, year_t& year, month_t& month, day_t& day) {
		assert(jd >= -31738.5 && "Minimum convertible date not provided.");
		jd = floor(jd - 0.5) + 0.5;
		long long j = static_cast<long long>(jd + 0.5) + 32044;
		long long g = j / 146097;
		long long dg = j % 146097;
		long long c = (dg / 36524 + 1) * 3 / 4;
		long long dc = dg - c * 36524;
		long long b = dc / 1461;
		long long db = dc % 1461;
		long long a = (db / 365 + 1) * 3 / 4;
		long long da = db - a * 365;
		long long y = g * 400 + c * 100 + b * 4 + a;
		long long m = (da * 5 + 308) / 153 - 2;
		year = y - 4800 + (m + 2) / 12;
		month = (m + 2) % 12 + 1;
		day = static_cast<day_t>(da - (m + 4) * 153 / 5 + 123);
	}
};
void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) {
	assert(jd >= -31738.5 && "Minimum convertable date not provided.");

	jd = floor(jd - 0.5) + 0.5;
	long long a = static_cast<long long>(jd + 0.5) + 32044;
	long long b = (4 * a + 3) / 146097;
	long long c = a - b * 146097 / 4;
	long long d = (4 * c + 3) / 1461;
	long long e = c - 1461 * d / 4;
	long long m = (5 * e + 2) / 153;
	day = static_cast<day_t>(e - (153 * m + 2) / 5 + 1);
	month = static_cast<month_t>(m + 3 - 12 * (m / 10));
	year = b * 100 + d - 4800 + m / 10;

#if defined( _DEBUG )
	{
	year_t y;
	month_t m;
	day_t d;
	detail::jd_to_gregorian_integer(jd, y, m, d);
	assert(year == y);
	assert(month == m);
	assert(day == d);
	detail::jd_to_gregorian_real(jd, y, m, d);
	assert(year == y);
	assert(month == m);
	assert(day == d);
	}
#endif
}
