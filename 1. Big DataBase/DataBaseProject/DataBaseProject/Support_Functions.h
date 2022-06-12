#pragma once

/****************************************************************/
/*        O V E R L O A D E D   O P E R A T O R S	            */
/****************************************************************/
ostream& operator << (ostream& stream, const Date& date)
{
	stream << setfill('0') << setw(4) << to_string(date.year);
	stream << "-";
	stream << setfill('0') << setw(2) << to_string(date.month);
	stream << "-";
	stream << setfill('0') << setw(2) << to_string(date.day);
	return stream;
}
bool operator < (const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}
bool operator == (const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}
bool operator >= (const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) >= tie(rhs.year, rhs.month, rhs.day);
}
bool operator <= (const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) <= tie(rhs.year, rhs.month, rhs.day);
}
bool operator > (const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) > tie(rhs.year, rhs.month, rhs.day);
}
bool operator != (const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) != tie(rhs.year, rhs.month, rhs.day);
}

// Combining 
void DataBase::operator+= (const DataBase& db2)
{
	auto it = begin(db2.database);
	for (it; it != end(db2.database); it++)
	{
		Date d = it->first;
		for (const string& ev : it->second)
		{
			database[d].insert(ev);
		}// string& ev
	}// for it
}

// Intersection of sets
void DataBase::operator-=(DataBase& db2)
{
	DataBase db3;
	auto it2 = begin(db2.database);	// iterator of a smaller database
	auto it = begin(database);		// iterator of a larger database
	for (it; it != end(database); )
	{
		Date d = it->first;
		db3 = db2.Find_Date(d, "==");
		if (db3.database.empty())
		{
			it = database.erase(it);
		}
		else
		{
			++it;
		}
	}//for it
}//operator-=
