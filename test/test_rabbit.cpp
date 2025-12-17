#include <gtest/gtest.h>

#include "rabbit.h"

TEST(RabbitTest, ConstructorInitialization) {
  Rabbit rabbit("Judy", 4);
  EXPECT_EQ(rabbit.getName(), "Judy");
  EXPECT_EQ(rabbit.getSpecies(), "Rabbit");
  EXPECT_EQ(rabbit.getAge(), 4);
  EXPECT_EQ(rabbit.getPurchaseCost(), 150.0);
  EXPECT_EQ(rabbit.getFeedingCost(), 5.0);
  EXPECT_EQ(rabbit.getMaintenanceCost(), 8.0);
}

TEST(RabbitTest, MakeSound) {
  Rabbit rabbit("Judy", 10);
  testing::internal::CaptureStdout();
  rabbit.makeSound();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Judy the Rabbit is thumping!\n");
}

TEST(RabbitTest, EndOfDayStats) {
  Rabbit rabbit("Judy", 10);
  rabbit.updateStatsEndOfDay();
  EXPECT_EQ(rabbit.getHungerLevel(), 14);
  EXPECT_EQ(rabbit.getHappinessLevel(), 90);
  EXPECT_EQ(rabbit.getEnergyLevel(), 91);
}

TEST(RabbitTest, PreferredHabitat) {
  Rabbit rabbit("Judy", 10);
  EXPECT_EQ(rabbit.getPreferredHabitat(), "Grassland");
}
