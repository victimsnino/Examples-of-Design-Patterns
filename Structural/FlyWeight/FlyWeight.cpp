#include <array>
#include <gtest/gtest.h>
#include <Loggers.h>

struct Detail
{
    std::array<char, 32>  detail_used_fields;
    std::array<char, 256> coded_factory_info;
    std::array<char, 512> coded_source_info;
};

TEST(FlyWeight, Init)
{
    note() << "Let's imagine we have a lot of factories of details for cars.. By the global rules each detail should contains a way to determine the source of factory";

    exec(Detail detail);

    note() << "We have all required info:";
    exec(detail.detail_used_fields);
    exec(detail.coded_factory_info);
    exec(detail.coded_source_info);
    exec(std::cout << "Sizeof: " << sizeof(detail) << " SizeOf detail fields:" << sizeof(detail.detail_used_fields) << std::endl);


    note() << "Looks like we spend a lot o memory for storing factory info... moreover, all details from one factory will contains the same info... Looks like probem of memory...";
}

struct NewDetailMeta
{
    std::array<char, 256> coded_factory_info;
    std::array<char, 512> coded_source_info;
};

struct NewDetail
{
    std::array<char, 32>  detail_used_fields;
    std::shared_ptr<NewDetailMeta> meta_info;
};

struct DetailsCreator
{
    NewDetail CreateDetail()
    {
        NewDetail detail{};
        detail.meta_info = metas[0];
        return detail;
    }
    std::vector<std::shared_ptr<NewDetailMeta>> metas{ std::make_shared<NewDetailMeta>() };
};

TEST(FlyWeight, Solution)
{
    note() << "Ok. let's store extra meta info in the separate place and store in object only reference/pointer/index for accessing required meta fields...";

    exec(DetailsCreator factory{});
    exec(auto detail = factory.CreateDetail());

    exec(detail.detail_used_fields);
    exec(detail.meta_info);

    exec(std::cout << "Sizeof " << sizeof(detail) << std::endl);
}
