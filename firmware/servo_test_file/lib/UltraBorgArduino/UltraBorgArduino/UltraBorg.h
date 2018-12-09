/**************************************/
/******** UltraBorg Constants *********/
/**************************************/

// Commands
// GET commands sent should be followed by a read for the result
// All other commands are send only (no reply)
#define UB_COMMAND_GET_TIME_USM1    (1)     // Get the time measured by ultrasonic #1 in us (0 for no detection)
#define UB_COMMAND_GET_TIME_USM2    (2)     // Get the time measured by ultrasonic #2 in us (0 for no detection)
#define UB_COMMAND_GET_TIME_USM3    (3)     // Get the time measured by ultrasonic #3 in us (0 for no detection)
#define UB_COMMAND_GET_TIME_USM4    (4)     // Get the time measured by ultrasonic #4 in us (0 for no detection)
#define UB_COMMAND_SET_PWM1         (5)     // Set the PWM duty cycle for drive #1 (16 bit)
#define UB_COMMAND_GET_PWM1         (6)     // Get the PWM duty cycle for drive #1 (16 bit)
#define UB_COMMAND_SET_PWM2         (7)     // Set the PWM duty cycle for drive #2 (16 bit)
#define UB_COMMAND_GET_PWM2         (8)     // Get the PWM duty cycle for drive #2 (16 bit)
#define UB_COMMAND_SET_PWM3         (9)     // Set the PWM duty cycle for drive #3 (16 bit)
#define UB_COMMAND_GET_PWM3         (10)    // Get the PWM duty cycle for drive #3 (16 bit)
#define UB_COMMAND_SET_PWM4         (11)    // Set the PWM duty cycle for drive #4 (16 bit)
#define UB_COMMAND_GET_PWM4         (12)    // Get the PWM duty cycle for drive #4 (16 bit)
#define UB_COMMAND_CALIBRATE_PWM1   (13)    // Set the PWM duty cycle for drive #1 (16 bit, ignores limit checks)
#define UB_COMMAND_CALIBRATE_PWM2   (14)    // Set the PWM duty cycle for drive #2 (16 bit, ignores limit checks)
#define UB_COMMAND_CALIBRATE_PWM3   (15)    // Set the PWM duty cycle for drive #3 (16 bit, ignores limit checks)
#define UB_COMMAND_CALIBRATE_PWM4   (16)    // Set the PWM duty cycle for drive #4 (16 bit, ignores limit checks)
#define UB_COMMAND_GET_PWM_MIN_1    (17)    // Get the minimum allowed PWM duty cycle for drive #1
#define UB_COMMAND_GET_PWM_MAX_1    (18)    // Get the maximum allowed PWM duty cycle for drive #1
#define UB_COMMAND_GET_PWM_BOOT_1   (19)    // Get the startup PWM duty cycle for drive #1
#define UB_COMMAND_GET_PWM_MIN_2    (20)    // Get the minimum allowed PWM duty cycle for drive #2
#define UB_COMMAND_GET_PWM_MAX_2    (21)    // Get the maximum allowed PWM duty cycle for drive #2
#define UB_COMMAND_GET_PWM_BOOT_2   (22)    // Get the startup PWM duty cycle for drive #2
#define UB_COMMAND_GET_PWM_MIN_3    (23)    // Get the minimum allowed PWM duty cycle for drive #3
#define UB_COMMAND_GET_PWM_MAX_3    (24)    // Get the maximum allowed PWM duty cycle for drive #3
#define UB_COMMAND_GET_PWM_BOOT_3   (25)    // Get the startup PWM duty cycle for drive #3
#define UB_COMMAND_GET_PWM_MIN_4    (26)    // Get the minimum allowed PWM duty cycle for drive #4
#define UB_COMMAND_GET_PWM_MAX_4    (27)    // Get the maximum allowed PWM duty cycle for drive #4
#define UB_COMMAND_GET_PWM_BOOT_4   (28)    // Get the startup PWM duty cycle for drive #4
#define UB_COMMAND_SET_PWM_MIN_1    (29)    // Set the minimum allowed PWM duty cycle for drive #1
#define UB_COMMAND_SET_PWM_MAX_1    (30)    // Set the maximum allowed PWM duty cycle for drive #1
#define UB_COMMAND_SET_PWM_BOOT_1   (31)    // Set the startup PWM duty cycle for drive #1
#define UB_COMMAND_SET_PWM_MIN_2    (32)    // Set the minimum allowed PWM duty cycle for drive #2
#define UB_COMMAND_SET_PWM_MAX_2    (33)    // Set the maximum allowed PWM duty cycle for drive #2
#define UB_COMMAND_SET_PWM_BOOT_2   (34)    // Set the startup PWM duty cycle for drive #2
#define UB_COMMAND_SET_PWM_MIN_3    (35)    // Set the minimum allowed PWM duty cycle for drive #3
#define UB_COMMAND_SET_PWM_MAX_3    (36)    // Set the maximum allowed PWM duty cycle for drive #3
#define UB_COMMAND_SET_PWM_BOOT_3   (37)    // Set the startup PWM duty cycle for drive #3
#define UB_COMMAND_SET_PWM_MIN_4    (38)    // Set the minimum allowed PWM duty cycle for drive #4
#define UB_COMMAND_SET_PWM_MAX_4    (39)    // Set the maximum allowed PWM duty cycle for drive #4
#define UB_COMMAND_SET_PWM_BOOT_4   (40)    // Set the startup PWM duty cycle for drive #4
#define UB_COMMAND_GET_FILTER_USM1  (41)    // Get the filtered time measured by ultrasonic #1 in us (0 for no detection)
#define UB_COMMAND_GET_FILTER_USM2  (42)    // Get the filtered time measured by ultrasonic #2 in us (0 for no detection)
#define UB_COMMAND_GET_FILTER_USM3  (43)    // Get the filtered time measured by ultrasonic #3 in us (0 for no detection)
#define UB_COMMAND_GET_FILTER_USM4  (44)    // Get the filtered time measured by ultrasonic #4 in us (0 for no detection)
#define UB_COMMAND_GET_ID           (0x99)  // Get the board identifier
#define UB_COMMAND_SET_I2C_ADD      (0xAA)  // Set a new I2C address

