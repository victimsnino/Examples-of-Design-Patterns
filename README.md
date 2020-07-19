# Examples-of-Design-Patterns
This repository contains examples of different design patterns implemented on the C++. <br>
Each patternd described in the form of short story with continous understanding, "why do we need to use this pattern?". <br> 
Each folder of pattern contains Readme.md with output from the exe with different colors. It shows you required sources, small comments and main notes for understanding situation. <br>
Even this output (without reading sources) can be useful and enough for understanding pattern or remembering.<br>

## For example small part from the Abstract Factory
``` diff 
+[----------] 4 tests from AbstractFactory
+[ RUN      ] AbstractFactory.InitSimpleMaze

! ********************************************************************************
! Simple game: we have rooms and walls in our maze.
! Maze can contain only one type of walls and rooms.
! Both of them should have similar type. Let's create simple maze
! ********************************************************************************
std::unique_ptr<IRoom> room = std::make_unique<SimpleRoom>()
room->AddWall(std::make_shared<SimpleWall>());
# For room Simple added wall Simple
room->AddWall(std::make_shared<SimpleWall>());
# For room Simple added wall Simple
room->AddWall(std::make_shared<SimpleWall>());
# For room Simple added wall Simple
room->AddWall(std::make_shared<SimpleWall>());
# For room Simple added wall Simple
+[       OK ] AbstractFactory.InitSimpleMaze (5 ms)
+[ RUN      ] AbstractFactory.InitMagic

! ********************************************************************************
! Ok, now copy-paste and create another room with another walls
! ********************************************************************************
std::unique_ptr<IRoom> room = std::make_unique<MagicRoom>();
.......

```
Continue you can find in the folder with this pattern =) <br>
Also it contains short U<L with whole classes in the such a situation/pattern
## Note
Repository and all patterns implemented with help of gtests for separating one situation from another. <br>
Order of the "tests" is important since from one test to another become the "understanding", why do we need to use pattern and how.
### Repository in the progress

