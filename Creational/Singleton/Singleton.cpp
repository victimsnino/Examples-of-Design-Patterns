#include <gtest/gtest.h>
#include <Loggers.h>

struct Car
{
    Car() {}
};

struct Registry
{
    void RegistryCar(Car* car)
    {
        code_comment() << "Added new uniq number of car";
    }
};

TEST(Singleton, Init)
{
    note() << "Ok, let's imagine, we have a factory of cars and global registry of this cars by uniq id.";

    exec(Registry registry);

    exec(Car car_1);
    exec(Car car_2);
    exec(Car car_3);
    exec(registry.RegistryCar(&car_1));
    exec(registry.RegistryCar(&car_3));
    exec(registry.RegistryCar(&car_2));
}

void CreateNCars(int count, Registry& registry)
{
    code_comment() << ">>> Start function CreateNCars";
    exec(for (int i = 0; i < count; ++i)
    {
        Car car;
        registry.RegistryCar(&car);
    });
    code_comment() << "<<<< End of function CreateNCars";
}

TEST(Singleton, Problem)
{
    note() << "All works fine, but it looks like we have problem:"
        << " if we have some hierarchy of functions and classes, then we need to put this registry inside all of them"
        << "For example, let's create function for creating N cars in line";

    exec(Registry registry);

    exec(CreateNCars(2, registry));
    exec(CreateNCars(3, registry));

    note() << "Not bad, but... it is not cool to put it everywhere...";
}

Registry g_registry;

void CreateNCarsWithGlobal(int count)
{
    code_comment() << ">>> Start function CreateNCarsWithGlobal";
    exec(for (int i = 0; i < count; ++i)
    {
        Car car;
        g_registry.RegistryCar(&car);
    });
    code_comment() << "<<<< End of function CreateNCarsWithGlobal";
}

TEST(Singleton, GlobalVar)
{
    note() << "One of the possible solution: create global variable!";

    exec(CreateNCarsWithGlobal(2));
    exec(CreateNCarsWithGlobal(3));

    note() << "Much better, but... we have a requirements: only one registry should be able in the system, but now i can create another one registry..";

    exec(Registry one_more_registry);
    exec(Registry one_more_more_registry);

    note() << "Not cool! How to control it?";
}

struct RegistrySingleton
{
    static RegistrySingleton& GetInstance()
    {
        static RegistrySingleton instance{};
        return instance;
    }

    void RegistryCar(Car* car)
    {
        code_comment() << "Added new uniq number of car";
    }
private:
    RegistrySingleton() = default;
};

void CreateNCarsSingleton(int count)
{
    code_comment() << ">>> Start function CreateNCarsSingleton";
    exec(for (int i = 0; i < count; ++i)
    {
        Car car;
        RegistrySingleton::GetInstance().RegistryCar(&car);
    });
    code_comment() << "<<<< End of function CreateNCarsSingleton";
}

TEST(Singleton, Singleton)
{
    note() << "Solution: to add to the Registry function 'GetInstance', that will create static object and return ref to it"
        << "As a result, on the second call it will return the same object as in the first one. As a result, it is like a global var"
        << "But as a result it is possible to make Constructor a private";

    exec(auto & registry = RegistrySingleton::GetInstance());
    exec(Car car_1);
    exec(Car car_2);
    exec(Car car_3);
    exec(registry.RegistryCar(&car_1));
    exec(registry.RegistryCar(&car_3));
    exec(registry.RegistryCar(&car_2));

    exec(CreateNCarsSingleton(2));
}