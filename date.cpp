#define _CRT_SECURE_NO_WARNINGS

#include "date.h"

Date::Date()
{
	time_t sec = time(NULL);
	tm* time_info = localtime(&sec);

	year_		= time_info->tm_year + 1900;
	month_		= time_info->tm_mon + 1;
	day_		= time_info->tm_mday;
	hours_		= time_info->tm_hour;
	minutes_	= time_info->tm_min;
	seconds_	= time_info->tm_sec;
}

Date::Date(int day, int month, int year, int hours, int minutes, int seconds) :
			day_(day), month_(month), year_(year), hours_(hours), minutes_(minutes), seconds_(seconds) {}

void Date::set_day(const int day)			{ day_		= day; }
void Date::set_month(const int month)		{ month_	= month; }
void Date::set_year(const int year)			{ year_		= year; }
void Date::set_hours(const int hours)		{ hours_	= hours; }
void Date::set_minutes(const int minutes)	{ minutes_	= minutes; }
void Date::set_seconds(const int seconds)	{ seconds_	= seconds; }
Date* Date::set_current_time()				{ return new Date(); }

int	Date::get_day()		const	{ return day_; }
int	Date::get_month()	const	{ return month_; }
int	Date::get_year()	const	{ return year_; }
int	Date::get_hours()	const	{ return hours_; }
int	Date::get_minutes() const	{ return minutes_; }
int	Date::get_seconds() const	{ return seconds_; }

string Date::get_date() const
{
	string initial_date;
	if (day_ < 10) { initial_date += "0"; }
	initial_date += to_string(day_) + ".";
	if (month_ < 10) { initial_date += "0"; }
	initial_date += to_string(month_) + "." + to_string(year_) + " " + to_string(hours_) + ":";
	if (minutes_ < 10) { initial_date += "0"; }
	initial_date += to_string(minutes_) + ":";
	if (seconds_ < 10) { initial_date += "0"; }
	initial_date += to_string(seconds_);

	return initial_date;
}

void Date::modify_date(int day, int month, int year, int hours, int minutes, int seconds)
{
	year_		= year;
	month_		= month;
	day_		= day;
	hours_		= hours;
	minutes_	= minutes;
	seconds_	= seconds;
}

void Date::delete_date()
{
	year_		= 0;
	month_		= 0;
	day_		= 0;
	hours_		= 0;
	minutes_	= 0;
	seconds_	= 0;
}
