// define the stepper driver pins
#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

// define how many cycles to a full rotation
#define CYCLES_PER_ROTATION 512

void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  delay(500);

}

void loop()
{
  turns(0.1);
}

void turns(float rotations)
{
  // if the rotation count is -ve then it is CCW
  bool clockwise = rotations > 0;
  // calculate how many cycles the stepper will have to make
  int cycles = rotations * CYCLES_PER_ROTATION;
  // force the cycle count to be positive
  cycles = abs(cycles);
  // only move if the user specifed an actual movement
  if (rotations != 0)
  {
    if (clockwise)
    {
      // for each cycle
      for (int x = 0; x < cycles; x++)
      {
        // for each phase
        for (int y = 0; y < 8; y++)
        {
          // go to phase y
          phaseSelect(y);
          // pause so the stepper has time to react
          delay(10);
          //readDistance();
        }
      }
    } else {
      // for each cycle
      for (int x = 0; x < cycles; x++)
      {
        // for each phase (backwards for CCW rotation)
        for (int y = 7; y >= 0; y--)
        {
          // go to phase y
          phaseSelect(y);
          // pause so the stepper has time to react
          delay(10);
          //readDistance();
        }
      }
    }
  }
  // go to the default state (all poles off) when finished
  phaseSelect(8);
}

void phaseSelect(int phase)
{
  switch (phase) {
    case 0:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 4:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 5:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 6:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 7:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
  }
}

