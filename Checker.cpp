#include <assert.h>
#include <iostream>
using namespace std;

bool checkForOutOfRange(float temp) {
  if (temp < 0 || temp > 45) {
    cout << "Temperature out of range!\n";
    return false;
  }
  return true;
}

bool checkForStateOfCharge(float soc) {
  if (soc < 20 || soc > 80) {
    cout << "State of Charge out of range!\n";
    return false;
  }
  return true;
}

bool checkForChargeRate(float rate) {
  if (rate > 0.8) {
    cout << "Charge Rate out of range!\n";
    return false;
  }
  return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool tempOk = checkForOutOfRange(temperature);
  bool socOk = checkForStateOfCharge(soc);
  bool chargeRateOk = checkForChargeRate(chargeRate);

  return tempOk && socOk && chargeRateOk;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
  assert(batteryIsOk(-1, 15, 0) == false);
  assert(batteryIsOk(10,10,0.7)== false);
  assert(batteryIsOk(9, 25, 0.9) == false);
}
