#include <gtest/gtest.h>

enum TypeOfObject
{
    Simple,
    Magic,
    Iron
};

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
        std::cout << "IRoom::AddWall" << std::endl;
        EXPECT_EQ(type, wall->type);
    }

    TypeOfObject type;
};

struct SimpleWall : IWall
{
    SimpleWall() : IWall(Simple) {std::cout << "*** SimpleWall::SimpleWall() ***" << std::endl;}
};

struct SimpleRoom : IRoom
{
    SimpleRoom() : IRoom(Simple){std::cout << "*** SimpleRoom::SimpleRoom() ***" << std::endl;}
};

TEST(AbstractFactory, InitSimpleMaze)
{
    std::cout << "*** Simple game: we have rooms and walls in our maze. " << std::endl
              << "Maze can contain only one type of walls and rooms." <<std::endl
              << "Both of them should have similar type. Let's create simple maze"
              << std::endl;
    std::unique_ptr<IRoom> room = std::make_unique<SimpleRoom>();
    room->AddWall(std::make_shared<SimpleWall>());
    room->AddWall(std::make_shared<SimpleWall>());
    room->AddWall(std::make_shared<SimpleWall>());
    room->AddWall(std::make_shared<SimpleWall>());
}

struct MagicRoom : public IRoom
{
    MagicRoom() : IRoom(Magic){std::cout << "**** MagicRoom::MagicRoom()" << std::endl;}
};

struct MagicWall : public IWall
{
    MagicWall() : IWall(Magic) { std::cout << "**** MagicWall::MagicWall()" << std::endl;}
};

TEST(AbstractFactory, InitMagic)
{
    std::cout << "Ok, now copy-paste and create another room with another walls" << std::endl;
    std::unique_ptr<IRoom> room = std::make_unique<MagicRoom>();
    room->AddWall(std::make_shared<MagicWall>());
    room->AddWall(std::make_shared<SimpleWall>());
    room->AddWall(std::make_shared<MagicWall>());
    room->AddWall(std::make_shared<MagicWall>());
    std::cout   << "Looks like i skipped one wall..." << std::endl
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
    std::cout << "Lets use abstract factory" << std::endl;
    std::unique_ptr<IAbstractFactory> factory = std::make_unique<MagicFactory>();

    std::unique_ptr<IRoom> room = factory->CreateRoom();
    room->AddWall(factory->CreateWall());
    room->AddWall(factory->CreateWall());
    room->AddWall(factory->CreateWall());
    room->AddWall(factory->CreateWall());

    std::cout << "Looks much better. I guess, we can just move it into separate function!";
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
    
    std::cout << "Lets extract method and put in factory!" << std::endl;
    CreateWithFactory(std::make_unique<MagicFactory>());
    std::cout << "And another one!" << std::endl;
    CreateWithFactory(std::make_unique<SimpleFactory>());
    std::cout << "Awesome!" << std::endl;
}