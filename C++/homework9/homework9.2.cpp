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

    void method()
    { std::cout << "generic method" << std::endl;}
};

class OceanCreature : virtual public GenericCreature
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

class TerrestrialCreature : virtual public GenericCreature
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

    void walk()
    {
        std::cout << "  walk" << std::endl;
    }
};

class Amphibious : public OceanCreature, public TerrestrialCreature
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

class Waterfowl : public Bird, public OceanCreature
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
};

int main() {
    GenericCreature gc;
    std::cout << "\n\n";

    OceanCreature fish;
    fish.swim();
    fish.method();
    std::cout << "\n\n";

    TerrestrialCreature cat;
    cat.walk();
    cat.method();
    std::cout << "\n\n";

    Bird sparrow;
    sparrow.fly(); //должен вызываться
    sparrow.walk();
    sparrow.method();
    // sparrow.swim(); //вызываться не должен
    std::cout << "\n\n";

    Waterfowl goose;
    goose.fly();
    goose.swim();
    goose.walk();
    goose.method();
    std::cout << "\n\n";

    Amphibious frog;
    frog.swim();
    frog.walk();
    frog.method();
    std::cout << "\n\n";

    return 0;
}