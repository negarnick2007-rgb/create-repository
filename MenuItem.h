#ifndef MENUITEM_H
#define MENUITEM_H
#include <string>

using namespace std;

class MenuItem{
	private:
		string kind;
		int id;
		string name;
		string description;
		double price;
		int preparationTime;
		bool available;
	public:
		MenuItem();
		virtual ~MenuItem();
		
		string getKind() const;
		int getID() const;
		string getName() const;
		string getDescription() const;
		double getPrice() const;
		int getPrepTime() const;
		bool getAvailable() const;
		
		virtual void displayDetails() const= 0;
		virtual void readItem()= 0;
		friend istream& operator >> (istream& input, MenuItem& item);
		
		void setKind(string kind);
		void setID(int id);
		void setName(string newName);
		void setPrice(double newPrice);
		void setDescription(string newDescription);
		void setAvailable(bool available);
		void setPrepTime(int minute);
};

#endif