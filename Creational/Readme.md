``` diff
+ [ RUN      ] AbstractFactory.InitSimpleMaze
! ********************************************************************************
! Simple game: we have rooms and walls in our maze.
! Maze can contain only one type of walls and rooms.
! Both of them should have similar type. Let's create simple maze
! ********************************************************************************
std::unique_ptr<IRoom> room = std::make_unique<SimpleRoom>()
room->AddWall(std::make_shared<SimpleWall>());
room->AddWall(std::make_shared<SimpleWall>());
room->AddWall(std::make_shared<SimpleWall>());
room->AddWall(std::make_shared<SimpleWall>());
+ [       OK ] AbstractFactory.InitSimpleMaze (1 ms)
+ [ RUN      ] AbstractFactory.InitMagic
! ********************************************************************************
! Ok, now copy-paste and create another room with another walls
! ********************************************************************************
std::unique_ptr<IRoom> room = std::make_unique<MagicRoom>();
room->AddWall(std::make_shared<MagicWall>());
room->AddWall(std::make_shared<SimpleWall>());
- D:\Coding\Patterns\Creational\AbstractFactory\AbstractFactory.cpp(23): error: Expected equality of these values:
  type
    Which is: 1
  wall->type
    Which is: 0
room->AddWall(std::make_shared<MagicWall>());
room->AddWall(std::make_shared<MagicWall>());
! ********************************************************************************
! Looks like i skipped one wall...
! But what if we will have a lot of functions? Do i need to change it every time?
! ********************************************************************************
- [  FAILED  ] AbstractFactory.InitMagic (11 ms)
+ [ RUN      ] AbstractFactory.InitWithFactory
! ********************************************************************************
! Lets use abstract factory
! ********************************************************************************
std::unique_ptr<IAbstractFactory> factory = std::make_unique<MagicFactory>();
std::unique_ptr<IRoom> room = factory->CreateRoom();
room->AddWall(factory->CreateWall());
room->AddWall(factory->CreateWall());
room->AddWall(factory->CreateWall());
room->AddWall(factory->CreateWall());
! ********************************************************************************
! Looks much better. I guess, we can just move it into separate function!
! ********************************************************************************
+ [       OK ] AbstractFactory.InitWithFactory (18 ms)
+ [ RUN      ] AbstractFactory.InitWithSeparateFunction
! ********************************************************************************
! Lets extract method and put in factory!
! ********************************************************************************
CreateWithFactory(std::make_unique<MagicFactory>());
! ********************************************************************************
! And another one!
! ********************************************************************************
CreateWithFactory(std::make_unique<SimpleFactory>());
! ********************************************************************************
! Awesome!
! ********************************************************************************
+ [       OK ] AbstractFactory.InitWithSeparateFunction (14 ms)

```
