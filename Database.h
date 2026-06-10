#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"

using namespace std;

class Database{
	private:
		static sqlite3* db;
		static bool initialized;
	public:
		static bool init(const string& dbPath= "food_order.db");
		static sqlite3* getDB();
		static void close();
};

#endif