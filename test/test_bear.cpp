#include <gtest/gtest.h>

#include "bear.h"

TEST(BearTest, ConstructorInitialization) {
  Bear bear("Pooh", 10);
  EXPECT_EQ(bear.getName(), "Pooh");
  EXPECT_EQ(bear.getSpecies(), "Bear");
  EXPECT_EQ(bear.getAge(), 10);
  EXPECT_EQ(bear.getPurchaseCost(), 2000.0);
  EXPECT_EQ(bear.getFeedingCost(), 30.0);
  EXPECT_EQ(bear.getMaintenanceCost(), 50.0);
}
