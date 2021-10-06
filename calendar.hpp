#pragma once
/*	calendar.hpp

	Calendar library declarations.

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

#include <string>
#include <limits>
#include <cassert>

// TYPES
// --------------------------------------------------------------------------------------

using jd_t = double;		// Julian date (JD)

using year_t = long long;	// year +/- 24 billion
using month_t = int;		// month [1..12]
using day_t = int;			// day [1..31]


// VALUES
// --------------------------------------------------------------------------------------

double constexpr EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;
enum civil_month_codes_long { January = 1, February, March, April, May, June, July, August, September, October, November, December };
enum civil_month_codes_short { JAN = January, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
enum civil_weekday_codes_long { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
enum civil_weekday_codes_short { MON = Monday, TUE, WED, THU, FRI, SAT, SUN };



// FUNCTIONS
// --------------------------------------------------------------------------------------
namespace utility {
	inline double mod(double a, double b) { return a - b * floor(a / b); }
	inline double jwday(double j) { return mod(floor(j + 1.5), 7.0); }
};


namespace civil {
	// month functions

	/*! Get the full name of the civil month.
		\return pointer to the month name as a c-string.
		\param month [in] month number [1..12]
	*/
	constexpr char const* month_name_long(month_t month) {
		constexpr char const* names[] = {
			"",
			"January", "February", "March", "April", "May", "June",
			"July", "August", "September", "October", "November", "December"
		};

		assert(month > 0);
		assert(month < 13);
		return names[month];
	}



	/*! Get the short name of the civil month.
		\return pointer to the 3-letter month name as a c-string.
		\param month [in] month number [1..12]
	*/
	constexpr char const* month_name_short(month_t month) {
		constexpr char const* names[] = {
			"",
			"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
			"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
		};

		assert(month > 0);
		assert(month < 13);
		return names[month];
	}


	// day functions

	/*! Get the full name of the civil day of week.
		\return pointer to the day name as a c-string.
		\param day [in] day number [0..6], where 0 = Monday
	*/
	constexpr char const* day_name(day_t day) {
		constexpr char const* names[] = {
			"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
		};
		assert(day >= 0);
		assert(day < 7);
		return names[day];
	}

	inline day_t day_of_week(jd_t jd) { return static_cast<day_t>(utility::mod(jd + 0.5, 7)); }


	/*!	Returns the number of days in the given month of the civil calendar.
		\return The number of days in the given month.
		\param month [in] month number [1..12]
		\param isLeapYear [in] 'true' for leapyear, 'false' otherwise.
	*/
	constexpr day_t days_in_month(month_t month, bool isLeapYear) {
		constexpr day_t daysInMonth[2][13] = {
			0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
			0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
		};
		return daysInMonth[isLeapYear][month];
	}
};



// ALTERNATE QUERY
// ===============
template <class Calendar> inline year_t year(Calendar const& date) { return date.year(); }
template <class Calendar> inline month_t month(Calendar const& date) { return date.month(); }
template <class Calendar> inline day_t day(Calendar const& date) { return date.day(); }
