#include "battery.h"
#include "battery_check.h"
#include <iostream>
using namespace std;

bool isMax(float value, float maxValue) {
    return value > maxValue;
}

bool isMin(float value, float minValue) {
    return value < minValue;
}

void checkLowWarning(float value, float min, float max, const string& argument, string& message) {
    float tolerance = 0.05 * max;
    if (value > min && value <= min + tolerance) {
        message += "Warning: " + argument + " approaching discharge limit.\n";
    }
}

void checkHighWarning(float value, float max, const string& argument, string& message) {
    float tolerance = 0.05 * max;
    if (value >= max - tolerance && value < max) {
        message += "Warning: " + argument + " approaching peak-charge limit.\n";
    }
}

RangeResult isParametersInRange(float value, float min, float max, const string& argument) {
    RangeResult result = {true, ""};
    
    checkLowWarning(value, min, max, argument, result.message);
    checkHighWarning(value, max, argument, result.message);

    // Check for low and high bounds
    if (isMin(value, min)) {
        result.message += argument + " too low.\n";
        result.inRange = false;
    }
    if (isMax(value, max)) {
        result.message += argument + " too high.\n";
        result.inRange = false;
    }

    return result;
}

RangeResult isChargeRateOk(float chargeRate) {
    RangeResult result = {true, ""};
    checkLowWarning(chargeRate, 0, 0.8, "Charge Rate", result.message);
    checkHighWarning(chargeRate, 0.8, "Charge Rate", result.message);
    
    if (isMax(chargeRate, 0.8)) {
        result.message += "Charge Rate out of range.\n";
        result.inRange = false;
    }
    return result;
}

bool batteryCheck(float temperature, float soc, float chargeRate) {
    // Validate parameters individually
    RangeResult temperatureResult = isParametersInRange(temperature, 0, 45, "Temperature");
    RangeResult socResult = isParametersInRange(soc, 20, 80, "State of Charge");
    RangeResult chargeRateResult = isChargeRateOk(chargeRate);

    // Print warnings for each result
    printWarning(temperatureResult);
    printWarning(socResult);
    printWarning(chargeRateResult);

    // Return true only if all checks are in range
    return temperatureResult.inRange && socResult.inRange && chargeRateResult.inRange;
}

void printWarning(const RangeResult& result) {
    if (!result.message.empty()) {
        cout << result.message;
    }
}
