#include <iostream>
#include <vector>
#include <memory>

class GenericCreature
{
public:
    GenericCreature()
    {
        std::cout << "GenericCreature::obj created (def)" << std::endl;
    }

    virtual ~GenericCreature()
    {
        std::cout << "GenericCreature::obj deleted" << std::endl;
    }

    virtual void eat() {std::cout << "..." << std::endl;}
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

    void eat() override
    {
        std::cout << "OceanCreature is eating plankton." << std::endl;
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
    
    void eat() override
    {
        std::cout << "Amphibious is eating insects." << std::endl;
    }

    void walk()
    {
        std::cout << "  walk" << std::endl;
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

    void eat() override
    {
        std::cout << "TerrestrialCreature is eating plants." << std::endl;
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

    void eat() override
    {
        std::cout << "Bird is eating seeds." << std::endl;
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

    void eat() override
    {
        std::cout << "Waterfowl is eating fish." << std::endl;
    }
};

int main()
{
    std::vector<GenericCreature*> creatures;
    creatures.push_back(new OceanCreature());
    creatures.push_back(new Amphibious());
    creatures.push_back(new TerrestrialCreature());
    creatures.push_back(new Bird());
    creatures.push_back(new Waterfowl());

    std::cout << std::endl;
    std::cout << "------------Polymorphic behavior:------------" << std::endl;
    for (const auto& creature : creatures)
    { creature->eat(); }

    std::cout << std::endl;
    std::cout << "------------Non-polymorphic behavior:------------" << std::endl;
    std::vector<GenericCreature> creatures_ob;
    
    creatures_ob.push_back(OceanCreature());
    creatures_ob.push_back(TerrestrialCreature());
    creatures_ob.push_back(Amphibious());
    creatures_ob.push_back(Bird());
    creatures_ob.push_back(Waterfowl());

    std::cout << "\n\n";
    for (auto &creature : creatures_ob) {
        creature.eat();
    }
    std::cout << "\n\n";

    for (auto creature : creatures) {
        delete creature;
    }

    return 0;
}