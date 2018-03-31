const int REED_PIN = 2; // Pin connected to reed switch
const int LED_PIN = 13; // LED pin - active-high
const float RADIUS = 0.3; // metres
const float PIE = 3.14159;
const int numberOfMagnets = 1;
const int intervalLength = 5; // 10 seconds
const uint32_t period = intervalLength*1000; // 10 seconds
boolean closed = false;
int revs = 0;
float circumference = 2*PIE*RADIUS;
float arcLength = circumference/numberOfMagnets;
int numIntervals = 0;

void setup() 
{
  Serial.begin(9600);
  // Since the other end of the reed switch is connected to ground, we need
  // to pull-up the reed switch pin internally.
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  float distance = 0;
  for( uint32_t tStart = millis();  (millis()-tStart) < period;  ) {
    int proximity = digitalRead(REED_PIN); // Read the state of the switch
    if (proximity == LOW) // If the pin reads low, the switch is closed.
    {
      Serial.println("Switch closed");
      Serial.print("revs: ");
      Serial.println(revs);
      closed = true;
      digitalWrite(LED_PIN, HIGH); // Turn the LED on
    }
    else
    {
      if (closed == true) {
        revs++;
        distance += arcLength;
      }
      closed = false;
      digitalWrite(LED_PIN, LOW); // Turn the LED off
//      Serial.print("distance: ");
//      Serial.println(distance);
    }
  }
  numIntervals++;
  Serial.println("10 seconds elapsed.....................");
  Serial.print("Distance this interval: ");
  Serial.print(distance);
  Serial.println(" m");
  Serial.print("Speed this interval: ");
  Serial.print(distance/intervalLength);
  Serial.println(" m/s");
  Serial.print("Total distance: ");
  Serial.println(revs*arcLength);
  Serial.print("Average speed: ");
  Serial.println((revs*arcLength)/(numIntervals*intervalLength));
}
