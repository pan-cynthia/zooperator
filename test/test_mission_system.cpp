#include <gtest/gtest.h>

#include "MissionSystem.h"
#include "bear.h"
#include "elephant.h"
#include "exhibit.h"
#include "game.h"
#include "lion.h"
#include "monkey.h"
#include "penguin.h"
#include "player.h"
#include "rabbit.h"
#include "tortoise.h"
#include "zoo.h"

TEST(MissionSystemTest, ConstructorInitialization) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  SUCCEED();
}

TEST(MissionSystemTest, Day1MissionsSetup) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  std::vector<Mission>& missions = mission_system.getMissions();

  bool purchased_animal = false;
  bool purchased_exhibit = false;
  bool added_to_exhibit = false;

  for (const auto& mission : missions) {
    if (mission.required && mission.type == MissionType::OWN_X_ANIMALS) {
      purchased_animal = true;
      EXPECT_EQ(mission.int_param, 1);
    }
    if (mission.required && mission.type == MissionType::OWN_X_EXHIBITS) {
      purchased_exhibit = true;
      EXPECT_EQ(mission.int_param, 1);
    }
    if (mission.required && mission.type == MissionType::ADD_ANIMAL_TO_EXHIBIT) {
      added_to_exhibit = true;
    }
  }

  EXPECT_TRUE(purchased_animal);
  EXPECT_TRUE(purchased_exhibit);
  EXPECT_TRUE(added_to_exhibit);
}

TEST(MissionSystemTest, DailyMissionCorrectness) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  // day -> missions(type, required?)
  std::map<int, std::vector<std::pair<MissionType, bool>>> daily_missions = {
      {1,
       {
           {MissionType::OWN_X_ANIMALS, true},
           {MissionType::OWN_X_EXHIBITS, true},
           {MissionType::ADD_ANIMAL_TO_EXHIBIT, true},
           {MissionType::BALANCE_AT_LEAST, false},
       }},
      {2,
       {
           {MissionType::OWN_X_SPECIES, true},
           {MissionType::FEED_X_ANIMALS, true},
           {MissionType::NO_HOMELESS_ANIMALS, true},
           {MissionType::ZOO_RATING_ABOVE, false},
       }},
      {3,
       {
           {MissionType::OWN_X_SPECIES, true},
           {MissionType::OWN_X_EXHIBITS, true},
           {MissionType::FEED_X_ANIMALS, true},
           {MissionType::CLEAN_X_EXHIBITS, false},
       }},
      {4,
       {
           {MissionType::PLAY_WITH_ANIMAL, true},
           {MissionType::FEED_X_ANIMALS, true},
           {MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, true},
           {MissionType::PREFERRED_HABITATS, true},
           {MissionType::ZOO_RATING_ABOVE, false},
       }},
      {5,
       {
           {MissionType::OWN_X_SPECIES, true},
           {MissionType::OWN_MEDIUM_ANIMAL, true},
           {MissionType::NO_HOMELESS_ANIMALS, true},
           {MissionType::BALANCE_AT_LEAST, false},
           {MissionType::ATTRACT_X_VISITORS, false},
       }},
      {6,
       {
           {MissionType::EXERCISE_ANIMAL, true},
           {MissionType::FEED_X_ANIMALS, true},
           {MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, true},
           {MissionType::ZOO_RATING_ABOVE, false},
           {MissionType::OWN_X_ANIMALS, false},
       }},
      {7,
       {
           {MissionType::OWN_X_EXHIBITS, true},
           {MissionType::NO_ANIMALS_NEED_ATTENTION, true},
           {MissionType::ZOO_RATING_ABOVE, false},
           {MissionType::BALANCE_AT_LEAST, false},
           {MissionType::PREFERRED_HABITATS, false},
       }},
      {8,
       {
           {MissionType::OWN_X_SPECIES, true},
           {MissionType::FEED_X_ANIMALS, true},
           {MissionType::ZOO_RATING_ABOVE, false},
           {MissionType::BALANCE_AT_LEAST, false},
           {MissionType::OWN_SPECIAL_ANIMAL, false},
       }},
      {9,
       {
           {MissionType::OWN_X_SPECIES, true},
           {MissionType::NO_ANIMALS_NEED_ATTENTION, true},
           {MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, true},
           {MissionType::ZOO_RATING_ABOVE, false},
           {MissionType::ATTRACT_X_VISITORS, false},
       }},
      {10,
       {
           {MissionType::NO_HOMELESS_ANIMALS, true},
           {MissionType::PREFERRED_HABITATS, true},
           {MissionType::NO_SICK_ANIMALS, true},
           {MissionType::NO_ANIMALS_NEED_ATTENTION, true},
           {MissionType::OWN_X_SPECIES, false},
           {MissionType::OWN_ELEPHANT, false},
           {MissionType::ZOO_RATING_ABOVE, false},
           {MissionType::BALANCE_AT_LEAST, false},
       }},
  };

  for (int day = 1; day <= 10; ++day) {
    mission_system.setupDailyMissions(day);
    auto& missions = mission_system.getMissions();

    std::map<MissionType, bool> mission_map;
    for (const auto& mission : missions) {
      mission_map[mission.type] = mission.required;
    }

    for (const auto& expected : daily_missions[day]) {
      MissionType type = expected.first;
      bool required = expected.second;
      EXPECT_TRUE(mission_map.count(type));
      EXPECT_EQ(mission_map[type], required);
    }
  }
}

