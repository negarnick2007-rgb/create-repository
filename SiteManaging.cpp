#include <iostream>
#include <vector>
#include <limits>
#include "SiteManaging.h"
#include "Restaurant.h"
#include "Order.h"
#include "RestaurantDAO.h"
#include "Customer.h"
#include "MemberShipLevel.h"
#include "NormalLevel.h"
#include "SilverLevel.h"
#include "GoldLevel.h"
#include "VipLevel.h"
#include "CustomerDAO.h"

using namespace std;


Restaurant* FindRestaurantByID(int id, vector<Restaurant*>& allRestaurants)
{
	for(size_t i=0; i<allRestaurants.size(); i++){
		if(allRestaurants[i]->getID() == id){
			return allRestaurants[i];
		}
	}
	return nullptr;
}

void addNewRestaurant(sqlite3* db, vector<Restaurant*>& allRestaurants)
{
	Restaurant* r= new Restaurant();
	cout << "Enter your new restaurant details: (restaurantID/name/phone number/description/address/your ID" << endl;
	cout << "The address should be like: (city/street/place number)" << endl;
	
	cin >> *r;
	
	RestaurantDAO::saveRestaurant(db, r);
	allRestaurants.push_back(r);
	cout << "Restaurant added successfully!" << endl << endl;
}

void removeRestaurant(sqlite3* db, vector<Restaurant*>& allRestaurants)
{
	int id;
	cout << "Enter the restaurant ID: ";
	while(!(cin >> id)){
		cerr << "Please enter numeric ID: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	for(size_t i=0; i<allRestaurants.size(); i++){
		if(allRestaurants[i]->getID() == id){
			RestaurantDAO::deleteRestaurant(db, id);
			delete allRestaurants[i];
			allRestaurants.erase(allRestaurants.begin()+i);
			cout << "The restaurant removed!" << endl << endl;
			return;
		}
	}
	cout << "There is no restaurant with this ID!" << endl << endl;
}

void deleteAllRestaurants(vector<Restaurant*>& allRestaurants)
{
	for(size_t i=0; i<allRestaurants.size(); i++){
		delete allRestaurants[i];
		allRestaurants[i]= nullptr;
	}
}

