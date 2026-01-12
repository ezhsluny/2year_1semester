#include <iostream>
#include <vector>
#include <memory>

class GenericCreature
{
public:
    // GenericCreature()
    // {
    //     std::cout << "GenericCreature::obj created (def)" << std::endl;
    // }

    virtual ~GenericCreature() = default;
    virtual void eat() = 0;
};

class OceanCreature : virtual public GenericCreature
{
public:
    // OceanCreature()
    // {
    //     std::cout << "OceanCreature::obj created (def)" << std::endl;
    // }

    // ~OceanCreature()
    // {
    //     std::cout << "OceanCreature::obj deleted" << std::endl;
    // }

    void eat() override
    {
        std::cout << "OceanCreature is eating plankton." << std::endl;
    }

    void swim()
    {
        std::cout << "  swim" << std::endl;
    }
};

class TerrestrialCreature : virtual public GenericCreature
{
public:
    // TerrestrialCreature()
    // {
    //     std::cout << "TerrestrialCreature::obj created (def)" << std::endl;
    // }

    // ~TerrestrialCreature()
    // {
    //     std::cout << "TerrestrialCreature::obj deleted" << std::endl;
    // }

    void walk()
    {
        std::cout << "  walk" << std::endl;
    }

    void eat() override
    {
        std::cout << "TerrestrialCreature is eating plants." << std::endl;
    }
};

class Amphibious : public OceanCreature
{
public:
    // Amphibious()
    // {
    //     std::cout << "Amphibious::obj created (def)" << std::endl;
    // }

    // ~Amphibious()
    // {
    //     std::cout << "Amphibious::obj deleted" << std::endl;
    // }
    
    void eat() override
    {
        std::cout << "Amphibious is eating insects." << std::endl;
    }

    void walk()
    {
        std::cout << "  walk" << std::endl;
    }
};

class Bird : public TerrestrialCreature
{
public:
    // Bird()
    // {
    //     std::cout << "Bird::obj created (def)" << std::endl;
    // }

    // ~Bird()
    // {
    //     std::cout << "Bird::obj deleted" << std::endl;
    // }

    void fly()
    {
        std::cout << "  fly" << std::endl;
    }

    void eat() override
    {
        std::cout << "Bird is eating seeds." << std::endl;
    }
};


class Crocodile : public Amphibious
{
public:
    // Crocodile()
    // {
    //     std::cout << "Crocodile::obj created (def)" << std::endl;
    // }

    // ~Crocodile()
    // {
    //     std::cout << "Crocodile::obj deleted" << std::endl;
    // }

    void eat() override
    {
        std::cout << "Crocodile is eating fish." << std::endl;
    }
};

class Alligator : public Amphibious
{
public:
    // Alligator()
    // {
    //     std::cout << "Alligator::obj created (def)" << std::endl;
    // }

    // ~Alligator()
    // {
    //     std::cout << "Alligator::obj deleted" << std::endl;
    // }

    void eat() override
    {
        std::cout << "Alligator is eating meat." << std::endl;
    }
};

class Pigeon : public Bird
{
public:
    // Pigeon()
    // {
    //     std::cout << "Pigeon::obj created (def)" << std::endl;
    // }

    // ~Pigeon()
    // {
    //     std::cout << "Pigeon::obj deleted" << std::endl;
    // }

    void eat() override
    {
        std::cout << "Pigeon is eating corn." << std::endl;
    }
};

class Duck : public Bird
{
public:
    // Parrot()
    // {
    //     std::cout << "Parrot::obj created (def)" << std::endl;
    // }

    // ~Parrot()
    // {
    //     std::cout << "Parrot::obj deleted" << std::endl;
    // }

    void eat() override
    {
        std::cout << "Duck is eating fruits." << std::endl;
    }
};

class Manul : public TerrestrialCreature
{
public:
    // Manul()
    // {
    //     std::cout << "Manul::obj created (def)" << std::endl;
    // }

    // ~Manul()
    // {
    //     std::cout << "Manul::obj deleted" << std::endl;
    // }

    void eat() override
    {
        std::cout << "Manul is eating small rodents." << std::endl;
    }
};

class Rabbit : public TerrestrialCreature
{
public:
    // Rabbit()
    // {
    //     std::cout << "Rabbit::obj created (def)" << std::endl;
    // }

    // ~Rabbit()
    // {
    //     std::cout << "Rabbit::obj deleted" << std::endl;
    // }

    void eat() override
    {
        std::cout << "Rabbit is eating berries." << std::endl;
    }
};


class Creator
{
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<GenericCreature> createCreature() = 0;
};

class CrocodileCreator : public Creator
{
public:
    std::unique_ptr<GenericCreature> createCreature() override
    {
        return std::make_unique<Crocodile>();
    }
};

class AlligatorCreator : public Creator
{
public:
    std::unique_ptr<GenericCreature> createCreature() override
    {
        return std::make_unique<Alligator>();
    }
};

class PigeonCreator : public Creator
{
public:
    std::unique_ptr<GenericCreature> createCreature() override
    {
        return std::make_unique<Pigeon>();
    }
};

class DuckCreator : public Creator
{
public:
    std::unique_ptr<GenericCreature> createCreature() override
    {
        return std::make_unique<Duck>();
    }
};

class ManulCreator : public Creator
{
public:
    std::unique_ptr<GenericCreature> createCreature() override
    {
        return std::make_unique<Manul>();
    }
};

class RabbitCreator : public Creator
{
public:
    std::unique_ptr<GenericCreature> createCreature() override
    {
        return std::make_unique<Rabbit>();
    }
};


void createAndFeed(Creator& creator, int count)
{
    std::vector<std::unique_ptr<GenericCreature>> creatures;
    for (int i = 0; i < count; ++i)
    {
        creatures.push_back(creator.createCreature());
    }

    for (const auto& creature : creatures)
    {
        creature->eat();
    }
}


int main()
{
    CrocodileCreator crocodileCreator;
    AlligatorCreator alligatorCreator;
    PigeonCreator pigeonCreator;
    DuckCreator duckCreator;
    ManulCreator manulCreator;
    RabbitCreator rabbitCreator;

    std::cout << std::endl;
    createAndFeed(crocodileCreator, 3);
    std::cout << std::endl;
    
    createAndFeed(alligatorCreator, 4);
    std::cout << std::endl;
    
    createAndFeed(pigeonCreator, 3);
    std::cout << std::endl;
    
    createAndFeed(duckCreator, 4);
    std::cout << std::endl;
    
    createAndFeed(manulCreator, 3);
    std::cout << std::endl;

    createAndFeed(rabbitCreator, 3);
    std::cout << std::endl;
    

    return 0;
}