TEST(MissionSystemTest, RequiredAndOptionalMissions) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  bool has_required = false;
  bool has_optional = false;

  std::vector<Mission>& missions = mission_system.getMissions();

  for (const auto& mission : missions) {
    if (mission.required) {
      has_required = true;
    } else {
      has_optional = true;
    }
  }

  EXPECT_TRUE(has_required);
  EXPECT_TRUE(has_optional);
}

TEST(MissionSystemTest, OptionalMissionsHaveRewards) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  std::vector<Mission>& missions = mission_system.getMissions();

  for (const auto& mission : missions) {
    if (!mission.required) {
      EXPECT_GT(mission.reward_amount, 0);
    }
  }
}

TEST(MissionSystemTest, CompleteMissionUpdatesStatus) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  std::vector<Mission>& missions = mission_system.getMissions();
  Mission& mission = missions[0];
  EXPECT_FALSE(mission.completed);
}

TEST(MissionSystemTest, CheckDay1MissionsCompleteCorrectly) {
  Zoo zoo("Test Zoo", 5000.0);
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Elephant>("Ellie", 12);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  auto exhibit = std::make_unique<Exhibit>("Plains", "Savanna", 3, 1000.0, 50.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  zoo.addAnimalToExhibit(animal_ptr, exhibit_ptr);

  mission_system.checkMissions(true);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_X_ANIMALS || mission.type == MissionType::OWN_X_EXHIBITS ||
        mission.type == MissionType::ADD_ANIMAL_TO_EXHIBIT) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, TrackAnimalFed) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(2);

  auto rabbit = std::make_unique<Rabbit>("Judy", 8);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  mission_system.trackAnimalFed(rabbit_ptr);
  EXPECT_EQ(mission_system.getAnimalsFedToday().size(), 1);
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::FEED_X_ANIMALS) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, TrackMultipleAnimalsFed) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(3);

  auto rabbit = std::make_unique<Rabbit>("Judy", 8);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  auto monkey = std::make_unique<Monkey>("Bananas", 12);
  Animal* monkey_ptr = monkey.get();
  zoo.purchaseAnimal(std::move(monkey));

  mission_system.trackAnimalFed(rabbit_ptr);
  mission_system.trackAnimalFed(monkey_ptr);
  EXPECT_EQ(mission_system.getAnimalsFedToday().size(), 2);
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::FEED_X_ANIMALS) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, TrackPlayedWithAnimal) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(4);

  mission_system.trackPlayedWithAnimal();
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::PLAY_WITH_ANIMAL) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, TrackExercisedAnimal) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(6);

  mission_system.trackExercisedAnimal();
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::EXERCISE_ANIMAL) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, TrackExhibitCleaned) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(3);

  auto exhibit = std::make_unique<Exhibit>("Amazon", "Jungle", 6, 800.0, 45.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  mission_system.trackExhibitCleaned(exhibit_ptr);
  EXPECT_EQ(mission_system.getExhibitsCleanedToday().size(), 1);
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::CLEAN_X_EXHIBITS) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, FeedingSameAnimalTwiceCountsOnce) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(3);

  auto penguin = std::make_unique<Penguin>("Pororo", 8);
  Animal* penguin_ptr = penguin.get();
  zoo.purchaseAnimal(std::move(penguin));

  auto bear = std::make_unique<Bear>("Grizz", 25);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  mission_system.trackAnimalFed(penguin_ptr);
  mission_system.trackAnimalFed(penguin_ptr);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::FEED_X_ANIMALS) {
      EXPECT_FALSE(mission.completed);
    }
  }

  mission_system.trackAnimalFed(bear_ptr);
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::FEED_X_ANIMALS) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, ResetDailyTracking) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto lion = std::make_unique<Lion>("Simba", 12);
  Animal* lion_ptr = lion.get();
  zoo.purchaseAnimal(std::move(lion));

  mission_system.setupDailyMissions(4);

  mission_system.trackAnimalFed(lion_ptr);
  mission_system.trackPlayedWithAnimal();
  mission_system.trackExercisedAnimal();

  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::PLAY_WITH_ANIMAL ||
        mission.type == MissionType::FEED_X_ANIMALS) {
      EXPECT_TRUE(mission.completed);
    }
  }

  mission_system.resetDailyTracking();
  mission_system.setupDailyMissions(6);
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::FEED_X_ANIMALS ||
        mission.type == MissionType::EXERCISE_ANIMAL) {
      EXPECT_FALSE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, AdvanceDayWhenAllRequiredMissionsComplete) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Rabbit>("Judy", 7);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  zoo.addAnimalToExhibit(animal_ptr, exhibit_ptr);

  mission_system.checkMissions(true);
  EXPECT_TRUE(mission_system.canAdvanceDay());
}

