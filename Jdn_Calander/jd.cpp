/*	Jdn.cpp

	Date and time library to_string method implementations.

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

#include "Jd.hpp"
#include "Gregorian.hpp"
#include <sstream>
#include <ctime>
using namespace std;

/**	Jd default constructor.  Initialize to the current local time. */
Jd::Jd() : jd_(0) {
	time_t nowTime = time(NULL);
	struct tm tmNow;
	localtime_s(&tmNow, &nowTime);
	jd_ = gregorian_to_jd(
		year_t(tmNow.tm_year) + 1900,
		month_t(tmNow.tm_mon) + 1,
		day_t(tmNow.tm_mday)
	);
}


/** Print the Julian Day as a string. */
std::string Jd::to_string() const {
	ostringstream oss;
	oss << "JD " << jd_;
	return oss.str();
}