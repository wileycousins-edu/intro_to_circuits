// intro to circuits music machine

// define our constants
#define VCC 5.0

int light;

void setup(void) {
  // serial
  Serial.begin(9600);
  // initialize light to 0
  light = 0;
}

void loop(void) {
  // set light equal to the analog reading of pin A0
  light = analogRead(0);
  Serial.print("light level: ");
  Serial.println(light);
  
  // generate an A440 on pin 10
  //light = 1023 - light;
  light *= 4;
  //light = light * 8;
  tone(10, light);
  
  // wait a little
  delay(50);
}
