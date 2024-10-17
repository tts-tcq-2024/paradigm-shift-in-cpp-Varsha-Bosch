#ifndef BATTERY_H
#define BATTERY_H

#include <string>
using namespace std;

struct RangeResult {
    bool inRange;
    string message;
};

RangeResult isParametersInRange(float value, float min, float max, const string& argument);
RangeResult isChargeRateOk(float chargeRate);

#endif // BATTERY_H
