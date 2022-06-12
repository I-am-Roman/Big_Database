#include <stdexcept>
#include "DataBase.h"

/*In this project there is .txt document with all possible tests. 
The user just has to copy the content to the console and get the result. */

using namespace std;
void print_line(char temp, uint16_t i);
int main()
{
	DataBase db, db2;

	print_line('*', 50); cout << endl;
	print_line(' ', 16); cout << "D A T A    B A S E" << endl;
	print_line('*', 50); cout << endl;
	cout << endl;
	cout << "Add	[date][event]	- add pair from [date,event] in database" << endl;
	cout << "Add_SE  [date][events]	- add pair from [date,some events] in database" << endl;
	cout << "Print			- print all dates and events" << endl;
	cout << "Del	[condition]	- delete pair from [date,event(-s)] from database" << endl;
	cout << "Find	[condition]	- find all entries according to the condition" << endl;
	cout << "Last	[date]		- find the last day that is no more than the condition" << endl;
	cout << "Exit			- exit from programm" << endl;

	for (string line; getline(cin, line); )
	{
		istringstream is(line);
		string command;
		is >> command;

		if (command == "Add")
		{
			Date date = ParseDate(is);
			if (date.year == -1 && date.month == -1 && date.day == -1)
				continue;
			string event = ParseEvent(is);
			if (event.empty())
				continue;
			db.Add(date, event);
		}
		else if (command == "Add_SE")
		{
			// Add some events
			Date date = ParseDate(is);
			if (date.year == -1 && date.month == -1 && date.day == -1)
				continue;
			set<string> event = ParseSomeEvent(is);
			if (event.empty())
				continue;
			db.AddInDataBase(date, event);
		}
		else if (command == "Print")
		{
			db.Print();
		}
		else if (command == "Del")
		{
			int count = 0;
			if (is.eof())
			{
				count = db.Clear();
			}
			else
			{
				db2 = db.Find(is, db);
				count = db.Del(db2);
				db.Print();
			}
			cout << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find")
		{
			db2 = db.Find(is, db);
			cout << endl;
			db2.Print();
			db2.Clear();
		}
		else if (command == "Last")
		{
			auto day = ParseDate(is);
			db2 = db.Find_Date(day, "LAST");
			if (db2.empty())
				cout << "No entries" << endl;
			else
				db2.Print();
			db2.Clear();
		}
		else if (command == "Exit")
		{
			break;
		}
		else if (command.empty())
		{
			continue;
		}
		else
		{
			cout << "Unknown command: " + command;
		}


	}// for line
	return 0;
}// for main 

void print_line(char temp, uint16_t i)
{
	for (int j = 0; j < i; j++)
		cout << temp;
}