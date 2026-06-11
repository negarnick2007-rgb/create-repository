#include <iostream>
#include <vector>
#include <limits>
#include "Database.h"
#include "CustomerManaging.h"
#include "Order.h"
#include "Restaurant.h"
#include "OrderDAO.h"

using namespace std;

Order* buildOrder(int customerID, int restaurantID)
{
	Order* order= new Order(customerID, restaurantID);
	return order;
}

void ordersHistory(int customerID, vector<Order*>& allOrders)
{
	int size=0;
	for(size_t i=0; i<allOrders.size(); i++){
		if(allOrders[i]->getCustomerID() == customerID){
			size++;
			cout << i+1 << ". ";
			allOrders[i]->displayOrder();
			cout << endl;
		}
	}
	if(size == 0){
		cout << "The Order History Is Empty!" << endl << endl;
	}
}

bool canAddItem(int ItemID, int restaurantID, vector<Restaurant*>& allRestaurants)
{
	Restaurant* r= findSelectedRestaurant(restaurantID, allRestaurants);
	if(r != nullptr && r->getItemById(ItemID) != nullptr){
		return true;
	}
	return false;
}

void paymentManaging(sqlite3* db, Order* order, vector<Order*>& allOrders)
{
	double totalPrice;
	cout << "Please pay the bill: (send the total price) ";
	while(!(cin >> totalPrice)){
		cerr << "Please enter numeric total price: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	bool canPay= order->finalizePayment(totalPrice);
	
	while(!canPay){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> totalPrice;
		canPay= order->finalizePayment(totalPrice);
	}
	int orderID= OrderDAO::saveOrder(db, order);
	order->setOrderID(orderID);
	
	allOrders.push_back(order);
}

void deleteAllOrders(vector<Order*>& allOrders)
{
	for(size_t i=0; i<allOrders.size(); i++){
		delete allOrders[i];
		allOrders[i]= nullptr;
	}
}

void showAllRestaurants(vector<Restaurant*>& allRestaurants)
{
	for(size_t i=0; i<allRestaurants.size(); i++){
		if(allRestaurants[i]->isActive()){
			allRestaurants[i]->printRestaurantInfo();
		}
	}
}

Restaurant* findSelectedRestaurant(int id, vector<Restaurant*>& allRestaurants)
{
	for(size_t i=0; i<allRestaurants.size(); i++){
		if(allRestaurants[i]->getID() == id){
			return allRestaurants[i];
		}
	}
	return nullptr;
}

void addToOrder(Order* order, int restaurantID, vector<Restaurant*>& allRestaurants) 
{
	Restaurant* r= findSelectedRestaurant(restaurantID, allRestaurants);
	if(r == nullptr){
		cout << "Restaurant does not exist!" << endl << endl;
		return;
	}
	
	int id=0;
	cout << "Enter the ID of items you want to add to your order: (Enter -1 to end the order)";
	while(id != -1){
		cin >> id;
		if(id == -1){
			break;
		}
		if(canAddItem(id, restaurantID, allRestaurants)){
			MenuItem* item= r->getItemById(id);
			order->addItemToOrder(item);
		}else{
			cout << "No Item with this ID!" << endl << endl;
		}
	}
}

void removeFromOrder(Order* order)
{
	cout << "Enter the ID of items you want to remove from your order: (Enter -1 to end) ";
	int id=0;
	while(id != -1){
		cin >> id;
		order->removeItem(id);
	}
}