#include <iostream>
#include <vector>

class Time
{
   int hours = 0;
   int minutes = 0;
   int seconds = 0;
   static int obj_count;
public:
   Time()
   {
      obj_count += 1;
      std::cout << "new Time::object was constructed (default), current object count: " << obj_count << '\n';
   };
   Time(int h, int m, int s) : hours(h), minutes(m), seconds(s)
   {
      obj_count += 1;
      std::cout << "new Time::object was constructed (init), current object count: " << obj_count << '\n';
   }
   Time(const Time& other) : hours(other.hours), minutes(other.minutes), seconds(other.seconds)
   {
      obj_count += 1;
      std::cout << "new Time::object was constructed (copy), current object count: " << obj_count << '\n';
   }
   Time(Time&& other) : hours(other.hours), minutes(other.minutes), seconds(other.seconds)
   {
      other.hours = 0;
      other.minutes = 0;
      other.seconds = 0;
      obj_count += 1;
      std::cout << "new Time::object was constructed (move), current object count: " << obj_count << '\n';
   }
   ~Time()
   {
      obj_count -= 1;
      std::cout << "Time::object was deleted, current object count: " << obj_count << '\n';
   }

   Time& operator= (const Time& other)
   {
      if (this != &other) {
         this->hours = other.hours;
         this->minutes = other.minutes;
         this->seconds = other.seconds;
      }
      return *this;
   }

   Time& operator= (Time&& other) noexcept
   {
      if (this != &other) {
         this->hours = other.hours;
         this->minutes = other.minutes;
         this->seconds = other.seconds;
         other.hours = 0;
         other.minutes = 0;
         other.seconds = 0;
      }
      std::cout << "Time::object was move assigned, current object count: " << obj_count << '\n';
      return *this;
   }

   void SetHours(int hours) { this->hours = hours; };
   void SetMinutes(int minutes) { this->minutes = minutes; };
   void SetSeconds(int seconds) { this->seconds = seconds; };
   int GetHours() const { return hours; }
   int GetMinutes() const { return minutes; }
   int GetSeconds() const { return seconds; }
   int ToSeconds() const { return hours*3600 + minutes*60 + seconds; }

   void PrintTime() const
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

int main() {
   Time t1(10, 20, 30);
   Time t2 = std::move(t1); // t1 теперь rvalue
   t2.PrintTime();
   t1.PrintTime();
   std::cout << "\n\n";

   Time t3(12, 30, 45);
   Time t4;
   t4 = std::move(t3); // t3 rvalue
   t4.PrintTime();
   t3.PrintTime();
   std::cout << "\n\n";

   std::vector<Time> times;
   times.push_back(Time(1, 2, 3)); // rvalue
   times.push_back(std::move(t2)); // rvalue
   std::cout << "\n\n";

   Time t5(4, 5, 6);
   times.push_back(t5); // lvalue
   std::cout << "\n\n";

   for (const Time& t : times) {
      t.PrintTime();
   }

   return 0;
}
