#include <iostream>
#include <string>
#include "GoldLevel.h"
#include "SilverLevel.h"
#include "VipLevel.h"

using namespace std;

string GoldLevel::getLevelName() const 
{
	return "Gold";
}

int GoldLevel::getPointRange() const 
{
	return 300;
}

int GoldLevel::getEarnedPoints(double orderAmount) const
{
    return (int)(orderAmount * 1.5);
}

double GoldLevel::getFinalPrice(double basePrice) const
{
    return basePrice * 0.90;
}

double GoldLevel::getShippingCost(double baseShipping) const
{
    return baseShipping * 0.5;
}

int GoldLevel::getCouponCount() const
{
	return 2;
}

MembershipLevel* GoldLevel::checkUpgrade(int Points) const
{
    if(Points >= 700){
    	return new VipLevel();
	}
    return nullptr;
}

MembershipLevel* GoldLevel::checkDowngrade(int Points) const
{
    if(Points < 300){
    	return new SilverLevel();
	}
    return nullptr;
}

int GoldLevel::getNextLevelP() const
{
	return 700;
}