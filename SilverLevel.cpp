#include <iostream>
#include <string>
#include "SilverLevel.h"
#include "NormalLevel.h"
#include "GoldLevel.h"

using namespace std;

string SilverLevel::getLevelName() const 
{
	return "Silver";
}

int SilverLevel::getPointRange() const 
{
	return 100;
}

int SilverLevel::getEarnedPoints(double orderAmount) const
{
    return (int)(orderAmount * 1.2);
}

double SilverLevel::getFinalPrice(double basePrice) const
{
    return basePrice * 0.95;
}

double SilverLevel::getShippingCost(double baseShipping) const
{
    return baseShipping * 0.75;
}

int SilverLevel::getCouponCount() const 
{
	return 1;
}

MembershipLevel* SilverLevel::checkUpgrade(int Points) const
{
    if(Points >= 300){
    	return new GoldLevel();
	}
    return nullptr;
}

MembershipLevel* SilverLevel::checkDowngrade(int Points) const
{
    if(Points < 100){
    	return new NormalLevel();
	}
    return nullptr;
}