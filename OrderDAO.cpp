#include <iostream>
#include <vector>
#include <string>
#include "Database.h"
#include "OrderDAO.h"
#include "Order.h"
#include "MenuItem.h"
#include "MenuItemDAO.h"


using namespace std;

int OrderDAO::saveOrder(sqlite3* db, Order* order)
{
    if (!db || !order){
    	return -1;
	}
    
    const char* sql = "INSERT INTO Orders (customerID, restaurantID, totalPrice, status) "
                      "VALUES (?, ?, ?, ?);";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    sqlite3_bind_int(stmt, 1, order->getCustomerID());
    sqlite3_bind_int(stmt, 2, order->getRestaurantID());
    sqlite3_bind_double(stmt, 3, order->getTotalPrice());
    sqlite3_bind_text(stmt, 4, order->getStatus().c_str(), -1, SQLITE_STATIC);
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    int newID = sqlite3_last_insert_rowid(db);
    order->setOrderID(newID);
    
    const vector<MenuItem*>& items = order->getItems();
    const char* sqlItem = "INSERT INTO OrderItems (orderID, itemID) VALUES (?, ?);";
    
    for (size_t i=0; i<items.size(); i++){
        sqlite3_prepare_v2(db, sqlItem, -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, newID);
        sqlite3_bind_int(stmt, 2, items[i]->getID());
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    
    return newID;
}

void OrderDAO::loadAllOrders(sqlite3* db, vector<Order*>& allOrders)
{
    if (!db){
    	return;
	}
    
    const char* sql = "SELECT * FROM Orders;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int customerID = sqlite3_column_int(stmt, 1);
        int restaurantID = sqlite3_column_int(stmt, 2);
        double totalPrice = sqlite3_column_double(stmt, 3);
        string status = (const char*)sqlite3_column_text(stmt, 4);
        
        Order* order = new Order(customerID, restaurantID);
        order->setOrderID(id);
        order->setTotalPrice(totalPrice);
        order->setStatus(status);
        
        allOrders.push_back(order);
        
        const char* sql2= "SELECT itemID FROM OrderItems WHERE orderID=?;";
        sqlite3_stmt* stmt2;
        sqlite3_prepare_v2(db, sql2, -1, &stmt2, nullptr);
        sqlite3_bind_int(stmt2, 1, id);
        
        while(sqlite3_step(stmt2) == SQLITE_ROW){
        	int itemID= sqlite3_column_int(stmt2, 0);
        	MenuItem* item= MenuItemDAO::getMenuItemById(db, itemID, restaurantID);
        	if(item != nullptr){
        		order->loadItem(item);
			}
		}
		sqlite3_finalize(stmt2);
    }
    
    sqlite3_finalize(stmt);
}

bool OrderDAO::updateOrderStatus(sqlite3* db, int orderID, const string& status)
{
    if (!db){
    	return false;
	}
    
    const char* sql = "UPDATE Orders SET status = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, status.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, orderID);
    
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}

bool OrderDAO::deleteOrder(sqlite3* db, int orderID)
{
    if (!db){
    	return false;
	}
    const char* sql1 = "DELETE FROM OrderItems WHERE orderID = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql1, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, orderID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    const char* sql2 = "DELETE FROM Orders WHERE id = ?;";
    sqlite3_prepare_v2(db, sql2, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, orderID);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}