void changeRestaurantActivity(sqlite3* db, vector<Restaurant*>& allRestaurants)
{
	int id;
	cout << "Enter ID of the restaurant: ";
	while(!(cin >> id)){
		cerr << "Please enter numeric ID: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	Restaurant* r= FindRestaurantByID(id, allRestaurants);
	
	if(r == nullptr){
		cerr << "There is no restaurant with this ID!" << endl << endl;
		return;
	}
	
	bool act;
	string active;
	string type;
	
	cout << "Do you want to set the restaurant active? Yes/No" << endl;
	cin >> active;
	if(active == "Yes" || active == "yes"){
		type= "active";
		act= true;
	}else{
		type= "inactive";
		act= false;
	}
	r->setActive(act);
	RestaurantDAO::updateRestaurant(db, r);
	
	cout << "The restaurant set " << type << endl << endl;
}

void SalesStatistics(vector<Order*>& allOrders)
{
	double total= 0.0;
	int count= Order::getOrderCount();
	cout << "Count of all orders: " << count << endl;
	
	for(size_t i=0; i<allOrders.size(); i++){
		total= total + allOrders[i]->getTotalPrice();
	}
	
	cout << "Total sales price: " << total << endl << endl;
}

void deleteOneOrder(vector<Order*>& allOrders, int id)
{
	for(size_t i=0; i<allOrders.size(); i++){
		if(allOrders[i]->getOrderId() == id){
			delete allOrders[i];
			allOrders.erase(allOrders.begin() + i);
			break;
		}
	}
}

void showLevels(vector<Customer*>& allCustomers)
{
	int normal=0, silver = 0, gold = 0, vip=0;
	for(size_t i=0; i<allCustomers.size(); i++){
		if(allCustomers[i]->getLevel()->getLevelName() == "Normal"){
			normal++;
		}else if(allCustomers[i]->getLevel()->getLevelName() == "Silver"){
			silver++;
		}else if(allCustomers[i]->getLevel()->getLevelName() == "Gold"){
			gold++;
		}else if(allCustomers[i]->getLevel()->getLevelName() == "VIP"){
			vip++;
		}
	}
	cout << "+++ Number of Customers in each level +++" << endl << endl;
	cout << "Normal level: " << normal << " person" << endl;
	cout << "Silver level: " << silver << " persen" << endl;
	cout << "Gold level: " << gold << " person" << endl;
	cout << "VIP level: " << vip << " person" << endl << endl;
}

void changeLevel(sqlite3* db, vector<Customer*>& allCustomers)
{
	int customerID;
	cout << "Enter the ID of the customer you want to change its level or points: ";
	while(!(cin >> customerID)){
		cerr << "Please enter a numeric Id: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	Customer* cust;
	for(size_t i=0; i<allCustomers.size(); i++){
		if(allCustomers[i]->getCustomerID() == customerID){
			cust= allCustomers[i];
			break;
		}
	}
	cout << "Level: " << cust->getLevel()->getLevelName() << endl;
	cout << "Points: " << cust->getPoints() << endl << endl;
	cout << "What do you want to change?" << endl;
	cout << "1. Level" << endl;
	cout << "2. Points" << endl;
	int n;
	while(!(cin >> n)){
		cerr << "Wrong order! try again...  ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	switch (n){
		case 1: {
			string oldl = cust->getLevel()->getLevelName();
			string level;
			cout << "Enter new level (Normal / Silver / Gold / VIP): ";
			cin >> level;
			MembershipLevel* l;
			if(level == "Normal" || level == "normal"){
				l= new NormalLevel();
				int p= l->getPointRange();
				cust->setPoints(p);
				
			}else if(level == "Silver" || level =="silver"){
				l = new SilverLevel();
				int p= l->getPointRange();
				cust->setPoints(p);
				
			}else if(level == "Gold" || level == "gold"){
				l= new GoldLevel();
				int p= l->getPointRange();
				cust->setPoints(p);
				
			}else{
				l= new VipLevel();
				int p= l->getPointRange();
				cust->setPoints(p);
			}
			
			cust->setLevel(l);
			string newl= cust->getLevel()->getLevelName();
			
			if(oldl != newl){
				CustomerDAO::saveLevels(db, cust->getCustomerID(), oldl, newl);
			}
			CustomerDAO::updateCustomer(db, cust);
			break;
		}
		case 2:{
			string oldl= cust->getLevel()->getLevelName();
			int point;
			cout << "Enter new points: ";
			cin >> point;
			MembershipLevel* l;
			if(point >= 0 && point < 100){
				l = new NormalLevel();
				cust->setLevel(l);
				if(oldl != "Normal"){
					CustomerDAO::saveLevels(db, cust->getCustomerID(), oldl, "Normal");
				}
				
			}else if(point >= 100 && point < 300){
				l = new SilverLevel();
				cust->setLevel(l);
				if(oldl != "Silver"){
					CustomerDAO::saveLevels(db, cust->getCustomerID(), oldl, "Silver");
				}
				
			}else if(point >= 300 && point < 700){
				l = new GoldLevel();
				cust->setLevel(l);
				if(oldl != "Gold"){
					CustomerDAO::saveLevels(db, cust->getCustomerID(), oldl, "Gold");
				}
				
			}else if(point >= 700){
				l = new VipLevel();
				cust->setLevel(l);
				if(oldl != "VIP"){
					CustomerDAO::saveLevels(db, cust->getCustomerID(), oldl, "VIP");
				}
				
			}
			cust->setPoints(point);
			CustomerDAO::updateCustomer(db, cust);
			break;
		}
	}
}