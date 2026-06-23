#include <iostream>
#include <string>
#include "VipLevel.h"
#include "GoldLevel.h"

using namespace std;

string VipLevel::getLevelName() const 
{
	return "VIP";
}

int VipLevel::getPointRange() const 
{
	return 700;
}

int VipLevel::getEarnedPoints(double orderAmount) const
{
    return (int)(orderAmount * 2.0);
}

double VipLevel::getFinalPrice(double basePrice) const
{
    return basePrice * 0.85;
}

double VipLevel::getShippingCost(double baseShipping) const
{
    return 0.0;
}

int VipLevel::getCouponCount() const 
{
	return 3;
}

MembershipLevel* VipLevel::checkUpgrade(int Points) const
{
    return nullptr;
}

MembershipLevel* VipLevel::checkDowngrade(int Points) const
{
    if(Points < 700){
    	return new GoldLevel();
	}
    return nullptr;
}