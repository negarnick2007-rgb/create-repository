#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include "Database.h"
#include "CustomerManaging.h"
#include "Order.h"
#include "Restaurant.h"
#include "OrderDAO.h"
#include "Customer.h"
#include "CustomerDAO.h"

using namespace std;

Order* buildOrder(int customerID, int restaurantID)
{
	Order* order= new Order(customerID, restaurantID);
	return order;
}

Customer* buildCustomer(sqlite3* db, int customerID, vector<Customer*>& allCustomers)
{
	for(size_t i=0; i<allCustomers.size(); i++){
		if(allCustomers[i]->getCustomerID() == customerID){
			return allCustomers[i];
		}
	}
	
	Customer* customer= new Customer(customerID);
	allCustomers.push_back(customer);
	
	CustomerDAO::saveCustomer(db, customer);
	return customer;
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

void paymentManaging(sqlite3* db, Order* order, vector<Order*>& allOrders, Customer* customer)
{
	double firstPrice= order->getTotalPrice();
	double finalPrice= customer->getLevel()->getFinalPrice(firstPrice);
	double shipCost = customer->getLevel()->getShippingCost(10.0);
	double discount = firstPrice - finalPrice;
	double bill= finalPrice + shipCost;
	
	cout << "Base price: " << firstPrice << endl;
	cout << "Discount: " << discount << endl;
	cout << "Shipping cost: " << shipCost << endl;
	cout << "Final Price: " << bill << endl;
	if(customer->getCoupons() > 0){
		int coupon= customer->getCoupons();
		cout << "You have " << coupon << " coupons to use (you can get a free french fries!)" << endl;
		cout << "Enter 'Yes' to use or 'No' to continue... " << endl;
		string x;
		cin >> x;
		if(x == "Yes" || x == "yes"){
			customer->useCoupon();
			CustomerDAO::updateCustomer(db, customer);
			cout << "The number of your coupons after use: " << customer->getCoupons() << endl;
		}
	}
	double totalPrice;
	cout << "Please pay the bill: (send the final price) ";
	while(!(cin >> totalPrice)){
		cerr << "Please enter numeric total price: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	bool canPay= order->finalizePayment(firstPrice, discount, shipCost, totalPrice);
	
	while(!canPay){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> totalPrice;
		canPay= order->finalizePayment(firstPrice, discount, shipCost, totalPrice);
	}
	int amount= firstPrice;
	
	string oldl = customer->getLevel()->getLevelName();
	customer->addPoints(amount);
	string newl = customer->getLevel()->getLevelName();
	
	if(newl != oldl){
		CustomerDAO::saveLevels(db, customer->getCustomerID(), oldl, newl);
	}
	
	CustomerDAO::updateCustomer(db, customer);
	
	cout << "Points you have earned now: " << customer->getLevel()->getEarnedPoints(firstPrice) << endl;
	
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

void deleteAllCustomers(vector<Customer*>& allCustomers)
{
	for(size_t i=0; i<allCustomers.size(); i++){
		delete allCustomers[i];
		allCustomers[i]= nullptr;
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

void cancelingOrder(sqlite3* db, int customerID, vector<Order*>& allOrders, vector<Customer*>& allCustomers)
{
	int orderID;
	cout << "Enter the order ID you want to cancel: ";
	while(!(cin >> orderID)){
		cerr << "Please enter a numberic order ID: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	for(size_t i=0; i<allOrders.size(); i++){
		if(allOrders[i]->getOrderId() == orderID){
			allOrders[i]->setStatus("Cancelled...");
			OrderDAO::updateOrderStatus(db, orderID, "Cancelled...");
			
			double price= allOrders[i]->getTotalPrice();
			for(size_t j=0; j<allCustomers.size(); j++){
				if(allCustomers[j]->getCustomerID() == customerID){
					int p = price;
					
					string oldl= allCustomers[j]->getLevel()->getLevelName();
					allCustomers[j]->deductPoints(p);
					string newl= allCustomers[j]->getLevel()->getLevelName();
					
					if(oldl != newl){
						CustomerDAO::saveLevels(db, allCustomers[j]->getCustomerID(), oldl, newl);
					}
					
					CustomerDAO::updateCustomer(db, allCustomers[j]);
					cout << "Your Points now: "  << allCustomers[j]->getPoints() << endl;
					cout << "Your level now: " << allCustomers[j]->getLevel()->getLevelName() << endl << endl;
					break;
				}
			}
			return;
		}
	}
	cout << "There is no order with this Id!" << endl;
}

void showMessage(int customerID, vector<Order*>& allOrders)
{
	int n=0;
	for(size_t i=0; i<allOrders.size(); i++){
		if(allOrders[i]->getCustomerID() == customerID){
			n++;
		}
	}
	if(n >= 3){
		cout << "(Frequent Buyer)" << endl;
	}
	
	long long int t= time(0);
	tm* x= localtime(&t);
	int hour= x->tm_hour;
	if(hour >= 20 && hour <= 24){
		cout << "(Night Customer)" << endl;
	}
}