#include <gtest/gtest.h>
#include <Loggers.h>

struct DataSaver
{
    virtual void AddText(const std::string& data) = 0;
    virtual void SaveCollectedText() = 0;
};

struct TxtSaver : public DataSaver
{
    void AddText(const std::string& data) override { code_comment() << std::string("Add to TxtSaver: ") + data; };
    void SaveCollectedText() override { code_comment() << "TxtSaver Save;"; };
};

struct DocSaver : public DataSaver
{
    void AddText(const std::string& data) override { code_comment() << std::string("Add to DocSaver: ") + data; };
    void SaveCollectedText() override { code_comment() << "DocSaver Save;"; };
};

TEST(Adapter, Init)
{
    note() << "Let's image, that we have a bunch of different savers of text data. Our task -> Save input data to all available formats";

    exec(std::vector<std::unique_ptr<DataSaver>> savers);
    exec(savers.emplace_back(std::make_unique<TxtSaver>()));
    exec(savers.emplace_back(std::make_unique<DocSaver>()));

    exec(for (const auto& text : { "First", "Second", "End" })
        for (auto& saver : savers)
            saver->AddText(text););

    exec(for (auto& saver : savers)
        saver->SaveCollectedText());
}

struct LaTeXExternalSaver
{
    void AddNewText(const std::string& data) { code_comment() << std::string("Add to LaTeXExternalSaver: ") + data; };
    void Save() { code_comment() << "LaTeXExternalSaver Save;"; };
};

TEST(Adapter, Problem)
{
    note() << "Let's imagine then, that we have new format and special library for this format, but problem is that new format has non-compatible interface and we can't use inheritance..."
        << "Naive solution: use it as is";

    exec(std::vector<std::unique_ptr<DataSaver>> savers);
    exec(savers.emplace_back(std::make_unique<TxtSaver>()));
    exec(savers.emplace_back(std::make_unique<DocSaver>()));

    exec(auto latex = std::make_unique<LaTeXExternalSaver>());

    exec(for (const auto& text : { "First", "Second", "End" })
    {
        for (auto& saver : savers)
        {
            saver->AddText(text);
        }
        latex->AddNewText(text);
    });

    exec(for (auto& saver : savers)
    {
        saver->SaveCollectedText();
    });
    exec(latex->Save());

    note() << " It looks so ugly... What if we will have one more external savers??";
}

struct LatexSaverAdapterInterface : public DataSaver, private LaTeXExternalSaver
{
    void AddText(const std::string& data) override { AddNewText(data); }
    void SaveCollectedText() override { Save(); };
};

TEST(Adapter, Solution)
{
    note() << "Let's create an adapter over our external saver for unifying interfaces";

    exec(std::vector<std::unique_ptr<DataSaver>> savers);
    exec(savers.emplace_back(std::make_unique<TxtSaver>()));
    exec(savers.emplace_back(std::make_unique<DocSaver>()));
    exec(savers.emplace_back(std::make_unique<LatexSaverAdapterInterface>()));

    exec(for (const auto& text : { "First", "Second", "End" })
        for (auto& saver : savers)
            saver->AddText(text););

    exec(for (auto& saver : savers)
        saver->SaveCollectedText());
}


// Another way: adapt object instead of interface
struct LatexSaverAdapterObject : public DataSaver
{
    void AddText(const std::string& data) override { m_saver->AddNewText(data); }
    void SaveCollectedText() override { m_saver->Save(); };

    std::unique_ptr<LaTeXExternalSaver> m_saver = std::make_unique<LaTeXExternalSaver>();
};

// In this case it is more easy to change adaptee object (for example, it is possible to put it into constructor instead of inheritance all subclasses
