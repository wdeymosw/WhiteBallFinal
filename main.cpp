// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <iostream>
#include <map>
#include <set>
#include <string>

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

bool operator < (const Date& lhs, const Date& rhs){
  int lResult = lhs.GetYear() * lengthYear + lhs.GetMonth() * lengthMonth + lhs.GetDay();
  int rResult = rhs.GetYear() * lengthYear + rhs.GetMonth() * lengthMonth + rhs.GetDay();
  if (lResult < rResult)
  {
    return true;
  }
  else return false;
  
}

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

  /* ??? */ string Find(const Date& date) const;
  
  void Print() const;
private:
  map <Date, set<string>> dataBase;
};


int main() {
  Database db;
    
  string command;
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую
    
    
  }

  return 0;
}