// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
const int& lengthYear = 365;
const int& lengthMonth = 31;

class Date {
public:
  Date (){
    year = 1;
    month = 1;
    day = 1;
  }

  Date (int newYear, int newMonth, int newDay)
  {
    year = newYear;

    if (newMonth <= 12 && newMonth >= 1){
      month = newMonth;
    }
    else{
      stringstream ss;
      ss << "Month value is invalid: " << month;
      throw runtime_error(ss.str());
    }
    if (newDay <= 31 && newDay >= 1){
      day = newDay;
    }
    else{
      stringstream ss;
      ss << "Day value is invalid: " << day;
      throw runtime_error(ss.str());
    }
  }
  
  
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
istream& operator >> (istream&, Date&);

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
  
  string query, event;
  Date date;

  istringstream stream(command);
  stream >> query;
  try {
  if (query == "Add")
    {
      stream >> date >> event;
    }
  if (query == "Del")
    {
      stream >> date >> event;
    }
  if (query == "Find")
  {
     stream >> date;
  }
  if (command == "Print"){
  }
  else {
    cout << "Unknown command: " << command;
  }
  }
  catch (exception& ex) {
      cout << ex.what();
  }

    
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

istream& operator >> (istream& stream, Date& date) {
  int year, month, day;
  char sumbolOne, sumbolTwo;

  stream >> year;
  bool yearCorrect = (year <= 9999 && year >= 0);
  stream >> sumbolOne;
  bool sumboOnelCorrect = (sumbolOne == '-');
  stream >> month;
  bool monthCorrect = ( month <= 99 && month >= -99);
  stream >> sumbolTwo;
  bool sumbolTwoCorrect = (sumbolTwo == '-');
  stream >> day;
  bool dayCorrect = (day <= 99 && day >= - 99);

  if (yearCorrect && sumboOnelCorrect && monthCorrect && sumbolTwoCorrect && dayCorrect){
    date = {year, month, day};
  }
  else {
    stringstream ss;
    ss << "Wrong date format: " << year << sumbolOne << month << sumbolTwo << day;
    throw runtime_error(ss.str());
  }
  



}