// Values
// These are the corresponding numbers for states used by the above commands
#define UB_I2C_ID_SERVO_USM         (0x36)      // I2C values returned when calling the GET_ID command
#define UB_DEFAULT_I2C_ADDRESS      (0x36)      // I2C address set by default (before using SET_I2C_ADD)
#define UB_USM_US_TO_MM             (0.171500)  // Conversion from 'GET_TIME_USM' commands to millimeters
#define UB_PWM_UNSET                (0xFFFF)    // Special value for UbSetServoStartup*, when used resets startup position to be central
#define UB_DELAY_AFTER_EEPROM       (50)        // Delay time after writing EEPROM values before trying to talk again

// Limits
// These define the maximums that the UltraBorg will accept
#define UB_I2C_MAX_LEN              (4)     // Maximum number of bytes in an I2C message
#define UB_DEFAULT_PWM_MAX          (4000)  // Servo maximum limit when set to default 
#define UB_DEFAULT_PWM_MIN          (2000)  // Servo minimum limit when set to default
#define UB_MINIMUM_I2C_ADDRESS      (0x03)  // Minimum allowed value for the I2C address
#define UB_MAXIMUM_I2C_ADDRESS      (0x77)  // Maximum allowed value for the I2C address

/***************************************/
/******** UltraBorg Properties *********/
/***************************************/

// Types
typedef unsigned char byte;                 // Define the term 'byte' if it has not been already

// Values
extern byte Ubi2cAddress;                   // The I2C address we are currently talking to
extern signed long UbServo1Min;             // The current minimum limit for servo #1
extern signed long UbServo1Max;             // The current maximum limit for servo #1
extern signed long UbServo2Min;             // The current minimum limit for servo #2
extern signed long UbServo2Max;             // The current maximum limit for servo #2
extern signed long UbServo3Min;             // The current minimum limit for servo #3
extern signed long UbServo3Max;             // The current maximum limit for servo #3
extern signed long UbServo4Min;             // The current minimum limit for servo #4
extern signed long UbServo4Max;             // The current maximum limit for servo #4

/**************************************/
/******** UltraBorg Functions *********/
/**************************************/

/***** General functions *****/

// Check we are talking to the UltraBorg
bool UbInit(void);

/***** Servo functions *****/

// Sets the drive position for servo output #1
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition1(float position);

// Sets the drive position for servo output #2
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition2(float position);

// Sets the drive position for servo output #3
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition3(float position);

// Sets the drive position for servo output #4
// 0 is central, -1 is maximum left, +1 is maximum right
void UbSetServoPosition4(float position);

// Gets the drive position for servo output #1
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition1(void);

// Gets the drive position for servo output #2
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition2(void);

// Gets the drive position for servo output #3
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition3(void);

// Gets the drive position for servo output #4
// 0 is central, -1 is maximum left, +1 is maximum right
float UbGetServoPosition4(void);

/***** Ultrasonic functions *****/

// Gets the filtered distance for ultrasonic module #1 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance1 instead (no filtering)
float UbGetDistance1(void);

// Gets the filtered distance for ultrasonic module #2 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance2 instead (no filtering)
float UbGetDistance2(void);

// Gets the filtered distance for ultrasonic module #3 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance3 instead (no filtering)
float UbGetDistance3(void);

// Gets the filtered distance for ultrasonic module #4 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// If you need a faster response try UbGetRawDistance4 instead (no filtering)
float UbGetDistance4(void);

