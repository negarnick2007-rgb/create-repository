#ifndef VIPLEVEL_H
#define VIPLEVEL_H
#include <string>
#include "MembershipLevel.h"

using namespace std;

class VipLevel : public MembershipLevel{
	public:
    	string getLevelName() const override;
	    int getPointRange() const override;
    	int getEarnedPoints(double orderAmount) const override;
    	double getFinalPrice(double basePrice) const override;
    	double getShippingCost(double baseShipping) const override;
    	int getCouponCount() const override;
    	MembershipLevel* checkUpgrade(int Points) const override;
    	MembershipLevel* checkDowngrade(int Points) const override;
    	int getNextLevelP() const override;
};

#endif