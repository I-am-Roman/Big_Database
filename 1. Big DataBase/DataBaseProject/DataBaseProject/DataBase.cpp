
#include "DataBase.h"
#include "Support_Functions.h"
#include "Find.h"

/****************************************************************/
/*							D E L			 				    */
/****************************************************************/
size_t DataBase :: Del(DataBase& db2)
{
	DataBase db3;
	size_t count = db2.database.size();
	auto it2 = begin(db2.database);	// iterator of a smaller database

	auto it = begin(database);		// iterator of a larger database
	for (it; it != end(database); )
	{
		Date d = it->first;
		db3 = db2.Find_Date(d, "==");
		if (!db3.database.empty())
		{
			it = database.erase(it);
		}
		else
		{
			++it;
		}
	}//for it
	return count;
}
/****************************************************************/
/*					Ф У Н К Ц И Я   A d d    				     */
/****************************************************************/
//Add pair of - (Date, event)
void DataBase::Add(const Date& d, const string& ev)
{
	database[d].insert(ev);
}

// Add pair of - (Date, SET of events)
void DataBase::AddInDataBase(const Date& d, set<string>& ev)
{
	for (auto it = ev.begin(); it != ev.end(); it++)
	{
		string event = *it;
		database[d].insert(event);
	}
	ev.clear();
}

/****************************************************************/
/*						E M P T Y		        			    */
/****************************************************************/
bool DataBase::empty()
{
	return database.empty();
}
/****************************************************************/
/*						P R I N T				 				*/
/****************************************************************/
void DataBase::Print()
{
	if (database.empty())
	{
		cout << "Database is empty!" << endl;
	}
	for (const auto& Cal : database)
	{
		cout << Cal.first;
		cout << " ";
		for (const string& ev : Cal.second)
		{
			cout << ev << ", ";
		}
		cout << endl;
	}
}
/****************************************************************/
/*							C L E A R		   				     */
/****************************************************************/

size_t DataBase::Clear()
{
	size_t num = database.size();
	database.clear();
	return num;
}

/****************************************************************/
/*			P A R S E   D A T E   A N D   E V E N T			     */
/****************************************************************/
// Date formatting
Date ParseDate(istream& in) 
{
	Date result{};

	in >> result.year;
	EnsureNextSymbolAndSkip(in);
	in >> result.month;
	try
	{
		if (result.month <= 0 || result.month > 24)
		{
			throw logic_error("Wrong date format: Month");
		}
	}
	catch (exception& ex) 
	{
	cout << "Exception happens: " << ex.what();
	return {-1,-1,-1};
	}
	EnsureNextSymbolAndSkip(in);
	in >> result.day;
	try 
	{
		if (result.day <= 0 || result.day > 31)
		{
			throw logic_error("Wrong date format: Day");
		}
	}
	catch (exception& ex)
	{
		cout << "Exception happens: " << ex.what();
		return { -1,-1,-1 };
	}
	return result;
}

void EnsureNextSymbolAndSkip(istream& stream) 
{
	try 
	{
		if (!(stream.peek() != '/'
			|| stream.peek() != '.'
			|| stream.peek() != ' '
			|| stream.peek() != '-'))
		{
			throw logic_error("Wrong date format!");
		}

	}
	catch (exception& ex) {
		cout << "Exception happens: " << ex.what();
		return;
	}
	stream.ignore(1);

}//EnsureNextSymbolAndSkip

// formatting set of events 
set<string> ParseSomeEvent(istream& stream)
{
	string event;
	string res_event;
	set <string> ev;

	while (!stream.eof())
	{
		stream >> event;
		res_event = event;
		try 
		{
			if (res_event == "" || res_event == " ")
			{
				throw logic_error("Wrong event format: Event is empty");
			}
		}
		catch (exception& ex) 
		{
			cout << "Exception happens: " << ex.what();
			return ev;
		}
		ev.insert(res_event);
		res_event = "";
	}
	return ev;
}
 
string ParseEvent(istream& stream)
{
	string event ="";
	string event_one;
	stream >> event;

	while (!stream.eof())
	{	
		stream >> event_one;
		if (event_one == " " || event_one == "")
			break;
		event = event + " " + event_one;
		event_one = "\0";

	}
	try 
	{
		if (event == "" || event == " ")
			throw logic_error("Wrong event format: Event is empty ");
	}
	catch (exception& ex) {
		cout << "Exception happens: " << ex.what();
		return "";
	}
	return event;
}

