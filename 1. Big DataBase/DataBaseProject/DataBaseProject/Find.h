#pragma once

/****************************************************************/
/*							F I N D							    */
/****************************************************************/

DataBase DataBase::Find_Date(const Date& date, const string& condition)
{
	DataBase send;
	if (condition == "==")
	{
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			if (date == it->first)
			{
				Date d = it->first;
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
			}
		}//for it
		return send;
	}// if == 
	else if (condition == "!=")
	{
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			if (date != it->first)
			{
				Date d = it->first;
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
			}
		}//for it
		return send;
	}//if !=
	else if (condition == ">")
	{
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			if (date < it->first)
			{
				Date d = it->first;
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
			}
		}//for it
		return send;
	}// if >
	else if (condition == "<")
	{
		//cout << "Less" << endl;
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			//cout << "In for" << endl;
			if (date > it->first)
			{
				//cout << "In for 2" << endl;
				Date d = it->first;
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
			}

		}//for it
		return send;
	}// if < 
	else if (condition == ">=")
	{
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			if (date <= it->first)
			{
				Date d = it->first;
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
			}
		}//for it
		return send;
	}// if >=
	else if (condition == "<=")
	{
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			if (date >= it->first)
			{
				Date d = it->first;
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
			}
		}//for it
		return send;
	}// if <=
	else if (condition == "LAST")
	{
		auto it = end(database);

		while (it != begin(database))
		{
			--it;
			if (date >= it->first)
			{
				Date d = it->first;
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
				return send;
			}
		}//while
		return send;
	}// if <=
	else
	{
		cout << "Wrong condition:" + condition << endl;
	}
	return send;

}

DataBase DataBase::Find_Event(const string& event, const string& condition)
{
	DataBase send;
	if (condition == "==")
	{
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			Date d = it->first;
			for (const string& ev : it->second)
			{
				if (event == ev)
				{
					for (const string& ev : it->second)
					{
						send.Add(d, ev);
					}// for ev 
				}
			}

		}//for it
		return send;
	}// if == 
	else if (condition == "!=")
	{
		bool NotEqual = true;
		auto it = begin(database);
		for (auto it = begin(database); it != end(database); it++)
		{
			Date d = it->first;
			// choose somthing date 
			for (const string& ev : it->second)
			{
				// if the event is equal to the forbidden word (!=)
				if (event == ev)
				{
					NotEqual = false;
				}

			}// for ev 
			if (NotEqual)
			{
				for (const string& ev : it->second)
				{
					send.Add(d, ev);
				}
			}// if NotEqual
			NotEqual = true;
		}//for it
		return send;
	}//if !=
	else
	{
		cout << "Wrong format: " + condition << endl;
	}

	return send;
}
 
DataBase DataBase::Find(istream& stream, DataBase& dtbs)
{
	DataBase databank_1, databank_2, temp;
	queue <string> operation;
	// number of terms 
	uint8_t summand = 1; 
	string And_Or;
	// If the condition is date == 2017 01 01 - working with dates (<=, >=, !=, ==, <, >) - allowed.operat
	// If the condition is event != "Holiday" - working with events ( != , ==) - allowed. opera
	while (!stream.eof())
	{
		string cond;
		string operat;
		stream >> cond;   
		stream >> operat; 

		switch (summand)
		{
		case 1:
		{
			if (cond == "date")
			{
				Date d = ParseDate(stream);
				databank_1 = dtbs.Find_Date(d, operat);
			}//if date
			if (cond == "event")
			{
				string event;
				string event_two;
				stream >> event;

				while (!stream.eof())
				{
					stream >> event_two;
					if (event_two == " " || event_two == "")
						break;
					if (event_two == "AND" || event_two == "OR")
					{
						And_Or = event_two;
						break;
					}
					event = event + " " + event_two;
					event_two = "\0";

				}
				databank_1 = dtbs.Find_Event(event, operat);
			}//if event		
			summand++;
		}
		break;
		case 2:
		{
			if (cond == "date")
			{
				Date d = ParseDate(stream);
				databank_2 = dtbs.Find_Date(d, operat);
			}//if date
			if (cond == "event")
			{
				string event = "";
				string event_two;
				stream >> event;
				while (!stream.eof())
				{
					stream >> event_two;
					if (event_two == "AND" || event_two == "OR")
					{
						And_Or = event_two;
						break;
					}
					event = event + " " + event_two;
					event_two = "\0";

				}

				databank_2 = dtbs.Find_Event(event, operat);

			}//if event	
			summand++;
		}
		break;
		default:
		{
			if (cond == "date")
			{
				Date d = ParseDate(stream);
				databank_2 = dtbs.Find_Date(d, operat);

			}//if date
			if (cond == "event")
			{
				string e;
				stream >> e;
				databank_2 = dtbs.Find_Event(e, operat);
			}//if event
		}

		}// switch


		if (And_Or.empty())
		{
			stream >> And_Or; 
		}

		if (And_Or == "AND" || And_Or == "OR")
		{
			operation.push(And_Or);
			And_Or = "\0";
		}

		if ((!databank_1.empty() && !databank_2.empty()) || (summand > 2))
		{
			string name_op = operation.back();
			if (name_op == "AND")
			{
				// it is important to determine which database is larger
				if (databank_1.database.size() > databank_2.database.size())
				{
					databank_1 -= databank_2;
					databank_2.database.clear();
				}
				else
				{
					temp = databank_2;
					databank_2 = databank_1;
					databank_1 = temp;
					databank_1 -= databank_2;
					databank_2.database.clear();
				}

			}
			if (name_op == "OR")
			{	
				databank_1 += databank_2;
				databank_2.database.clear();
			}
		}
	}

	return databank_1;
}