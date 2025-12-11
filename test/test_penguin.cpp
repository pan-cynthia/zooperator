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