// Gets the raw distance for ultrasonic module #1 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance1
float UbGetRawDistance1(void);

// Gets the raw distance for ultrasonic module #2 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance2
float UbGetRawDistance2(void);

// Gets the raw distance for ultrasonic module #3 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance3
float UbGetRawDistance3(void);

// Gets the raw distance for ultrasonic module #4 in millimeters
// Returns 0 for no object detected or no ultrasonic module attached
// For a filtered (less jumpy) reading use UbGetDistance4
float UbGetRawDistance4(void);

/***** Startup functions *****/

// Gets the startup PWM level for servo output #1
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup1(void);

// Gets the startup PWM level for servo output #2
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup2(void);

// Gets the startup PWM level for servo output #3
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup3(void);

// Gets the startup PWM level for servo output #4
// This can be anywhere in the minimum to maximum range
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoStartup4(void);

// Sets the startup PWM level for servo output #1
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup1(unsigned int pwmLevel);

// Sets the startup PWM level for servo output #2
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup2(unsigned int pwmLevel);

// Sets the startup PWM level for servo output #3
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup3(unsigned int pwmLevel);

// Sets the startup PWM level for servo output #4
// This can be anywhere in the minimum to maximum range
// 
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// This value is checked against the current servo limits before setting
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
bool UbSetServoStartup4(unsigned int pwmLevel);

/***** Limit functions *****/

// Gets the minimum PWM level for servo output #1
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum1(void);

// Gets the minimum PWM level for servo output #2
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum2(void);

// Gets the minimum PWM level for servo output #3
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum3(void);

// Gets the minimum PWM level for servo output #4
// This corresponds to position -1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMinimum4(void);

// Gets the maximum PWM level for servo output #1
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum1(void);

// Gets the maximum PWM level for servo output #2
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum2(void);

// Gets the maximum PWM level for servo output #3
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum3(void);

// Gets the maximum PWM level for servo output #4
// This corresponds to position +1
// The value is an integer where 2000 represents a 1 ms servo burst
unsigned int UbGetServoMaximum4(void);

// Sets the raw PWM level for servo output #1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition1(unsigned int pwmLevel);

// Sets the raw PWM level for servo output #2
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition2(unsigned int pwmLevel);

// Sets the raw PWM level for servo output #3
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition3(unsigned int pwmLevel);

// Sets the raw PWM level for servo output #4
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// NO LIMIT CHECKING IS PERFORMED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbCalibrateServoPosition4(unsigned int pwmLevel);

// Gets the raw PWM level for servo output #1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition1
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition1(void);

// Gets the raw PWM level for servo output #2
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition2
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition2(void);

// Gets the raw PWM level for servo output #3
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition3
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition3(void);

// Gets the raw PWM level for servo output #4
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// This value requires interpreting into an actual servo position, this is already done by UbGetServoPosition4
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
unsigned int UbGetRawServoPosition4(void);

// Sets the minimum PWM level for servo output #1
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum1(unsigned int pwmLevel);

// Sets the minimum PWM level for servo output #2
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum2(unsigned int pwmLevel);

// Sets the minimum PWM level for servo output #3
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum3(unsigned int pwmLevel);

// Sets the minimum PWM level for servo output #1
// This corresponds to position -1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMinimum4(unsigned int pwmLevel);

// Sets the maximum PWM level for servo output #1
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition1 / UbGetServoPosition1
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum1(unsigned int pwmLevel);

// Sets the maximum PWM level for servo output #2
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition2 / UbGetServoPosition2
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum2(unsigned int pwmLevel);

// Sets the maximum PWM level for servo output #3
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition3 / UbGetServoPosition3
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum3(unsigned int pwmLevel);

// Sets the maximum PWM level for servo output #4
// This corresponds to position +1
// This value can be set anywhere from 0 for a 0% duty cycle to 65535 for a 100% duty cycle
// 
// Setting values outside the range of the servo for extended periods of time can damage the servo
// LIMIT CHECKING IS ALTERED BY THIS COMMAND!
// We recommend using the tuning GUI for setting the servo limits for UbSetServoPosition4 / UbGetServoPosition4
// 
// The value is an integer where 2000 represents a 1ms servo burst, approximately 3% duty cycle
void UbSetServoMaximum4(unsigned int pwmLevel);

/***** Advanced functions *****/

// Scans the I2C bus for UltraBorg boards and returns a count of all the boards found
byte UbScanForCount(void);

// Scans the I2C bus for an UltraBorg board, index is which address to return (from 0 to count - 1)
// Returns address 0 if no board is found for that index
byte UbScanForAddress(byte index);

// Sets the UltraBorg at the current address to newAddress
// Warning, this new I²C address will still be used after resetting the power on the device
// If successful returns true and updates Ubi2cAddress, otherwise returns false
bool UbSetNewAddress(byte newAddress);

