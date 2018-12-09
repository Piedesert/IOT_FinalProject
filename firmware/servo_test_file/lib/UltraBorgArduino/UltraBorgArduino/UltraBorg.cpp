/**************************************/
/********* UltraBorg Library **********/
/**************************************/

// Includes
#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif
#include <Wire.h>               // The I2C library
#include "UltraBorg.h"          // The UltraBorg library constants

// Parameters
byte Ubi2cAddress = UB_DEFAULT_I2C_ADDRESS;     // The I2C address we are currently talking to

// Private memory
byte rdBuffer[UB_I2C_MAX_LEN];                  // Buffer used for reading replies
signed long UbServo1Min = UB_DEFAULT_PWM_MIN;  // The current minimum limit for servo #1
signed long UbServo1Max = UB_DEFAULT_PWM_MAX;  // The current maximum limit for servo #1
signed long UbServo2Min = UB_DEFAULT_PWM_MIN;  // The current minimum limit for servo #2
signed long UbServo2Max = UB_DEFAULT_PWM_MAX;  // The current maximum limit for servo #2
signed long UbServo3Min = UB_DEFAULT_PWM_MIN;  // The current minimum limit for servo #3
signed long UbServo3Max = UB_DEFAULT_PWM_MAX;  // The current maximum limit for servo #3
signed long UbServo4Min = UB_DEFAULT_PWM_MIN;  // The current minimum limit for servo #4
signed long UbServo4Max = UB_DEFAULT_PWM_MAX;  // The current maximum limit for servo #4

// Private function used to read the reply to GET commands
// Overwrites the contents of rdBuffer
void ReadInReply(void) {
    int idx;
    Wire.requestFrom(Ubi2cAddress, (byte)UB_I2C_MAX_LEN);
    for (idx = 0; idx < UB_I2C_MAX_LEN; ++idx) {
        if (Wire.available()) {
            rdBuffer[idx] = Wire.read();
        } else {
            rdBuffer[idx] = 0;
        }
    }
}

/**************************************/
/******** UltraBorg Functions *********/
/**************************************/

/***** General functions *****/

// Check we are talking to the UltraBorg
bool UbInit(void) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_ID);
    Wire.endTransmission();
    ReadInReply();

    if (rdBuffer[1] == UB_I2C_ID_SERVO_USM) {
        // Read in the limits for this board
        UbServo1Min = UbGetServoMinimum1();
        UbServo1Max = UbGetServoMaximum1();
        UbServo2Min = UbGetServoMinimum2();
        UbServo2Max = UbGetServoMaximum2();
        UbServo3Min = UbGetServoMinimum3();
        UbServo3Max = UbGetServoMaximum3();
        UbServo4Min = UbGetServoMinimum4();
        UbServo4Max = UbGetServoMaximum4();

        return true;
    } else {
        return false;
    }
}

/***** Servo functions *****/

// Sets the drive position for servo output #1
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition1(float position) {
    float powerOut = (position + 1.0) / 2.0;
    unsigned int pwmDuty = (unsigned int)((powerOut * (UbServo1Max - UbServo1Min)) + UbServo1Min);
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM1);
    Wire.write((byte)((pwmDuty >> 8) & 0xFF));
    Wire.write((byte)(pwmDuty & 0xFF));
    Wire.endTransmission();
}

// Sets the drive position for servo output #2
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition2(float position) {
    float powerOut = (position + 1.0) / 2.0;
    unsigned int pwmDuty = (unsigned int)((powerOut * (UbServo2Max - UbServo2Min)) + UbServo2Min);
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM2);
    Wire.write((byte)((pwmDuty >> 8) & 0xFF));
    Wire.write((byte)(pwmDuty & 0xFF));
    Wire.endTransmission();
}

// Sets the drive position for servo output #3
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition3(float position) {
    float powerOut = (position + 1.0) / 2.0;
    unsigned int pwmDuty = (unsigned int)((powerOut * (UbServo3Max - UbServo3Min)) + UbServo3Min);
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM3);
    Wire.write((byte)((pwmDuty >> 8) & 0xFF));
    Wire.write((byte)(pwmDuty & 0xFF));
    Wire.endTransmission();
}