TEST(MissionSystemTest, CannotAdvanceDayWhenRequiredMissionsIncomplete) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Rabbit>("Judy", 7);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  mission_system.checkMissions(true);
  EXPECT_FALSE(mission_system.canAdvanceDay());

  zoo.addAnimalToExhibit(animal_ptr, exhibit_ptr);

  mission_system.checkMissions(true);
  EXPECT_TRUE(mission_system.canAdvanceDay());
}

TEST(MissionSystemTest, EndOfDayMissionsNotCheckedImmediately) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Rabbit>("Judy", 7);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  zoo.addAnimalToExhibit(animal_ptr, exhibit_ptr);

  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.end_of_day) {
      EXPECT_FALSE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, CompletingOptionalMissionAddsReward) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  double initial_balance = zoo.getBalance();
  std::vector<Mission>& missions = mission_system.getMissions();

  for (size_t i = 0; i < missions.size(); ++i) {
    if (!missions[i].required) {
      double reward = missions[i].reward_amount;
      mission_system.completeMission(i);
      EXPECT_EQ(zoo.getBalance(), initial_balance + reward);
      break;
    }
  }
}

// mission progress tests

TEST(MissionSystemTest, GetMissionProgressForAnimals) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  zoo.purchaseAnimal(std::make_unique<Rabbit>("Judy", 7));

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_X_ANIMALS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1/1]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForExhibits) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  zoo.purchaseExhibit(std::make_unique<Exhibit>("Trees", "Forest", 4, 600.0, 35.0));

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_X_EXHIBITS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1/1]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForSpecies) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(2);

  zoo.purchaseAnimal(std::make_unique<Tortoise>("Crush", 20));

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_X_SPECIES) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1/2]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForFeeding) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Lion>("Scar", 20);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  mission_system.setupDailyMissions(2);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::FEED_X_ANIMALS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [0/1 fed]");
    }
  }

  mission_system.trackAnimalFed(animal_ptr);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::FEED_X_ANIMALS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, "");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForSickAnimals) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(10);

  auto animal = std::make_unique<Elephant>("Dumbo", 12);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_SICK_ANIMALS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [0 sick]");
    }
  }

  animal_ptr->updateHealth(-70);
  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_SICK_ANIMALS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1 sick]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForHomelessAnimals) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Monkey>("George", 4);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  auto exhibit = std::make_unique<Exhibit>("Amazon", "Jungle", 4, 800.0, 45.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  mission_system.setupDailyMissions(2);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_HOMELESS_ANIMALS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1 homeless]");
    }
  }

  zoo.addAnimalToExhibit(animal_ptr, exhibit_ptr);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_HOMELESS_ANIMALS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [0 homeless]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForNeedyAnimals) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Tortoise>("Crush", 25);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  mission_system.setupDailyMissions(7);
  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_ANIMALS_NEED_ATTENTION) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, "");
    }
  }

  animal_ptr->updateHappiness(-85);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_ANIMALS_NEED_ATTENTION) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForWrongHabitats) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Penguin>("Pororo", 8);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  auto exhibit1 = std::make_unique<Exhibit>("Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit1_ptr = exhibit1.get();
  zoo.purchaseExhibit(std::move(exhibit1));

  auto exhibit2 = std::make_unique<Exhibit>("Brrr", "Arctic", 2, 1200.0, 60.0);
  Exhibit* exhibit2_ptr = exhibit2.get();
  zoo.purchaseExhibit(std::move(exhibit2));

  zoo.addAnimalToExhibit(animal_ptr, exhibit1_ptr);

  mission_system.setupDailyMissions(4);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::PREFERRED_HABITATS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1 wrong]");
    }
  }

  zoo.addAnimalToExhibit(animal_ptr, exhibit2_ptr);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::PREFERRED_HABITATS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, "");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForExhibitsCleaned) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto exhibit = std::make_unique<Exhibit>("Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));
  mission_system.setupDailyMissions(3);

  mission_system.trackExhibitCleaned(exhibit_ptr);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::CLEAN_X_EXHIBITS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1/1 cleaned]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForExhibitCleanliness) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  auto exhibit = std::make_unique<Exhibit>("Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  mission_system.setupDailyMissions(4);
  exhibit_ptr->updateCleanliness(-60);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [1 dirty]");
    }
  }

  exhibit_ptr->clean();

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, "");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForBalance) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::BALANCE_AT_LEAST) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [$2000/$1200]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForRating) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(2);
  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::ZOO_RATING_ABOVE) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [0.7/5.0]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForVisitors) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(5);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::ATTRACT_X_VISITORS) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, " [0/40 visitors]");
    }
  }
}

