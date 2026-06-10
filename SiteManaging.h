#ifndef SITE_MANAGING_H
#define SITE_MANAGING_H
#include <vector>
#include "Database.h"

using namespace std;

class Restaurant;
class Order;

Restaurant* FindRestaurantByID(int id, vector<Restaurant*>& allRestaurants);
void addNewRestaurant(sqlite3* db, vector<Restaurant*>& allRestaurants);
void removeRestaurant(sqlite3* db, vector<Restaurant*>& allRestaurants);
void deleteAllRestaurants(vector<Restaurant*>& allRestaurants);
void changeRestaurantActivity(sqlite3* db, vector<Restaurant*>& allRestaurants);
void SalesStatistics(vector<Order*>& allOrders);

#endif