// Sets the drive position for servo output #4
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition4(float position) {
    float powerOut = (position + 1.0) / 2.0;
    unsigned int pwmDuty = (unsigned int)((powerOut * (UbServo4Max - UbServo4Min)) + UbServo4Min);
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM4);
    Wire.write((byte)((pwmDuty >> 8) & 0xFF));
    Wire.write((byte)(pwmDuty & 0xFF));
    Wire.endTransmission();
}

// Gets the drive position for servo output #1
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition1(void) {
    unsigned int pwmDuty;
    float powerOut;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM1);
    Wire.endTransmission();
    ReadInReply();
    pwmDuty = (rdBuffer[1] << 8) + rdBuffer[2];
    powerOut = ((float)pwmDuty - UbServo1Min) / (UbServo1Max - UbServo1Min);
    return (2.0 * powerOut) - 1.0;
}

// Gets the drive position for servo output #2
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition2(void) {
    unsigned int pwmDuty;
    float powerOut;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM2);
    Wire.endTransmission();
    ReadInReply();
    pwmDuty = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    powerOut = ((float)pwmDuty - UbServo2Min) / (UbServo2Max - UbServo2Min);
    return (2.0 * powerOut) - 1.0;
}

// Gets the drive position for servo output #3
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition3(void) {
    unsigned int pwmDuty;
    float powerOut;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM3);
    Wire.endTransmission();
    ReadInReply();
    pwmDuty = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    powerOut = ((float)pwmDuty - UbServo3Min) / (UbServo3Max - UbServo3Min);
    return (2.0 * powerOut) - 1.0;
}

// Gets the drive position for servo output #4
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition4(void) {
    unsigned int pwmDuty;
    float powerOut;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM4);
    Wire.endTransmission();
    ReadInReply();
    pwmDuty = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    powerOut = ((float)pwmDuty - UbServo4Min) / (UbServo4Max - UbServo4Min);
    return (2.0 * powerOut) - 1.0;
}

/***** Ultrasonic functions *****/

// Gets the filtered distance for ultrasonic module #1 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance1 instead (no filtering)
float UbGetDistance1(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_FILTER_USM1);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
}

// Gets the filtered distance for ultrasonic module #2 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance2 instead (no filtering)
float UbGetDistance2(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_FILTER_USM2);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
}

// Gets the filtered distance for ultrasonic module #3 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance3 instead (no filtering)
float UbGetDistance3(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_FILTER_USM3);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
};

// Gets the filtered distance for ultrasonic module #4 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance4 instead (no filtering)
float UbGetDistance4(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_FILTER_USM4);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
}

// Gets the raw distance for ultrasonic module #1 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance1
float UbGetRawDistance1(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_TIME_USM1);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
}

// Gets the raw distance for ultrasonic module #2 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance2
float UbGetRawDistance2(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_TIME_USM2);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
}

// Gets the raw distance for ultrasonic module #3 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance3
float UbGetRawDistance3(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_TIME_USM3);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
}

// Gets the raw distance for ultrasonic module #4 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance4
float UbGetRawDistance4(void) {
    unsigned int time_us;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_TIME_USM4);
    Wire.endTransmission();
    ReadInReply();
    time_us = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    if (time_us == 65535) time_us = 0;
    return (float)time_us * UB_USM_US_TO_MM;
}

/***** Startup functions *****/

// Gets the startup PWM level for servo output #1
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup1(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_BOOT_1);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the startup PWM level for servo output #2
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup2(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_BOOT_2);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the startup PWM level for servo output #3
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup3(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_BOOT_3);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the startup PWM level for servo output #4
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup4(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_BOOT_4);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Sets the startup PWM level for servo output #1
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup1(unsigned int pwmLevel) {
    bool inRange = true;
    if (UbServo1Min < UbServo1Max) {
        // Normal direction
        if (pwmLevel < UbServo1Min) {
            inRange = false;
        } else if (pwmLevel > UbServo1Max) {
            inRange = false;
        }
    } else {
        // Inverted direction
        if (pwmLevel > UbServo1Min) {
            inRange = false;
        } else if (pwmLevel < UbServo1Max) {
            inRange = false;
        }
    }
    if (pwmLevel == UB_PWM_UNSET) {
        // Force to unset behaviour (central)
        inRange = true;
    }

    if (inRange) {
        Wire.beginTransmission(Ubi2cAddress);
        Wire.write(UB_COMMAND_SET_PWM_BOOT_1);
        Wire.write((byte)((pwmLevel >> 8) & 0xFF));
        Wire.write((byte)(pwmLevel & 0xFF));
        Wire.endTransmission();
        delay(UB_DELAY_AFTER_EEPROM);
    }
    return inRange;
}

