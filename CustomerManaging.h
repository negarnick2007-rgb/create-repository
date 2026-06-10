#ifndef CUSTOMER_MANAGING_H
#define CUSTOMER_MANAGING_H
#include <vector>
#include "Database.h"

using namespace std;

class Order;
class Restaurant;

Order* buildOrder(int customerID, int restaurantID);
Restaurant* findSelectedRestaurant(int id, vector<Restaurant*>& allRestaurants);
void ordersHistory(int customerID, vector<Order*>& allOrders);
bool canAddItem(int ItemID, int restaurantID, vector<Restaurant*>& allRestaurants);
void paymentManaging(sqlite3* db, Order* order, vector<Order*>& allOrders);
void deleteAllOrders(vector<Order*>& allOrders);
void showAllRestaurants(vector<Restaurant*>& allRestaurants);
void addToOrder(Order* order, int restaurantID, vector<Restaurant*>& allRestaurants);
void removeFromOrder(Order* order);

#endif
