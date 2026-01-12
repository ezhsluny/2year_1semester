#include <iostream>
#include <vector>
#include <memory>
#include <ctime>

class House {
public:
    virtual ~House() = default;
    virtual void build() const = 0;
};

class WoodHouse : public House {
public:
    void build() const override {
        std::cout << "Wood House" << std::endl;
    }
};

class BrickHouse : public House {
public:
    void build() const override {
        std::cout << "Brick House" << std::endl;
    }
};

class ConcreteHouse : public House {
public:
    void build() const override {
        std::cout << "Concrete House" << std::endl;
    }
};

class Developer {
public:
    virtual ~Developer() = default;
    virtual std::unique_ptr<House> buildHouse() const = 0;
};

class WoodDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<WoodHouse>();
    }
};

class BrickDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<BrickHouse>();
    }
};

class ConcreteDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<ConcreteHouse>();
    }
};

void buildQuarter(Developer& developer, int numHouses) {
    std::vector<std::unique_ptr<House>> quarter;
    for (int i = 0; i < numHouses; ++i) {
        quarter.push_back(developer.buildHouse());
        quarter.back()->build();
    }
}

int main() {
    std::srand(std::time(0));
    WoodDeveloper woodDeveloper;
    BrickDeveloper brickDeveloper;
    ConcreteDeveloper concreteDeveloper;

    int n = 4 + std::rand() % 13;
    std::cout << "Building a quarter with Wood Houses:" << std::endl;
    buildQuarter(woodDeveloper, n);
    n = 4 + std::rand() % 13;
    std::cout << "Building a quarter with Brick Houses:" << std::endl;
    buildQuarter(brickDeveloper, n);
    n = 4 + std::rand() % 13;
    std::cout << "Building a quarter with Concrete Houses:" << std::endl;
    buildQuarter(concreteDeveloper, n);

    return 0;
}
