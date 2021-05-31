/*
 * Controls a watch winder that uses the 28BYJ-48 Stepper Motor and Arduino Nano
 * Small Watch Winder by Edward Huang, Tony Huang
 * Current Settings: TPD: 650, delay 5ms, 20 turns/cycle, break time/cycle: 255015 ms, total cycles: 33
 * TPD Pattern: 6 hours of winding and 18 hours of resting time. 
 */

#define pin1 8
#define pin2 9
#define pin3 10
#define pin4 11
#define motorDelay 5 // delay in milliseconds
#define cycle 10 // clockwise and counterclockwise
#define numSteps 32*32*4// Total of 4096 steps for 1 revolution

int motorstate = 0;
int clkwise = 0;
int cntrclkwise = 0;

// Initialize Serial and motor pins
void setup() 
{
  Serial.begin(9600);
  Serial.println("Start");
  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}

//loop includes entire day cycle. 6 hour rotation cycle and 18 hour break
void loop() 
{
  // 6 hour rotation cycle. 33 cycles
  for(int i = 0; i < 33; i++){
    rotationCycle();
  }

  // 18 hour delay
  for(int h = 0; h < 18; h++){
    // Serial.print("Hour: ");
    // Serial.println(h);
    for(int m = 0; m < 60; m++){
      // Serial.print("Minute: ");
      // Serial.println(m);
      for(int s = 0; s < 60; s++){
        delay(1000); 
        // Serial.print("Second: ");
        // Serial.println(s);
      }
    }
  }
}

// rotationCycle includes one entire cycle. Clockwise rotation, Counterclockwise Rotation, Break
void rotationCycle(){
  // Rotate Clockwise 
  for(int i = 0; i < cycle; i++)
  {
    for(int j = 0; j < numSteps; j++){
      myStep(1);
      delay(motorDelay);
    }
    clkwise++;
    //Serial.print("Clockwise: ");
    //Serial.println(clkwise);
  }

  // Rotate Counter Clockwise
  for(int i=0; i < cycle; i++)
  {
    for(int j = 0; j < numSteps; j++){
      myStep(-1);
      delay(motorDelay);
    }
    cntrclkwise++;
    //Serial.print("Counter Clockwise: ");
    //Serial.println(cntrclkwise);
  }
  
  // Break after doing one cycle equating to 255015 ms
  for(int s = 0; s < 255; s++){
    delay(1000); 
  }
  delay(15);
}

// myStep drives the stepper motor and controls the 8 states of the motor
void myStep(int dir)
{
  motorstate = motorstate + dir;
  if (motorstate < 0) motorstate += 8;
  if (motorstate >=8) motorstate -= 8;
  switch (motorstate)
  {
    case 0:
      digitalWrite(pin1, 0);
      digitalWrite(pin2, 1);
      digitalWrite(pin3, 1);
      digitalWrite(pin4, 1);
      break;
     case 1:
      digitalWrite(pin1, 0);
      digitalWrite(pin2, 0);
      digitalWrite(pin3, 1);
      digitalWrite(pin4, 1);
      break;
    case 2:
      digitalWrite(pin1, 1);
      digitalWrite(pin2, 0);
      digitalWrite(pin3, 1);
      digitalWrite(pin4, 1);
      break;
    case 3:
      digitalWrite(pin1, 1);
      digitalWrite(pin2, 0);
      digitalWrite(pin3, 0);
      digitalWrite(pin4, 1);
      break;
    case 4:
      digitalWrite(pin1, 1);
      digitalWrite(pin2, 1);
      digitalWrite(pin3, 0);
      digitalWrite(pin4, 1);
      break;
    case 5:
      digitalWrite(pin1, 1);
      digitalWrite(pin2, 1);
      digitalWrite(pin3, 0);
      digitalWrite(pin4, 0);
      break;
    case 6:
      digitalWrite(pin1, 1);
      digitalWrite(pin2, 1);
      digitalWrite(pin3, 1);
      digitalWrite(pin4, 1);
      break;
    case 7:
      digitalWrite(pin1, 0);
      digitalWrite(pin2, 1);
      digitalWrite(pin3, 1);
      digitalWrite(pin4, 0);
      break;
  }
}
