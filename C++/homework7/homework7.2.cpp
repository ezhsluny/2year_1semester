#include <iostream>
#include "time.cpp"


class Clock
{
    Time t;

    public:
    Clock()
    {
        std::cout << "Clock::obj was constructed (def)" << std::endl;
    }

    Clock(const Clock&)
    {
        std::cout << "Clock::obj was constructed (copy)" << std::endl;
    }

    ~Clock()
    {
        std::cout << "Clock::obj was deleted" << std::endl;
    }

    Clock(int h, int m, int s) : t(Time(h,m,s))
    {
        std::cout << "Clock::obj was constructed (init with int)" << std::endl;
    }

    Clock(const Time& time) : t(time)
    {
        std::cout << "Clock::obj was constructed (init with Time::obj)" << std::endl;
    }

    Time GetTime() { return t; }

    void SetClock(const Time& time)
    {
        t.SetHours(time.GetHours());
        t.SetMinutes(time.GetMinutes());
        t.SetSeconds(time.GetSeconds());
    }
};


class Cuckoo_clock : public Clock
{
    private:
    Time& time;

    public:
    Cuckoo_clock(Time& t) : Clock(), time(t)
    {
        std::cout << "Cuckoo_clock::obj was constructed (init)" << std::endl;
    }

    Cuckoo_clock(const Cuckoo_clock& other) : Clock(other), time(other.time)
    {
        std::cout << "Cuckoo_clock::obj was constructed (copy)" << std::endl;
    }

    ~Cuckoo_clock()
    {
        std::cout << "Cuckoo_clock::obj was deleted" << std::endl;
    }

    void cuckoo_sound()
    {
        int h = time.GetHours();
        int m = time.GetMinutes();
        int s = time.GetSeconds();

        if (m == 0 && s == 0)
            for (int i = 0; i < h; ++i)
                std::cout << "Cuckoo!" << std::endl;
    }
};


class Wall_clock : public Cuckoo_clock
{
    public:
    Wall_clock(Time& t) : Cuckoo_clock(t)
    {
        std::cout << "Wall_clock::obj was constructed (def)" << std::endl;
    }

    Wall_clock(const Wall_clock& other) : Cuckoo_clock(other)
    {
        std::cout << "Wall_clock::obj was constructed (copy)" << std::endl;
    }

    ~Wall_clock()
    {
        std::cout << "Wall_clock::obj was deleted" << std::endl;
    }
};


class Pendulum_clock : public Wall_clock
{
    public:
    Pendulum_clock(Time& t) : Wall_clock(t)
    {
        std::cout << "Pendulum_clock::obj was constructed (def)" << std::endl;
    }

    Pendulum_clock(const Pendulum_clock& other) : Wall_clock(other)
    {
        std::cout << "Pendulum_clock::obj was constructed (copy)" << std::endl;
    }

    ~Pendulum_clock()
    {
        std::cout << "Pendulum_clock::obj was deleted" << std::endl;
    }

    void show_pendulum()
    {
        std::string pendulum = "  |\n   |\n    |\n     |\n   *****\n   *   *\n   *****\n";
        std::cout << pendulum << std::endl;
    }
};

class Watch : public Clock
{
    private:
    Time& time;

    public:
    Watch(Time& t) : Clock(), time(t)
    {
        std::cout << "Watch::obj was constructed (def)" << std::endl;
    }

    Watch(const Watch& other) : Clock(other), time(other.time)
    {
        std::cout << "Watch::obj was constructed (copy)" << std::endl;
    }

    ~Watch()
    {
        std::cout << "Watch::obj was deleted" << std::endl;
    }

    void show_watch()
    {
        std::string watch = "-----------------------\n|                     |\n|          |          |\n|          |          |\n|          |______    |\n|                     |\n|                     |\n|                     |\n-----------------------\n";
        std::cout << watch << std::endl;
    }
};

class Smart_watch : public Watch
{
    int steps = 0;
    int heart_rate = 0;

    public:
    Smart_watch(Time& t) : Watch(t), steps(0), heart_rate(0)
    {
        std::cout << "Smart_watch::obj was constructed (def)" << std::endl;
    }

    Smart_watch(const Smart_watch& other) : Watch(other), steps(other.steps), heart_rate(other.heart_rate)
    {
        std::cout << "Smart_watch::obj was constructed (copy)" << std::endl;
    }

    ~Smart_watch()
    {
        std::cout << "Smart_watch::obj was deleted" << std::endl;
    }

    void CountSteps(int n)
    {
        steps = n;
    }

    void Measure_HR(int hr)
    {
        heart_rate = hr;
    }
    
    void smart_watch()
    {
        std::cout << "steps: " << steps << " heart rate: " << heart_rate << std::endl;
    }
};

int main()
{
    Time shared_time(5, 0, 0);

    
    Cuckoo_clock ck(shared_time);
    ck.cuckoo_sound();
    std::cout << "\n\n" << std::endl;

    Wall_clock wc(shared_time);
    wc.cuckoo_sound();
    std::cout << "\n\n" << std::endl;

    Pendulum_clock pc(shared_time);
    pc.show_pendulum();
    std::cout << "\n\n" << std::endl;

    Watch w(shared_time);
    w.show_watch();
    std::cout << "\n\n" << std::endl;

    Smart_watch sw(shared_time);
    sw.show_watch();
    sw.CountSteps(10000);
    sw.Measure_HR(103);
    sw.smart_watch();
    std::cout << "\n\n" << std::endl;

    return 0;
}
