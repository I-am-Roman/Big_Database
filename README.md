# Big_Database
Database on C++ 
  Краеугольным камнем реализации является использование map<Date,set<string>>, 
  куда мы записываем всю информацию, полученную от пользователя.
  Класс имеет несколько ключевых методов:
  
  1.1. Add - добавление даты - событие 
  
  1.2. AddInDataBase - добавление даты - нескольких событий
  
 2. Print - печать базы данных 
 
 3. empty - проверка базы данных на пустоту
  
  4.1. Del - удаление события/даты, удовлетворяющих условию condition
  
  4.2. Clear - удаление всей базы данных
 
  5.1. operator+= - объединение баз данных 
  
  5.2. operator-= - пересечение баз данных 
  
  Функции EnsureNextSymbolAndSkip, ParseDate, ParseSomeEvent, ParseEvent
  служат для правильного принятия из потока информации. Программа способна осуществлять 
  поиск по базе данных с некоторым условие (condition). 
  Например, 
  
  Add_SE 2020 02 02 Glad Hrom Kot Rels
  
  Add 2019 03 01 Happy Birthday
  
  Add 2019 04 01 Sport
  
  Add 2010 02 01 Picture_Show
  
  Add 2010 02 01 Imagine_Show
  
  Find event == Glad
  
  Результат: 
  2020 02 02 Glad Hrom Kot Rels
  
  Программа не поддерживает условия со скобками "()".
  
  Внутри папки DataBaseProject есть 1. Test for Big DateBase с тестами для программы.
