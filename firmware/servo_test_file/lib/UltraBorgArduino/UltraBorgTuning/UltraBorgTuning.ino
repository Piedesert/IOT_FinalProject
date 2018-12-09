// This is the UltraBorg tuning example for setting up the correct servo ranges using an Arduino
// See https://www.piborg.org/ultraborg/tuning#arduino for operational instructions.
//
// Before talking to the UltraBorg for the first time we check if we can see the board properly by 
// trying to call UbInit(), if it fails the LED on the Arduino will flash until it can see the board.
// 
// The pins on one of the UltraBoreg six-pin headers need to be connected as follows:
// Pin 1 -> IOREF       The voltage reference for the Arduino I/O, it is marked with a 1
// Pin 2 -> Unused      May be left disconnected
// Pin 3 -> SDA         I2C data line, used for communications
// Pin 4 -> 5V          Power for the PIC, otherwise known as 5v
// Pin 5 -> SCL         I2C clock line, used for communications
// Pin 6 -> GND         Ground, otherwise known as 0v, reference for all other lines
//
// The pins are arranged:
// 1: IOREF   2: Unused
// 3: SDA     4: 5V
// 5: SCL     6: GND
//
// The SDA and SCL connections vary between Arduinos and may not be clearly marked,
// refer to the table below
//
// Board            SDA     SCL
// -----------------------------
// Uno              A4      A5
// Ethernet         A4      A5
// Mega2560         20      21
// Leonardo         2       3
// Due              SDA1    SCL1
//
// If the LED on the Arduino will not stop flashing check the UltraBorg is connected properly (pins as listed above).
// If you are connected and powered but you still cannot get the example to work then uncomment line 59 to
// get the example to scan the I2C bus for the boards address itself, this makes the code slightly larger but
// allows a single board attached to work with any set address.
// See UbSetNewAddress if you wish to change the I2C address used by the UltraBorg.
// If you do change the I2C address change line 59 to set the new address, if using 0x10 for example:
//     Ubi2cAddress = 0x10;
// This way you may also connect multiple UltraBorgs by daisy-chaining them after giving each a unique address, 
// simply set the required address to UbAddress before calling a Ub* function to talk to the required board.
//
// This example has a binary sketch size of 10,974 bytes when compiled for an Arduino Uno using IDE v1.0.5-r2

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

#include <Wire.h>               // The I2C library
#include "UltraBorg.h"          // The UltraBorg library

// Runs once
void setup()
{
    Wire.begin();               // Join the I2C bus (we will be acting as master)
    pinMode(led, OUTPUT);       // Initialise the LED pin as an output
    digitalWrite(led, LOW);     // Turn the LED off by making the voltage LOW
    Serial.begin(9600);         // open the serial port at 9600 bps

    // Get the first address of an UltraBorg attached to the I2C bus
    //Ubi2cAddress = UbScanForAddress(0);
}

// Function to set a servo position
void setServo(int servo, int position) {
    switch (servo) {
        case 1: UbCalibrateServoPosition1((unsigned int)position); break;
        case 2: UbCalibrateServoPosition2((unsigned int)position); break;
        case 3: UbCalibrateServoPosition3((unsigned int)position); break;
        case 4: UbCalibrateServoPosition4((unsigned int)position); break;
    }
}

