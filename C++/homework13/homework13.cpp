#include <iostream>
#include <vector>
#include <string>

class HouseBuilder {
public:
    virtual ~HouseBuilder() {}
    virtual void buildWalls() = 0;
    virtual void buildFloor() = 0;
    virtual void buildRoof() = 0;
    virtual void buildAdditionalElements() = 0;
    virtual void getResult() = 0;
};

class House {
public:
    std::vector<std::string> parts;

    void listParts() const {
        for (const auto& part : parts) {
            std::cout << part << std::endl;
        }
        std::cout << std::endl;
    }
};

class Documentation {
public:
    std::vector<std::string> pages;

    void listPages() const {
        for (const auto& page : pages) {
            std::cout << page << std::endl;
        }
        std::cout << std::endl;
    }
};

class CertainHouseBuilder : public HouseBuilder {
private:
    House* house;

public:
    CertainHouseBuilder() {
        this->Reset();
    }

    ~CertainHouseBuilder() {
        delete house;
    }

    void Reset() {
        this->house = new House();
    }

    void buildWalls() override {
        this->house->parts.push_back("Walls");
    }

    void buildFloor() override {
        this->house->parts.push_back("Floor");
    }

    void buildRoof() override {
        this->house->parts.push_back("Roof");
    }

    void buildAdditionalElements() override {
        this->house->parts.push_back("Additional Elements");
    }

    void getResult() override {
        this->house->listParts();
    }
};

class CertainDocumentationBuilder : public HouseBuilder {
private:
    Documentation* documentation;

public:
    CertainDocumentationBuilder() {
        this->Reset();
    }

    ~CertainDocumentationBuilder() {
        delete documentation;
    }

    void Reset() {
        this->documentation = new Documentation();
    }

    void buildWalls() override {
        this->documentation->pages.push_back("Walls Documentation");
    }

    void buildFloor() override {
        this->documentation->pages.push_back("Floor Documentation");
    }

    void buildRoof() override {
        this->documentation->pages.push_back("Roof Documentation");
    }

    void buildAdditionalElements() override {
        this->documentation->pages.push_back("Additional Elements Documentation");
    }

    void getResult() override {
        this->documentation->listPages();
    }
};

class Director {
private:
    HouseBuilder* builder;

public:
    void setBuilder(HouseBuilder* builder) {
        this->builder = builder;
    }

    void constructHouse() {
        this->builder->buildWalls();
        this->builder->buildFloor();
        this->builder->buildRoof();
        this->builder->buildAdditionalElements();
    }
};

int main() {
    Director* director = new Director();

    CertainHouseBuilder* houseBuilder = new CertainHouseBuilder();
    director->setBuilder(houseBuilder);
    director->constructHouse();
    houseBuilder->getResult();

    CertainDocumentationBuilder* documentationBuilder = new CertainDocumentationBuilder();
    director->setBuilder(documentationBuilder);
    director->constructHouse();
    documentationBuilder->getResult();

    delete director;
    delete houseBuilder;
    delete documentationBuilder;

    return 0;
}
