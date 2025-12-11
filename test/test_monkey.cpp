#include <gtest/gtest.h>

#include "monkey.h"

TEST(MonkeyTest, ConstructorInitialization) {
  Monkey monkey("George", 3);
  EXPECT_EQ(monkey.getName(), "George");
  EXPECT_EQ(monkey.getSpecies(), "Monkey");
  EXPECT_EQ(monkey.getAge(), 3);
  EXPECT_EQ(monkey.getPurchaseCost(), 600.0);
  EXPECT_EQ(monkey.getFeedingCost(), 12.0);
  EXPECT_EQ(monkey.getMaintenanceCost(), 20.0);
}
