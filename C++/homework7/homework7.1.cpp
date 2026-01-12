// time.cpp
#include <iostream>

class SimpleWatch;
class Time;

class Watch
{
   int mode = 24;
   public:
      Watch() {}

      ~Watch() {}

      void set_mode(int);
      void PrintTime(const Time& time);
      void setTime(Time& time, int h, int m, int s);
};

class Time
{
   public:
      int hours;
      int minutes;
      int seconds;

      Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

      int GetHours() const { return hours; }
      int GetMinutes() const { return minutes; }
      int GetSeconds() const { return seconds; }

      friend class SimpleWatch;
      friend void Watch::PrintTime(const Time& time);
      friend void Watch::setTime(Time& time, int h, int m, int s);
};

void Watch::set_mode(int mode)
{
   this->mode = mode;
}

void Watch::PrintTime(const Time& time)
{
   int h = time.GetHours();
   if (mode == 12)
   {
      h %= 12;
   }
   std::cout << h << ":" << time.GetMinutes() << ":" << time.GetSeconds() << std::endl;
}

void Watch::setTime(Time& time, int h, int m, int s)
{
   time.hours = h;
   time.minutes = m;
   time.seconds = s;
}

class SimpleWatch
{
   public:
      SimpleWatch()
      {
         std::cout << "new SimpleWatch::object was constructed (default) " << '\n';
      }

      ~SimpleWatch()
      {
         std::cout << "SimpleWatch::object was deleted " << '\n';
      }

      void show_time(Time& t)
      {
         std::cout << t.hours << ":" << t.minutes << ":" << t.seconds << std::endl;
      }

      void set_time(Time& t, int h, int m, int s)
      {
         t.hours = h;
         t.minutes = m;
         t.seconds = s;
      }
};

int main()
{
   Time t(2,12,2);

   SimpleWatch sw;
   sw.show_time(t);
   sw.set_time(t, 10, 10, 10);
   sw.show_time(t);

   Watch w;
   w.PrintTime(t);
   w.setTime(t, 21, 21, 21);
   w.PrintTime(t);
   w.set_mode(12);
   w.PrintTime(t);

   return 0;
}
