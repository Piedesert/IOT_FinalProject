
void setup() {
  // Subscribe to the webhook response event
  Particle.subscribe("hook-response/what2wear", myHandler, MY_DEVICES);
}

void loop() {
  // Get some data
  String data = String(10);
  // Trigger the webhook
  Particle.publish("what2wear", PRIVATE);
  // Wait 60 seconds
  delay(60000);
}

void myHandler(const char *event, const char *data) {
  // Handle the webhook response
}
