#include <gtest/gtest.h>

#include "monkey.h"

TEST(MonkeyTest, ConstructorInitialization) {
  Monkey monkey("George", 3);
  EXPECT_EQ(monkey.getName(), "George");
  EXPECT_EQ(monkey.getSpecies(), "Monkey");
  EXPECT_EQ(monkey.getAge(), 3);
  EXPECT_EQ(monkey.getPurchaseCost(), 600.0);
  EXPECT_EQ(monkey.getFeedingCost(), 15.0);
  EXPECT_EQ(monkey.getMaintenanceCost(), 25.0);
}

TEST(MonkeyTest, MakeSound) {
  Monkey monkey("George", 3);
  testing::internal::CaptureStdout();
  monkey.makeSound();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "George the Monkey is screeching!\n");
}

TEST(MonkeyTest, EndOfDayStats) {
  Monkey monkey("George", 3);
  monkey.updateStatsEndOfDay();
  EXPECT_EQ(monkey.getHungerLevel(), 13);
  EXPECT_EQ(monkey.getHappinessLevel(), 85);
  EXPECT_EQ(monkey.getEnergyLevel(), 89);
}

TEST(MonkeyTest, PreferredHabitat) {
  Monkey monkey("George", 3);
  EXPECT_EQ(monkey.getPreferredHabitat(), "Jungle");
}
