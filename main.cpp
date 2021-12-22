// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
const int lengthYear = 365;
const int lengthMonth = 31;

class Date {
public:
  int GetYear() const{
    return year;
  }
  int GetMonth() const{
    return month;
  }
  int GetDay() const{
    return day;
  }

  void SetDate (int newYear, int newMonth, int newDay)
  {
    year = newYear;
    month = newMonth;
    day = newDay;
  }


private:
  int year, month, day;
};

bool operator < (const Date& lhs, const Date& rhs);

class Database {
public:
  void AddEvent(const Date& date, const string& event){
    dataBase[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event){
      auto findDate = dataBase.find(date);
      bool ansver = false;
      if (findDate != dataBase.end()){
        auto events = findDate->second;
        auto iter = events.find(event);
        if (iter!= events.end())
        {
          dataBase[date].erase(iter);
          ansver = true;
        }

      }
      return ansver;

    }

  int  DeleteDate(const Date& date){
    // delete events and date for key [date]
    auto findDate = dataBase.find(date);
    int number = 0;
    if (findDate != dataBase.end()) {
      auto events = dataBase[date];
      number = events.size();
      dataBase.erase(findDate);       
    }
    return number; 
  }

  /* ??? */ 
  string Find(const Date& date) const{
    string result = "";
    auto findDate = dataBase.find(date);
    if (findDate != dataBase.end()){
      auto events = findDate->second;
      for (const auto& event : events){
        result += event + " ";
      }
      result += "\n";

    }
    return result;

  }
  
  void Print() const{

    for (const auto& date : dataBase)
    {
      const auto& data = date.first;
      const auto& events = date.second;
      cout << setfill('0') << setw(4) << data.GetYear() <<"-" 
          << setw(2) << data.GetMonth() << "-" 
          << setw(2) << data.GetDay();
      for (auto& event: events){
        cout << " " << event;
      }
      cout << endl;
    }

  }

private:
  map <Date, set<string>> dataBase;
};

istream& operator >> (istream&, Database&);


int main() {
  Database db;
    
  string command;
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую 
  
  string query, data, event;

  istringstream stream(command);
  stream >> query;

  if (query == "Add")
    {
      stream >> data >> event;
    }
  if (query == "Del")
    {
      stream >> data >> event;
    }
  if (query == "Find")
  {
     stream >> data;
  }
  if (command == "Print"){}

    
  }

  return 0;
}

bool operator < (const Date& lhs, const Date& rhs){
  int lResult = lhs.GetYear() * lengthYear + lhs.GetMonth() * lengthMonth + lhs.GetDay();
  int rResult = rhs.GetYear() * lengthYear + rhs.GetMonth() * lengthMonth + rhs.GetDay();
  if (lResult < rResult)
  {
    return true;
  }
  else return false;
  
}
