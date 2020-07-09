#include <gtest/gtest.h>
#include <Loggers.h>

enum TypeOfObject
{
    Simple,
    Magic
};

std::vector<std::string> names
{
    "Simple",
    "Magic"
};

std::ostream& operator<<(std::ostream& str, TypeOfObject const& type)
{
    return str << names[type];
}

struct IWall
{
    IWall(TypeOfObject _type) : type(_type) {}
    TypeOfObject type;
};

struct IRoom
{
    IRoom(TypeOfObject _type) : type(_type) {}

    void AddWall(std::shared_ptr<IWall>&& wall)
    {
        std::stringstream ss;
        ss << "For room " << type << " added wall " << wall->type;
        GrayLogger() << ss.str();
        EXPECT_EQ(type, wall->type);
    }

    TypeOfObject type;
    };

    struct SimpleWall : IWall
    {
        SimpleWall() : IWall(TypeOfObject::Simple) {}
    };

    struct SimpleRoom : IRoom
    {
        SimpleRoom() : IRoom(TypeOfObject::Simple) {}
    };

    TEST(AbstractFactory, InitSimpleMaze)
    {
        YellowLogger() << "Simple game: we have rooms and walls in our maze."
                << "Maze can contain only one type of walls and rooms."
                << "Both of them should have similar type. Let's create simple maze";

        exec(std::unique_ptr<IRoom> room = std::make_unique<SimpleRoom>());
        exec(room->AddWall(std::make_shared<SimpleWall>()););
        exec(room->AddWall(std::make_shared<SimpleWall>()););
        exec(room->AddWall(std::make_shared<SimpleWall>()););
        exec(room->AddWall(std::make_shared<SimpleWall>()););
    }

    struct MagicRoom : public IRoom
    {
        MagicRoom() : IRoom(TypeOfObject::Magic){}
    };

    struct MagicWall : public IWall
    {
        MagicWall() : IWall(TypeOfObject::Magic) { }
    };

    TEST(AbstractFactory, InitMagic)
    {
        YellowLogger() << "Ok, now copy-paste and create another room with another walls";
        exec(std::unique_ptr<IRoom> room = std::make_unique<MagicRoom>(););
        exec(room->AddWall(std::make_shared<MagicWall>()););
        exec(room->AddWall(std::make_shared<SimpleWall>()););
        exec(room->AddWall(std::make_shared<MagicWall>()););
        exec(room->AddWall(std::make_shared<MagicWall>()););
        YellowLogger() << "Looks like i skipped one wall..."
                << "But what if we will have a lot of functions? Do i need to change it every time?";
    }

    struct IAbstractFactory
    {
        virtual std::unique_ptr<IRoom> CreateRoom() = 0;
        virtual std::shared_ptr<IWall> CreateWall() = 0;
    };

    struct MagicFactory : IAbstractFactory
    {
        std::unique_ptr<IRoom> CreateRoom() override { return std::make_unique<MagicRoom>(); }
        std::shared_ptr<IWall> CreateWall() override { return std::make_shared<MagicWall>(); }
    };

    TEST(AbstractFactory, InitWithFactory)
    {
        YellowLogger() << "Lets use abstract factory";
        exec(std::unique_ptr<IAbstractFactory> factory = std::make_unique<MagicFactory>(););

        exec(std::unique_ptr<IRoom> room = factory->CreateRoom(););
        exec(room->AddWall(factory->CreateWall()););
        exec(room->AddWall(factory->CreateWall()););
        exec(room->AddWall(factory->CreateWall()););
        exec(room->AddWall(factory->CreateWall()););

        YellowLogger() << "Looks much better. I guess, we can just move it into separate function!";
    }

    struct SimpleFactory : IAbstractFactory
    {
        std::unique_ptr<IRoom> CreateRoom() override { return std::make_unique<SimpleRoom>(); }
        std::shared_ptr<IWall> CreateWall() override { return std::make_shared<SimpleWall>(); }
    };

    void CreateWithFactory(std::unique_ptr<IAbstractFactory>&& factory)
    {
        std::unique_ptr<IRoom> room = factory->CreateRoom();
        room->AddWall(factory->CreateWall());
        room->AddWall(factory->CreateWall());
        room->AddWall(factory->CreateWall());
        room->AddWall(factory->CreateWall());
    }

    TEST(AbstractFactory, InitWithSeparateFunction)
    {
        YellowLogger() << "Lets extract method and put in factory!";
        exec(CreateWithFactory(std::make_unique<MagicFactory>()););
        YellowLogger() << "And another one!";
        exec(CreateWithFactory(std::make_unique<SimpleFactory>()););
        YellowLogger() << "Awesome!";
    }