TEST(MissionSystemTest, GetMissionProgressForDefaultCase) {
  Zoo zoo("SF Zoo");
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(4);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::ADD_ANIMAL_TO_EXHIBIT ||
        mission.type == MissionType::PLAY_WITH_ANIMAL ||
        mission.type == MissionType::EXERCISE_ANIMAL ||
        mission.type == MissionType::OWN_MEDIUM_ANIMAL ||
        mission.type == MissionType::OWN_SPECIAL_ANIMAL ||
        mission.type == MissionType::OWN_ELEPHANT) {
      std::string progress = mission_system.getMissionProgress(mission);
      EXPECT_EQ(progress, "");
    }
  }
}

// mission impossible tests

TEST(MissionSystemTest, MissionImpossibleInsufficientFunds) {
  Zoo zoo("SF Zoo", 100.0);
  MissionSystem mission_system(zoo);
  EXPECT_TRUE(mission_system.checkMissionsImpossible(3));
}

TEST(MissionSystemTest, MissionNotImpossibleSufficientFunds) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  EXPECT_FALSE(mission_system.checkMissionsImpossible(3));
}

TEST(MissionSystemTest, MissionImpossibleCannotAffordSpecies) {
  Zoo zoo("SF Zoo", 100.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(2);

  EXPECT_TRUE(mission_system.checkMissionsImpossible(0));
}

TEST(MissionSystemTest, MissionImpossibleCannotAffordExhibits) {
  Zoo zoo("SF Zoo", 200.0);  // cheapest exhibit is $300
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(3);

  EXPECT_TRUE(mission_system.checkMissionsImpossible(0));
}

TEST(MissionSystemTest, MissionImpossibleCannotTreatNeedyAnimals) {
  Zoo zoo("SF Zoo", 2250.0);  // treatment is $50
  MissionSystem mission_system(zoo);

  // satisfy day 7 own 3 exhibits mission first
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Grassy", "Grassland", 2, 300.0, 15.0));
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Trees", "Forest", 3, 600.0, 35.0));
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Brrr", "Arctic", 4, 1200.0, 60.0));

  auto animal = std::make_unique<Rabbit>("Miffy", 8);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  animal_ptr->updateHappiness(-90);
  mission_system.setupDailyMissions(7);
  EXPECT_TRUE(mission_system.checkMissionsImpossible(0));
}

TEST(MissionSystemTest, MissionImpossibleCannotTreatSickAnimals) {
  Zoo zoo("SF Zoo", 150.0);  // treatment is $50
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Rabbit>("Miffy", 8);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  animal_ptr->updateHealth(-60);
  mission_system.setupDailyMissions(10);
  EXPECT_TRUE(mission_system.checkMissionsImpossible(0));
}

TEST(MissionSystemTest, MissionImpossibleCannotPurchaseMediumAnimal) {
  Zoo zoo("SF Zoo", 2600.0);  // penguin is $400, monkey is $600
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(5);

  // satisfy day 5 own 4 different species mission first
  zoo.purchaseAnimal(std::make_unique<Elephant>("Ellie", 22));
  zoo.purchaseAnimal(std::make_unique<Lion>("Scar", 20));
  zoo.purchaseAnimal(std::make_unique<Rabbit>("Judy", 8));
  zoo.purchaseAnimal(std::make_unique<Tortoise>("Crush", 30));

  EXPECT_TRUE(mission_system.checkMissionsImpossible(0));
}

// specific mission tests

TEST(MissionSystemTest, OwnElephant) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(10);

  zoo.purchaseAnimal(std::make_unique<Elephant>("Ellie", 22));
  mission_system.checkMissions(true);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_ELEPHANT) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, OwnMediumAnimalWithMonkey) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(5);

  zoo.purchaseAnimal(std::make_unique<Monkey>("George", 6));

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_MEDIUM_ANIMAL) {
      EXPECT_FALSE(mission.completed);
    }
  }

  mission_system.checkMissions(false);
  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_MEDIUM_ANIMAL) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, OwnMediumAnimalWithPenguin) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(5);

  zoo.purchaseAnimal(std::make_unique<Penguin>("Pororo", 8));
  mission_system.checkMissions(false);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_MEDIUM_ANIMAL) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, OwnSpecialAnimalWithBear) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(8);

  zoo.purchaseAnimal(std::make_unique<Bear>("Corduroy", 8));
  mission_system.checkMissions(true);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_SPECIAL_ANIMAL) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, OwnSpecialAnimalWithLion) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(8);

  zoo.purchaseAnimal(std::make_unique<Lion>("Scar", 20));
  mission_system.checkMissions(true);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::OWN_SPECIAL_ANIMAL) {
      EXPECT_TRUE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, NoSickAnimalsMission) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);

  auto animal = std::make_unique<Rabbit>("Judy", 8);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));

  mission_system.setupDailyMissions(10);

  animal_ptr->updateHealth(-60);
  mission_system.checkMissions(true);
  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_SICK_ANIMALS) {
      EXPECT_FALSE(mission.completed);
    }
  }

  animal_ptr->updateHealth(30);
  EXPECT_EQ(animal_ptr->getHealthLevel(), 70);
  mission_system.checkMissions(true);
  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::NO_SICK_ANIMALS) {
      EXPECT_TRUE(mission.condition_met);
    }
  }
}

