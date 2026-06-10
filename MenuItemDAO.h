#ifndef MENUITEMDAO_H
#define MENUITEMDAO_H

#include <vector>
#include "sqlite3.h"

using namespace std;
class MenuItem;

class MenuItemDAO{
	public:
		static int saveMenuItem(sqlite3* db, MenuItem* item, int restaurantID);
		static MenuItem* getMenuItemById(sqlite3* db, int itemID, int restaurantID);
		static vector<MenuItem*> getItemsByRestaurant(sqlite3* db, int restaurantID);
		static bool updateMenuItem(sqlite3* db, MenuItem* item, int restaurantID);
		static bool deleteMenuItem(sqlite3* db, int itemID);
};

#endif