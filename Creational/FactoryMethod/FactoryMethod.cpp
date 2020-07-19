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

struct Wall;
struct Door;

struct Wall { TypeOfObject type = Simple; };
struct Door { TypeOfObject type = Simple; };

struct Room
{
    void AddWall(std::shared_ptr<Wall> wall)
    {
        code_comment() << std::string("Added wall: ") + names[wall->type];
        EXPECT_EQ(wall->type, m_expected_wall_type);
    };
    void AddDoor(std::shared_ptr<Door> door)
    {
        code_comment() << std::string("Added door: ") + names[door->type];
        EXPECT_EQ(door->type, m_expected_door_type);
    }

    void ExpectWall(TypeOfObject wall_type) { m_expected_wall_type = wall_type; }
    void ExpectDoor(TypeOfObject wall_type) { m_expected_door_type = wall_type; }
private:
    TypeOfObject m_expected_wall_type{};
    TypeOfObject m_expected_door_type{};
};


TEST(FactoryMethod, Init)
{
    note() << "Let's imagine, that we build a simple maze!";
    note() << "Create room with 3 walls and 1 room";
    exec(auto room1 = std::make_shared<Room>();)

    exec(room1->AddWall(std::make_shared<Wall>());)
    exec(room1->AddWall(std::make_shared<Wall>());)
    exec(room1->AddWall(std::make_shared<Wall>());)
    exec(room1->AddDoor(std::make_shared<Door>());)

    note() << "Create room with 2 walls and 2 rooms";
    exec(auto room2 = std::make_shared<Room>();)

    exec(room2->AddWall(std::make_shared<Wall>());)
    exec(room2->AddWall(std::make_shared<Wall>());)
    exec(room2->AddDoor(std::make_shared<Door>());)
    exec(room2->AddDoor(std::make_shared<Door>());)
}

struct MagicWall : public Wall { MagicWall() { type = Magic; } };
struct MagicDoor : public Door { MagicDoor() { type = Magic; } };

TEST(FactoryMethod, InitWithAnotherWalls)
{
    note() << "Ok, now let's create same maze but with magic walls!";
    code_comment() << "Create room with 3 walls and 1 room";
    exec(auto room1 = std::make_shared<Room>());
    exec(room1->ExpectWall(Magic));

    exec(room1->AddWall(std::make_shared<MagicWall>()));
    exec(room1->AddWall(std::make_shared<MagicWall>()));
    exec(room1->AddWall(std::make_shared<MagicWall>()));
    exec(room1->AddDoor(std::make_shared<Door>()));

    code_comment() << "Create room with 2 walls and 2 rooms";
    exec(auto room2 = std::make_shared<Room>());
    exec(room2->ExpectWall(Magic));

    exec(room2->AddWall(std::make_shared<Wall>()));
    exec(room2->AddWall(std::make_shared<MagicWall>()));
    exec(room2->AddDoor(std::make_shared<Door>()));
    exec(room2->AddDoor(std::make_shared<Door>()));

    note() << "Look's like I forgot to change one line.... It is not cool";
}

template<typename RoomType, typename WallType, typename DoorType>
struct Creator
{
    virtual std::shared_ptr<Room> CreateRoom() { return std::make_shared<RoomType>(); }
    virtual std::shared_ptr<Wall> CreateWall() { return std::make_shared<WallType>(); }
    virtual std::shared_ptr<Door> CreateDoor() { return std::make_shared<DoorType>(); }
};

TEST(FactoryMethod, ApplyFactoryMethod)
{
    note() << "Let's use factory method in this case! ";
    {
        note() << "Let's create simple rooms, magic walls and simple doors!";
        Creator<Room, MagicWall, Door> creator;
        SimpleLogger() << "Creator<Room, MagicWall, Door> creator;";

        exec(auto room1 = creator.CreateRoom());
        exec(room1->ExpectWall(Magic));

        exec(room1->AddWall(creator.CreateWall()));
        exec(room1->AddWall(creator.CreateWall()));
        exec(room1->AddWall(creator.CreateWall()));
        exec(room1->AddDoor(creator.CreateDoor()));

        code_comment() << "Create room with 2 walls and 2 rooms";
        exec(auto room2 = std::make_shared<Room>());
        exec(room2->ExpectWall(Magic));

        exec(room2->AddWall(creator.CreateWall()));
        exec(room2->AddWall(creator.CreateWall()));
        exec(room2->AddDoor(creator.CreateDoor()));
        exec(room2->AddDoor(creator.CreateDoor()));
    }
    {
        note() << "Ok, now let's create simple rooms, simple walls, but magic doors!";
        Creator<Room, Wall, MagicDoor> creator;
        SimpleLogger() << "Creator<Room, Wall, MagicDoor> creator;";

        exec(auto room1 = creator.CreateRoom());
        exec(room1->ExpectDoor(Magic));

        exec(room1->AddWall(creator.CreateWall()));
        exec(room1->AddWall(creator.CreateWall()));
        exec(room1->AddWall(creator.CreateWall()));
        exec(room1->AddDoor(creator.CreateDoor()));

        code_comment() << "Create room with 2 walls and 2 rooms";
        exec(auto room2 = std::make_shared<Room>());
        exec(room2->ExpectDoor(Magic));

        exec(room2->AddWall(creator.CreateWall()));
        exec(room2->AddWall(creator.CreateWall()));
        exec(room2->AddDoor(creator.CreateDoor()));
        exec(room2->AddDoor(creator.CreateDoor()));
    }
}

struct CreatorBase
{
    virtual std::shared_ptr<Room> CreateRoom() { return std::make_shared<Room>(); }
    virtual std::shared_ptr<Wall> CreateWall() { return std::make_shared<Wall>(); }
    virtual std::shared_ptr<Door> CreateDoor() { return std::make_shared<Door>(); }
};


// Another way of implementing is inheritance
struct CreatorWithMagicWalls : CreatorBase
{
    std::shared_ptr<Wall> CreateWall() override { return std::make_shared<MagicWall>(); }
};