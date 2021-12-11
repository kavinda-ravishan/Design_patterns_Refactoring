#include <iostream>
#include <string.h>

using namespace std;

class AbstractProductA
{
public:
    virtual ~AbstractProductA() {}
    virtual std::string functionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA
{
public:
    std::string functionA() const override
    {
        return "The result of product A1";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
public:
    std::string functionA() const override
    {
        return "The result of product A2";
    }
};

class AbstractProductB
{
public:
    virtual ~AbstractProductB() {}
    virtual std::string functionB() const = 0;
    virtual std::string functionBA(const AbstractProductA &collaborator) const = 0;
};

class ConcreteProductB1 : public AbstractProductB
{
public:
    std::string functionB() const override
    {
        return "The result of product B1\n";
    }

    std::string functionBA(const AbstractProductA &collaborator) const override
    {
        return "The result of product B1 with (" + collaborator.functionA() + ")\n";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    std::string functionB() const override
    {
        return "The result of product B2\n";
    }

    std::string functionBA(const AbstractProductA &collaborator) const override
    {
        return "The result of product B2 with (" + collaborator.functionA() + ")\n";
    }
};

class AbstractFactory
{
public:
    virtual ~AbstractFactory() {}
    virtual AbstractProductA *createProductA() const = 0;
    virtual AbstractProductB *createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *createProductA() const override
    {
        return new ConcreteProductA1();
    }
    AbstractProductB *createProductB() const override
    {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA *createProductA() const override
    {
        return new ConcreteProductA2();
    }
    AbstractProductB *createProductB() const override
    {
        return new ConcreteProductB2();
    }
};

void ClientCode(const AbstractFactory &factory)
{
    const AbstractProductA *productA = factory.createProductA();
    const AbstractProductB *productB = factory.createProductB();

    cout << productB->functionB();
    cout << productB->functionBA(*productA);

    delete productA;
    delete productB;
}

int main(int argc, char *argv[])
{

    const AbstractFactory *factory1 = new ConcreteFactory1();
    const AbstractFactory *factory2 = new ConcreteFactory2();

    ClientCode(*factory1);
    ClientCode(*factory2);

    delete factory1;
    delete factory2;

    return 0;
}