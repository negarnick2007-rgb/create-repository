#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <string>
#include <vector>

#include "Address.h"

using std::string;
using std::vector;

class MenuItem;
class FoodItem;
class DrinkItem;

class Restaurant {
	private:
		int id;
		string name;
		string phoneNumber;
		string description;
		bool active;
		Address address;
		vector <MenuItem*> items;
		int managerID;
	public:
		Restaurant();
		~Restaurant();
		
		int getID() const;
		string getPhoneNumber() const;
		string getName() const;
		string getDescription() const;
		bool isActive() const;
		int getManagerID() const;
		int getItemCount() const;
		const Address& getAddress() const;
		
		void setManagerID(int id);
		void changeAddress(Address& address);
		void addMenuItem(MenuItem* item);
		void removeItem(int itemId);
		void displayMenu() const;
		void printRestaurantInfo() const;
		void setActive(bool active);
		void setID(int id);
		void setName(string name);
		void setPhoneNumber(string phn);
		void setDescription(string des);
		MenuItem* getItemById(int itemID) const;
		
		friend istream& operator >> (istream& input, Restaurant& r);
};

#endif