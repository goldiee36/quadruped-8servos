#include <Servo.h>
/*
frh = front right hip
 frl = front right leg
 flh = front left hip
 fll = front left leg
 rlh = rear left hip
 rll = rear left leg
 rrh = rear right hip
 rrl = rear right leg
 */
Servo frh;
Servo frl;
Servo flh;
Servo fll;
Servo rlh;
Servo rll;
Servo rrh;
Servo rrl;

int delaybw = 50; //high current draw protection


// CALIBRATION
// HIPS
#define frh90 171
#define flh90 14
#define rlh90 170
#define rrh90 5

#define frh0 76
#define flh0 98
#define rlh0 83
#define rrh0 83

#define frh1deg (frh90-frh0)/90
#define flh1deg (flh90-flh0)/90
#define rlh1deg (rlh90-rlh0)/90
#define rrh1deg (rrh90-rrh0)/90

//LEGS
#define frl90 155
#define fll90 17
#define rll90 145
#define rrl90 10

#define frl0 68
#define fll0 101
#define rll0 54
#define rrl0 95

#define frl1deg (frl90-frl0)/90
#define fll1deg (fll90-fll0)/90
#define rll1deg (rll90-rll0)/90
#define rrl1deg (rrl90-rrl0)/90

long getfrh(long x) { return x * frh1deg + frh0; }
long getflh(long x) { return x * flh1deg + flh0; }
long getrlh(long x) { return x * rlh1deg + rlh0; }
long getrrh(long x) { return x * rrh1deg + rrh0; }
long getfrl(long x) { return x * frl1deg + frl0; }
long getfll(long x) { return x * fll1deg + fll0; }
long getrll(long x) { return x * rll1deg + rll0; }
long getrrl(long x) { return x * rrl1deg + rrl0; }

unsigned long movementStartTime;
unsigned int movementSpeed = 1000;


void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);  // LED pin
  
  // assign servos to pins and reposition
  frh.attach(5); frh.write(getfrh(0)); delay(delaybw);
  frl.attach(6); frl.write(getfrl(70)); delay(delaybw);
  flh.attach(7); flh.write(getflh(45)); delay(delaybw);
  fll.attach(8); fll.write(getfll(70)); delay(delaybw);
  rlh.attach(9); rlh.write(getrlh(0)); delay(delaybw);
  rll.attach(10); rll.write(getrll(70)); delay(delaybw);
  rrh.attach(11); rrh.write(getrrh(45)); delay(delaybw);
  rrl.attach(12); rrl.write(getrrl(70)); delay(delaybw);
  
  delay(2000);
  movementStartTime = millis();
  delay(50);
  setServoForward();
  Serial.println(millis());
  Serial.println(movementStartTime);
}



int delayw = 50;


void loop() {
  setServoForward();
}


void setMovementStartTime() {
  
}

void setMovementSpeed() {
  
}

void setServoForward() {
  int legMaxRaise = 25;
  int legsOnGround = 70;
  int legMovementDuration =  75; //for raising a leg or moving the hip into a new position while the leg is raised
  int hipMin = -23;
  int hipMax = 45;

  unsigned long elapsedTime = millis()-movementStartTime;
  for ( int leg = 4 ; leg >= 1 ; leg-- ) {
    unsigned int currentTimePosition;
    currentTimePosition = (millis()-movementStartTime+(movementSpeed/4*leg))%movementSpeed;
    if (currentTimePosition <= legMovementDuration) { //leg needs to be rised
      switch (leg) {
        case 4:
          rrl.write(getrrl(legMaxRaise));
          break;
        case 3:
          frl.write(getfrl(legMaxRaise));
          break;
        case 2:
          rll.write(getrll(legMaxRaise));
          break;
        case 1:
          fll.write(getfll(legMaxRaise));
          break;
      }      
    }
    else {
      if ( currentTimePosition >= legMovementDuration*2 ) { //put down leg
        switch (leg) {
          case 4:
            rrl.write(getrrl(legsOnGround));
            break;
          case 3:
            frl.write(getfrl(legsOnGround));
            break;
          case 2:
            rll.write(getrll(legsOnGround));
            break;
          case 1:
            fll.write(getfll(legsOnGround));
            break;
        } //switch end
      //move hip
      } //if end
      switch (leg) {
      case 4:
        rrh.write(getrrh( map( currentTimePosition,0,movementSpeed,hipMin,hipMax) ));
        break;
      case 3:
        frh.write(getfrh( map( currentTimePosition,0,movementSpeed,hipMax,hipMin) ));
        break;
      case 2:
        rlh.write(getrlh( map( currentTimePosition,0,movementSpeed,hipMin,hipMax) ));
        break;
      case 1:
        flh.write(getflh( map( currentTimePosition,0,movementSpeed,hipMax,hipMin) ));
        break;
      } //switch end
    } //else end

  } //for end
}

 /*Serial.println( map( (millis()-movementStartTime-(movementSpeed/4))%movementSpeed ,0,movementSpeed,45,-23) );*/

void loop2() 
{
  rrl.write(getrrl(45)); //láb fel

  delay(delayw);
  
  rrh.write(getrrh(-23));
  frh.write(getfrh(-23));
  rlh.write(getrlh(23));
  flh.write(getflh(23));

  delay(delayw);

  rrl.write(getrrl(70)); //láb le
  frl.write(getfrl(45)); //láb fel

  delay(delayw);

  rrh.write(getrrh(0));
  frh.write(getfrh(45));
  rlh.write(getrlh(45));
  flh.write(getflh(0));

  delay(delayw);
  
  frl.write(getfrl(70)); //láb le
  rll.write(getrll(45)); //láb fel

  delay(delayw);
  
  rrh.write(getrrh(23));
  frh.write(getfrh(23));
  rlh.write(getrlh(-23));
  flh.write(getflh(-23));

  delay(delayw);

  rll.write(getrll(70)); //láb le
  fll.write(getfll(45)); //láb fel

  delay(delayw);
  
  rrh.write(getrrh(45));
  frh.write(getfrh(0));
  rlh.write(getrlh(0));
  flh.write(getflh(45));

  delay(delayw);

  fll.write(getfll(70)); //láb le
  
  delay(50);
}


