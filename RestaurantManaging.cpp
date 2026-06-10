#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "RestaurantManaging.h"
#include "Restaurant.h"
#include "Address.h"
#include "Order.h"
#include "MenuItem.h"
#include "FoodItem.h"
#include "DrinkItem.h"
#include "RestaurantDAO.h"
#include "MenuItemDAO.h"
#include "OrderDAO.h"

using namespace std;

Restaurant* FindMyRestaurant(int id, int managerID, vector<Restaurant*>& allRestaurants)
{
	for(size_t i=0; i<allRestaurants.size(); i++){
		if(allRestaurants[i]->getID() == id && allRestaurants[i]->getManagerID() == managerID){
			return allRestaurants[i];
		}
	}
	cerr << "Invalid restaurant ID or manager ID!" << endl << endl;
	return nullptr;
}

void showMyRestaurant(Restaurant* r)
{
	r->printRestaurantInfo();
}

void showMyRestaurantOrders(Restaurant* r, vector<Order*>& allOrders)
{
	for(size_t i=0; i<allOrders.size(); i++){
		if(allOrders[i]->getRestaurantID() == r->getID()){
			allOrders[i]->displayOrder();
		}
	}
}

void EditOrderStatus(sqlite3* db, Restaurant* r, vector<Order*>& allOrders)
{
	int orderID, k;
	string status;
	cout << "Enter order ID: ";
	cin >> orderID;
	for(size_t i=0; i<allOrders.size(); i++){
		if(allOrders[i]->getOrderId() == orderID){
			k=i;
			break;
		}
	}
	cout << "Enter new status:";
	cin.ignore();
	getline(cin, status);
	allOrders[k]->setStatus(status);
	OrderDAO::updateOrderStatus(db, orderID, status);
	cout << "The status of the order changed!" << endl << endl;
	
}

void changeRestaurantAddress(sqlite3* db, Restaurant* r)
{
	Address addr;
	cout << "Enter the new address by format: city street placeNumber";
	cin >> addr;
	r->changeAddress(addr);
	RestaurantDAO::updateRestaurant(db, r);
	cout << "The address changed!" << endl << endl;
	
}

void changeRestaurantName(sqlite3* db, Restaurant* r)
{
	string name;
	cout << "Enter new name: ";
	cin.ignore();
	getline(cin, name);
	r->setName(name);
	RestaurantDAO::updateRestaurant(db, r);
	cout << "Your restaurant name changed!" << endl << endl;
}

void changeRestaurantPhone(sqlite3* db, Restaurant* r)
{
	string phoneNumber;
	cout << "Enter new phone number: ";
	cin.ignore();
	getline(cin, phoneNumber);
	r->setPhoneNumber(phoneNumber);
	RestaurantDAO::updateRestaurant(db, r);
	cout << "Your restaurant phone number changed!" << endl << endl;
}

void changeRestaurantDescripe(sqlite3* db, Restaurant* r)
{
	string description;
	cout << "Enter your description about the restaurant: ";
	cin.ignore();
	getline(cin, description);
	r->setDescription(description);
	RestaurantDAO::updateRestaurant(db, r);
	cout << "Restaurant description changed!" << endl << endl;
}

void changeManagerID(sqlite3* db, Restaurant* r)
{
	int id;
	cout << "Enter your new ID: ";
	cin >> id;
	r->setManagerID(id);
	RestaurantDAO::updateRestaurant(db, r);
	cout << "Your ID changed!" << endl << endl;
}

void EditItemDetails(sqlite3* db, Restaurant* r)
{
	int itemId, num;
	cout << "Enter Id of the item";
	cin >> itemId;
	
	cout << "Which one do you want to edit?" << endl;
	cout << "1. Name" << endl;
	cout << "2. Price" << endl;
	cout << "3. Description" << endl;
	cout << "4. availability" << endl;
	cout << "5. Preparation time in minute" << endl;
	cout << "6. Volume" << endl;
	
	cin >> num;
	while(!(num >= 1 && num <= 6)){
		cerr << "Invalid operation! Try again..." << endl << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> num;
	}
	
	MenuItem* item= r->getItemById(itemId);
	
	switch(num) {
		case 1: {
			string name;
			cin.ignore();
			cout << "Enter a new name for item: ";
			getline(cin, name);
			item->setName(name);
			cout << "Item name changed!" << endl << endl;
			break;
		}
		case 2: {
			double price;
			cout << "Enter new price: ";
			cin >> price;
			item->setPrice(price);
			cout << "Item price changed!" << endl << endl;
			break;
		}
		case 3: {
			string description;
			cout << "Enter new description: ";
			cin.ignore();
			getline(cin, description);
			item->setDescription(description);
			cout << "Description changed!" << endl << endl;
			break;
		}
		case 4: {
			bool available;
			string active;
			cout << "Do you want to set this item available? Yes/No";
			cin >> active;
			if(active == "Yes" || active == "yes"){
				available= true;
			}else{
				available= false;
			}
			item->setAvailable(available);
			break;
		}
		case 5: {
			int time;
			cout << "Enter new preparation time in minute: ";
			cin >> time;
			item->setPrepTime(time);
			cout << "Preparation time changed!" << endl << endl;
			break;
		}
		case 6: {
			DrinkItem* drink= dynamic_cast<DrinkItem*>(item);
			if(drink != nullptr){
				double volume;
				cout << "Enter the volume in ml: ";
				cin >> volume;
				drink->setVolume(volume);
				cout << "The volume changed!" << endl << endl;
			}else{
				cerr << "A food item doesn't have volume!" << endl << endl;
			}
			break;
		}
	}
	MenuItemDAO::updateMenuItem(db, item, r->getID());
}

void EditRestaurantMenu(sqlite3* db, Restaurant* r)
{
	cout << "What do you want to edit?" << endl;
	cout << "1. Add an item" << endl;
	cout << "2. Remove an item" << endl;
	
	int num;
	cin >> num;
	
	while(!(num == 1 || num ==2)){
		cerr << "Invalid operation! Try again...";
		cin.clear();
		cin.ignore();
		cin >> num;
	}
	switch(num) {
		case 1: {
			MenuItem* item;
			string type;
			cout << "Enter type of new item  Food/Drink: ";
			cin >> type;
			if(type == "Food" || type == "food"){
				item= new FoodItem();
				item->setKind(type);
				cout << "Enter details of item: (id/name/description/price/preparation time in minute/availability(yes/no))" << endl;
				cin >> *item;
				MenuItemDAO::saveMenuItem(db, item, r->getID());
				r->addMenuItem(item);
				cout << "changes saved!" << endl << endl;
			}else{
				item= new DrinkItem();
				item->setKind(type);
				cout << "Enter details of item: (id/name/description/price/preparation time in minute/volume/availability(yes/no))" << endl;
				cin >> *item;
				MenuItemDAO::saveMenuItem(db, item, r->getID());
				r->addMenuItem(item);
				cout << "changes saved!" << endl << endl;
			}
			break;
		}
		case 2: {
			int id;
			cout << "Enter ID of the item you want to remove: ";
			cin >> id;
			MenuItemDAO::deleteMenuItem(db, id);
			r->removeItem(id);
			cout << "changes saved!" << endl << endl;
			break;
		}
	}
}