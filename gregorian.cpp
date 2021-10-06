/*	gregorian.cpp

	Gregorian calendar class implementation.

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
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>


/**	Gregorian default constructor.  Initialize to the current local time. */
Gregorian::Gregorian() {
	time_t nowTime = time(NULL);
	struct tm tmNow;
	localtime_s(&tmNow, &nowTime);
	year_ = year_t(tmNow.tm_year) + 1900;
	month_ = month_t(tmNow.tm_mon) + 1;
	day_ = day_t(tmNow.tm_mday);
}

/** Print the Gregorian Date as a string. */
std::string Gregorian::to_string() const {
	std::ostringstream oss;
	oss << civil::day_name(civil::day_of_week(to_jd())) << ", ";
	oss << gregorian_month_name(month_) << ' ' << (unsigned)day_ << ' ';
	if (year_ <= 0)
		oss << (-year_ + 1) << " BCE";
	else
		oss << year_ << " CE";
	return oss.str();
}


/** Gregorian + (integer year) operator. */
Gregorian operator + (Gregorian const& dt, detail::packaged_year_integer const& year) {
	year_t y = dt.year() + year.nYears_;
	month_t m = dt.month();
	day_t d = dt.day();
	if (m == February && d == 29 && !is_gregorian_leapyear(y))
		d = 28;
	return Gregorian(y, m, d);
}


/** Gregorian + (integer month) operator. */
Gregorian operator + (Gregorian const& dt, detail::packaged_month_integer const& month) {
	year_t yearsToAdd = month.nMonths_ / 12;
	month_t monthsToAdd = month.nMonths_ % 12;
	year_t y = dt.year() + yearsToAdd;
	month_t m = dt.month() + monthsToAdd;

	int adjustment = (m - 1) / 12 + (m - 12) / 12;
	y += adjustment;
	m -= month_t(adjustment * 12);
	day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_gregorian_leapyear(y)));
	return Gregorian(y, m, d);
}
