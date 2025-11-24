#include <gtest/gtest.h>

#include "penguin.h"

TEST(PenguinTest, ConstructorInitialization) {
  Penguin penguin("Pororo", 8);
  EXPECT_EQ(penguin.getName(), "Pororo");
  EXPECT_EQ(penguin.getSpecies(), "Penguin");
  EXPECT_EQ(penguin.getAge(), 8);
  EXPECT_EQ(penguin.getPurchaseCost(), 500.0);
  EXPECT_EQ(penguin.getFeedingCost(), 15.0);
  EXPECT_EQ(penguin.getMaintenanceCost(), 25.0);
}
