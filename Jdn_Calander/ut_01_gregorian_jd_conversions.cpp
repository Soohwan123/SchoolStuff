/*	ut_01_gregorian_jd_conversions.cpp

	Calendar library unit test of Gregorian calendar base conversion functions.

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

#include "Gregorian.hpp"
#include <gats/TestApp.hpp>
#include <sstream>
using namespace std;



/*! Test known Gregorian to JD conversions. */
GATS_TEST_CASE( test_01_gregorian_to_jd ) {

	auto test = [this](year_t year, month_t month, day_t day, jd_t jd, int line) {
		auto jg = gregorian_to_jd(year, month, day);
		ostringstream oss;
		oss << "jg(" << jg << ") != jdn(" << jd << ") from line: " << line;
		GATS_CHECK_MESSAGE(jg == jd, oss.str());
	};

	test(4714_BCE, November, 24, -0.5, __LINE__);			// beginning of the Julian Epoch
	test(1, January, 1, GREGORIAN_EPOCH, __LINE__);			// January 1, 1 CE
	test(1582, October, 15, 2'299'160.5, __LINE__);			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582, December, 20, 2'299'226.5, __LINE__);		// Gregorian adoption date France
	test(1752, September, 14, 2'361'221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858, November, 16, 2'400'000 - 0.5, __LINE__);
	test(2012, September, 14, 2'456'184.5, __LINE__);
	test(2132, August, 31, 2'500'000 - 0.5, __LINE__);
}



/**	Test known JD to Gregorian conversions. */
GATS_TEST_CASE( test_02_to_gregorian ) {

	auto test = [this]( year_t year, month_t month, day_t day, jd_t jd, int line ) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_gregorian(jd, y, m, d);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		GATS_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		GATS_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		GATS_CHECK_MESSAGE(d == day, ossD.str());
	};

	test(4714_BCE, November, 24, -0.5, __LINE__);			// beginning of the Julian Epoch
	test(1, January, 1, GREGORIAN_EPOCH, __LINE__);			// January 1, 1 CE
	test(1582, October, 15, 2'299'160.5, __LINE__);			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582, December, 20, 2'299'226.5, __LINE__);		// Gregorian adoption date France
	test(1752, September, 14, 2'361'221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858, November, 16, 2'400'000 - 0.5, __LINE__);
	test(2012, September, 14, 2'456'184.5, __LINE__);
	test(2132, August, 31, 2'500'000 - 0.5, __LINE__);
}

//#define FULL_TEST
#if defined(FULL_TEST)
/**	Check all conversions from the lowest Proleptic Gregorian date, until a day well in the future. */
GATS_TEST_CASE(test_03_gregorian_full) {

	jd_t low = gregorian_to_jd(-4799, January, 1);
	jd_t high = gregorian_to_jd(4800, January, 1);
	for (jd_t jd = low; jd <= high; ++jd) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_gregorian(jd, year, month, day);
		jd_t reconvertedJd = gregorian_to_jd(year, month, day);
		GATS_CHECK_EQUAL(jd, reconvertedJd);
	}
}
#endif
