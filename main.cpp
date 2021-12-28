// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int& LENGTH_YEAR = 365;
const int& LENGTH_MONTH = 31;
const int& COUNT_MONTH = 12;
const int& ONE = 1;




class Date {
public:

  Date()
  {
    year = ONE;
    month = ONE;
    day = ONE;
  }

  Date (int newYear, int newMonth, int newDay)
  {

    if (newMonth > COUNT_MONTH && newMonth < ONE){
      stringstream ss;
      ss << "Month value is invalid: " << newMonth << "\n";
      throw range_error(ss.str());
    }
    else if (newDay > LENGTH_MONTH && newDay < ONE) {
      stringstream ss;
      ss << "Day value is invalid: " << newDay << "\n";
      throw range_error(ss.str());
    }
    year = newYear;
    month = newMonth;
    day = newDay;
    
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




private:
  int year, month, day;
};

bool operator < (const Date& lhs, const Date& rhs);
istream& operator >> (istream&, Date&);
ostream& operator << (ostream&, const Date&);

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
          dataBase.at(date).erase(event);
          events = dataBase[date];
          if (events.size() == 0){
            DeleteDate(date);
          }
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

  string Find(const Date& date) const{
    string result = "";
    auto findDate = dataBase.find(date);
    if (findDate != dataBase.end()){
      auto events = findDate->second;
     
      for (auto& event : events)
      {
        cout << event << "\n";
      }
      
    }
    return result;
  }
  
  void Print() const{
    for (const auto& date : dataBase)
    {
      
      for (auto& event: date.second){
        cout << date.first << " " << event << "\n";
      }
      cout << endl;
    }
  }

private:
  map <Date, set<string>> dataBase;
};


int main() {
  Database db;
    
  string command;
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую 
  
  string query, event;
  Date date;

  istringstream stream(command);
  if (stream >> query){
    try {

      if (query == "Add"){
        bool correct = (stream >> date && stream >> event);
        if (correct){
          db.AddEvent(date, event);
        }
      }
      else if (query == "Del"){
        if (stream >> date){
          if (stream >> event){
            if (db.DeleteEvent(date, event)){
              cout << "Deleted successfully\n";
            }
            else {cout << "Event not found\n";}
          }
          else{ cout << "Deleted " << db.DeleteDate(date) << " events\n"; }
        }
      }
      else if (query == "Find"){
        if (stream >> date){cout << db.Find(date);}
      }
      else if (command == "Print"){
        db.Print();
      }
      else {
        stringstream ss;
        ss << "Unknown command: " << query << "\n"<< endl;
        throw runtime_error(ss.str());}
  }
    catch (exception& ex) {
      cout << ex.what();
      break;
    }


  }
    
  }

  return 0;
}

bool operator < (const Date& lhs, const Date& rhs){
  int lResult = lhs.GetYear() * LENGTH_YEAR + lhs.GetMonth() * LENGTH_MONTH + lhs.GetDay();
  int rResult = rhs.GetYear() * LENGTH_YEAR + rhs.GetMonth() * LENGTH_MONTH + rhs.GetDay();
  if (lResult < rResult)
  {
    return true;
  }
  else return false;
  
}

istream& operator >> (istream& stream, Date& date) {
  
  string dataString;
  stream >> dataString;
  istringstream ss(dataString);
  
  int year, month, day;
  bool correct = true;

  correct = correct && (ss >> year);
  correct = correct && (ss.peek() == '-');
  ss.ignore(1);
  correct = correct && (ss >> month);
   correct = correct && (ss.peek() == '-');
  ss.ignore(1);
  correct = correct && (ss >> day);
  correct = correct && (ss.eof());



  if (correct){
    date = {year, month, day};
  }
  else {
    stringstream ss;
    ss << "Wrong date format: " << dataString << endl;
    throw runtime_error(ss.str());
  }

  return stream;
}

ostream& operator << (ostream& stream,const Date& date)  {
      stream << setfill('0') << setw(4) << date.GetYear() <<"-";
      stream << setfill('0') << setw(2) << date.GetMonth() << "-";
      stream << setfill('0') << setw(2) << date.GetDay();
  return stream;
}

  

