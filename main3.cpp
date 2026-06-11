#include <iostream>
#include <vector>
#include <limits>
#include "Restaurant.h"
#include "Order.h"
#include "CustomerManaging.h"
#include "RestaurantManaging.h"
#include "SiteManaging.h"
#include "Database.h"
#include "RestaurantDAO.h"
#include "OrderDAO.h"

using namespace std;

int main()
{
	if(!Database::init("restaurant.db")){
		cerr << "Error in opening the database" << endl;
		return 1;
	}
	sqlite3* db= Database::getDB();
	
    int type;
    
    vector<Restaurant*> allRestaurants;
    vector<Order*> allOrders;

	RestaurantDAO::loadAllRestaurants(db, allRestaurants);
	OrderDAO::loadAllOrders(db, allOrders);
	
    while (true) {
    	cout << "Do you want to login as which user?" << endl << endl;
        cout << "1. Customer" << endl;
        cout << "2. Manager of restaurant" << endl;
        cout << "3. Manager of site" << endl;
        cout << "0. Exit Program" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> type)) {
            cerr << "Invalid choice! Please enter another number..." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (type == 0) {
            cout << "Cleaning up and exiting..." << endl;
            deleteAllOrders(allOrders);
            deleteAllRestaurants(allRestaurants);
            Database::close();
            break; 
        }
        
        if (type == 1) {
            cout << "\n============ The List Of All Restaurants ============" << endl << endl;
            showAllRestaurants(allRestaurants);
            
            int restaurantID, customerID;
            cout << "Enter your ID and the restaurant ID: ";
            while(!(cin >> customerID >> restaurantID)){
            	cerr << "Invalid choice! Please enter another numbers..." << endl << endl;
            	cin.clear();
            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
            
            Order* order = buildOrder(customerID, restaurantID);
            
            bool backToMain = false;
            while (!backToMain) {
                int num1;
                cout << "\n--- CUSTOMER MENU ---" << endl;
                cout << "1. Adding an item to your order" << endl;
                cout << "2. Removing an item from your order" << endl;
                cout << "3. Showing your order histories" << endl;
                cout << "4. Continue and place the order" << endl;
                cout << "5. Make the order empty and set again" << endl;
                cout << "0. Back to main menu" << endl;
                cout << "Choose your operation: ";
                
                cin >> num1;
                while (!(num1 >= 0 && num1 <= 5)) {
                    cerr << "Invalid choice! please try again..." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> num1;
                }

                switch (num1) {
                    case 1:
                        addToOrder(order, restaurantID, allRestaurants);
                        break;
                    case 2:
                        removeFromOrder(order);
                        break;
                    case 3:
                        ordersHistory(customerID, allOrders);
                        break;
                    case 4:
                        paymentManaging(db, order, allOrders);
                        backToMain = true; 
                        break;
                    case 5:
                    {
                        int newID;
                        cout << "Enter new restaurant ID: ";
                        while(!(cin >> newID)){
                        	cerr << "Please enter a numeric ID: ";
                        	cin.clear();
                        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
                        order->clearOrder(newID);
                        cout << "Order reset to Restaurant ID: " << newID << endl;
                        break;
                    }
                    case 0:
                        backToMain = true; 
                        break;
                }
            }
        }
        
        else if (type == 2) {
            int restaurantID, managerID;
            cout << "Enter your ID and your restaurant ID: ";
            while(!(cin >> managerID >> restaurantID)){
            	cerr << "Invalid choice! Please enter another numbers..." << endl << endl;
            	cin.clear();
            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
            
            Restaurant* r = FindMyRestaurant(restaurantID, managerID, allRestaurants);
            if (r == nullptr) {
                continue; 
            }

            bool backToMain = false;
            while (!backToMain) {
                showMyRestaurant(r);
                cout << "\n--- RESTAURANT MANAGER MENU ---" << endl;
                cout << "1. Edit order status" << endl;
                cout << "2. Show restaurant orders" << endl;
                cout << "3. Change restaurant address" << endl;
                cout << "4. Change restaurant name" << endl;
                cout << "5. Change restaurant phone number" << endl;
                cout << "6. Change restaurant description" << endl;
                cout << "7. Change manager ID" << endl;
                cout << "8. Edit details of menu items" << endl;
                cout << "9. Edit restaurant menu" << endl;
                cout << "0. Back to Main Menu" << endl;
                cout << "Choose your operation: ";

                int num1;
                cin >> num1;
                while (!(num1 >= 0 && num1 <= 9)) {
                    cerr << "Invalid operation! Try again" << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> num1;
                }

                switch (num1) {
                    case 1: EditOrderStatus(db, r, allOrders); break;
                    case 2: showMyRestaurantOrders(r, allOrders); break;
                    case 3: changeRestaurantAddress(db, r); break;
                    case 4: changeRestaurantName(db, r); break;
                    case 5: changeRestaurantPhone(db, r); break;
                    case 6: changeRestaurantDescripe(db, r); break;
                    case 7: changeManagerID(db, r); break;
                    case 8: EditItemDetails(db, r); break;
                    case 9: EditRestaurantMenu(db, r); break;
                    case 0: backToMain = true; break;
                }
            }
        }

        else if (type == 3) {
            bool backToMain = false;
            while (!backToMain) {
                cout << "\n--- SITE MANAGER MENU ---" << endl;
                cout << "1. Add a new restaurant" << endl;
                cout << "2. Remove a restaurant" << endl;
                cout << "3. Change a restaurant's activity" << endl;
                cout << "4. Show the sales statistics" << endl;
                cout << "5. Delete order from the site" << endl;
                cout << "0. Back to Main Menu" << endl;
                cout << "Choose your operation: ";

                int num1;
                cin >> num1;
                while (!(num1 >= 0 && num1 <= 5)) {
                    cerr << "Invalid operation! Try again..." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> num1;
                }

                switch (num1) {
                    case 1: addNewRestaurant(db, allRestaurants); break;
                    case 2: removeRestaurant(db, allRestaurants); break;
                    case 3: changeRestaurantActivity(db, allRestaurants); break;
                    case 4: SalesStatistics(allOrders); break;
                    case 5: {
                    	cout << "Enter the ID of the order you want to delete: ";
                    	int id;
                    	while(!(cin >> id)){
                    		cerr << "Pleasr enter a numeric ID: ";
                    		cin.clear();
                    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
                    	cout << "Are you sure about your decision? No one will see it again! Yes/No: ";
                    	string decision;
                    	cin >> decision;
                    	if(decision == "Yes" || decision == "yes"){
                    		bool rm= OrderDAO::deleteOrder(db, id);
                    		if(rm){
                    			deleteOneOrder(allOrders, id); // just for delete one special order from vector
                    			cout << "Order deleted successfully!" << endl << endl;
							}
						}else{
							cerr << "Operation failed! Try again..." << endl << endl;
						}
						break;
					}
                    case 0: backToMain = true; break;
                }
            }
        }
        else {
            cerr << "Invalid choice! Please try again." << endl << endl;
        }
    } 
	
    return 0;
}