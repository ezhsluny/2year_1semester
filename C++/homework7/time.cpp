#ifndef TIMECLASS_HPP
#define TIMECLASS_HPP


#include <iostream>

class Watch;
class SimpleWatch;

class Time
{
   int hours = 0;
   int minutes = 0;
   int seconds = 0;
   static int obj_count;
public:
   friend class Watch; //- только дружесвенные ф-ии(2-3)
   friend class SimpleWatch;
   Time() 
   {
      obj_count += 1;
      std::cout << "new Time::object was constructed (default), current object count: " << obj_count << '\n';
   }
   Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) 
   {
      obj_count += 1;
      std::cout << "new Time::object was constructed (init), current object count: " << obj_count << '\n';
   }
   Time(const Time& other) : hours(other.hours)
   {
      minutes = other.minutes;
      seconds = other.seconds;
      obj_count += 1;
      std::cout << "new Time::object was constructed (copy), current object count: " << obj_count << '\n';
   }
   ~Time() 
   {
      obj_count -= 1;
      std::cout << "Time::object was deleted, current object count: " << obj_count << '\n';
   }

   void SetHours(int hours) { this->hours = hours; };
   void SetMinutes(int minutes) { this->minutes = minutes; };
   void SetSeconds(int);
   int GetHours() const { return hours; }
   int GetMinutes() const { return minutes; }
   int GetSeconds() const { return seconds; }
   int ToSeconds() const { return hours*3600 + minutes*60 + seconds; }

   Time& operator= (const Time& other)
   {
      this->hours = other.hours;
      minutes = other.minutes;
      seconds = other.seconds;
      return *this;
   }
   
   void PrintTime()
   {
      std::cout << "H:" << this->GetHours() << " M:" << this->GetMinutes() << " S:" << this->GetSeconds() << std::endl;
   }

   Time& operator += (int s)
   {
      seconds += s;
      return *this;
   }

   Time& operator -=(int s)
   {
      seconds -= s;
      Normalize();
      return *this;
   }

   void Normalize()
   {
      int carry = 0;

      if (seconds < 0) {
         carry = (seconds / 60) - 1;
         seconds = 60 + (seconds % 60);
      } else {
         carry = seconds / 60;
         seconds = seconds % 60;
      }

      minutes += carry;
      carry = 0;
      if (minutes < 0) {
         carry = (minutes / 60) - 1;
         minutes = 60 + (minutes % 60);
      } else {
         carry = minutes / 60;
         minutes = minutes % 60;
      }

      hours += carry;
      hours = (hours + 24) % 24;
   }

};

int Time::obj_count = 0;

void Time::SetSeconds(int seconds) { this->seconds = seconds; };

Time operator + (const Time& t, int s)
{
   return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

bool operator == (const Time& t, const Time& other)
{
   return (t.GetHours()==other.GetHours() && t.GetMinutes() == other.GetMinutes() && t.GetSeconds() == other.GetSeconds());
}


Time operator - (const Time& t, int s)
{
   Time result(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
   result.Normalize();
   return result;
}


std::ostream& operator << (std::ostream& out, const Time& t)
{
   out << t.GetHours() << ":" << t.GetMinutes() << ":" << t.GetSeconds();
   return out;
}

std::istream& operator >> (std::istream& in, Time& t)
{
   int h, m, s;
   char tmp;

   in >> h;
   in >> m;
   in >> s;

   t = Time(h, m, s);
   return in;
}

#endif