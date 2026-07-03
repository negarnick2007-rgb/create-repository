#include <iostream>
#include "Customer.h"
#include "NormalLevel.h"

using namespace std;

Customer::Customer(int id) : customerID(id), points(0), coupons(0)
{
    level = new NormalLevel();
}

Customer::Customer(int id, int points, MembershipLevel* level, int coupons): customerID(id), points(points), level(level), coupons(coupons){}

Customer::~Customer()
{
    delete level;
}

int Customer::getCustomerID() const 
{
	return customerID;
}

int Customer::getPoints() const 
{
	return points;
}

MembershipLevel* Customer::getLevel() const 
{
	return level;
}

int Customer::getCoupons() const 
{
	return coupons;
}

void Customer::addPoints(int orderAmount)
{
    int earned = level->getEarnedPoints(orderAmount);
    points= points + earned;

    MembershipLevel* upgraded= level->checkUpgrade(points);
    if(upgraded != nullptr){
        cout << "Congratulations! Your membership level has been upgraded to " << upgraded->getLevelName() << "!" << endl;
        delete level;
        level= upgraded;
    }
}

void Customer::deductPoints(int orderAmount)
{
    points= points - orderAmount;
    if(points < 0){
    	points= 0;
	}
    MembershipLevel* downgraded= level->checkDowngrade(points);
    
    if(downgraded != nullptr){
        cout << "Your membership level has been downgraded to " << downgraded->getLevelName() << "." << endl;
        delete level;
        level= downgraded;
    }
}

void Customer::setLevel(MembershipLevel* newlevel)
{
    delete level;
    level= newlevel;
}

void Customer::useCoupon()
{
    if(coupons > 0){
    	coupons--;
	}
}

void Customer::addCoupons()
{
    coupons= coupons + level->getCouponCount();
}

void Customer::setPoints(int points)
{
	this->points= points;
}