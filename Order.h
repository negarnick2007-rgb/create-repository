#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include <string>

using namespace std;

class MenuItem;

class Order{
	private:
		static int orderNumber;
		vector <MenuItem*> items;
		double totalPrice;
		string orderStatus;
		int customerID;
		int restaurantID;
		int orderID;
	public:
		Order(int id, int resId);
		int getOrderId() const;
		string getStatus() const;
		double getTotalPrice() const;
		int getItemCount() const;
		bool finalizePayment(double totalPrice);
		int getCustomerID() const;
		int getRestaurantID() const;
		int static getOrderCount();
		const vector<MenuItem*>& getItems() const;
		
		void setOrderID(int id);
		void setStatus(string status);
		void addItemToOrder(MenuItem* item);
		void removeItem(int itemId);
		void displayOrder() const;
		void clearOrder(int newRestaurantID);
		void setTotalPrice(double price);
		void loadItem(MenuItem* item);
};

#endif