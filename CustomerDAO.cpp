#include <vector>
#include <string>
#include "sqlite3.h"
#include "Customer.h"
#include "CustomerDAO.h"
#include "NormalLevel.h"
#include "SilverLevel.h"
#include "GoldLevel.h"
#include "VipLevel.h"

using namespace std;

bool CustomerDAO::saveCustomer(sqlite3* db, Customer* customer)
{
	const char* sql= "INSERT OR IGNORE INTO Customers (id, points, level, coupons)"
					"VALUES (?, ?, ?, ?);";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, customer->getCustomerID());
	sqlite3_bind_int(stmt, 2, customer->getPoints());
	sqlite3_bind_text(stmt, 3, customer->getLevel()->getLevelName().c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 4, customer->getCoupons());
	
	bool rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	
	return rc == SQLITE_DONE;
}

bool CustomerDAO::updateCustomer(sqlite3* db, Customer* customer) 
{
	const char* sql= "UPDATE Customers SET points=?, level=?, coupons=? WHERE id=?;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, customer->getPoints());
	sqlite3_bind_text(stmt, 2, customer->getLevel()->getLevelName().c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, customer->getCoupons());
	sqlite3_bind_int(stmt, 4, customer->getCustomerID());
	
	bool rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	
	return rc == SQLITE_DONE;
}

void CustomerDAO::loadAllCustomers(sqlite3* db, vector<Customer*>& allCustomers) 
{
	const char* sql= "SELECT id, points, level, coupons FROM Customers;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	
	while(sqlite3_step(stmt) == SQLITE_ROW){
		int id= sqlite3_column_int(stmt, 0);
		int points= sqlite3_column_int(stmt, 1);
		string levelName= (char*)sqlite3_column_text(stmt, 2);
		int coupons= sqlite3_column_int(stmt, 3);
		
		MembershipLevel* level= nullptr;
		if(levelName == "Silver"){
			level= new SilverLevel();
		}
		else if(levelName == "Gold"){
			level= new GoldLevel();
		}
		else if(levelName == "VIP"){
			level= new VipLevel();
		}else{
			level= new NormalLevel();
		}
		
		Customer* customer= new Customer(id, points, level, coupons);
		allCustomers.push_back(customer);
	}
	
	sqlite3_finalize(stmt);
}

bool CustomerDAO::deleteCustomer(sqlite3* db, int customerID)
{
	const char* sql= "DELETE FROM Customers WHERE id=?;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, customerID);
	
	bool rc= sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	
	return rc == SQLITE_DONE;
}