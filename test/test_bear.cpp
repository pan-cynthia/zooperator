#include <gtest/gtest.h>

#include "bear.h"

TEST(BearTest, ConstructorInitialization) {
  Bear bear("Pooh", 10);
  EXPECT_EQ(bear.getName(), "Pooh");
  EXPECT_EQ(bear.getSpecies(), "Bear");
  EXPECT_EQ(bear.getAge(), 10);
  EXPECT_EQ(bear.getPurchaseCost(), 800.0);
  EXPECT_EQ(bear.getFeedingCost(), 40.0);
  EXPECT_EQ(bear.getMaintenanceCost(), 60.0);
}

TEST(BearTest, MakeSound) {
  Bear bear("Pooh", 10);
  testing::internal::CaptureStdout();
  bear.makeSound();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Pooh the Bear is growling!\n");
}

TEST(BearTest, EndOfDayStats) {
  Bear bear("Pooh", 10);
  bear.updateStatsEndOfDay();
  EXPECT_EQ(bear.getHungerLevel(), 9);
  EXPECT_EQ(bear.getHappinessLevel(), 92);
  EXPECT_EQ(bear.getEnergyLevel(), 94);
}

TEST(BearTest, PreferredHabitat) {
  Bear bear("Pooh", 10);
  EXPECT_EQ(bear.getPreferredHabitat(), "Forest");
}