// Sets the startup PWM level for servo output #2
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup2(unsigned int pwmLevel) {
    bool inRange = true;
    if (UbServo2Min < UbServo2Max) {
        // Normal direction
        if (pwmLevel < UbServo2Min) {
            inRange = false;
        } else if (pwmLevel > UbServo2Max) {
            inRange = false;
        }
    } else {
        // Inverted direction
        if (pwmLevel > UbServo2Min) {
            inRange = false;
        } else if (pwmLevel < UbServo2Max) {
            inRange = false;
        }
    }
    if (pwmLevel == UB_PWM_UNSET) {
        // Force to unset behaviour (central)
        inRange = true;
    }

    if (inRange) {
        Wire.beginTransmission(Ubi2cAddress);
        Wire.write(UB_COMMAND_SET_PWM_BOOT_2);
        Wire.write((byte)((pwmLevel >> 8) & 0xFF));
        Wire.write((byte)(pwmLevel & 0xFF));
        Wire.endTransmission();
        delay(UB_DELAY_AFTER_EEPROM);
    }
    return inRange;
}

// Sets the startup PWM level for servo output #3
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup3(unsigned int pwmLevel) {
    bool inRange = true;
    if (UbServo3Min < UbServo3Max) {
        // Normal direction
        if (pwmLevel < UbServo3Min) {
            inRange = false;
        } else if (pwmLevel > UbServo3Max) {
            inRange = false;
        }
    } else {
        // Inverted direction
        if (pwmLevel > UbServo3Min) {
            inRange = false;
        } else if (pwmLevel < UbServo3Max) {
            inRange = false;
        }
    }
    if (pwmLevel == UB_PWM_UNSET) {
        // Force to unset behaviour (central)
        inRange = true;
    }

    if (inRange) {
        Wire.beginTransmission(Ubi2cAddress);
        Wire.write(UB_COMMAND_SET_PWM_BOOT_3);
        Wire.write((byte)((pwmLevel >> 8) & 0xFF));
        Wire.write((byte)(pwmLevel & 0xFF));
        Wire.endTransmission();
        delay(UB_DELAY_AFTER_EEPROM);
    }
    return inRange;
}

// Sets the startup PWM level for servo output #4
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup4(unsigned int pwmLevel) {
    bool inRange = true;
    if (UbServo4Min < UbServo4Max) {
        // Normal direction
        if (pwmLevel < UbServo4Min) {
            inRange = false;
        } else if (pwmLevel > UbServo4Max) {
            inRange = false;
        }
    } else {
        // Inverted direction
        if (pwmLevel > UbServo4Min) {
            inRange = false;
        } else if (pwmLevel < UbServo4Max) {
            inRange = false;
        }
    }
    if (pwmLevel == UB_PWM_UNSET) {
        // Force to unset behaviour (central)
        inRange = true;
    }

    if (inRange) {
        Wire.beginTransmission(Ubi2cAddress);
        Wire.write(UB_COMMAND_SET_PWM_BOOT_4);
        Wire.write((byte)((pwmLevel >> 8) & 0xFF));
        Wire.write((byte)(pwmLevel & 0xFF));
        Wire.endTransmission();
        delay(UB_DELAY_AFTER_EEPROM);
    }
    return inRange;
}

/***** Limit functions *****/

// Gets the minimum PWM level for servo output #1
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum1(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MIN_1);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the minimum PWM level for servo output #2
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum2(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MIN_2);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the minimum PWM level for servo output #3
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum3(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MIN_3);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the minimum PWM level for servo output #4
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum4(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MIN_4);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the maximum PWM level for servo output #1
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum1(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MAX_1);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the maximum PWM level for servo output #2
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum2(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MAX_2);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the maximum PWM level for servo output #3
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum3(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MAX_3);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the maximum PWM level for servo output #4
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum4(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM_MAX_4);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Sets the raw PWM level for servo output #1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition1(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_CALIBRATE_PWM1);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
}

