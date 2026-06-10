#include <iostream>
#include <string>
#include "Database.h"

using namespace std;

sqlite3* Database::db= nullptr;
bool Database::initialized= false;

bool Database::init(const string& dbPath) 
{
	if(initialized){
		return true;
	}
	
	int rc= sqlite3_open(dbPath.c_str(), &db);
	if(rc != SQLITE_OK){
		cerr << "Error in open data base!" << sqlite3_errmsg(db) << endl;
		return false;
	}
	
	const char* createTables= 
		"CREATE TABLE IF NOT EXISTS Restaurants ("
		"id INTEGER PRIMARY KEY,"
		"name TEXT NOT NULL,"
		"phoneNumber TEXT,"
		"description TEXT,"
		"active INTEGER DEFAULT 1,"
		"managerID INTEGER,"
		"city TEXT,"
		"street TEXT,"
		"placeNumber INTEGER"
		");"
		
		"CREATE TABLE IF NOT EXISTS RestaurantItems ("
		"id INTEGER NOT NULL,"
		"restaurantID INTEGER NOT NULL,"
		"name TEXT NOT NULL,"
		"description TEXT,"
		"price REAL NOT NULL,"
		"preparationTime INTEGER,"
		"available INTEGER DEFAULT 1,"
		"kind TEXT NOT NULL,"
		"volume REAL DEFAULT 0,"
		"PRIMARY KEY(id, restaurantID),"
		"FOREIGN KEY(restaurantID)REFERENCES Restaurants(id)"
		");"
		
		"CREATE TABLE IF NOT EXISTS Orders ("
		"id INTEGER PRIMARY KEY,"
		"customerID INTEGER NOT NULL,"
		"restaurantID INTEGER NOT NULL,"
		"totalPrice REAL DEFAULT 0,"
		"status TEXT DEFAULT 'In preparation...' "
		");"
		
		"CREATE TABLE IF NOT EXISTS OrderItems("
		"orderID INTEGER NOT NULL,"
		"itemID INTEGER NOT NULL,"
		"FOREIGN KEY(orderID) REFERENCES Orders(id),"
		"FOREIGN KEY(itemID) REFERENCES RestaurantItems(id)"
		");";
		
	char* errorMessage= nullptr;
	rc= sqlite3_exec(db, createTables, nullptr, nullptr, &errorMessage);
	if(rc != SQLITE_OK){
		cerr << "Error in build tables!" << errorMessage;
		sqlite3_free(errorMessage);
		return false;
	}
	
	initialized= true;
	return true;
}

sqlite3* Database::getDB() 
{
	return db;
}

void Database::close() 
{
	if(db){
		sqlite3_close(db);
		db= nullptr;
		initialized= false;
	}
}