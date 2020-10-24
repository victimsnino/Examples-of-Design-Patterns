#include <gtest/gtest.h>
#include <Loggers.h>

struct Car{};

struct ServiceRobot
{
    virtual void DoWork(Car* car) = 0;
};

struct WashingRobot : public ServiceRobot
{
    void DoWork(Car* car) override { code_comment() << "Wash car..."; }
};

struct RepairingRobot : public ServiceRobot
{
    void DoWork(Car* car) override { code_comment() << "Repair car..."; }
};

struct TunningRobot : public ServiceRobot
{
    void DoWork(Car* car) override { code_comment() << "Tune car..."; }
};

TEST(Decorator, Init)
{
    note() << "Let's imagine we have a automotive robots for maintaining cars."
        << "They can wash, repair, boost perfomance and etc. For this one we have different robots. Let's imagine we want to apply all robots on one car..";

    exec(Car car{});

    exec(WashingRobot wash);
    exec(RepairingRobot repair);
    exec(TunningRobot tune);

    exec(wash.DoWork(&car));
    exec(repair.DoWork(&car));
    exec(tune.DoWork(&car));
}

struct BaseRobot : public ServiceRobot
{
    void DoWork(Car* car) override { code_comment() << "Do some base work..."; }
};

struct ModuleForRobot : public ServiceRobot
{
    ModuleForRobot(ServiceRobot* robot)
        : m_robot(robot) {}


    void DoWork(Car* car) override final { m_robot->DoWork(car); DoModuleWork(car); }
protected:
    virtual void DoModuleWork(Car* car) {}
private:
    ServiceRobot* m_robot;
};

struct WashingModule : public ModuleForRobot
{
    using ModuleForRobot::ModuleForRobot;
protected:
    void DoModuleWork(Car* car) override { code_comment() << "Washing..."; }
};

struct RepairingModule : public ModuleForRobot
{
    using ModuleForRobot::ModuleForRobot;
protected:
    void DoModuleWork(Car* car) override { code_comment() << "Repairing..."; }
};

struct TuningModule : public ModuleForRobot
{
    using ModuleForRobot::ModuleForRobot;
protected:
    void DoModuleWork(Car* car) override { code_comment() << "Tuning..."; }
};

TEST(Decorator, Problem)
{
    note() << "But we have a problem: with new rules we can apply only one robot to one machine... But we can configure them before work..."
        << "How to solve it? Iheritance? Looks like we have combination boom! We need to create all possible combination of robots.."
        << " Wash, Repair, Tune.. WashRepair, WashTune, RepairTune and etc... (also it is possible to do work in different order)";
    note() << "Correct solution to do robots 'modular' (it contains a lot of modules). For example, module for washing, module for tuning and etc..";

    exec(BaseRobot robot);
    exec(Car car);

    exec(auto moduled_robot = TuningModule{ new WashingModule{new RepairingModule{&robot}}});

    exec(moduled_robot.DoWork(&car));
}