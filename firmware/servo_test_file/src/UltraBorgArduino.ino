/*
 *
 */

Servo microServo;

int position = 0;

// Runs once
void setup()
{
    // Serial data to port 300
    Serial.begin(300);

    // Connecting the servo to pin D0
    microServo.attach(D0);
}

// Runs looped after setup
void loop()
{
    for (size_t position = 0; position < 180; position++) {
        microServo.write(position);
        Serial.printf("position: %d" + position);
        delay(100);
    }
    for (size_t position = 180; position >= 1; position--) {
        microServo.write(position);
        Serial.printf("position: %d" + position);
        delay(100);
    }
}
