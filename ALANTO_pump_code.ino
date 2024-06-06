// Define pin for the relay
const int relayPin = 7; // Pin digital 7

void setup() {
  pinMode(relayPin, OUTPUT); // Set relayPin as output
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Turning on the pump
  digitalWrite(relayPin, HIGH);
  // turning off for 3 minutes
  delay(180000);
  // turning on the pump for 0.5 second
  digitalWrite(relayPin, LOW);
  delay(500);
}
