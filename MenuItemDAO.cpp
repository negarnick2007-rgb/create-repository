#include <iostream>
#include <string>
#include <vector>
#include "Database.h"
#include "MenuItemDAO.h"
#include "MenuItem.h"
#include "DrinkItem.h"
#include "FoodItem.h"

using namespace std;

int MenuItemDAO::saveMenuItem(sqlite3* db, MenuItem* item, int restaurantID)
{
	string kind= "";
	double volume= 0.0;
	DrinkItem* d= dynamic_cast<DrinkItem*>(item);
	if(d != nullptr){
		kind= "drink";
		volume= d->getVolume();
	}else{
		kind= "food";
	}
	
	const char* sql = "INSERT INTO RestaurantItems (id, restaurantID, name, description, price, preparationTime, available, kind, volume) "
					  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
	
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	
	sqlite3_bind_int(stmt, 1, item->getID());
	sqlite3_bind_int(stmt, 2, restaurantID);
	sqlite3_bind_text(stmt, 3, item->getName().c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, item->getDescription().c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 5, item->getPrice());
	sqlite3_bind_int(stmt, 6, item->getPrepTime());
	sqlite3_bind_int(stmt, 7, item->getAvailable() ? 1 : 0);
	sqlite3_bind_text(stmt, 8, kind.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 9, volume);
	
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	
	return item->getID();
}

MenuItem* MenuItemDAO::getMenuItemById(sqlite3* db, int itemID, int restaurantID) 
{
    const char* sql = "SELECT * FROM RestaurantItems WHERE id = ? AND restaurantID = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, itemID);
    sqlite3_bind_int(stmt, 2, restaurantID);
    
    MenuItem* item = nullptr;
    
    if(sqlite3_step(stmt) == SQLITE_ROW){
        string kind = (char*)sqlite3_column_text(stmt, 7);
        if(kind == "drink"){
            DrinkItem* d = new DrinkItem();
            d->setVolume(sqlite3_column_double(stmt, 8));
            item = d;
        }else{
            item = new FoodItem();
        }
        
        item->setKind(kind);
        item->setID(sqlite3_column_int(stmt, 0));
        item->setName((char*)sqlite3_column_text(stmt, 2));
        item->setDescription((char*)sqlite3_column_text(stmt, 3));
        item->setPrice(sqlite3_column_double(stmt, 4));
        item->setPrepTime(sqlite3_column_int(stmt, 5));
        item->setAvailable(sqlite3_column_int(stmt, 6) == 1);
    }
    
    sqlite3_finalize(stmt);
    return item;
}

vector<MenuItem*> MenuItemDAO::getItemsByRestaurant(sqlite3* db, int restaurantID)
{
	vector<MenuItem*> items;

	const char* sql = "SELECT * FROM RestaurantItems WHERE restaurantID = ?;";
	
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, restaurantID);
	
	while(sqlite3_step(stmt) == SQLITE_ROW){
		string kind = (char*)sqlite3_column_text(stmt, 7);
		MenuItem* item = nullptr;
		
		if(kind == "drink"){
			DrinkItem* d = new DrinkItem();
			d->setVolume(sqlite3_column_double(stmt, 8));
			item = d;
		} else {
			item = new FoodItem();
		}
		item->setKind(kind);
		item->setID(sqlite3_column_int(stmt, 0));
		item->setName((char*)sqlite3_column_text(stmt, 2));
		item->setDescription((char*)sqlite3_column_text(stmt, 3));
		item->setPrice(sqlite3_column_double(stmt, 4));
		item->setPrepTime(sqlite3_column_int(stmt, 5));
		item->setAvailable(sqlite3_column_int(stmt, 6) == 1);
		
		items.push_back(item);
	}
	
	sqlite3_finalize(stmt);
	return items;
}

bool MenuItemDAO::updateMenuItem(sqlite3* db, MenuItem* item, int restaurantID) 
{
	double volume= 0.0;
	DrinkItem* d= dynamic_cast<DrinkItem*>(item);
	if(d != nullptr){
		volume= d->getVolume();
	}
	
	const char* sql = "UPDATE RestaurantItems SET name=?, description=?, price=?, "
					  "preparationTime=?, available=?, volume=? WHERE id=? AND restaurantID=?;";
	
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, item->getName().c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, item->getDescription().c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 3, item->getPrice());
	sqlite3_bind_int(stmt, 4, item->getPrepTime());
	sqlite3_bind_int(stmt, 5, item->getAvailable() ? 1 : 0);
	sqlite3_bind_double(stmt, 6, volume);
	sqlite3_bind_int(stmt, 7, item->getID());
	sqlite3_bind_int(stmt, 8, restaurantID);
	
	int rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	
	return rc == SQLITE_DONE;
}

bool MenuItemDAO::deleteMenuItem(sqlite3* db, int itemID) 
{
	const char* sql = "DELETE FROM RestaurantItems WHERE id = ?;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, itemID);
	int rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	
	return rc == SQLITE_DONE;
}