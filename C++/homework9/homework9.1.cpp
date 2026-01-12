#include <iostream>
#include <string>

class GenericCreature
{
public:
    GenericCreature()
    {
        std::cout << "GenericCreature::obj created (def)" << std::endl;
    }

    ~GenericCreature()
    {
        std::cout << "GenericCreature::obj deleted" << std::endl;
    }
};

class OceanCreature : public GenericCreature
{
public:
    OceanCreature()
    {
        std::cout << "OceanCreature::obj created (def)" << std::endl;
    }

    ~OceanCreature()
    {
        std::cout << "OceanCreature::obj deleted" << std::endl;
    }

    void swim()
    {
        std::cout << "  swim" << std::endl;
    }
};

class Amphibious : public OceanCreature
{
public:
    Amphibious()
    {
        std::cout << "Amphibious::obj created (def)" << std::endl;
    }

    ~Amphibious()
    {
        std::cout << "Amphibious::obj deleted" << std::endl;
    }

    void walk()
    {
        std::cout << "  walk" << std::endl;
    }
};

class TerrestrialCreature : public Amphibious
{
public:
    TerrestrialCreature()
    {
        std::cout << "TerrestrialCreature::obj created (def)" << std::endl;
    }

    ~TerrestrialCreature()
    {
        std::cout << "TerrestrialCreature::obj deleted" << std::endl;
    }

    void swim() const = delete;
};

class Bird : public TerrestrialCreature
{
public:
    Bird()
    {
        std::cout << "Bird::obj created (def)" << std::endl;
    }

    ~Bird()
    {
        std::cout << "Bird::obj deleted" << std::endl;
    }

    void fly()
    {
        std::cout << "  fly" << std::endl;
    }
};

class Waterfowl : public Bird
{
public:
    Waterfowl()
    {
        std::cout << "Waterfowl::obj created (def)" << std::endl;
    }

    ~Waterfowl()
    {
        std::cout << "Waterfowl::obj deleted" << std::endl;
    }

    using OceanCreature::swim;
};

int main() {
    GenericCreature gc;
    std::cout << "\n\n";

    OceanCreature fish;
    fish.swim();
    std::cout << "\n\n";

    TerrestrialCreature cat;
    cat.walk();
    std::cout << "\n\n";

    Bird sparrow;
    sparrow.fly(); //должен вызываться
    sparrow.walk();
    // sparrow.swim(); //вызываться не должен
    std::cout << "\n\n";

    Waterfowl goose;
    goose.fly();
    goose.swim();
    goose.walk();
    std::cout << "\n\n";

    Amphibious frog;
    frog.swim();
    frog.walk();
    std::cout << "\n\n";

    return 0;
}
