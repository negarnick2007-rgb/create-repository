#ifndef SITE_MANAGING_H
#define SITE_MANAGING_H
#include <vector>
#include "Database.h"

using namespace std;

class Restaurant;
class Order;
class Customer;

Restaurant* FindRestaurantByID(int id, vector<Restaurant*>& allRestaurants);
void addNewRestaurant(sqlite3* db, vector<Restaurant*>& allRestaurants);
void removeRestaurant(sqlite3* db, vector<Restaurant*>& allRestaurants);
void deleteAllRestaurants(vector<Restaurant*>& allRestaurants);
void changeRestaurantActivity(sqlite3* db, vector<Restaurant*>& allRestaurants);
void SalesStatistics(vector<Order*>& allOrders);
void deleteOneOrder(vector<Order*>& allOrders, int id);
void showLevels(vector<Customer*>& allCustomers);
void changeLevel(sqlite3* db, vector<Customer*>& allCustomers);

#endif