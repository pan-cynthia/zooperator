#include <gtest/gtest.h>

#include "lion.h"

TEST(LionTest, ConstructorInitialization) {
  Lion lion("Simba", 12);
  EXPECT_EQ(lion.getName(), "Simba");
  EXPECT_EQ(lion.getSpecies(), "Lion");
  EXPECT_EQ(lion.getAge(), 12);
  EXPECT_EQ(lion.getPurchaseCost(), 2000.0);
  EXPECT_EQ(lion.getFeedingCost(), 50.0);
  EXPECT_EQ(lion.getMaintenanceCost(), 80.0);
}
