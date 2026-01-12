#include <iostream>
#include <vector>
#include <memory>

class GenericCreature;
class OceanCreature;
class Amphibious;
class TerrestrialCreature;
class Bird;
class Waterfowl;

class CreatureVisitor {
public:
    virtual void visit(OceanCreature& creature) = 0;
    virtual void visit(Amphibious& creature) = 0;
    virtual void visit(TerrestrialCreature& creature) = 0;
    virtual void visit(Bird& creature) = 0;
    virtual void visit(Waterfowl& creature) = 0;
    virtual ~CreatureVisitor() = default;
};


class CertainVisitor : public CreatureVisitor {
public:
    void visit(OceanCreature& creature) override;
    void visit(Amphibious& creature) override;
    void visit(TerrestrialCreature& creature) override;
    void visit(Bird& creature) override;
    void visit(Waterfowl& creature) override;
};


class GenericCreature {
public:
    GenericCreature() {
        std::cout << "GenericCreature::obj created (def)" << std::endl;
    }

    virtual ~GenericCreature() = default;
    virtual void eat() = 0;
    virtual void accept(CreatureVisitor& visitor) = 0;
};

class OceanCreature : virtual public GenericCreature {
public:
    OceanCreature() {
        std::cout << "OceanCreature::obj created (def)" << std::endl;
    }

    ~OceanCreature() {
        std::cout << "OceanCreature::obj deleted" << std::endl;
    }

    void eat() override {
        std::cout << "  eating plankton." << std::endl;
    }

    void swim() {
        std::cout << "  swimming." << std::endl;
    }

    void accept(CreatureVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Amphibious : public OceanCreature {
public:
    Amphibious() {
        std::cout << "Amphibious::obj created (def)" << std::endl;
    }

    ~Amphibious() {
        std::cout << "Amphibious::obj deleted" << std::endl;
    }

    void eat() override {
        std::cout << "  eating insects." << std::endl;
    }

    void walk() {
        std::cout << "  walking." << std::endl;
    }

    void accept(CreatureVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class TerrestrialCreature : virtual public GenericCreature {
public:
    TerrestrialCreature() {
        std::cout << "TerrestrialCreature::obj created (def)" << std::endl;
    }

    ~TerrestrialCreature() {
        std::cout << "TerrestrialCreature::obj deleted" << std::endl;
    }

    void walk() {
        std::cout << "  walking." << std::endl;
    }

    void eat() override {
        std::cout << "  eating plants." << std::endl;
    }

    void accept(CreatureVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Bird : public TerrestrialCreature {
public:
    Bird() {
        std::cout << "Bird::obj created (def)" << std::endl;
    }

    ~Bird() {
        std::cout << "Bird::obj deleted" << std::endl;
    }

    void fly() {
        std::cout << "  flying." << std::endl;
    }

    void eat() override {
        std::cout << "  eating seeds." << std::endl;
    }

    void accept(CreatureVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    Waterfowl() {
        std::cout << "Waterfowl::obj created (def)" << std::endl;
    }

    ~Waterfowl() {
        std::cout << "Waterfowl::obj deleted" << std::endl;
    }

    void eat() override {
        std::cout << "  eating fish." << std::endl;
    }

    void accept(CreatureVisitor& visitor) override {
        visitor.visit(*this);
    }
};


void CertainVisitor::visit(OceanCreature& creature) {
    creature.eat();
    creature.swim();
}

void CertainVisitor::visit(Amphibious& creature) {
    creature.walk();
    creature.eat();
    creature.swim();
}

void CertainVisitor::visit(TerrestrialCreature& creature) {
    creature.walk();
    creature.eat();
}

void CertainVisitor::visit(Bird& creature) {
    creature.fly();
    creature.eat();
    creature.walk();
}

void CertainVisitor::visit(Waterfowl& creature) {
    creature.fly();
    creature.eat();
    creature.swim();
    creature.walk();
}

int main() {
    std::vector<std::unique_ptr<GenericCreature>> creatures;
    creatures.push_back(std::make_unique<OceanCreature>());
    creatures.push_back(std::make_unique<Amphibious>());
    creatures.push_back(std::make_unique<TerrestrialCreature>());
    creatures.push_back(std::make_unique<Bird>());
    creatures.push_back(std::make_unique<Waterfowl>());

    CertainVisitor visitor;

    for (auto& creature : creatures) {
        creature->accept(visitor);
        std::cout << "\n\n";
    }

    return 0;
}
