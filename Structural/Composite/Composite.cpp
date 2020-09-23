#include <gtest/gtest.h>
#include <Loggers.h>
#include <numeric>
#include <memory>

class Campus_a_1
{
public:
    int GetWholeProfit() { return 0; }
};

class Campus_a_2
{
public:
    int Get_Profit() { return 0; }
};

class Company_A
{
public:
    int GetProfit()
    {
        exec(return m_campus_1.GetWholeProfit() + m_campus_2.Get_Profit());
    }

private:
    Campus_a_1 m_campus_1;
    Campus_a_2 m_campus_2;
};

class Campus_b_1
{
public:
    int GetMyWholeProfit() { return 0; }
};

class Campus_b_2
{
public:
    int Get_my_Profit() { return 0; }
};

class Company_B
{
public:
    int GetMyProfit()
    {
        exec(return m_campus_1.GetMyWholeProfit() + m_campus_2.Get_my_Profit());
    }

private:
    Campus_b_1 m_campus_1;
    Campus_b_2 m_campus_2;
};

TEST(Composite, Init)
{
    note() << "Let's imagine, that we have a lot of big companies, each company contains a lot of campuses and etc."
        << "We want to determine, what is profit we got during this day";

    exec(Company_A company_a);
    exec(Company_B company_b);

    exec(auto profit = company_a.GetProfit() + company_b.GetMyProfit());

    note() << "Cool, we solve our problem, but... it looks not comfortable, that each 'separate class' has a specific function for it and we need to call each of them manually..";
    
}

class BaseProfitable
{
public:
    virtual int GetProfit() = 0;
};

class Campus : public BaseProfitable
{
public:
    int GetProfit() override
    {
        code_comment() << "Return profit from campus";
        return 0;
    }
};

class Company : public BaseProfitable
{
public:
    int GetProfit() override
    {
        code_comment() << "Return profit from whole company";
        exec(return std::accumulate(m_campuses.begin(), m_campuses.end(), 0, [](int counter, auto& campuse) {return
            counter + campuse->GetProfit(); }));
    }

private:
    std::vector<std::shared_ptr<Campus>> m_campuses{ std::make_shared<Campus>(), std::make_shared<Campus>() };
};

class Corporation : public BaseProfitable
{
public:
    Corporation() {}

    int GetProfit() override
    {
        code_comment() << "Return profit from whole corporation";
        exec(return std::accumulate(m_companies.begin(), m_companies.end(), 0, [](int counter, auto& campuse) {return
            counter + campuse->GetProfit(); }))
    }

private:
    std::vector<std::shared_ptr<Company>> m_companies{std::make_shared<Company>(), std::make_shared<Company>() };
};


TEST(Composite, Solution)
{
    note() << "What if we created a base class, that can return a profit of self? And inherit all of our classes from it? Then we can call only one function from any type of class";

    exec(Corporation corporation{});
    exec(auto profit = corporation.GetProfit());

}