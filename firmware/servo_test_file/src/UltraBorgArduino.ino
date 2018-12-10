/*
 *
 */

Servo microServo;

const int CONNECT_DELAY_SECS = 30;
const int SLEEP_DELAY_SECS = 10;//2 * 60;
const int SLEEP_TIME_SECS = 10;//60 * 60;

unsigned long lastResponseTime = 0;

int position = 0;
int i = 0;
float reqData = 0.0;

void myHandler(const char *event, const char *data)
{
  i++;
  Serial.print(i);
  Serial.print(event);
  Serial.print(", data: ");
  if (data){
    reqData = *data;
    Serial.println(data);
  }
  else{
    Serial.println("NULL");
  }
}

// Runs once
void setup()
{
    // Serial data to port 9600
    Serial.begin(9600);
    // Connecting the servo to pin D0 and get it to reset back to 0
    microServo.attach(D0);
    microServo.write(180);
    microServo.write(0);

    // Set pointer to suggested clothes
    setClothes();

}

// Runs looped after setup
void loop()
{
  if(readyToSleep()) {
    Serial.println("Done waiting => Go to sleep"); delay(200);
    goToSleep();
  }



}

void setClothes() {
  position = (reqData/37.7) * 180.0;
  Serial.println(position);
  microServo.write(position);
  delay(5000);

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
}

void getClothesFromEvent() {
  // Subscribe to forcast event
  Particle.subscribe("pushedNWMSUFinalProjectTemperature", myHandler);
  if(waitFor(Particle.connected, CONNECT_DELAY_SECS * 1000)) {
    Serial.println("Connected to Particle");
  } else {
    Serial.println("Couldn't connect => Go to sleep");
    goToSleep();
  }
}

unsigned long timeSinceLastResponse() {
  return millis() - lastResponseTime;
}

bool readyToSleep() {
  if(1) {
    return true;
  }

  return timeSinceLastResponse() > SLEEP_DELAY_SECS * 1000;
}

void goToSleep() {
  System.sleep(SLEEP_MODE_DEEP, SLEEP_TIME_SECS);
}
