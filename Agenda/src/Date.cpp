#include "Date.hpp"
#include <iostream>
using namespace std;


bool isNum(char letter) {
	if (letter >= '0' && letter <= '9') return true;
	else return false;
}

Date::Date() {
	m_year = 0;
	m_month = 0;
	m_day = 0;
	m_hour = 0;
	m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
	m_year = t_year;
	m_month = t_month;
	m_day = t_day;
	m_hour = t_hour;
	m_minute = t_minute;
}

Date::Date(std::string dateString) {
	if (dateString.length() == 16 && dateString[4] == '-'
	    	&& dateString[7] == '-' && dateString[10] == '/' && dateString[13] == ':'
	    	&& isNum(dateString[0]) && isNum(dateString[1]) && isNum(dateString[2])
	    	&& isNum(dateString[3]) && isNum(dateString[5]) && isNum(dateString[6])
	    	&& isNum(dateString[8]) && isNum(dateString[9]) && isNum(dateString[11])
	    	&& isNum(dateString[12]) && isNum(dateString[14]) && isNum(dateString[15])) {
		m_year = (dateString[0]-'0')*1000 + (dateString[1]-'0')*100 + (dateString[2]-'0')*10 + (dateString[3]-'0');
		m_month = (dateString[5]-'0')*10 + (dateString[6]-'0');
		m_day = (dateString[8]-'0')*10 + (dateString[9]-'0');
		m_hour = (dateString[11]-'0')*10 + (dateString[12]-'0');
		m_minute = (dateString[14]-'0')*10 + (dateString[15]-'0');
	} else {
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_hour = 0;
		m_minute = 0;
	}
}

int Date::getYear(void) const {
	return m_year;
}

void Date::setYear(const int t_year) {
	m_year = t_year;
}

int Date::getMonth(void) const {
	return m_month;
}

void Date::setMonth(const int t_month) {
	m_month = t_month;
}

int Date::getDay(void) const {
	return m_day;
}

void Date::setDay(const int t_day) {
	m_day = t_day;
}

int Date::getHour(void) const {
	return m_hour;
}

void Date::setHour(const int t_hour) {
	m_hour = t_hour;
}

int Date::getMinute(void) const {
	return m_minute;
}

void Date::setMinute(const int t_minute) {
	m_minute = t_minute;
}

bool Date::isValid(const Date t_date) {
	if (t_date.getYear() < 1000 || t_date.getYear() > 9999) return false;
	if (t_date.getMonth() < 1 || t_date.getMonth() > 12) return false;
	if (t_date.getYear() % 400 == 0 || (t_date.getYear() % 4 == 0 && t_date.getYear() % 100 != 0)) {
		if (t_date.getMonth() == 2 && (t_date.getDay() > 29 || t_date.getDay() < 1)) return false;
	} else if (t_date.getMonth() == 2 && (t_date.getDay() > 28 || t_date.getDay() < 1)) return false;
	int mth = t_date.getMonth();
	if (mth == 1 || mth == 3 || mth == 5 || mth == 7 || mth == 8 || mth == 10 || mth == 12) {
		if (t_date.getDay() > 31 || t_date.getDay() < 1) return false;
	}
	if (mth == 4 || mth == 6 || mth == 9 || mth == 11) {
		if (t_date.getDay() > 30 || t_date.getDay() < 1) return false;
	}
	if (t_date.getHour() < 0 || t_date.getHour() > 23) return false;
	if (t_date.getMinute() < 0 || t_date.getMinute() > 59) return false;
	return true;
}

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
Date Date::stringToDate(const std::string t_dateString) {
	if (t_dateString.length() == 16 && t_dateString[4] == '-'
	    && t_dateString[7] == '-' && t_dateString[10] == '/' && t_dateString[13] == ':'
	    && isNum(t_dateString[0]) && isNum(t_dateString[1]) && isNum(t_dateString[2])
	    && isNum(t_dateString[3]) && isNum(t_dateString[5]) && isNum(t_dateString[6])
	    && isNum(t_dateString[8]) && isNum(t_dateString[9]) && isNum(t_dateString[11])
	    && isNum(t_dateString[12]) && isNum(t_dateString[14]) && isNum(t_dateString[15])) {
		
		Date re(t_dateString);
		return re;
	}
	Date iniRe;
	return iniRe;
}

std::string Date::dateToString(Date t_date) {
	string re = "0000-00-00/00:00";
	if (!isValid(t_date)) return re;
	re[0] = t_date.getYear() / 1000 + '0';
	re[1] = (t_date.getYear() / 100) % 10 + '0';
	re[2] = (t_date.getYear() % 100) / 10 + '0';
	re[3] = t_date.getYear() % 10 + '0';
	re[5] = t_date.getMonth() / 10 + '0';
	re[6] = t_date.getMonth() % 10 + '0';
	re[8] = t_date.getDay() / 10 + '0';
	re[9] = t_date.getDay() % 10 + '0';
	re[11] = t_date.getHour() / 10 + '0';
	re[12] = t_date.getHour() % 10 + '0';
	re[14] = t_date.getMinute() / 10 + '0';
	re[15] = t_date.getMinute() % 10 + '0';
	return re;
}

  /**
  *  @brief overload the assign operator
  */
Date &Date::operator=(const Date &t_date) {
	m_year = t_date.getYear();
	m_month = t_date.getMonth();
	m_day = t_date.getDay();
	m_hour = t_date.getHour();
	m_minute = t_date.getMinute();
	return *this;
}

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
bool Date::operator==(const Date &t_date) const {
	if (m_year == t_date.getYear() && m_month == t_date.getMonth()
		&& m_day == t_date.getDay() && m_hour == t_date.getHour() && m_minute == t_date.getMinute())
		return true;
	else return false;
}

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
bool Date::operator>(const Date &t_date) const {
	int y1 = m_year, y2 = t_date.getYear();
	int mth1 = m_month, mth2 = t_date.getMonth();
	int d1 = m_day, d2 = t_date.getDay();
	int h1 = m_hour, h2 = t_date.getHour();
	int min1 = m_minute, min2 = t_date.getMinute();

	if ((y1 > y2) ||
		(y1 == y2 && mth1 > mth2) ||
		(y1 == y2 && mth1 == mth2 && d1 > d2) ||
		(y1 == y2 && mth1 == mth2 && d1 == d2 && h1 > h2) ||
		(y1 == y2 && mth1 == mth2 && d1 == d2 && h1 == h2 && min1 > min2)) return true;
	else return false;
}

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
bool Date::operator<(const Date &t_date) const {
	if (*this > t_date || *this == t_date) return false;
	else return true;
}

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
bool Date::operator>=(const Date &t_date) const {
	if (*this > t_date || *this == t_date) return true;
	else return false;
}

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
bool Date::operator<=(const Date &t_date) const {
	if (*this < t_date || *this == t_date) return true;
	else return false;
}