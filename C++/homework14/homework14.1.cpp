#include <iostream>
#include <memory>

class SpeedStrategy {
public:
    virtual double calculateSpeed(int rpm) const = 0;
    virtual ~SpeedStrategy() = default;
};

class ReverseGear : public SpeedStrategy {
public:
    double calculateSpeed(int rpm) const override {
        return -rpm * 0.01;
    }
};

class FirstGear : public SpeedStrategy {
public:
    double calculateSpeed(int rpm) const override {
        return rpm * 1 * 0.02;
    }
};

class SecondGear : public SpeedStrategy {
public:
    double calculateSpeed(int rpm) const override {
        return rpm * 2 * 0.02;
    }
};

class ThirdGear : public SpeedStrategy {
public:
    double calculateSpeed(int rpm) const override {
        return rpm * 3 * 0.02;
    }
};

class FourthGear : public SpeedStrategy {
public:
    double calculateSpeed(int rpm) const override {
        return rpm * 4 * 0.02;
    }
};

class FifthGear : public SpeedStrategy {
public:
    double calculateSpeed(int rpm) const override {
        return rpm * 5 * 0.02;
    }
};

class Car {
public:
    Car(int rpm, std::unique_ptr<SpeedStrategy> strategy)
        : rpm(rpm), speedStrategy(std::move(strategy)) {
        updateSpeed();
    }

    void setRPM(int newRPM) {
        rpm = newRPM;
        updateSpeed();
    }

    void setGear(std::unique_ptr<SpeedStrategy> strategy) {
        speedStrategy = std::move(strategy);
        updateSpeed();
    }

    double getSpeed() const {
        return speed;
    }

    int getRPM() const {
        return rpm;
    }

private:
    int rpm;
    double speed = 0;
    std::unique_ptr<SpeedStrategy> speedStrategy;

    void updateSpeed() {
        speed = speedStrategy->calculateSpeed(rpm);
    }
};

int main() {
    auto firstGear = std::make_unique<FirstGear>();
    Car myCar(2000, std::move(firstGear));

    std::cout << "Initial speed: " << myCar.getSpeed() << std::endl;

    auto secondGear = std::make_unique<SecondGear>();
    myCar.setGear(std::move(secondGear));
    std::cout << "Speed in gear 2: " << myCar.getSpeed() << std::endl;

    myCar.setRPM(3000);
    std::cout << "Speed with 3000 RPM: " << myCar.getSpeed() << std::endl;

    auto reverseGear = std::make_unique<ReverseGear>();
    myCar.setGear(std::move(reverseGear));
    std::cout << "Speed in reverse gear: " << myCar.getSpeed() << std::endl;

    return 0;
}
