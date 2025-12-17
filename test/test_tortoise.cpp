#include <gtest/gtest.h>

#include "tortoise.h"

TEST(TortoiseTest, ConstructorInitialization) {
  Tortoise tortoise("Crush", 50);
  EXPECT_EQ(tortoise.getName(), "Crush");
  EXPECT_EQ(tortoise.getSpecies(), "Tortoise");
  EXPECT_EQ(tortoise.getAge(), 50);
  EXPECT_EQ(tortoise.getPurchaseCost(), 250.0);
  EXPECT_EQ(tortoise.getFeedingCost(), 6.0);
  EXPECT_EQ(tortoise.getMaintenanceCost(), 12.0);
}

TEST(TortoiseTest, MakeSound) {
  Tortoise tortoise("Crush", 10);
  testing::internal::CaptureStdout();
  tortoise.makeSound();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Crush the Tortoise is hissing!\n");
}

TEST(TortoiseTest, EndOfDayStats) {
  Tortoise tortoise("Crush", 10);
  tortoise.updateStatsEndOfDay();
  EXPECT_EQ(tortoise.getHungerLevel(), 9);
  EXPECT_EQ(tortoise.getHappinessLevel(), 94);
  EXPECT_EQ(tortoise.getEnergyLevel(), 95);
}

TEST(TortoiseTest, PreferredHabitat) {
  Tortoise tortoise("Crush", 10);
  EXPECT_EQ(tortoise.getPreferredHabitat(), "Grassland");
}
