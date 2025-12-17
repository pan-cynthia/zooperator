#include <gtest/gtest.h>

#include "elephant.h"

TEST(ElephantTest, ConstructorInitialization) {
  Elephant elephant("Dumbo", 10);
  EXPECT_EQ(elephant.getName(), "Dumbo");
  EXPECT_EQ(elephant.getSpecies(), "Elephant");
  EXPECT_EQ(elephant.getAge(), 10);
  EXPECT_EQ(elephant.getPurchaseCost(), 1200.0);
  EXPECT_EQ(elephant.getFeedingCost(), 50.0);
  EXPECT_EQ(elephant.getMaintenanceCost(), 80.0);
}

TEST(ElephantTest, MakeSound) {
  Elephant elephant("Dumbo", 10);
  testing::internal::CaptureStdout();
  elephant.makeSound();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Dumbo the Elephant is trumpeting!\n");
}

TEST(ElephantTest, EndOfDayStats) {
  Elephant elephant("Dumbo", 10);
  elephant.updateStatsEndOfDay();
  EXPECT_EQ(elephant.getHungerLevel(), 15);
  EXPECT_EQ(elephant.getHappinessLevel(), 88);
  EXPECT_EQ(elephant.getEnergyLevel(), 89);
}

TEST(ElephantTest, PreferredHabitat) {
  Elephant elephant("Dumbo", 10);
  EXPECT_EQ(elephant.getPreferredHabitat(), "Savanna");
}
