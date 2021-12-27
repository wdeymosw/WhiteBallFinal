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
const int& XX = 99;
const int& XXXX = 9999;


class Date {
public:
  Date (){
    year = ONE;
    month = ONE;
    day = ONE;
  }

  Date (int newYear, int newMonth, int newDay)
  {
    year = newYear;

    if (newMonth <= COUNT_MONTH && newMonth >= ONE){
      month = newMonth;
    }
    else{
      stringstream ss;
      ss << "Month value is invalid: " << newMonth << "\n";
      throw range_error(ss.str());
    }
    if (newDay <= LENGTH_MONTH && newDay >= ONE){
      day = newDay;
    }
    else{
      stringstream ss;
      ss << "Day value is invalid: " << newDay << "\n";
      throw range_error(ss.str());
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
          dataBase.at(date).erase(event);
          events = dataBase[date];
          if (events.size() == 0){
            DeleteDate(date);
          }
          // to do если дата пустая то удалить и саму дату
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
      vector <string> eventList;
      for (const auto& event : events){
        eventList.push_back(event);
      }
      for (int i = 0; i <= eventList.size()-1; ++ i)
      {
        result += eventList[i] +((i < eventList.size()-1)?" ":"\n");
      }
      
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
      else { cout << "Unknown command: " << query << "\n"; }
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
  char sumbolOne, sumbolTwo;

  ss >> year;
  bool yearCorrect = (year <= XXXX && year >= 0);
  ss >> sumbolOne;
  bool sumboOnelCorrect = (sumbolOne == '-');
  ss >> month;
  bool monthCorrect = ( month <= XX && month >= -XX);
  ss >> sumbolTwo;
  bool sumbolTwoCorrect = (sumbolTwo == '-');
  ss >> day;
  bool dayCorrect = (day <= XX && day >= -XX);


  if (yearCorrect && sumboOnelCorrect && monthCorrect && sumbolTwoCorrect && dayCorrect && ss.peek() == EOF){
    date = {year, month, day};
  }
  else {
    stringstream ss;
    ss << "Wrong date format: " << dataString << endl;
    throw runtime_error(ss.str());
  }

  return stream;
}
  

