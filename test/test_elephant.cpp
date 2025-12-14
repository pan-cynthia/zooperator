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
