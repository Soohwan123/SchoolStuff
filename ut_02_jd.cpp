/*	ut_02_jd.cpp

	Jd calendar class unit test.

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

#include <gats/TestApp.hpp>
#include <ctime>
#include "Gregorian.hpp"
using namespace std;



/* Default constructor initializes to current time. */
GATS_TEST_CASE(test_04_Jd_ctor_default) {
	time_t utcTime = time(NULL);
	Jd const nowJD;

	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	jd_t jd = gregorian_to_jd(year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday));

	GATS_CHECK_EQUAL(nowJD, jd); // uses ctor to cast jd_t to Jd
}



/* Default constructor initializes to current time suppressing time of day. */
GATS_TEST_CASE( test_05_Jd_ctor_default_no_time_of_day ) {
	time_t utcTime = time(NULL);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	Jd const nowJDN;

	jd_t jdn = gregorian_to_jd(year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday));
	GATS_CHECK_EQUAL(nowJDN, jdn);
}



/** Test literal constructors. */
GATS_TEST_CASE( test_06_Jd_ctor_literal ) {
	Jd const epochJdn( -0.5 );
	GATS_CHECK(-0.5 == epochJdn);
}



GATS_TEST_CASE( test_07_Jd_add_days ) {
	Jd d(2000);
	Jd res = d + days(10);
	GATS_CHECK(res.jd() == 2010);
	res = res - days(10);
	GATS_CHECK(res.jd() == 2000);
}



GATS_TEST_CASE( test_08_Jd_add_weeks ) {
	Jd d( 2000 );
	Jd res = d + weeks(10);
	GATS_CHECK( d + days(70) == res );
	res = res - weeks(10);
	GATS_CHECK( d == res );
}



GATS_TEST_CASE( test_09_Jd_add_years ) {
	Jd d = 2000;
	double const astroYears = 10.4;
	Jd res = d + years(astroYears);
	GATS_CHECK( 2000 + EARTH_ORBITAL_PERIOD_DAYS * astroYears == res );
	res = d - years(astroYears);
	GATS_CHECK( 2000 - EARTH_ORBITAL_PERIOD_DAYS * astroYears == res );
}


//
//GATS_TEST_CASE( test_10_Jd_day_of_week ) {
//	Gregorian g(2012, September, 24);  // a Monday
//
//	GATS_CHECK( day_of_week( g ) == Monday );
//}



GATS_TEST_CASE( Test_11_Jd_relational ) {
	Jd low( 2009 );
	Jd high( 2010 );
	Jd copyLow( low );

	GATS_CHECK( low == copyLow );
	GATS_CHECK( low < high );
	GATS_CHECK( low <= copyLow );
	GATS_CHECK( high >= low );
	GATS_CHECK( high > low );
	GATS_CHECK( high != low );
}



GATS_TEST_CASE( test_12_Jd_to_string ) {
	GATS_CHECK_EQUAL( Jd( 0 ).to_string(), std::string("JD 0") );
	GATS_CHECK_EQUAL( Jd( 10'000 ).to_string(), std::string("JD 10000") );
	GATS_CHECK_EQUAL( Jd( -10 ).to_string(), std::string("JD -10") );

	std::ostringstream oss;
	oss << Jd(0.5);
	GATS_CHECK_EQUAL( oss.str(), std::string("JD 0.5") );
}
