#ifndef DATE_H
#define DATE_H

#include <string>
#include <ctime>

using namespace std;


class Date
{
public:
	Date();
	Date(int day, int month, int year, int hours, int minutes, int seconds);

	void set_day(const int day);
	void set_month(const int month);
	void set_year(const int year);
	void set_hours(const int hours);
	void set_minutes(const int minutes);
	void set_seconds(const int seconds);
	Date* set_current_time();
	
	int	get_day() const;
	int	get_month() const;
	int	get_year() const;
	int	get_hours() const;
	int	get_minutes() const;
	int	get_seconds() const;

	string get_date() const;

	void modify_date(int day, int month, int year, int hours, int minutes, int seconds);
	void delete_date();

private:
	int	year_{ 0 };
	int	month_{ 0 };
	int	day_{ 0 };
	int	hours_{ 0 };
	int	minutes_{ 0 };
	int	seconds_{ 0 };
};
#endif // DATE_H
