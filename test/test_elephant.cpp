#include <gtest/gtest.h>

#include "elephant.h"

TEST(ElephantTest, ConstructorInitialization) {
  Elephant elephant("Dumbo", 10);
  EXPECT_EQ(elephant.getName(), "Dumbo");
  EXPECT_EQ(elephant.getSpecies(), "Elephant");
  EXPECT_EQ(elephant.getAge(), 10);
  EXPECT_EQ(elephant.getPurchaseCost(), 1500.0);
  EXPECT_EQ(elephant.getFeedingCost(), 40.0);
  EXPECT_EQ(elephant.getMaintenanceCost(), 64.0);
}
