/*
 *
 */

Servo microServo;

int position = 0;

// Runs once
void setup()
{
    // Serial data to port 9600
    Serial.begin(9600);
    // Connecting the servo to pin D0 and get it to reset back to 0
    microServo.attach(D0);
}



// Runs looped after setup
void loop()
{
  delay(3000);
}

void setClothes() {
  // for (size_t position = 0; position < 180; position++) {
  //     microServo.write(position);
  //     Serial.printf("position: %d" + position);
  //     delay(100);
  // }
  // for (size_t position = 180; position >= 1; position--) {
  //     microServo.write(position);
  //     Serial.printf("position: %d" + position);
  //     delay(100);
  // }
  //
  if (reqData <= 0) {
      microServo.write(180);
  } else if (reqData > 0 && reqData <= 10) {
      microServo.write(120);
  } else if (reqData > 10 && reqData <= 15) {
      microServo.write(90);
  } else if (reqData > 15 && reqData <= 25) {
      microServo.write(60);
  } else if (reqData > 25 && reqData <= 32) {
      microServo.write(30);
  } else {
      microServo.write(0);
  }
  // position = (reqData/37.7) * 180.0;
  // Serial.println(position);
  // microServo.write(position);
  delay(5000);
}
