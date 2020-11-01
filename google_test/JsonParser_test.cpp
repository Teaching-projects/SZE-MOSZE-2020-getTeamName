#include "../JsonParser.h"
#include "../creature.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(CreatureTests, FightEndTest)
{
    Creature* h1 = Creature::parseUnit("../Units/Kakarott.json");
    Creature* h2 = Creature::parseUnit("../Units/Maple.json");
    h1->fight(h2);
    ASSERT_TRUE(h1->isDead() || h2->isDead());
}

TEST(CreatureTests, FightResult)
{
    Creature* h1 = Creature::parseUnit("../Units/Maple.json");
    Creature* h2 = Creature::parseUnit("../Units/Sally.json");
    h1->fight(h2);
    ASSERT_DOUBLE_EQ(h1->getLife(),-3);
    ASSERT_DOUBLE_EQ(h2->getLife(),485);
}

TEST(CreatureTests, FightSuccessful)
{
    Creature* h1 = Creature::parseUnit("../Units/Maple.json");
    Creature* h2 = Creature::parseUnit("../Units/Sally.json");
    EXPECT_NO_THROW(h1->fight(h2));
}

TEST(CreatureTests, LevelUpTest)
{
    Creature* h1 = Creature::parseUnit("../Units/Kakarott.json");
    Creature* h2 = Creature::parseUnit("../Units/Maple.json");
    h1->fight(h2);
    ASSERT_DOUBLE_EQ(h1->getMax_Life(),550);
    ASSERT_DOUBLE_EQ(h1->getDamage(),462);
    ASSERT_DOUBLE_EQ(h1->getAttackcooldown(),1.8);
}


TEST(CreatureTests, LevelTest)
{
    Creature* h1 = Creature::parseUnit("../Units/Sally.json");
    Creature* h2 = Creature::parseUnit("../Units/Maple.json");
    h1->fight(h2);
    ASSERT_EQ(h1->getLevel(),2);
    ASSERT_EQ(h2->getLevel(),1);
    ASSERT_TRUE(h1->getLevel()>h2->getLevel());
}

TEST(CreatureTests, XPTest)
{
    Creature* h1 = Creature::parseUnit("../Units/Sally.json");
    Creature* h2 = Creature::parseUnit("../Units/Maple.json");
    h1->fight(h2);
    ASSERT_DOUBLE_EQ(h1->getExperience(),50);
    ASSERT_DOUBLE_EQ(h2->getExperience(),40);
}

TEST(CreatureTests, SelfAttackTest)
{
    Creature* h1 = Creature::parseUnit("../Units/Kakarott.json");
    Creature* h2 = Creature::parseUnit("../Units/Kakarott.json");
    EXPECT_NO_THROW(h1->fight(h2));
}

TEST(CreatureTests, ParseUnitTest)
{
    Creature* h1 = Creature::parseUnit("../Units/Kakarott.json");
    ASSERT_TRUE(h1->getName() == "Kakarott");
    ASSERT_DOUBLE_EQ(h1->getLife(),500);
    ASSERT_DOUBLE_EQ(h1->getDamage(),420);
    ASSERT_DOUBLE_EQ(h1->getAttackcooldown(),2);
}

TEST(CreatureTests, GoodParse)
{
    EXPECT_NO_THROW(Creature::parseUnit("../Units/Kakarott.json"));
    EXPECT_NO_THROW(Creature::parseUnit("../Units/Maple.json"));
    EXPECT_NO_THROW(Creature::parseUnit("../Units/Sally.json"));
    EXPECT_THROW(JsonParser("../Units/Bad1.json"), BadJsonException);
}

TEST(CreatureTests, ShuffledJSONTest)
{
    Creature* h1 = Creature::parseUnit("../Units/shuffled.json");
    ASSERT_TRUE(h1->getName() == "Sally");
    ASSERT_DOUBLE_EQ(h1->getLife(),450);
    ASSERT_DOUBLE_EQ(h1->getDamage(),30);
    ASSERT_DOUBLE_EQ(h1->getAttackcooldown(),2.5);
}

TEST(CreatureTests, GoodTypeTest)
{
    Creature h1("Kakarott", 420, 500, 2, 0, 1);
    EXPECT_EQ(typeid(std::string),typeid(h1.getName()));
    EXPECT_EQ(typeid(double),typeid(h1.getDamage()));
    EXPECT_EQ(typeid(double),typeid(h1.getLife()));
    EXPECT_EQ(typeid(double),typeid(h1.getAttackcooldown()));
    EXPECT_EQ(typeid(double),typeid(h1.getExperience()));
    EXPECT_EQ(typeid(int),typeid(h1.getLevel()));
}

TEST(CreatureTests, BadJSONTest)
{
    EXPECT_NO_THROW(JsonParser("../Units/Bad2.json"));
}


TEST(JsonParser, filename_parsing_ok) {
    JsonParser jsonParser("../Units/Kakarott.json");

	const std::map<std::string, std::string> valid = jsonParser.getData();
	std::map<std::string, std::string> expected
	{
		{"name", "Kakarott"},
		{"hp", "500"},
		{"dmg", "420"},
		{"attackcooldown", "2"}
	};

	for (auto&& iter : valid) {
		ASSERT_EQ(expected[iter.first], iter.second);
	}
}

TEST(JsonParser, bad_input_file) {
	ASSERT_THROW(JsonParser("../Units/Bad1.json"), BadJsonException);
}

TEST(JsonParser, ifstream_ok) {
	std::ifstream file("../Units/Kakarott.json");
	JsonParser jsonParser(file);

	const std::map<std::string, std::string> valid = jsonParser.getData();
	std::map<std::string, std::string> expected
	{
		{"name", "Kakarott"},
		{"hp", "500"},
		{"dmg", "420"},
		{"attackcooldown", "2"}
	};

	for (auto&& iter : valid) {
		ASSERT_EQ(expected[iter.first], iter.second);
	}
}

TEST(JsonParser, string_input_ok) {
	std::ifstream file("../Units/Kakarott.json");
	std::string temp = "", input = "";
	while (std::getline(file, temp)) {
		input += temp + "\n";
	}
	JsonParser jsonParser(input);
	const std::map<std::string, std::string> valid = jsonParser.getData();
	std::map<std::string, std::string> expected
	{
		{"name", "Kakarott"},
		{"hp", "500"},
		{"dmg", "420"},
		{"attackcooldown", "2"}
	};

	for (auto&& iter : valid) {
		ASSERT_EQ(expected[iter.first], iter.second);
	}
} 

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
