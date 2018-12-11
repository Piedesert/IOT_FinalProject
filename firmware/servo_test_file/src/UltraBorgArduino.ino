/*
 *
 */
#include <cstdlib>

Servo microServo;

int position = 0;
double reqData;



// Runs once
void setup()
{
    // Serial data to port 9600
    Serial.begin(9600);
    // Connecting the servo to pin D0 and get it to reset back to 0
    microServo.attach(D0);
    microServo.write(180);
    delay(2000);
}



// Runs looped after setup
void loop()
{
  Particle.subscribe("pushedNWMSUFinalProjectTemperature", myHandler);
  Serial.print("Local data: ");
  Serial.println(reqData);
  delay(2000);
  setClothes();
}

void myHandler(const char *event, const char *data)
{
  Serial.print("data: ");
  if (data){
    reqData = std::atof(data);
    Serial.println(data);
  }
  else{
    Serial.println("NULL");
  }
}

void setClothes() {
  position = (reqData/37.7) * 180.0;
  Serial.print("Pointer Position: ");
  Serial.println(position);
  microServo.write(position);
  delay(2000);
  // for (size_t position = 0; position < 180; position++) {
  //     microServo.write(position);
  //     Serial.printf("position: %d" + position);
  //     delay(1000);
  // }
  // for (size_t position = 180; position >= 1; position--) {
  //     microServo.write(position);
  //     Serial.printf("position: %d" + position);
  //     delay(100);
  // }
  //
  // if (reqData <= 0) {
  //     microServo.write(180);
  // } else if (reqData > 0 && reqData <= 10) {
  //     microServo.write(120);
  // } else if (reqData > 10 && reqData <= 15) {
  //     microServo.write(90);
  // } else if (reqData > 15 && reqData <= 25) {
  //     microServo.write(60);
  // } else if (reqData > 25 && reqData <= 32) {
  //     microServo.write(30);
  // } else {
  //     microServo.write(0);
  // }
}
