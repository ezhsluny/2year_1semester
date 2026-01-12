#include <iostream>
#include <vector>
#include <memory>

class GenericCreature
{
public:
    virtual ~GenericCreature() = default;
    virtual void eat() = 0;
    virtual std::unique_ptr<GenericCreature> create() const = 0;
};

class OceanCreature : virtual public GenericCreature
{
public:
    void eat() override
    {
        std::cout << "  eating plankton." << std::endl;
    }

    void swim()
    {
        std::cout << "  swim" << std::endl;
    }
};

class TerrestrialCreature : virtual public GenericCreature
{
public:
    void walk()
    {
        std::cout << "  walk" << std::endl;
    }

    void eat() override
    {
        std::cout << "  eating plants." << std::endl;
    }
};

class Amphibious : public OceanCreature
{
public:
    void eat() override
    {
        std::cout << "  eating insects." << std::endl;
    }

    void walk()
    {
        std::cout << "  walk" << std::endl;
    }
};

class Bird : public TerrestrialCreature
{
public:
    void fly()
    {
        std::cout << "  fly" << std::endl;
    }

    void eat() override
    {
        std::cout << "  eating seeds." << std::endl;
    }
};

class Crocodile : public Amphibious
{
public:
    void eat() override
    {
        std::cout << "Crocodile is eating fish." << std::endl;
    }

    std::unique_ptr<GenericCreature> create() const override
    {
        return std::make_unique<Crocodile>();
    }
};

class Alligator : public Amphibious
{
public:
    void eat() override
    {
        std::cout << "Alligator is eating meat." << std::endl;
    }

    std::unique_ptr<GenericCreature> create() const override
    {
        return std::make_unique<Alligator>();
    }
};

class Pigeon : public Bird
{
public:
    void eat() override
    {
        std::cout << "Pigeon is eating corn." << std::endl;
    }

    std::unique_ptr<GenericCreature> create() const override
    {
        return std::make_unique<Pigeon>();
    }
};

class Parrot : public Bird
{
public:
    void eat() override
    {
        std::cout << "Parrot is eating fruits." << std::endl;
    }

    std::unique_ptr<GenericCreature> create() const override
    {
        return std::make_unique<Parrot>();
    }
};

class Manul : public TerrestrialCreature
{
public:
    void eat() override
    {
        std::cout << "Manul is eating small rodents." << std::endl;
    }

    std::unique_ptr<GenericCreature> create() const override
    {
        return std::make_unique<Manul>();
    }
};

class Rabbit : public TerrestrialCreature
{
public:
    void eat() override
    {
        std::cout << "Rabbit is eating berries." << std::endl;
    }

    std::unique_ptr<GenericCreature> create() const override
    {
        return std::make_unique<Rabbit>();
    }
};

class Zoo
{
public:
    void addCreature(std::unique_ptr<GenericCreature> creature)
    {
        creatures.push_back(std::move(creature));
    }

    void feedAll()
    {
        for (const auto& creature : creatures)
        {
            creature->eat();
        }
    }

    void makeAllSwim()
    {
        for (const auto& creature : creatures)
        {
            if (auto oceanCreature = dynamic_cast<OceanCreature*>(creature.get()))
            {
                oceanCreature->swim();
            }
        }
    }

    void makeAllWalk()
    {
        for (const auto& creature : creatures)
        {
            if (auto terrestrialCreature = dynamic_cast<TerrestrialCreature*>(creature.get()))
            {
                terrestrialCreature->walk();
            }
        }
    }

    void makeAllFly()
    {
        for (const auto& creature : creatures)
        {
            if (auto bird = dynamic_cast<Bird*>(creature.get()))
            {
                bird->fly();
            }
        }
    }

private:
    std::vector<std::unique_ptr<GenericCreature>> creatures;
};

class ZooBuilder
{
public:
    ZooBuilder& addCrocodile()
    {
        zoo.addCreature(Crocodile().create());
        return *this;
    }

    ZooBuilder& addAlligator()
    {
        zoo.addCreature(Alligator().create());
        return *this;
    }

    ZooBuilder& addPigeon()
    {
        zoo.addCreature(Pigeon().create());
        return *this;
    }

    ZooBuilder& addParrot()
    {
        zoo.addCreature(Parrot().create());
        return *this;
    }

    ZooBuilder& addManul()
    {
        zoo.addCreature(Manul().create());
        return *this;
    }

    ZooBuilder& addRabbit()
    {
        zoo.addCreature(Rabbit().create());
        return *this;
    }

    Zoo build()
    {
        return std::move(zoo);
    }

private:
    Zoo zoo;
};

int main()
{
    ZooBuilder builder;
    builder.addCrocodile();
    builder.addAlligator();
    builder.addPigeon();
    builder.addParrot();
    builder.addManul();
    builder.addRabbit();

    Zoo zoo = builder.build();

    zoo.feedAll();
    zoo.makeAllSwim();
    zoo.makeAllWalk();
    zoo.makeAllFly();

    return 0;
}

