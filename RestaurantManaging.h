#ifndef RESTAURANT_MANAGING
#define RESTAURANT_MANAGING
#include <vector>
#include <string>
#include "Database.h"

using namespace std;

class Restaurant;
class Order;

Restaurant* FindMyRestaurant(int id, int managerID, vector<Restaurant*>& allRestaurants);
void showMyRestaurant(Restaurant* r);
void showMyRestaurantOrders(Restaurant* r, vector<Order*>& allOrders);
void EditOrderStatus(sqlite3* db, Restaurant* r, vector<Order*>& allOrders);
void changeRestaurantAddress(sqlite3* db, Restaurant* r);
void changeRestaurantName(sqlite3* db, Restaurant* r);
void changeRestaurantPhone(sqlite3* db, Restaurant* r);
void changeRestaurantDescripe(sqlite3* db, Restaurant* r);
void changeManagerID(sqlite3* db, Restaurant* r);
void EditItemDetails(sqlite3* db, Restaurant* r);
void EditRestaurantMenu(sqlite3* db, Restaurant* r);

#endif