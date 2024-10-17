#ifndef BATTERY_CHECK_H
#define BATTERY_CHECK_H

#include "battery.h"

bool batteryCheck(float temperature, float soc, float chargeRate);
void printWarning(const RangeResult& result);

#endif // BATTERY_CHECK_H
