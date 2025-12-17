#include <gtest/gtest.h>

#include "penguin.h"

TEST(PenguinTest, ConstructorInitialization) {
  Penguin penguin("Pororo", 8);
  EXPECT_EQ(penguin.getName(), "Pororo");
  EXPECT_EQ(penguin.getSpecies(), "Penguin");
  EXPECT_EQ(penguin.getAge(), 8);
  EXPECT_EQ(penguin.getPurchaseCost(), 400.0);
  EXPECT_EQ(penguin.getFeedingCost(), 10.0);
  EXPECT_EQ(penguin.getMaintenanceCost(), 20.0);
}

TEST(PenguinTest, MakeSound) {
  Penguin penguin("Pororo", 10);
  testing::internal::CaptureStdout();
  penguin.makeSound();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Pororo the Penguin is squawking!\n");
}

TEST(PenguinTest, EndOfDayStats) {
  Penguin penguin("Pororo", 10);
  penguin.updateStatsEndOfDay();
  EXPECT_EQ(penguin.getHungerLevel(), 12);
  EXPECT_EQ(penguin.getHappinessLevel(), 88);
  EXPECT_EQ(penguin.getEnergyLevel(), 92);
}

TEST(PenguinTest, PreferredHabitat) {
  Penguin penguin("Pororo", 10);
  EXPECT_EQ(penguin.getPreferredHabitat(), "Arctic");
}
