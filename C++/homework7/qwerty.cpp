#include <iostream>

class Watch;
class SimpleWatch;

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    friend class Watch;
    friend class SimpleWatch;

    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }

    void SetHours(int h) { hours = h; }
    void SetMinutes(int m) { minutes = m; }
    void SetSeconds(int s) { seconds = s; }
};

class Watch {
    int mode = 24;

public:
    Watch() {}
    ~Watch() {}

    void show_watch(Time& t) {
        int h = t.hours;
        if (mode == 12) {
            h %= 12;
            if (h == 0) h = 12; // Convert 0 to 12 for 12-hour format
        }
        std::cout << h << ":" << t.minutes << ":" << t.seconds << std::endl;
    }

    void set_watch(Time& t, int h, int m, int s) {
        t.hours = h;
        t.minutes = m;
        t.seconds = s;
    }

    void set_mode(int m) {
        mode = m;
    }
};

class SimpleWatch {
public:
    SimpleWatch() {
        std::cout << "new SimpleWatch::object was constructed (default) " << '\n';
    }

    ~SimpleWatch() {
        std::cout << "SimpleWatch::object was deleted " << '\n';
    }

    void show_time(Time& t) {
        std::cout << t.hours << ":" << t.minutes << ":" << t.seconds << std::endl;
    }

    void set_time(Time& t, int h, int m, int s) {
        t.hours = h;
        t.minutes = m;
        t.seconds = s;
    }
};

int main() {
    Time t(2, 12, 2);

    SimpleWatch sw;
    sw.show_time(t);
    sw.set_time(t, 10, 10, 10);
    sw.show_time(t);

    Watch w;
    w.show_watch(t);
    w.set_watch(t, 21, 21, 21);
    w.show_watch(t);
    w.set_mode(12);
    w.show_watch(t);

    return 0;
}
