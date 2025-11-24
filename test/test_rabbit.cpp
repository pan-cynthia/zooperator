#include <gtest/gtest.h>

#include "rabbit.h"

TEST(RabbitTest, ConstructorInitialization) {
  Rabbit rabbit("Judy", 4);
  EXPECT_EQ(rabbit.getName(), "Judy");
  EXPECT_EQ(rabbit.getSpecies(), "Rabbit");
  EXPECT_EQ(rabbit.getAge(), 4);
  EXPECT_EQ(rabbit.getPurchaseCost(), 150.0);
  EXPECT_EQ(rabbit.getFeedingCost(), 3.0);
  EXPECT_EQ(rabbit.getMaintenanceCost(), 5.0);
}
