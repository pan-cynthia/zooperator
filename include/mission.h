#include <string>

enum class MissionType {
  PURCHASE_ANIMAL,
  PURCHASE_EXHIBIT,
  ADD_ANIMAL_TO_EXHIBIT,
  OWN_X_ANIMALS,
  OWN_X_SPECIES,
  OWN_X_EXHIBITS,
  NO_ANIMALS_NEED_ATTENTION,
  NO_SICK_ANIMALS,
  NO_HOMELESS_ANIMALS,
  PREFERRED_HABITATS,
  EXHIBITS_CLEANLINESS_AT_LEAST_X,
  BALANCE_AT_LEAST,
  ZOO_RATING_ABOVE,
  OWN_ELEPHANT,
  OWN_SPECIAL_ANIMAL,
};

struct Mission {
  std::string description;
  MissionType type;

  bool required;
  bool completed;

  // optional parameters
  int int_param = 0;         // X animals, X exhibits
  double float_param = 0.0;  // rating thresholds, balance thresholds

  int reward_amount;

  Mission(bool required, const std::string& description, MissionType type, int int_param = 0,
          double float_param = 0.0, double reward_amount = 0.0)
      : description(description),
        type(type),
        required(required),
        completed(false),
        int_param(int_param),
        float_param(float_param),
        reward_amount(reward_amount) {}
};
