#include <iostream>
#include <vector>
#include <limits>
#include "SiteManaging.h"
#include "Restaurant.h"
#include "Order.h"
#include "RestaurantDAO.h"

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