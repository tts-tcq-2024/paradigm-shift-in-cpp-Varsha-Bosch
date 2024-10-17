#include "battery.h"
#include "battery_check.h"
#include <assert.h>
#include <iostream>
using namespace std;

int main() {
    // Test temperature in range with warnings
    RangeResult tempResult1 = isParametersInRange(5, 0, 45, "Temperature");
    assert(tempResult1.inRange == true);
    assert(tempResult1.message.find("Warning") != string::npos);  // Warning expected

    // Test temperature out of range
    RangeResult tempResult2 = isParametersInRange(-5, 0, 45, "Temperature");
    assert(tempResult2.inRange == false);
    assert(tempResult2.message.find("too low") != string::npos);

    // Test SoC warnings
    RangeResult socResult1 = isParametersInRange(22, 20, 80, "State of Charge");
    assert(socResult1.inRange == true);
    assert(socResult1.message.find("Warning") != string::npos);  // Warning expected

    // Test charge rate warnings
    RangeResult chargeResult1 = isChargeRateOk(0.75);
    assert(chargeResult1.inRange == true);
    assert(chargeResult1.message.find("Warning") != string::npos);  // Warning expected

    // Test charge rate out of range
    RangeResult chargeResult2 = isChargeRateOk(0.9);
    assert(chargeResult2.inRange == false);
    assert(chargeResult2.message.find("out of range") != string::npos);

    cout << "All tests passed!" << endl;
    return 0;
}
