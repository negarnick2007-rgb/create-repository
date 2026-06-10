#ifndef ORDERDAO_H
#define ORDERDAO_H

#include "sqlite3.h"
#include "Order.h"
#include <vector>
#include <string>

using namespace std;
class Order;

class OrderDAO {
public:
    static int saveOrder(sqlite3* db, Order* order);
    static void loadAllOrders(sqlite3* db, vector<Order*>& allOrders);
    static bool updateOrderStatus(sqlite3* db, int orderID, const string& status);
    static bool deleteOrder(sqlite3* db, int orderID);
};

#endif