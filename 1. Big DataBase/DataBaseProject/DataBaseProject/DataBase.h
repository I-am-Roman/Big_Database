#pragma once

#include <sstream>
#include <set>
#include <iomanip>
#include <map>
#include <iostream>
#include <queue>
#include<tuple>
#include <string>

using namespace std;

/****************************************************************/
/*					D A T E   A N D   D A T A B A S E			*/
/****************************************************************/
struct Date
{
	int year; // can be less than zero
	int month;
	int day;
};//Date

class DataBase
{
private:
	map <Date, set<string>> database;
	Date date;
	string event;
public:
	// Finding with condition
	DataBase Find_Date(const Date& date, const string& condition);
	DataBase Find(istream& stream, DataBase& dtbs);
	DataBase Find_Event(const string& event, const string& condition);
	size_t Del(DataBase& db2);

	void Add(const Date& d, const string& ev); 
	void AddInDataBase(const Date& d, set<string>& ev);
	// DataBase is empty ?  
	bool empty();
	void Print();
	// Clear all database
	size_t Clear();

	// union and intersection
	void operator+= (const DataBase& db2);
	void operator-= (DataBase& db2);

};

/****************************************************************/
/*            В   З А Г О Л О В О Ч Н Ы Й   Ф А Й Л             */
/****************************************************************/

/*Realization without "(" and ")"*/
void EnsureNextSymbolAndSkip(istream& var);
Date ParseDate(istream& in);
set<string> ParseSomeEvent(istream& stream);
string ParseEvent(istream& stream);