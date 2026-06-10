#ifndef RESTAURANTDAO_H
#define RESTAURANTDAO_H
#include <vector>
#include "sqlite3.h"


using namespace std;
class Restaurant;

class RestaurantDAO {
public:
    static int saveRestaurant(sqlite3* db, Restaurant* r);
    static Restaurant* getRestaurantById(sqlite3* db, int id);
    static void loadAllRestaurants(sqlite3* db, vector<Restaurant*>& allRestaurants);
    static bool updateRestaurant(sqlite3* db, Restaurant* r);
    static bool deleteRestaurant(sqlite3* db, int id);
};

#endif