// Runs looped after setup
void loop()
{
    int servo;
    int position;
    unsigned int min;
    unsigned int max;
    unsigned int start;
    char command;

    Serial.println("");
    Serial.println("Check for UltraBorg...");

    // Check we can see the UltraBorg
    if (UbInit()) {
        Serial.println("UltraBorg connected ^_^");
    } else {
        // Cannot find our board, flash the LED then try again
        Serial.println("No UltraBorg!");
        digitalWrite(led, HIGH);    // Turn the LED on
        delay(250);                 // Delay for a 1/4 second
        digitalWrite(led, LOW);     // Turn the LED off
        delay(250);                 // Delay for a 1/4 second
        return;                     // Skip to the end of the function
    }

    // Get the servo to work with
    Serial.println("Which servo do you want to tune [1-4] ?");
    while (Serial.available() == 0) delay(100);
    servo = Serial.parseInt();
    if ((servo < 1) || (servo > 4)) {
        Serial.println("The servo number must be between 1 and 4!");
        return;
    }
    Serial.print("Tuning servo #");
    Serial.println(servo);
    Serial.println("");

    // Show the loaded limits
    switch (servo) {
        case 1: min = UbGetServoMinimum1(); break;
        case 2: min = UbGetServoMinimum2(); break;
        case 3: min = UbGetServoMinimum3(); break;
        case 4: min = UbGetServoMinimum4(); break;
    }
    switch (servo) {
        case 1: max = UbGetServoMaximum1(); break;
        case 2: max = UbGetServoMaximum2(); break;
        case 3: max = UbGetServoMaximum3(); break;
        case 4: max = UbGetServoMaximum4(); break;
    }
    switch (servo) {
        case 1: start = UbGetServoStartup1(); break;
        case 2: start = UbGetServoStartup2(); break;
        case 3: start = UbGetServoStartup3(); break;
        case 4: start = UbGetServoStartup4(); break;
    }
    Serial.print("Current settings for servo #");
    Serial.println(servo);
    Serial.print("Minimum: ");
    Serial.println(min);
    Serial.print("Startup: ");
    if ((start == 0x0000) || (start == 0xFFFF)) {
        Serial.print("unset, will use ");
        Serial.println((min + max) >> 1);
    } else {
        Serial.println(start);
    }
    Serial.print("Maximum: ");
    Serial.println(max);
    Serial.println("");

    // Move to central
    Serial.println("Moving to 3000");
    position = 3000;
    setServo(servo, position);

    // Loop to set the maximum
    Serial.println("");
    Serial.print("Setting the maximum for servo #");
    Serial.println(servo);
    Serial.println("");
    Serial.println("Increase the position 100 at a time until the servo no longer moves");
    Serial.println("then decrease the position 10 at a time until the servo moves again");
    Serial.println("Send 'S' when done");
    Serial.println("");
    while (true) {
        // Get the next command
        Serial.print("Position? ");
        while (Serial.available() == 0) delay(100);
        command = Serial.peek();
        if ((command == 'S') || (command == 's')) {
            // Save the maximum position
            Serial.println(command);
            Serial.read();
            switch (servo) {
                case 1: UbSetServoMaximum1((unsigned int)position); break;
                case 2: UbSetServoMaximum2((unsigned int)position); break;
                case 3: UbSetServoMaximum3((unsigned int)position); break;
                case 4: UbSetServoMaximum4((unsigned int)position); break;
            }
            // Read back the maximum position
            Serial.println("");
            Serial.print("Saved - servo #");
            Serial.print(servo);
            Serial.print(" maximum = ");
            switch (servo) {
                case 1: max = UbGetServoMaximum1(); break;
                case 2: max = UbGetServoMaximum2(); break;
                case 3: max = UbGetServoMaximum3(); break;
                case 4: max = UbGetServoMaximum4(); break;
            }
            Serial.println(max);
            Serial.println("");
            break;
        } else {
            // Move to the next position
            position = Serial.parseInt();
            Serial.println(position);
            setServo(servo, position);
        }
    }

    // Move to central
    Serial.println("Moving to 3000");
    position = 3000;
    setServo(servo, position);

    // Loop to set the minimum
    Serial.println("");
    Serial.print("Setting the minimum for servo #");
    Serial.println(servo);
    Serial.println("");
    Serial.println("Decrease the position 100 at a time until the servo no longer moves");
    Serial.println("then increase the position 10 at a time until the servo moves again");
    Serial.println("Send 'S' when done");
    Serial.println("");
    while (true) {
        // Get the next command
        Serial.print("Position? ");
        while (Serial.available() == 0) delay(100);
        command = Serial.peek();
        if ((command == 'S') || (command == 's')) {
            // Save the maximum position
            Serial.println(command);
            Serial.read();
            switch (servo) {
                case 1: UbSetServoMinimum1((unsigned int)position); break;
                case 2: UbSetServoMinimum2((unsigned int)position); break;
                case 3: UbSetServoMinimum3((unsigned int)position); break;
                case 4: UbSetServoMinimum4((unsigned int)position); break;
            }
            // Read back the maximum position
            Serial.println("");
            Serial.print("Saved - servo #");
            Serial.print(servo);
            Serial.print(" minimum = ");
            switch (servo) {
                case 1: min = UbGetServoMinimum1(); break;
                case 2: min = UbGetServoMinimum2(); break;
                case 3: min = UbGetServoMinimum3(); break;
                case 4: min = UbGetServoMinimum4(); break;
            }
            Serial.println(min);
            Serial.println("");
            break;
        } else {
            // Move to the next position
            position = Serial.parseInt();
            Serial.println(position);
            setServo(servo, position);
        }
    }

    // Re-read the new limits into the library
    UbInit();

    // Move to central
    Serial.println("Moving to 3000");
    position = 3000;
    setServo(servo, position);

    // Loop to set the minimum
    Serial.println("");
    Serial.print("Setting the startup for servo #");
    Serial.println(servo);
    Serial.println("");
    Serial.print("Change the position to any place between ");
    Serial.print(min);
    Serial.print(" and ");
    Serial.println(max);
    Serial.println("Send 'S' when done");
    Serial.println("");
    while (true) {
        // Get the next command
        Serial.print("Position? ");
        while (Serial.available() == 0) delay(100);
        command = Serial.peek();
        if ((command == 'S') || (command == 's')) {
            // Save the maximum position
            Serial.println(command);
            Serial.read();
            switch (servo) {
                case 1: UbSetServoStartup1((unsigned int)position); break;
                case 2: UbSetServoStartup2((unsigned int)position); break;
                case 3: UbSetServoStartup3((unsigned int)position); break;
                case 4: UbSetServoStartup4((unsigned int)position); break;
            }
            // Read back the maximum position
            Serial.println("");
            Serial.print("Saved - servo #");
            Serial.print(servo);
            Serial.print(" startup = ");
            switch (servo) {
                case 1: start = UbGetServoStartup1(); break;
                case 2: start = UbGetServoStartup2(); break;
                case 3: start = UbGetServoStartup3(); break;
                case 4: start = UbGetServoStartup4(); break;
            }
            Serial.println(start);
            Serial.println("");
            break;
        } else {
            // Move to the next position
            position = Serial.parseInt();
            Serial.println(position);
            setServo(servo, position);
        }
    }
}
