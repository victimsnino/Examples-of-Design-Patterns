#pragma once
#include <algorithm>
#include <ostream>

struct YellowLogger
{
    ~YellowLogger()
    {
        if (m_buffer.empty())
            return;

        std::cout << "\033[1;33m"
            << "! ********************************************************************************";
        for (const auto& str : m_buffer)
            std::cout << "\n! " << str;
        std::cout << "\n! ********************************************************************************"
        << "\033[0m\n";
    }

    YellowLogger& operator<<(const std::string& str)
    {
        m_buffer.push_back(str);
        return *this;
    }
private:
    std::vector<std::string> m_buffer;
};

struct SimpleLogger : public std::stringstream
{
    ~SimpleLogger() override
    {
        std::cout << str() << "\n";
    }
};