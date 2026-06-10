#include <iostream>
#include <string>
#include <vector>
#include "Order.h"
#include "MenuItem.h"
#include "Restaurant.h"

using namespace std;

int Order::orderNumber = 0;

Order::Order(int id, int resId) : totalPrice(0.0), orderStatus("In preparation..."), customerID(id), restaurantID(resId), orderID(0)
{
	orderNumber++;
}

int Order::getOrderId() const
{
	return orderID;
}

string Order::getStatus() const
{
	return orderStatus;
}

int Order::getItemCount() const
{
	return items.size();
}

bool Order::finalizePayment(double totalPrice)
{
	if(this->totalPrice == totalPrice){
		cout << "Your order has been successfully placed!" << endl << endl;
		return true;
	}else{
		if(this->totalPrice > totalPrice){
			cerr << "Your payment is less than total price!" << endl;
		}else{
			if(this->totalPrice < totalPrice){
				cerr << "Your payment is more than total price!" << endl;
			}
		}
	}
	return false;
}

int Order::getCustomerID() const
{
	return customerID;
}

int Order::getRestaurantID() const
{
	return restaurantID;
}

void Order::setStatus(string status) 
{
	orderStatus= status;
}

void Order::addItemToOrder(MenuItem* item) 
{
	if(item != nullptr){
		items.push_back(item);
		totalPrice= totalPrice + item->getPrice();
		displayOrder();
	}
}

void Order::removeItem(int itemId) 
{
	int size= items.size();
	for(size_t i=0; i<items.size(); i++){
		if(items[i]->getID() == itemId){
			totalPrice= totalPrice - items[i]->getPrice();
			items.erase(items.begin() + i);
			break;
		}
	}
	if(size == items.size()){
		return;
	}else{
		displayOrder();
	}
}

double Order::getTotalPrice() const
{
	return totalPrice;
}

void Order::displayOrder() const
{
	cout << "<<<Your order details>>>" << endl << endl;
	cout << "Customer ID: " << customerID << endl;
	cout << "Restaurant ID: " << restaurantID << endl;
	cout << "Order ID: " << getOrderId() << endl <<endl;
	for(size_t i=0; i<items.size(); i++){
		items[i]->displayDetails();
	}
	cout << "total price: " << totalPrice << endl;
	cout << orderStatus << endl << endl;
}

void Order::clearOrder(int newRestaurantID) 
{
	items.clear();
	totalPrice = 0.0;
	orderStatus= "";
	restaurantID= newRestaurantID;
	cout << "Your order is empty now" << endl;
	cout << "Total price since now: " << totalPrice << endl << endl;
}

int Order::getOrderCount()
{
	return orderNumber;
}

const vector<MenuItem*>& Order::getItems() const
{
	return items;
}

void Order::setOrderID(int id)
{
	orderID= id;
}

void Order::setTotalPrice(double price)
{
	totalPrice= price;
}

void Order::loadItem(MenuItem* item)//just for Database
{
	items.push_back(item);
}