#include <gtest/gtest.h>
#include <Loggers.h>


struct MaterialOwner
{
    virtual std::string GetMaterialName() { return ""; };
};

struct CarCreator
{
    CarCreator(std::unique_ptr<MaterialOwner> material = std::make_unique<MaterialOwner>())
        : m_material(std::move(material)) {}

    virtual void CreateDoor() { code_comment() << "Created new door" << m_material->GetMaterialName(); }
    virtual void CreateWheel() { code_comment() << "Created new wheel" << m_material->GetMaterialName(); }
    virtual void CreateGlass() { code_comment() << "Created new glass" << m_material->GetMaterialName(); }

protected:
    std::unique_ptr<MaterialOwner> m_material;
};

struct FordMaterialOwner : MaterialOwner
{
    std::string GetMaterialName() override { return "MaterialOwner: Ford"; }
};

struct FerrariMaterialOwner : MaterialOwner
{
    std::string GetMaterialName() override { return "MaterialOwner: Ferrari"; }
};

TEST(Bridge, Init)
{
    note() << "Let's imagine, that we have factory of cars. Our factory owns special robots for building cars and components";

    exec(CarCreator creator);

    exec(creator.CreateDoor());
    exec(creator.CreateGlass());
    exec(creator.CreateWheel());

}

struct CarCreatorSedan : public CarCreator
{
    using CarCreator::CarCreator;
    void CreateDoor()  override { code_comment() << "Created new door for sedan"  << m_material->GetMaterialName();}
    void CreateWheel() override { code_comment() << "Created new wheel for sedan" << m_material->GetMaterialName(); }
    void CreateGlass() override { code_comment() << "Created new glass for sedan" << m_material->GetMaterialName(); }
};

struct CarCreatorCoupe : public CarCreator
{
    using CarCreator::CarCreator;
    void CreateDoor()  override { code_comment() << "Created new door for coupe"  << m_material->GetMaterialName(); }
    void CreateWheel() override { code_comment() << "Created new wheel for coupe" << m_material->GetMaterialName(); }
    void CreateGlass() override { code_comment() << "Created new glass for coupe" << m_material->GetMaterialName(); }
};

TEST(Bridge, MoreDifficult)
{
    note() << "Also we have different types of our cars.";

    exec(CarCreatorSedan creator_sedan);

    exec(creator_sedan.CreateDoor());
    exec(creator_sedan.CreateGlass());
    exec(creator_sedan.CreateWheel());


    exec(CarCreatorCoupe creator_coupe);

    exec(creator_coupe.CreateDoor());
    exec(creator_coupe.CreateGlass());
    exec(creator_coupe.CreateWheel());
}


TEST(Bridge, MoreDifficultWithMterial)
{
    note() << "Also we have different types of material's owners for our cars. Naive solution is to add inheritance like..."
        << "CarCreatorSedanFord"
        << "CarCreatorSedanFerrari"
        << "CarCreatoSedanKia"
        << "CarCreatorCoupeFord"
        << "CarCreatorCoupeFerrari"
        << "CarCreatorCoupeKia" << ""
        << "Looks so so ugly.. and now we have only 2 types of cars and 3 types of material's owners, what is next??";
    note() << "Much better to use patter bridge when we have two separate hierarchies and  'bridge' between them";

    exec(CarCreatorSedan creator_ford{std::make_unique<FordMaterialOwner>()});

    exec(creator_ford.CreateDoor());
    exec(creator_ford.CreateGlass());
    exec(creator_ford.CreateWheel());

    exec(CarCreatorSedan creator_ferrari{ std::make_unique<FerrariMaterialOwner>() });

    exec(creator_ferrari.CreateDoor());
    exec(creator_ferrari.CreateGlass());
    exec(creator_ferrari.CreateWheel());
}