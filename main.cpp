#include "mbed.h"
#include "arm_book_lib.h"

// Hardware connections
AnalogIn tempSensor(A0);  // LM35 connected to Analog Pin A0
DigitalOut heaterLED(D2); // LED connected to Digital Pin D2

// Temperature threshold
#define TEMP_THRESHOLD 25.0  // The temperature threshold to turn on the heater (LED)

// Initialize system
void systemInit() {
    heaterLED = OFF; // Initialize heater LED to OFF
}

// Checks temperature reading and turns heater on/off
void checkTemperature() {
    // LM35: 10mV per °C, and the sensor output is scaled to the reference voltage (3.3V).
    // The formula is: temperature (°C) = (Vout * 100)
    float voltage = tempSensor.read() * 3.3;  // Read the voltage (0 to 3.3V)
    float temp = voltage * 100.0;  // Convert voltage to Celsius (LM35 outputs 10mV per °C)

    printf("Temp: %.2f°C\n", temp);  // Print the current temperature

    // If temperature exceeds the threshold, turn on the heater (LED)
    if (temp < TEMP_THRESHOLD) {
        heaterLED = ON;  // Turn on the LED (Heater on)
    } 
    // If temperature is below the threshold, turn off the heater (LED)
    else {
        heaterLED = OFF;  // Turn off the LED (Heater off)
    }
}

int main() {
    systemInit();  // Initialize the system

    while (true) {
        checkTemperature();  // Check the temperature and adjust the heater state
        wait(1);  // Wait for 1 second before checking again (reduce CPU load)
    }
}
