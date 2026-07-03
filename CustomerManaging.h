#ifndef CUSTOMER_MANAGING_H
#define CUSTOMER_MANAGING_H
#include <vector>
#include "Database.h"

using namespace std;

class Order;
class Restaurant;
class Customer;

Order* buildOrder(int customerID, int restaurantID);
Customer* buildCustomer(sqlite3* db, int customerID, vector<Customer*>& allCustomers);
Restaurant* findSelectedRestaurant(int id, vector<Restaurant*>& allRestaurants);
void ordersHistory(int customerID, vector<Order*>& allOrders);
bool canAddItem(int ItemID, int restaurantID, vector<Restaurant*>& allRestaurants);
void paymentManaging(sqlite3* db, Order* order, vector<Order*>& allOrders, Customer* customer);
void deleteAllOrders(vector<Order*>& allOrders);
void deleteAllCustomers(vector<Customer*>& allCustomers);
void showAllRestaurants(vector<Restaurant*>& allRestaurants);
void addToOrder(Order* order, int restaurantID, vector<Restaurant*>& allRestaurants);
void removeFromOrder(Order* order);
void cancelingOrder(sqlite3* db, int customerID, vector<Order*>& allOrders, vector<Customer*>& allCustomers);

#endif
