#ifndef MEMBERSHIPLEVEL_H
#define MEMBERSHIPLEVEL_H
#include <string>
using namespace std;

class MembershipLevel{
	public:
    	virtual ~MembershipLevel() = default;
    	virtual string getLevelName() const = 0;
    	virtual int getPointRange() const = 0;
    	virtual int getEarnedPoints(double orderAmount) const = 0;
    	virtual double getFinalPrice(double basePrice) const = 0;
    	virtual double getShippingCost(double baseShipping) const = 0;
    	virtual int getCouponCount() const = 0;
    	virtual MembershipLevel* checkUpgrade(int Points) const = 0;
    	virtual MembershipLevel* checkDowngrade(int Points) const = 0;
    	virtual int getNextLevelP() const = 0; //for showing next level points range
};

#endif