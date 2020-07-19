#include <gtest/gtest.h>
#include <Loggers.h>

struct AI
{
    AI()
    {
        code_comment() << "Long time of building and configuring new AI core... Completed in 20 days";
    }

    AI(const AI&)
    {
        code_comment() << "Cloning internal part of AI.... Completed in 1 sec.";
    }

    virtual std::unique_ptr<AI> Clone() { return std::make_unique<AI>(*this); }
};

struct Robot
{
    Robot(const std::unique_ptr<AI>& core)
    {
        code_comment() << "Core attached to robot";
    }
};

TEST(Prototype, Init)
{
    note() << "Let's imagine we have a factory of the AI robots. We build AI, spend a lot of time for learning it and then put into all our robots"
        << "Then we create new AI and repeat it from the start."
        << "Process of creation new AI is very expensive by the time and money and we need to copy AI core every time";

    exec(auto original_core = std::make_unique<AI>(););

    exec(auto clone_1 = std::make_unique<AI>(*original_core););
    exec(auto robot_1 = std::make_unique<Robot>(clone_1););

    note() << "Awesome! Let's create one more robot!";
    exec(auto clone_2 = std::make_unique<AI>(*original_core););
    exec(auto robot_2 = std::make_unique<Robot>(clone_2););
}

struct AI_2_0 : AI
{
    AI_2_0()
    {
        code_comment() << "Version: 2_0: Creating additional parts... Completed in 5 days.";
    }

    AI_2_0(const AI_2_0& other)
        : AI::AI(other)
    {
        code_comment() << "Version 2_0: Configure additional parts... Completed in 3 sec.";
    }


    std::unique_ptr<AI> Clone() override { return std::make_unique<AI_2_0>(*this); }
};

TEST(Prototype, InitWithOneMoreAI)
{
    note() << "All is fine, but now we start to create not only new robots, but and AIs too";

    exec(auto original_core = std::make_unique<AI_2_0>());
    note() << "Great! let's copy old code for creating new robots!";

    exec(std::unique_ptr<AI> clone_1 = std::make_unique<AI_2_0>(*original_core););
    exec(auto robot_1 = std::make_unique<Robot>(clone_1););

    note() << "Awesome! Let's create one more robot!";
    exec(std::unique_ptr<AI> clone_2 = std::make_unique<AI_2_0>(*original_core););
    exec(auto robot_2 = std::make_unique<Robot>(clone_2););
}

TEST(Prototype, ExtractToProtype)
{
    note() << "All is good, but this approach has problems: in the moment of instatiation we must to need original type of AI..."
        << "As a result, it is not possible to extract process of creation robots in the separate function... ";


    exec(std::unique_ptr<AI> original_core = std::make_unique<AI_2_0>());

    exec(std::unique_ptr<AI> clone_1 = original_core->Clone(););
    exec(auto robot_1 = std::make_unique<Robot>(clone_1););

    note() << "Awesome! Let's create one more robot!";
    exec(std::unique_ptr<AI> clone_2 = original_core->Clone(););
    exec(auto robot_2 = std::make_unique<Robot>(clone_2););

    note() << "Now we can use it with any types of AI without knowing about specific type!";
}