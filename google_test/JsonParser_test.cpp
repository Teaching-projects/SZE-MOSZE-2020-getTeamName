#include "../JsonParser.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(JsonParser, filename_parsing_ok) {
    JsonParser jsonParser("./Units/Kakarott.json");

	const std::map<std::string, std::string> valid = jsonParser.getData();
	std::map<std::string, std::string> expected
	{
		{"name", "Kakarott"},
		{"hp", "30000"},
		{"dmg", "9000"}
	};

	for (auto&& iter : valid) {
		ASSERT_EQ(expected[iter.first], iter.second);
	}
}

TEST(JsonParser, bad_input_file) {
	ASSERT_THROW(JsonParser("./Units/Bad1.json"), BadJsonException);
}

TEST(JsonParser, ifstream_ok) {
	std::ifstream file("./Units/Kakarott.json");
	JsonParser jsonParser(file);

	const std::map<std::string, std::string> valid = jsonParser.getData();
	std::map<std::string, std::string> expected
	{
		{"name", "Kakarott"},
		{"hp", "30000"},
		{"dmg", "9000"}
	};

	for (auto&& iter : valid) {
		ASSERT_EQ(expected[iter.first], iter.second);
	}
}

TEST(JsonParser, string_input_ok) {
	std::ifstream file("./Units/Kakarott.json");
	std::string temp = "", input = "";
	while (std::getline(file, temp)) {
		input += temp + "\n";
	}
	JsonParser jsonParser(input);
	const std::map<std::string, std::string> valid = jsonParser.getData();
	std::map<std::string, std::string> expected
	{
		{"name", "Kakarott"},
		{"hp", "30000"},
		{"dmg", "9000"}
	};

	for (auto&& iter : valid) {
		ASSERT_EQ(expected[iter.first], iter.second);
	}
} 

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
