#include <NewPing.h>

// ---------------------------------------------------------
// Code used to communicate w/ 4 ultrasonic sensors.
// Adjust number by changing SONAR_NUM
// Adjust number of NewPing objects in "sonar" array
// Change pins for each sensor for NewPing objects
// Each sensor pinged at intervals in ms. 
// One cycle of all sensors takes PING_INTERVAl * SONAR_NUM
// Results are sent to the "oneSensorCycle" function
// "oneSensorCycle" currently just displays distance data
// Process sensor results in function
// Event-driven; complete sketch cannot use "delay" commands
// loop() cycles at faster than a 33ms rate
// If other processes take longer than 33ms, you'll need to
// increase PING_INTERVAL so it doesn't get behind.
// ---------------------------------------------------------

#define SONAR_NUM     4   // Number or sensors.
#define MAX_DISTANCE 4000 // Max distance in cm.
#define PING_INTERVAL 70  // Milliseconds between pings.

unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.

NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(2, 4, MAX_DISTANCE), // orange
  NewPing(2, 5, MAX_DISTANCE), // brown
  NewPing(2, 6, MAX_DISTANCE), // yellow
  NewPing(2, 7, MAX_DISTANCE)  // red
};

void setup() {
  Serial.begin(115200);         // figure out if this is correct serial
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (int i = 1; i < SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  for (int i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1)
        oneSensorCycle(); // Do something with results.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
     cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
}

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Do something with the results.
  for (int i = 0; i < SONAR_NUM; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" reading at ");
    Serial.print(cm[i], DEC); // IN CENTIMETERS
    Serial.print("cm ");
    Serial.print("\n");
  }
//  Serial.println();
}


