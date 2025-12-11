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
