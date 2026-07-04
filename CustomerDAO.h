#ifndef CUSTOMERDAO_H
#define CUSTOMERDAO_H
#include <vector>
#include "sqlite3.h"

using namespace std;
class Customer;

class CustomerDAO{
	public:
		static bool saveCustomer(sqlite3* db, Customer* customer);
		static bool updateCustomer(sqlite3* db, Customer* customer);
		static void loadAllCustomers(sqlite3* db, vector<Customer*>& allCustomers);
		static bool deleteCustomer(sqlite3* db, int customerID);
		static void saveLevels(sqlite3* db, int customerID, string oldl, string newl);
		static void levelHistory(sqlite3* db);
};

#endif