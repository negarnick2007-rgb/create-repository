#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "MembershipLevel.h"

class Customer{
	private:
    	int customerID;
    	int points;
    	MembershipLevel* level;
    	int coupons;

	public:
    	Customer(int id);
    	Customer(int id, int points, MembershipLevel* level, int coupons);
    	~Customer();
    	int getCustomerID() const;
    	int getPoints() const;
    	MembershipLevel* getLevel() const;
    	int getCoupons() const;
    	void addPoints(int orderAmount);
    	void deductPoints(int orderAmount);
    	void setLevel(MembershipLevel* level);
    	void useCoupon();
    	void addCoupons();
    	void setPoints(int points); //for changing by site manager
};

#endif