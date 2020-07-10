#include <gtest/gtest.h>
#include <Loggers.h>

struct Trailer {};

struct Car
{
    Car(size_t   count_of_doors,
        size_t   count_of_wheels,
        size_t   count_of_seats,
        Trailer* trailer,
        bool     is_spoiler,
        bool     is_turbine)
        : m_count_of_doors(count_of_doors)
        , m_count_of_wheels(count_of_wheels)
        , m_count_of_seats(count_of_seats)
        , m_trailer(trailer)
        , m_is_spoiler(is_spoiler)
        , m_is_turbine(is_turbine)
    {
        std::stringstream ss;
        ss << "Builded car with " << count_of_doors << " doors, "
                << count_of_wheels << " wheels, " << count_of_seats << " seats, trailer exist: "
                << std::boolalpha << !!trailer << ", spoiler: " << is_spoiler << ", turbine: " << is_turbine;
        code_comment() << ss.str();
    }

    size_t   m_count_of_doors;
    size_t   m_count_of_wheels;
    size_t   m_count_of_seats;
    Trailer* m_trailer;
    bool     m_is_spoiler;
    bool     m_is_turbine;
};


TEST(Builder, CreateACar)
{
    note() << "Ok, let's imagine, that we have a factory of cars different types."
            << "How do we can build car? Let's build simple car";

    exec(Car target_car(4, 4, 4, nullptr, false, false););

    note() << "But what about trucks?";
    exec(Trailer trailer;);
    exec(Car truck_car(2, 6, 2, &trailer, false, false););

    note() << "Ok, but what about sport-car with spoiler?";
    exec(Car sport_car(2, 4, 2, nullptr, true, false););

    note() << "With turbine but without spoiler?";
    exec(Car sport_car_with_turbine(4, 4, 4, nullptr, false, true););

    note() << "Ok, same, but with 2 doors!";
    exec(Car sport_car_with_turbine_2_doors(4, 2, 4, nullptr, false, true););
    EXPECT_EQ(sport_car_with_turbine_2_doors.m_count_of_seats, 2);

    note() << "Wait... Looks like i've missed field.. Oh, it is really hard to understand, where is what!"
            << " More it looks like a huge constructor!"
            << "In the last one i've not used spoiler and track... Why do i need to put it? And in the any other cases"
            << "Oh... What if i will add some other features like color, height, power, size of spoiler, and more others. Do i need to fill it every time??";
}

struct CarBuilder
{
    CarBuilder() {}

    virtual CarBuilder& WithDoors(size_t doors) { m_count_of_doors = doors; return *this; }
    virtual CarBuilder& WithWheels(size_t wheels) { m_count_of_wheels = wheels; return *this; }
    virtual CarBuilder& WithSeats(size_t seats) { m_count_of_seats = seats; return *this; }
    virtual CarBuilder& AttachTrailer(Trailer* trailer) { m_trailer = trailer;  return *this; }
    virtual CarBuilder& AddSpoiler() { m_is_spoiler = true;  return *this; }
    virtual CarBuilder& AddTurbine() { m_is_turbine = true;  return *this; }

    Car BuildCar() const
    {
        return Car(m_count_of_doors, m_count_of_wheels, m_count_of_seats, m_trailer, m_is_spoiler, m_is_turbine);
    }

private:
    size_t   m_count_of_doors{};
    size_t   m_count_of_wheels{};
    size_t   m_count_of_seats{};
    Trailer* m_trailer{};
    bool     m_is_spoiler{};
    bool     m_is_turbine{};
};

TEST(Builder, BuildViaBuilder)
{
    note() << "Let's try again with builder!";
    exec(CarBuilder().WithDoors(4).WithSeats(2).WithWheels(4).AddSpoiler().AddTurbine().BuildCar());


    note() << "Much better!";

    Trailer trailer;
    exec(CarBuilder().WithWheels(4).WithDoors(2).WithSeats(2).AttachTrailer(&trailer).BuildCar());

    note() << "Awesome!";
}

struct FordBuilder : CarBuilder
{
    CarBuilder& WithDoors(size_t doors) override { code_comment() << "Add Ford's door"; return CarBuilder::WithDoors(doors); }
    CarBuilder& WithWheels(size_t wheels) override { code_comment() << "Add Ford's wheels"; return CarBuilder::WithWheels(wheels); }
    CarBuilder& WithSeats(size_t seats) override { code_comment() << "Add Ford's seats"; return CarBuilder::WithSeats(seats); }
    CarBuilder& AttachTrailer(Trailer* trailer) override { code_comment() << "Add Ford's trailer"; return CarBuilder::AttachTrailer(trailer); }
    CarBuilder& AddSpoiler() override { code_comment() << "Add Ford's spoiler"; return CarBuilder::AddSpoiler(); }
    CarBuilder& AddTurbine() override { code_comment() << "Add Ford's turbine"; return CarBuilder::AddTurbine(); }
};

struct FerrariBuilder : CarBuilder
{
    CarBuilder& WithDoors(size_t doors) override { code_comment() << "Add Ferrari's door"; return CarBuilder::WithDoors(doors); }
    CarBuilder& WithWheels(size_t wheels) override { code_comment() << "Add Ferrari's wheels"; return CarBuilder::WithWheels(wheels); }
    CarBuilder& WithSeats(size_t seats) override { code_comment() << "Add Ferrari's seats"; return CarBuilder::WithSeats(seats); }
    CarBuilder& AttachTrailer(Trailer* trailer) override { code_comment() << "Add Ferrari's trailer"; return CarBuilder::AttachTrailer(trailer); }
    CarBuilder& AddSpoiler() override { code_comment() << "Add Ferrari's spoiler"; return CarBuilder::AddSpoiler(); }
    CarBuilder& AddTurbine() override { code_comment() << "Add Ferrari's turbine"; return CarBuilder::AddTurbine(); }
};

struct CoupeDirector
{
    CoupeDirector(CarBuilder& builder)
    {
        builder.WithWheels(4).WithSeats(2).WithDoors(2).AddSpoiler().AddTurbine().BuildCar();
    }
};

struct TruckDirector
{
    TruckDirector(CarBuilder& builder)
    {
        Trailer trailer;
        builder.WithWheels(6).WithSeats(2).WithDoors(2).AttachTrailer(&trailer).BuildCar();
    }
};

TEST(Builder, BuilderAndDirector)
{
    note() << "This pattern can be used in the other form via adding director."
        << "In the such a situation builder is responsible for 'creating' suitable materials and parts"
        << "And director is responsible for 'how to create' some forms"
        << "For example, building of any 'coupe' car is the same: 4 wheels, 2 doors, but it can use different types of metal of interior."
        << "Let's imagine, that last things depends from the brand, then";

    exec(CoupeDirector ford_coupe{ FordBuilder() });
    exec(CoupeDirector ferrari_coupe{ FerrariBuilder() });

    exec(TruckDirector ford_truck{ FordBuilder() });
    exec(TruckDirector ferrari_truck{ FerrariBuilder() });
}