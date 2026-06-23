#include <iostream>
#include <string>
#include "NormalLevel.h"
#include "SilverLevel.h"

using namespace std;

string NormalLevel::getLevelName() const 
{
	return "Normal";
}

int NormalLevel::getPointRange() const 
{
	return 0;
}

int NormalLevel::getEarnedPoints(double orderAmount) const
{
    return (int)(orderAmount * 1.0);
}

double NormalLevel::getFinalPrice(double basePrice) const
{
    return basePrice;
}

double NormalLevel::getShippingCost(double baseShipping) const
{
    return baseShipping;
}

int NormalLevel::getCouponCount() const 
{
	return 0;
}

MembershipLevel* NormalLevel::checkUpgrade(int Points) const
{
    if(Points >= 100){
    	return new SilverLevel();
	}
    return nullptr;
}

MembershipLevel* NormalLevel::checkDowngrade(int Points) const
{
    return nullptr;
}