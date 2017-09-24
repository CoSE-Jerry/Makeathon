#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#define PIN 3
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define buttonPin 2 //Button Pin

Servo myservo;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

int maximumRange = 500; // Maximum range needed
int minimumRange = 10; // Minimum range needed
long duration, distance, current, vertical, marker; // Duration used to calculate distance

int serial_CMD;
int current_CMD;
int current_BTN = 0;

int buttonState = HIGH;
int lastButtonState = LOW;

boolean face = true;
boolean tri = false;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin (9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);

  pinMode(12, OUTPUT);

  myservo.attach(9);

  digitalWrite(12, HIGH);

  strip.begin();
  strip.show();

  colorWipe(strip.Color(100, 50, 50), 50);
  colorWipe(strip.Color(50, 100, 50), 50);
  colorWipe(strip.Color(50, 50, 100), 50);
  colorWipe(strip.Color(0, 0, 0), 1);

  myservo.write(40);//facing down;
  delay(500);
  myservo.write(135);//facing straight

}

void loop() {
  button_read();

  if (current_BTN == 0)
  {
    sentinal();
  }

  if (current_BTN == 1)
  {
    triangulation();
  }
    if (current_BTN == 2)
  {
    emergency();
  }

}

int serial_read()
{
  if (Serial.available())
  {
    serial_CMD = (int)Serial.read();
  }
  return (int)Serial.read();
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void button_read()
{

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        buttonState = !buttonState;
      }
    }
  }
  lastButtonState = reading;
  if (lastButtonState == HIGH) {
    if (current_BTN == 0)
    {
      current_BTN = 1;
      delay(300);
    }

    else if (current_BTN == 1)
    {
      current_BTN = 2;
      delay(300);
    }
    else
    {
      current_BTN = 0;
      delay(300);
    }

  }
}

long measure() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58.2;

  if (distance >= maximumRange || distance <= minimumRange) {
    return (-1);
  }
  else {
    return (distance);

  }
}

void sentinal()
{
  tri = false;
  if (face == false)
    myservo.write(135);

  current = measure();
  if (current != -1)
  {
    if (current > 300)
    { digitalWrite(12, LOW);
      delay(100);
      digitalWrite(12, HIGH);
      delay(1000);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
    }
    else if (current > 200)
    { digitalWrite(12, LOW);
      delay(200);
      digitalWrite(12, HIGH);
      delay(500);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
    }
    else if (current > 100)
    { digitalWrite(12, LOW);
      delay(300);
      digitalWrite(12, HIGH);
      delay(200);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
    }

    else if (current < 100)
    { digitalWrite(12, LOW);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 0, 0);
      }
      strip.show();
      delay(50);
      digitalWrite(12, HIGH);
    }


  }
  else
    digitalWrite(12, HIGH);

}

void triangulation()
{ if (tri == false)
  { face = false;
    myservo.write(40);
    delay(800);
    vertical = measure();
    delay(800);
    myservo.write(85);
    marker = sqrt(2) * vertical;
    tri = true;
  }
  current = measure();
  if (current != -1)
  {
    if (current > 0.75 * marker)
    { digitalWrite(12, LOW);
      delay(100);
      digitalWrite(12, HIGH);
      delay(1000);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
    }
    else if (current > 0.5 * marker)
    { digitalWrite(12, LOW);
      delay(200);
      digitalWrite(12, HIGH);
      delay(500);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
    }
    else if (current > 0.25 * marker)
    { digitalWrite(12, LOW);
      delay(300);
      digitalWrite(12, HIGH);
      delay(200);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
    }

    else if (current < 0.25 * marker)
    { digitalWrite(12, LOW);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 0, 0);
      }
      strip.show();
      delay(50);
      digitalWrite(12, HIGH);
    }


  }
  else
    digitalWrite(12, HIGH);

}

void emergency()
{
  colorWipe(strip.Color(255, 0, 0), 10);
   colorWipe(strip.Color(0, 0, 255), 10);
   digitalWrite(12, LOW);
  
}