// Sets the raw PWM level for servo output #2
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition2(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_CALIBRATE_PWM2);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
}

// Sets the raw PWM level for servo output #3
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition3(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_CALIBRATE_PWM3);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
}

// Sets the raw PWM level for servo output #4
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition4(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_CALIBRATE_PWM4);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
}

// Gets the raw PWM level for servo output #1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition1
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition1(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM1);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the raw PWM level for servo output #2
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition2
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition2(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM2);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the raw PWM level for servo output #3
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition3
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition3(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM3);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Gets the raw PWM level for servo output #4
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition4
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition4(void) {
    unsigned int pwmLevel;
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_GET_PWM4);
    Wire.endTransmission();
    ReadInReply();
    pwmLevel = ((unsigned int)rdBuffer[1] << 8) + (unsigned int)rdBuffer[2];
    return pwmLevel;
}

// Sets the minimum PWM level for servo output #1
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum1(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MIN_1);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo1Min = UbGetServoMinimum1();
}

// Sets the minimum PWM level for servo output #2
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum2(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MIN_2);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo2Min = UbGetServoMinimum2();
}

// Sets the minimum PWM level for servo output #3
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum3(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MIN_3);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo3Min = UbGetServoMinimum3();
}

// Sets the minimum PWM level for servo output #1
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum4(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MIN_4);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo4Min = UbGetServoMinimum4();
}

// Sets the maximum PWM level for servo output #1
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum1(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MAX_1);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo1Min = UbGetServoMinimum1();
}

// Sets the maximum PWM level for servo output #2
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum2(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MAX_2);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo2Min = UbGetServoMinimum2();
}

// Sets the maximum PWM level for servo output #3
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum3(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MAX_3);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo3Min = UbGetServoMinimum3();
}

// Sets the maximum PWM level for servo output #4
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum4(unsigned int pwmLevel) {
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_PWM_MAX_4);
    Wire.write((byte)((pwmLevel >> 8) & 0xFF));
    Wire.write((byte)(pwmLevel & 0xFF));
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    UbServo4Min = UbGetServoMinimum4();
}

/***** Advanced functions *****/

// Scans the I2C bus for UltraBorg boards and returns a count of all the boards found
byte UbScanForCount(void) {
    byte found = 0;
    byte oldAddress = Ubi2cAddress;
    for (Ubi2cAddress = UB_MINIMUM_I2C_ADDRESS; Ubi2cAddress <= UB_MAXIMUM_I2C_ADDRESS; ++Ubi2cAddress) {
        if (UbInit()) {
            ++found;
        }
    }
    Ubi2cAddress = oldAddress;
    return found;
}

// Scans the I2C bus for an UltraBorg board, index is which address to return (from 0 to count - 1)
// Returns address 0 if no board is found for that index
byte UbScanForAddress(byte index) {
    byte found = 0;
    byte oldAddress = Ubi2cAddress;
    for (Ubi2cAddress = UB_MINIMUM_I2C_ADDRESS; Ubi2cAddress <= UB_MAXIMUM_I2C_ADDRESS; ++Ubi2cAddress) {
        if (UbInit()) {
            if (index == 0) {
                found = Ubi2cAddress;
                break;
            } else {
                --index;
            }
        }
    }
    Ubi2cAddress = oldAddress;
    return found;
}

// Sets the UltraBorg at the current address to newAddress
// Warning, this new I²C address will still be used after resetting the power on the device
// If successful returns true and updates Ubi2cAddress, otherwise returns false
bool UbSetNewAddress(byte newAddress) {
    byte oldAddress = Ubi2cAddress;
    if (newAddress < UB_MINIMUM_I2C_ADDRESS) {
        return false;
    } else if (newAddress > UB_MAXIMUM_I2C_ADDRESS) {
        return false;
    } else if (!UbInit()) {
        return false;
    }
    Wire.beginTransmission(Ubi2cAddress);
    Wire.write(UB_COMMAND_SET_I2C_ADD);
    Wire.write(newAddress);
    Wire.endTransmission();
    delay(UB_DELAY_AFTER_EEPROM);
    Ubi2cAddress = newAddress;
    if (UbInit()) {
        return true;
    } else {
        Ubi2cAddress = oldAddress;
        return false;
    }
}


