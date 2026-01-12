#include <iostream>

   int obj_count = 0;
class Time
{
// private:
   int hours = 0;
   int minutes = 0;
   int seconds = 0;


public:
   Time() 
   {
      obj_count += 1;
      std::cout << "new Time::object was constructed, current object count: " << obj_count << '\n';
   };
   Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) 
   {
      obj_count += 1;
      std::cout << "new Time::object was constructed, current object count: " << obj_count << '\n';
   }
   Time(const Time& other)
   {
      hours = other.hours;
      minutes = other.minutes;
      seconds = other.seconds;
      obj_count += 1;
      std::cout << "new Time::object was constructed, current object count: " << obj_count << '\n';
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
      return *this;
   }

   void Normalize()
   {
      int minutes_add = 0;
      int hours_add = 0;

      if (seconds > 59)
      {
         minutes_add = (int)seconds / 60;
      }
      else if (seconds < 0)
      {
         minutes_add = (int)seconds / 60 - 1;
      }
      seconds = (seconds + 60) % 60;
      minutes += minutes_add;
      if (minutes > 59)
      {
         hours_add = (int)minutes / 60;
      }
      else if (minutes < 0)
      {
         hours_add = (int)minutes / 60 - 1;
      }
      minutes = (minutes + 60) % 60;
      hours += hours_add;
      hours = (hours + 24) % 24;
   }
};

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
   return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
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

// int main()
// {
//    Time t;
//    std::cin >> t;

//    t -= 10;
//    t.Normalize();
//    std::cout << t << '\n';
//    std::cout << t.ToSeconds() << '\n';
//    t += 81;
//    t.Normalize();
//    std::cout << t << '\n';
// }

int main()
{
   Time t;
   t.SetHours(1);
   Time t2 = t;
   t2.SetHours(2);
   t2.PrintTime();
   {
       t2.SetHours(12);
       t2.PrintTime();
       Time t2(22, 22, 22);
       t2.PrintTime();
   }
   t2.PrintTime();
   Time t3(3, 3, 3);
   t3 = t;
   t3.SetHours(3);
   t3.PrintTime();
}