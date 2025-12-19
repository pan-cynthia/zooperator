#ifndef MISSION_SYSTEM_H
#define MISSION_SYSTEM_H

#include <set>
#include <string>
#include <vector>

#include "animal.h"
#include "exhibit.h"
#include "mission.h"
#include "zoo.h"

class MissionSystem {
 public:
  explicit MissionSystem(Zoo& zoo);
  MissionSystem() = delete;

  std::vector<Mission>& getMissions();
  std::set<Animal*> getAnimalsFedToday();
  std::set<Exhibit*> getExhibitsCleanedToday();

  // mission setup
  void setupDailyMissions(int day);
  void checkMissions(bool end_of_day);
  void completeMission(size_t mission_index);
  bool canAdvanceDay();
  bool checkMissionsImpossible(int action_points);

  void displayMissions(bool show_status);
  std::string getMissionProgress(const Mission& mission);

  // daily tracking
  void trackAnimalFed(Animal* animal);
  void trackExhibitCleaned(Exhibit* exhibit);
  void trackPlayedWithAnimal();
  void trackExercisedAnimal();
  void resetDailyTracking();

 private:
  Zoo& zoo_;
  std::vector<Mission> missions_;

  std::set<Animal*> animals_fed_today_;
  std::set<Exhibit*> exhibits_cleaned_today_;
  bool played_with_animal_today_ = false;
  bool exercised_animal_today_ = false;
};

#endif  // MISSION_SYSTEM_H
