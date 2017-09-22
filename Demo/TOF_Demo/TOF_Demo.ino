int pinF = 4;

unsigned long durationF;

void setup()
{
  pinMode(pinF, INPUT);
  delay(500);
}

void loop()
{
    readDistance();
}

void readDistance()
{
  uint16_t distanceF = 0;
  durationF = pulseIn(pinF, HIGH);
  distanceF = durationF / 10;

  Serial.print("Front Distance: ");
  Serial.println( distanceF);
  Serial.println();
}

