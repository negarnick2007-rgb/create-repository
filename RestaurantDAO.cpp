#include "RestaurantDAO.h"
#include <iostream>
#include <vector>
#include <string>
#include "Restaurant.h"
#include "Address.h"
#include "Database.h"
#include "MenuItemDAO.h"

using namespace std;

int RestaurantDAO::saveRestaurant(sqlite3* db, Restaurant* r)
{
    if (!db || !r){
    	return -1;
	}
    
    const char* sql = "INSERT OR REPLACE INTO Restaurants (id, name, phoneNumber, description, active, managerID, city, street, placeNumber) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    sqlite3_bind_int(stmt, 1, r->getID());
    sqlite3_bind_text(stmt, 2, r->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, r->getPhoneNumber().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, r->getDescription().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, r->isActive() ? 1 : 0);
    sqlite3_bind_int(stmt, 6, r->getManagerID());
    
    sqlite3_bind_text(stmt, 7, r->getAddress().getCity().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, r->getAddress().getStreet().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, r->getAddress().getPlaceNumber());
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return r->getID();
}

Restaurant* RestaurantDAO::getRestaurantById(sqlite3* db, int id)
{
    if (!db){
    	return nullptr;
	}
    
    const char* sql = "SELECT * FROM Restaurants WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    
    Restaurant* r = nullptr;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = (const char*)sqlite3_column_text(stmt, 1);
        string phoneNumber = (const char*)sqlite3_column_text(stmt, 2);
        string description = (const char*)sqlite3_column_text(stmt, 3);
        bool active = (sqlite3_column_int(stmt, 4) == 1);
        int managerID = sqlite3_column_int(stmt, 5);
        
        string city = (const char*)sqlite3_column_text(stmt, 6);
        string street = (const char*)sqlite3_column_text(stmt, 7);
        int placeNumber = sqlite3_column_int(stmt, 8);
        
        Address addr;
        addr.setCity(city);
        addr.setStreet(street);
        addr.setPlaceNumber(placeNumber);

        r = new Restaurant();
        r->setID(id);
        r->setName(name);
        r->setPhoneNumber(phoneNumber);
        r->setDescription(description);
        r->setActive(active);
        r->setManagerID(managerID);
        r->changeAddress(addr);
    }
    
    sqlite3_finalize(stmt);
    return r;
}

void RestaurantDAO::loadAllRestaurants(sqlite3* db, vector<Restaurant*>& allRestaurants)
{
	if (!db){
    	return;
	}
    
    const char* sql = "SELECT * FROM Restaurants;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = (const char*)sqlite3_column_text(stmt, 1);
        string phoneNumber = (const char*)sqlite3_column_text(stmt, 2);
        string description = (const char*)sqlite3_column_text(stmt, 3);
        bool active = (sqlite3_column_int(stmt, 4) == 1);
        int managerID = sqlite3_column_int(stmt, 5);
        
        string city = (const char*)sqlite3_column_text(stmt, 6);
        string street = (const char*)sqlite3_column_text(stmt, 7);
        int placeNumber = sqlite3_column_int(stmt, 8);
        
        Address addr;
        addr.setCity(city);
        addr.setStreet(street);
        addr.setPlaceNumber(placeNumber);
        
        Restaurant* r = new Restaurant();
        r->setID(id);
        r->setName(name);
        r->setPhoneNumber(phoneNumber);
        r->setDescription(description);
        r->setActive(active);
        r->setManagerID(managerID);
        r->changeAddress(addr);
        
        vector<MenuItem*> menu= MenuItemDAO::getItemsByRestaurant(db, id);
        for(size_t i=0; i<menu.size(); i++){
        	r->addMenuItem(menu[i]);
		}
		
        allRestaurants.push_back(r);
    }
    
    sqlite3_finalize(stmt);
}

bool RestaurantDAO::updateRestaurant(sqlite3* db, Restaurant* r)
{
    if (!db || !r){
    	return false;
	}
    
    const char* sql = "UPDATE Restaurants SET name=?, phoneNumber=?, description=?, active=?, managerID=?, "
                      "city=?, street=?, placeNumber=? WHERE id=?;";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    sqlite3_bind_text(stmt, 1, r->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, r->getPhoneNumber().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, r->getDescription().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, r->isActive() ? 1 : 0);
    sqlite3_bind_int(stmt, 5, r->getManagerID());
    
    sqlite3_bind_text(stmt, 6, r->getAddress().getCity().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, r->getAddress().getStreet().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 8, r->getAddress().getPlaceNumber());
    
    sqlite3_bind_int(stmt, 9, r->getID());
    
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}

bool RestaurantDAO::deleteRestaurant(sqlite3* db, int id)
{
    if (!db){
    	return false;
	}
    
    const char* sql1 = "DELETE FROM RestaurantItems WHERE restaurantID = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql1, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    const char* sql2 = "DELETE FROM Orders WHERE restaurantID = ?;";
    sqlite3_prepare_v2(db, sql2, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    const char* sql3 = "DELETE FROM Restaurants WHERE id = ?;";
    sqlite3_prepare_v2(db, sql3, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}