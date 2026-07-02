#ifndef SILVERLEVEL_H
#define SILVERLEVEL_H
#include <string>
#include "MembershipLevel.h"

using namespace std;

class SilverLevel : public MembershipLevel{
	public:
    	string getLevelName() const override;
    	int getPointRange() const override;
    	int getEarnedPoints(double orderAmount) const override;
    	double getFinalPrice(double basePrice) const override;
    	double getShippingCost(double baseShipping) const override;
    	int getCouponCount() const override;
    	MembershipLevel* checkUpgrade(int Points) const override;
    	MembershipLevel* checkDowngrade(int Points) const override;
};

#endif