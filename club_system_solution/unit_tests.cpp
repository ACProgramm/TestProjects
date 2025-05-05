#include "gtest/gtest.h"
#include <cmath>
#include <string>
#include <sstream>

int toMinutes(const std::string& t) {
    int h = std::stoi(t.substr(0, 2));
    int m = std::stoi(t.substr(3, 2));
    return h * 60 + m;
}

std::string toTime(int mins) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << (mins / 60) << ":"
       << std::setw(2) << std::setfill('0') << (mins % 60);
    return ss.str();
}

TEST(TimeConversionTest, ToMinutes) {
    EXPECT_EQ(toMinutes("00:00"), 0);
    EXPECT_EQ(toMinutes("01:30"), 90);
    EXPECT_EQ(toMinutes("23:59"), 1439);
}

TEST(TimeConversionTest, ToTime) {
    EXPECT_EQ(toTime(0), "00:00");
    EXPECT_EQ(toTime(75), "01:15");
    EXPECT_EQ(toTime(1439), "23:59");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
