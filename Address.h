#ifndef ADDRESS_H
#define ADDRESS_H
#include <string>
#include <iostream>

using namespace std;

class Address{
	private:
		string city;
		string street;
		int placeNumber;
	public:
		Address();
		void printAddress() const;
		
		string getCity() const;
		string getStreet() const;
		int getPlaceNumber() const;
		
		void setCity(string city);
		void setStreet(string street);
		void setPlaceNumber(int num);
		
		friend istream& operator >> (istream& input, Address& add);
};

#endif