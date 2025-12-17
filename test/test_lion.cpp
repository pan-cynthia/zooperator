#include <gtest/gtest.h>

#include "lion.h"

TEST(LionTest, ConstructorInitialization) {
  Lion lion("Simba", 12);
  EXPECT_EQ(lion.getName(), "Simba");
  EXPECT_EQ(lion.getSpecies(), "Lion");
  EXPECT_EQ(lion.getAge(), 12);
  EXPECT_EQ(lion.getPurchaseCost(), 1000.0);
  EXPECT_EQ(lion.getFeedingCost(), 40.0);
  EXPECT_EQ(lion.getMaintenanceCost(), 60.0);
}

TEST(LionTest, MakeSound) {
  Lion lion("Simba", 12);
  testing::internal::CaptureStdout();
  lion.makeSound();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Simba the Lion is roaring!\n");
}

TEST(LionTest, EndOfDayStats) {
  Lion lion("Simba", 12);
  lion.updateStatsEndOfDay();
  EXPECT_EQ(lion.getHungerLevel(), 17);
  EXPECT_EQ(lion.getHappinessLevel(), 90);
  EXPECT_EQ(lion.getEnergyLevel(), 92);
}

TEST(LionTest, PreferredHabitat) {
  Lion lion("Simba", 12);
  EXPECT_EQ(lion.getPreferredHabitat(), "Savanna");
}
