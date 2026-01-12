#include <iostream>
#include <memory>

class House {
public:
    virtual ~House() = default;
    virtual void build() const = 0;
};

class WoodHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Wood House" << std::endl;
    }
};

class BrickHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Brick House" << std::endl;
    }
};

class ConcreteHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Concrete House" << std::endl;
    }
};

class Fence {
public:
    virtual ~Fence() = default;
    virtual void build() const = 0;
};

class WoodFence : public Fence {
public:
    void build() const override {
        std::cout << "Building a Wood Fence" << std::endl;
    }
};

class BrickFence : public Fence {
public:
    void build() const override {
        std::cout << "Building a Brick Fence" << std::endl;
    }
};

class ConcreteFence : public Fence {
public:
    void build() const override {
        std::cout << "Building a Concrete Fence" << std::endl;
    }
};

class Barn {
public:
    virtual ~Barn() = default;
    virtual void build() const = 0;
};

class WoodBarn : public Barn {
public:
    void build() const override {
        std::cout << "Building a Wood Barn" << std::endl;
    }
};

class BrickBarn : public Barn {
public:
    void build() const override {
        std::cout << "Building a Brick Barn" << std::endl;
    }
};

class ConcreteBarn : public Barn {
public:
    void build() const override {
        std::cout << "Building a Concrete Barn" << std::endl;
    }
};

class Developer {
public:
    virtual ~Developer() = default;
    virtual std::unique_ptr<House> buildHouse() const = 0;
    virtual std::unique_ptr<Fence> buildFence() const = 0;
    virtual std::unique_ptr<Barn> buildBarn() const = 0;
};

class WoodDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<WoodHouse>();
    }
    std::unique_ptr<Fence> buildFence() const override {
        return std::make_unique<WoodFence>();
    }
    std::unique_ptr<Barn> buildBarn() const override {
        return std::make_unique<WoodBarn>();
    }
};

class BrickDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<BrickHouse>();
    }
    std::unique_ptr<Fence> buildFence() const override {
        return std::make_unique<BrickFence>();
    }
    std::unique_ptr<Barn> buildBarn() const override {
        return std::make_unique<BrickBarn>();
    }
};

class ConcreteDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<ConcreteHouse>();
    }
    std::unique_ptr<Fence> buildFence() const override {
        return std::make_unique<ConcreteFence>();
    }
    std::unique_ptr<Barn> buildBarn() const override {
        return std::make_unique<ConcreteBarn>();
    }
};

void buildPlot(const Developer& developer) {
    std::unique_ptr<House> house = developer.buildHouse();
    std::unique_ptr<Fence> fence = developer.buildFence();
    std::unique_ptr<Barn> barn = developer.buildBarn();

    house->build();
    fence->build();
    barn->build();
}

int main() {
    WoodDeveloper woodDeveloper;
    BrickDeveloper brickDeveloper;
    ConcreteDeveloper concreteDeveloper;

    std::cout << "Building a plot with Wood structures:" << std::endl;
    buildPlot(woodDeveloper);
    std::cout << std::endl;

    std::cout << "Building a plot with Brick structures:" << std::endl;
    buildPlot(brickDeveloper);
    std::cout << std::endl;

    std::cout << "Building a plot with Concrete structures:" << std::endl;
    buildPlot(concreteDeveloper);
    std::cout << std::endl;

    return 0;
}
