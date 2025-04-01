#include "mbed.h"
#include "arm_book_lib.h"

// Hardware connections
AnalogIn tempSensor(A0);
DigitalOut heaterLED(D2);



// Temperature thresholds
#define TEMP_LOW 10.0
#define TEMP_HIGH 20.0

void systemInit() {
    heaterLED = OFF;
}
//Checks Temperature reading and turn on/off heater
void checkTemperature() {
    float temp = tempSensor.read() * 3.3 * 100.0; // Convert to Celsius


    if (temp < TEMP_LOW) { //if the temp is below threshold it turns on heater
        heaterLED = ON;
    } 
    else if (temp > TEMP_HIGH) { //if the temp is below threshold it turns off heater
        heaterLED = OFF;
    }
}

int main() {
    systemInit();

    while (true) {
        checkTemperature();
    }
}
