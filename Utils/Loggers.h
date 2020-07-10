#pragma once
#include <algorithm>
#include <ostream>

struct ColoredLogger
{
    ColoredLogger(uint32_t color, const char* symbol, bool header_footer = true)
        : m_color(color)
        , m_header_footer(header_footer)
        , m_symbol(symbol) {}

    ~ColoredLogger()
    {
        if (m_buffer.empty())
            return;

        std::cout << "\033[1;" << m_color << "m";
        PrintHeader();

        for (size_t i = 0; i <m_buffer.size(); ++i)
            std::cout << GetBeginOfLine(m_header_footer || i > 0) << m_buffer[i];

        PrintHeader();
        std::cout << "\033[0m\n";
    }

    ColoredLogger& operator<<(const std::string& str)
    {
        m_buffer.push_back(str);
        return *this;
    }

    template<typename  T>
    ColoredLogger& operator<<(const T& str)
    {
        std::stringstream ss;
        ss << str;
        m_buffer.push_back(ss.str());
        return *this;
    }

private:
    void PrintHeader() const
    {
        if (m_header_footer)
            std::cout << GetBeginOfLine() << "********************************************************************************";
    }

    std::string GetBeginOfLine(bool split_line = true) const
    {
        return std::string(split_line ? "\n" : "") + m_symbol + " ";
    }

private:
    std::vector<std::string> m_buffer;
    uint32_t m_color;
    bool m_header_footer;
    const char* m_symbol;
};

struct YellowLogger : ColoredLogger
{
    YellowLogger() : ColoredLogger(33, "!", true){}
};

struct GrayLogger : ColoredLogger
{
    GrayLogger() : ColoredLogger(30, "#", false) {}
};

struct SimpleLogger : public std::stringstream
{
    ~SimpleLogger() override
    {
        std::cout << str() << "\n";
    }
};


#define log_and_execute(x) SimpleLogger() << #x; x;
#define exec(x) log_and_execute(x)

#define note() YellowLogger()
#define code_comment() GrayLogger()