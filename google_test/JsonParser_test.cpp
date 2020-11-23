#include "../JSON.h"
#include "../Hero.h"
#include "../Monster.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(CreatureTests, FightEndTest)
{
    Hero h1 = Hero::parse("../Dark_Wanderer.json");
    Monster h2 = Monster::parse("../Zombie.json");
    h1.fightTilDeath(h2);
    ASSERT_TRUE(h1.isAlive() || h2.isAlive());
}

TEST(CreatureTests, FightResult)
{
    Hero h1 = Hero::parse("../Dark_Wanderer.json");
    Monster h2 = Monster::parse("../Blood_Raven.json");
    h1.fightTilDeath(h2);
    ASSERT_DOUBLE_EQ(h1.getHealthPoints(),0);
    ASSERT_DOUBLE_EQ(h2.getHealthPoints(),101);
}

TEST(CreatureTests, FightSuccessful)
{
    Hero h1 = Hero::parse("../Dark_Wanderer.json");
    Monster h2 = Monster::parse("../Blood_Raven.json");
    EXPECT_NO_THROW(h1.fightTilDeath(h2));
}

TEST(CreatureTests, LevelUpTest)
{
    Hero h1 = Hero::parse("../Dark_Wanderer.json");
    Monster h2 = Monster::parse("../Blood_Raven.json");
    h1.fightTilDeath(h2);
    ASSERT_DOUBLE_EQ(h1.getHealthPoints(),0);
    ASSERT_DOUBLE_EQ(h1.getDamage(),3);
    ASSERT_DOUBLE_EQ(h1.getAttackCoolDown(),1.100000);
}


TEST(CreatureTests, LevelTest)
{
    Hero h1 = Hero::parse("../Dark_Wanderer.json");
    Monster h2 = Monster::parse("../Zombie.json");
    h1.fightTilDeath(h2);
    ASSERT_EQ(h1.getLevel(),1);
}

TEST(CreatureTests, XPTest)
{
    Hero h1 = Hero::parse("../Dark_Wanderer.json");
    Monster h2 = Monster::parse("../Blood_Raven.json");
    h1.fightTilDeath(h2);
    ASSERT_DOUBLE_EQ(h1.getExperience(),12);
}

TEST(CreatureTests, SelfAttackTest)
{
    Hero h1 = Hero::parse("../Dark_Wanderer.json");
    Hero h2 = Hero::parse("../Dark_Wanderer.json");
    EXPECT_NO_THROW(h1.fightTilDeath(h2));
}

TEST(CreatureTests, parseTest)
{
    Monster h1 = Monster::parse("../Units/Maple.json");
    ASSERT_TRUE(h1.getName() == "Maple");
    ASSERT_DOUBLE_EQ(h1.getHealthPoints(),150);
    ASSERT_DOUBLE_EQ(h1.getDamage(),10);
    ASSERT_DOUBLE_EQ(h1.getAttackCoolDown(),3);
}

TEST(CreatureTests, GoodParse)
{
    EXPECT_NO_THROW(Monster::parse("../Zombie.json"));
    EXPECT_NO_THROW(Monster::parse("../Fallen.json"));
    EXPECT_NO_THROW(Monster::parse("../Blood_Raven.json"));
    EXPECT_THROW(JSON::parseFromFile("../Units/Bad1.json"), JSON::ParseException);
}

TEST(CreatureTests, ShuffledJSONTest)
{
    Monster h1 = Monster::parse("../Units/shuffled.json");
    ASSERT_TRUE(h1.getName() == "Sally");
    ASSERT_DOUBLE_EQ(h1.getHealthPoints(),450);
    ASSERT_DOUBLE_EQ(h1.getDamage(),30);
    ASSERT_DOUBLE_EQ(h1.getAttackCoolDown(),2.5);
}

TEST(CreatureTests, GoodTypeTest)
{
    Monster h1("Fallen", 4, 2, 1.6, 0.1);
    EXPECT_EQ(typeid(std::string),typeid(h1.getName()));
    EXPECT_EQ(typeid(double),typeid(h1.getDamage()));
    EXPECT_EQ(typeid(double),typeid(h1.getHealthPoints()));
    EXPECT_EQ(typeid(double),typeid(h1.getAttackCoolDown()));
}

TEST(CreatureTests, BadJSONTest)
{
    EXPECT_NO_THROW(JSON::parseFromFile("../Units/Bad2.json"));
}

TEST(JsonParser, filename_parsing_ok) {
    JSON j = JSON::parseFromFile("../Units/Maple.json");

    ASSERT_EQ("Maple",j.get<std::string>("name"));
    ASSERT_EQ(150,j.get<double>("health_points"));
    ASSERT_EQ(10,j.get<double>("damage"));
    ASSERT_EQ(3,j.get<double>("attack_cooldown"));
}

TEST(JsonParser, bad_input_file) {
	ASSERT_THROW(JSON::parseFromFile("../Units/Bad1.json"), JSON::ParseException);
}

TEST(JsonParser, ifstream_ok) {
	std::ifstream file("../Units/Maple.json");
	JSON j = JSON::parseFromStream(file);

    ASSERT_EQ("Maple",j.get<std::string>("name"));
    ASSERT_EQ(150,j.get<double>("health_points"));
    ASSERT_EQ(10,j.get<double>("damage"));
    ASSERT_EQ(3,j.get<double>("attack_cooldown"));
}

TEST(JsonParser, string_input_ok) {
	std::ifstream file("../Units/Maple.json");
	std::string temp = "", input = "";
	while (std::getline(file, temp)) {
		input += temp;
	}
	JSON j = JSON::parseFromString(input);

    ASSERT_EQ("Maple",j.get<std::string>("name"));
    ASSERT_EQ(150,j.get<double>("health_points"));
    ASSERT_EQ(10,j.get<double>("damage"));
    ASSERT_EQ(3,j.get<double>("attack_cooldown"));
	
} 

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
