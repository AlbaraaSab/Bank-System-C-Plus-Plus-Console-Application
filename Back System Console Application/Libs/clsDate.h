#pragma warning (disable : 4996)
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsDate
{

private:
	short _Day;
	short _Month;
	short _Year;
	short _Hour;
	short _Minute;
	short _Second;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
		_Hour = now->tm_hour;
		_Minute = now->tm_min;
		_Second = now->tm_sec;
	}

	clsDate(short day, short month, short year, short hour = 0, short minute = 0, short second = 0)
	{
		_Day = day;
		_Month = month;
		_Year = year;
		_Hour = hour;
		_Minute = minute;
		_Second = second;
	}

	clsDate(string date)
	{
		StringToDate(date);
	}

	clsDate(short day, short year)
	{
		TotalDaysToDate(day, year);
	}

	void setDay(short day)
	{
		_Day = day;
	}

	short getDay()
	{
		return _Day;
	}

	void setMonth(short month)
	{
		_Month = month;
	}

	short getMonth()
	{
		return _Month;
	}

	void setYear(short year)
	{
		_Year = year;
	}

	short getYear()
	{
		return _Year;
	}

	void setHour(short hour)
	{
		_Hour = hour;
	}

	short getHour()
	{
		return _Hour;
	}

	void setMinute(short minute)
	{
		_Minute = minute;
	}

	short getMinute()
	{
		return _Minute;
	}

	void setSecond(short second)
	{
		_Second = second;
	}

	short getSecond()
	{
		return _Second;
	}


	__declspec(property(get = getDay, put = setDay)) short Day;
	__declspec(property(get = getMonth, put = setMonth)) short Month;
	__declspec(property(get = getYear, put = setYear)) short Year;
	__declspec(property(get = getHour, put = setHour)) short Hour;
	__declspec(property(get = getMinute, put = setMinute)) short Minute;
	__declspec(property(get = getSecond, put = setSecond)) short Second;

	enum enDateCompare
	{
		Before = -1,
		Equal = 0,
		After = 1,
	};

	static bool LeapYear(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool LeapYear()
	{
		return LeapYear(_Year);
	}

	static short NumberOfDaysinYear(short year)
	{
		return LeapYear(year) ? 366 : 365;
	}

	short NumberOfDaysinYear()
	{
		return NumberOfDaysinYear(_Year);
	}

	static short NumberOfHoursinYear(short year)
	{
		return NumberOfDaysinYear(year) * 24;
	}

	short NumberOfHoursinYear()
	{
		return NumberOfDaysinYear(_Year) * 24;
	}

	static int NumberOfMinutsinYear(short year)
	{
		return NumberOfHoursinYear(year) * 60;
	}
	
	int NumberOfMinutsinYear()
	{
		return NumberOfHoursinYear(_Year) * 60;
	}

	static int NumberOfSecondsinYear(short year)
	{
		return NumberOfMinutsinYear(year) * 60;
	}
	
	int NumberOfSecondsinYear()
	{
		return NumberOfMinutsinYear(_Year) * 60;
	}

	static short NumberOfDaysinMonth(short year, short month)
	{
		if (month < 1 || month > 12)
		{
			return 0;
		}

		short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (month == 2) ? (LeapYear(year) ? 29 : 28) : NumberOfDays[month - 1];
	}
	
	short NumberOfDaysinMonth()
	{
		return NumberOfDaysinMonth(_Year, _Month);
	}

	static short NumberOfHoursinMonth(short year, short month)
	{
		return NumberOfDaysinMonth(year, month) * 24;
	}

	short NumberOfHoursinMonth()
	{
		return NumberOfHoursinMonth(_Year, _Month);
	}

	static int NumberOfMinutsinMonth(short year, short month)
	{
		return NumberOfHoursinMonth(year, month) * 60;
	}

	int NumberOfMinutsinMonth()
	{
		return NumberOfMinutsinMonth(_Year, _Month);
	}

	static int NumberOfSecondsinMonth(short year, short month)
	{
		return NumberOfMinutsinMonth(year, month) * 60;
	}

	int NumberOfSecondsinMonth()
	{
		return NumberOfSecondsinMonth(_Year, _Month) * 60;
	}

	static short TotalDaysFromTheBeginningOfYear(short day, short month, short year)
	{
		short totalDays = 0;

		for (short i = 1; i <= month - 1; i++)
		{
			totalDays += NumberOfDaysinMonth(year, i);
		}
		return totalDays + day;
	}

	short TotalDaysFromTheBeginningOfYear()
	{
		return TotalDaysFromTheBeginningOfYear(_Day, _Month, _Year);
	}

	static bool isLastDayInMonth(clsDate Date)
	{
		short MonthDays = NumberOfDaysinMonth(Date.Year, Date.Month);

		return (Date.Day == MonthDays);
	}

	bool isLastDayInMonth()
	{
		return isLastDayInMonth(clsDate(_Day, _Month, _Year));
	}

	static bool isLastMonth(clsDate Date)
	{
		return (Date.Month == 12);
	}

	bool isLastMonth()
	{
		return isLastMonth(clsDate(_Day, _Month, _Year));
	}

	static clsDate IncreaseDateByOneDay(clsDate & Date)
	{
		if (isLastDayInMonth(Date))
		{
			if (isLastMonth(Date))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate & Date, short x)
	{
		for (short i = 0; i < x; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short x)
	{
		IncreaseDateByXDays(*this, x);
	}
	
	static clsDate IncreaseDateByOneWeek(clsDate & Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}
	
	static clsDate IncreaseDateByXWeeks(clsDate Date, short x)
	{
		for (short i = 0; i < x; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short x)
	{
		for (short i = 0; i < x; i++)
		{
			IncreaseDateByOneWeek();
		}
	}
	
	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short MonthDays = NumberOfDaysinMonth(Date.Year, Date.Month);

		if (Date.Day > MonthDays)
		{
			Date.Day = MonthDays;
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		if (_Month == 12)
		{
			_Month = 1;
			_Year++;
		}
		else
		{
			_Month++;
		}

		short MonthDays = NumberOfDaysinMonth(_Year, _Month);

		if (_Day > MonthDays)
		{
			_Day = MonthDays;
		}
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, short x)
	{
		for (size_t i = 0; i < x; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonths(short x)
	{
		for (size_t i = 0; i < x; i++)
		{
			IncreaseDateByOneMonth();
		}
	}
	
	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;

		return Date;
	}
	
	void IncreaseDateByOneYear()
	{
		_Year++;
	}

	static clsDate IncreaseDateByXYears(clsDate Date, short x)
	{
		for (short i = 0; i < x; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	void IncreaseDateByXYears(short x)
	{
		for (short i = 0; i < x; i++)
		{
			IncreaseDateByOneYear();
		}
	}
	
	static clsDate IncreaseDateByXYearsFaster(clsDate Date, short x)
	{
		Date.Year += x;

		return Date;
	}

	void IncreaseDateByXYearsFaster(short x)
	{
		_Year += x;
	}
	
	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		Date.Year += 10;
		return Date;
	}
	
	void IncreaseDateByOneDecade()
	{
		_Year += 10;
	}
	
	static clsDate IncreaseDateByXDecades(clsDate Date, short x)
	{
		for (short i = 0; i < x; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;
	}

	void IncreaseDateByXDecades(short x)
	{
		for (short i = 0; i < x; i++)
		{
			IncreaseDateByOneDecade();
		}
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate Date, short x)
	{
		Date.Year += (10 * x);

		return Date;
	}

	void IncreaseDateByXDecadesFaster(short x)
	{
		_Year += (10 * x);
	}
	
	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		Date.Year += 100;

		return Date;
	}
	
	void IncreaseDateByOneCentury()
	{
		_Year += 100;
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year += 1000;

		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}


	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysinMonth(Date.Year, Date.Month);
			}

		}
		else
		{
			Date.Day--;
		}

		return Date;
	}
	
	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short Days)
	{
		for (short i = 0; i < Days; i++)
		{
			DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		for (short i = 0; i < 7; i++)
		{
			DecreaseDateByOneDay();
		}
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
		{
			DecreaseDateByOneWeek(Date);
		}
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
		{
			DecreaseDateByOneWeek();
		}
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}

		short MonthDays = NumberOfDaysinMonth(Date.Year, Date.Month);

		if (Date.Day > MonthDays)
		{
			Date.Day = MonthDays;
		}
	}

	void DecreaseDateByOneMonth()
	{
		if (_Month == 1)
		{
			_Month = 12;
			_Year--;
		}
		else
		{
			_Month--;
		}

		short MonthDays = NumberOfDaysinMonth(_Year, _Month);

		if (_Day > MonthDays)
		{
			_Day = MonthDays;
		}
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, short Months)
	{
		for (short i = 0; i < Months; i++)
		{
			DecreaseDateByOneMonth(Date);
		}
	}

	void DecreaseDateByXMonths(short Months)
	{
		for (short i = 0; i < Months; i++)
		{
			DecreaseDateByOneMonth();
		}
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;
	}

	void DecreaseDateByOneYear()
	{
		_Year--;
	}

	static clsDate DecreaseDateByXYears(clsDate Date, short Years)
	{
		for (short i = 0; i < Years; i++)
		{
			DecreaseDateByOneYear(Date);
		}
	}

	void DecreaseDateByXYears(short Years)
	{
		for (short i = 0; i < Years; i++)
		{
			DecreaseDateByOneYear();
		}
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate Date, short Years)
	{
		Date.Year -= Years;
	}

	void DecreaseDateByXYearsFaster(short Years)
	{
		_Year -= Years;
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		Date.Year -= 10;
	}

	void DecreaseDateByOneDecade()
	{
		_Year -= 10;
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, short Decades)
	{
		for (short i = 0; i < Decades; i++)
		{
			DecreaseDateByOneDecade(Date);
		}
	}

	void DecreaseDateByXDecades(short Decades)
	{
		for (short i = 0; i < Decades; i++)
		{
			DecreaseDateByOneDecade();
		}
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate Date, short Decades)
	{
		Date.Year -= (10 * Decades);
	}

	void DecreaseDateByXDecadesFaster(short Decades)
	{
		_Year -= (10 * Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		Date.Year -= 100;
	}

	void DecreaseDateByOneCentury()
	{
		_Year -= 100;
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year -= 1000;
	}

	void DecreaseDateByOneMillennium()
	{
		_Year -= 1000;
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? ((Date1.Month < Date2.Month) ? true : (Date1.Month == Date2.Month) ? Date1.Day < Date2.Day : false) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return ((Date1.Year == Date2.Year) ? (Date1.Month == Date2.Month) ? (Date1.Day == Date2.Day) : false : false);
	}
	
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}


	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		return IsDate1AfterDate2(Date1, Date2) ? enDateCompare::After : IsDate1EqualDate2(Date1, Date2) ? enDateCompare::Equal : enDateCompare::Before;
	}

	enDateCompare CompareDates(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2) ? enDateCompare::After : IsDate1EqualDate2(*this, Date2) ? enDateCompare::Equal : enDateCompare::Before;
	}

	static int DifferenceInDaysBetwennTwoDates(clsDate Date1, clsDate Date2, bool isEndDay = true)
	{
		int Diff = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Diff++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return isEndDay ? ++Diff : Diff;
	}

	int DifferenceInDaysBetwennTwoDates(clsDate Date2, bool isEndDay = true)
	{
		int Diff = 0;

		while (IsDate1BeforeDate2(*this, Date2))
		{
			Diff++;
			IncreaseDateByOneDay();
		}

		return isEndDay ? ++Diff : Diff;
	}

	static clsDate Now()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	void DateNow()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return DifferenceInDaysBetwennTwoDates(DateOfBirth, clsDate::Now(), true);
	}

	static void  SwapDates(clsDate& Date1, clsDate& Date2)
	{

		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;

	}

	static short DayOfWeekOrder(short year, short month, short day)
	{
		short a, y, m, d;

		a = (14 - month) / 12;

		y = year - a;
		m = month + (12 * a) - 2;

		d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;

		return d;
	}

	short DayOfWeekOrder()
	{
		short a, y, m, d;

		a = (14 - _Month) / 12;

		y = _Year - a;
		m = _Month + (12 * a) - 2;

		d = (_Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;

		return d;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
	}

	static string DayOfWeekName(short DayOrder)
	{
		string array[7] = { "Sun", "Mon", "Tus", "Wed", "Thu", "Fri", "Sat" };

		return array[DayOrder];
	}

	static short IsEndOfWeek(clsDate Date)
	{
		return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}

	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		//Weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd()
	{
		return  IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		//Weekends are Sun,Mon,Tue,Wed and Thur

	   /*
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex >= 5 && DayIndex <= 4);
	   */

	   //shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(Date);

	}

	bool IsBusinessDay()
	{
		return  IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(short DayOrder)
	{
		return 6 - DayOrder;
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		clsDate EndDate;
		EndDate.Day = NumberOfDaysinMonth(Date.Year, Date.Month);
		EndDate.Month = Date.Month;
		EndDate.Year = Date.Year;

		return DifferenceInDaysBetwennTwoDates(Date, EndDate, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		clsDate EndDate;
		EndDate.Day = NumberOfDaysinMonth(_Year, _Month);
		EndDate.Month = _Month;
		EndDate.Year = _Year;

		return DifferenceInDaysBetwennTwoDates(*this, EndDate, true);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		clsDate EndDate;
		EndDate.Day = 31;
		EndDate.Month = 12;
		EndDate.Year = Date.Year;

		return DifferenceInDaysBetwennTwoDates(Date, EndDate, true);
	}

	short DaysUntilTheEndOfYear()
	{
		clsDate EndDate;
		EndDate.Day = 31;
		EndDate.Month = 12;
		EndDate.Year = _Year;

		return DifferenceInDaysBetwennTwoDates(*this, EndDate, true);
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return Days;

	}

	static short VacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short VacDays = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
			{
				VacDays++;
			}
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return VacDays;
	}

	short VacationDays(clsDate DateTo)
	{
		short VacDays = 0;

		while (IsDateBeforeDate2(DateTo))
		{
			if (IsBusinessDay(*this))
			{
				VacDays++;
			}
			IncreaseDateByOneDay();
		}

		return VacDays;
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacaDays)
	{
		for (short i = 0; i < VacaDays; i++)
		{
			if (IsWeekEnd(DateFrom))
			{
				VacaDays++;
			}
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}

	void CalculateVacationReturnDate(short VacaDays)
	{
		for (short i = 0; i < VacaDays; i++)
		{
			if (IsWeekEnd(*this))
			{
				VacaDays++;
			}
			IncreaseDateByOneDay();
		}
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Day < 1 || Date.Day > 31)
		{
			return false;
		}
		else if (Date.Month < 1 || Date.Month > 12)
		{
			return false;
		}
		else if (Date.Month == 2)
		{
			if (LeapYear(Date.Year))
			{
				if (Date.Day > 29)
				{
					return false;
				}
			}
			else
			{
				if (Date.Day > 28)
				{
					return false;
				}
			}

		}
		else if (Date.Day > NumberOfDaysinMonth(Date.Year, Date.Month))
		{
			return false;
		}

		return true;
	}

	bool IsValidDate()
	{
		if (_Day < 1 || _Day > 31)
		{
			return false;
		}
		else if (_Month < 1 || _Month > 12)
		{
			return false;
		}
		else if (_Month == 2)
		{
			if (LeapYear(_Year))
			{
				if (_Day > 29)
				{
					return false;
				}
			}
			else
			{
				if (_Day > 28)
				{
					return false;
				}
			}

		}
		else if (_Day > NumberOfDaysinMonth(_Year, _Month))
		{
			return false;
		}

		return true;
	}

	void TotalDaysToDate(short totalDays, short year)
	{
		short day = totalDays;
		short MonthDays = 0;

		_Year = year;
		_Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysinMonth(year, _Month);

			if (day > MonthDays)
			{
				day -= MonthDays;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = day;
				break;
			}
		}
	}

	static clsDate StringToDate(string str, string Delim)
	{
		vector<string> DateString = clsString::Split(str, Delim);

		clsDate Date;
		Date.Day = stoi(DateString[0]);
		Date.Month = stoi(DateString[1]);
		Date.Year = stoi(DateString[2]);

		return Date;
	}

	void StringToDate(string str)
	{
		vector<string> DateString = clsString::Split(str, "/");

		_Day = stoi(DateString[0]);
		_Month = stoi(DateString[1]);
		_Year = stoi(DateString[2]);
	}
	
	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{

		return DateToString(*this);
	}
	
	static string DateTimeToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year) + " - " + to_string(Date.Hour) + ":" + to_string(Date.Minute) + ":" + to_string(Date.Second);
	}

	static string FormatDate(clsDate Date, string format = "dd/mm/yyyy")
	{
		string FormattedDateString = "";
		FormattedDateString = clsString::ReplaceWordInString(format, "dd", to_string(Date.Day));
		FormattedDateString = clsString::ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = clsString::ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date.Year));

		return FormattedDateString;
	}

	string FormatDate(string format = "dd/mm/yyyy")
	{
		string FormattedDateString = "";
		FormattedDateString = clsString::ReplaceWordInString(format, "dd", to_string(_Day));
		FormattedDateString = clsString::ReplaceWordInString(FormattedDateString, "mm", to_string(_Month));
		FormattedDateString = clsString::ReplaceWordInString(FormattedDateString, "yyyy", to_string(_Year));

		return FormattedDateString;
	}

	void Print()
	{
		cout << DateToString() << endl;
	}

	static string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
						   "Apr", "May", "Jun",
						   "Jul", "Aug", "Sep",
						   "Oct", "Nov", "Dec"
		};

		return (Months[MonthNumber - 1]);
	}

	string MonthShortName()
	{

		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;

		// Index of the day from 0 to 6
		int current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysinMonth(Year, Month);

		// Print the current month name
		printf("\n  _______________%s_______________\n\n",
			MonthShortName(Month).c_str());

		// Print the columns
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		// Print appropriate spaces
		int i;
		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);


			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");

	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintYearCalendar(int Year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", Year);
		printf("  _________________________________\n");


		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}

		return;
	}

	void PrintYearCalendar()
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", _Year);
		printf("  _________________________________\n");


		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, _Year);
		}

		return;
	}

};

