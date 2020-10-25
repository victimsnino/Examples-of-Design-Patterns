#include <gtest/gtest.h>
#include <Loggers.h>

struct LeftWing
{
    void Rotate(int v) { code_comment() << "Rotate Left Wing to " + std::to_string(v); }
};

struct RightWing
{
    void Rotate(int v) { code_comment() << "Rotate Right Wing to " + std::to_string(v); }
};

struct Engine
{
    void Start() { code_comment() << "Launch engine"; }
    void Stop() { code_comment() << "Stop engine"; }
};

struct Wheels
{
    void Open() { code_comment() << "Open wheels"; }
    void Close() { code_comment() << "Close wheels"; }
};


TEST(Facade, Init)
{
    note() << "Let's imagine we have a space rocket. It rocket contains a lot of submodules. We can control it via special interface-framewrk provided by company...";

    exec(LeftWing left{});
    exec(RightWing right{});

    exec(Engine engine{});
    exec(Wheels wheels{});

    note() << "Lets imagine we want to launch our rocket";

    exec(engine.Start());
    exec(left.Rotate(90));
    exec(right.Rotate(90));
    exec("Wait...");
    exec(wheels.Close());

    note() << "Then we need to change target rotation...";

    exec(left.Rotate(110));
    exec(right.Rotate(110));

    note() << "And then finish our flight...";

    exec(wheels.Open());
    exec(engine.Stop())
    exec(left.Rotate(0));
    exec(right.Rotate(0));

    note() << "Awesome, but... looks like it is really hard to use our 'rocket-framework'";

}

struct RocketFacade
{
    void Launch()
    {
        m_engine.Start();
        m_left.Rotate(90);
        m_right.Rotate(90);
        m_wheels.Close();

    }

    void ChangeRotation(int v)
    {
        m_left.Rotate(v);
        m_right.Rotate(v);
    }

    void StopFlight()
    {
        m_wheels.Open();
        m_engine.Stop();
        m_left.Rotate(0);
        m_right.Rotate(0);
    }
private:
    LeftWing  m_left{};
    RightWing m_right{};
    Engine    m_engine{};
    Wheels    m_wheels{};
};

TEST(Facade, Solution)
{
    note() << "For improving usability we can wrap it to RocketFacade - special class that will handle whole rocket with simple interface instead of controlling each component manually...";

    exec(RocketFacade facade{});
    exec(facade.Launch());
    exec(facade.ChangeRotation(110));
    exec(facade.StopFlight());

}