TEST(MissionSystemTest, PreferredHabitatsMission) {
  Zoo zoo("Test Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(4);

  auto rabbit = std::make_unique<Rabbit>("Judy", 4);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  auto exhibit = std::make_unique<Exhibit>("Polar Express", "Arctic", 2, 1200.0, 60.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  zoo.addAnimalToExhibit(rabbit_ptr, exhibit_ptr);
  mission_system.checkMissions(true);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::PREFERRED_HABITATS) {
      EXPECT_FALSE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, CleanlinessThresholdMission) {
  Zoo zoo("Test Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(4);

  auto exhibit = std::make_unique<Exhibit>("Plains", "Savanna", 3, 1000.0, 50.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  exhibit_ptr->updateCleanliness(-30);
  mission_system.setupDailyMissions(4);
  mission_system.checkMissions(true);

  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X) {
      EXPECT_FALSE(mission.completed);
    }
  }
}

TEST(MissionSystemTest, AttractVisitorsMission) {
  Zoo zoo("SF Zoo", 5000.0);
  MissionSystem mission_system(zoo);
  mission_system.setupDailyMissions(5);

  mission_system.checkMissions(true);
  for (const auto& mission : mission_system.getMissions()) {
    if (mission.type == MissionType::ATTRACT_X_VISITORS) {
      EXPECT_FALSE(mission.completed);
    }
  }
}
