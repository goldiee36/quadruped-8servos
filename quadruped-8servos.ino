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

long getfrh(long degree) { return degree * frh1deg + frh0; }
long getflh(long degree) { return degree * flh1deg + flh0; }
long getrlh(long degree) { return degree * rlh1deg + rlh0; }
long getrrh(long degree) { return degree * rrh1deg + rrh0; }
long getfrl(long degree) { return degree * frl1deg + frl0; }
long getfll(long degree) { return degree * fll1deg + fll0; }
long getrll(long degree) { return degree * rll1deg + rll0; }
long getrrl(long degree) { return degree * rrl1deg + rrl0; }

void setHip(byte hip, int degree) {
  switch (hip) {
        case 1:
          frh.write(getfrh(degree));
          break;
        case 2:
          flh.write(getflh(degree));
          break;
        case 3:
          rlh.write(getrlh(degree));
          break;
        case 4:
          rrh.write(getrrh(degree));
          break;
      }     
}

void setLeg(byte leg, int degree) {
  switch (leg) {
        case 1:
          frl.write(getfrl(degree));
          break;
        case 2:
          fll.write(getfll(degree));
          break;
        case 3:
          rll.write(getrll(degree));
          break;
        case 4:
          rrl.write(getrrl(degree));
          break;
      }     
}

unsigned long movementStartTime;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);  // LED pin
  
  // assign servos to pins and reposition
  frh.attach(5); frh.write(getfrh(-6)); delay(50);
  frl.attach(6); frl.write(getfrl(70)); delay(50);
  flh.attach(7); flh.write(getflh(28)); delay(50);
  fll.attach(8); fll.write(getfll(70)); delay(50);
  rlh.attach(9); rlh.write(getrlh(11)); delay(50);
  rll.attach(10); rll.write(getrll(70)); delay(50);
  rrh.attach(11); rrh.write(getrrh(45)); delay(50);
  rrl.attach(12); rrl.write(getrrl(70)); delay(50);
  
  delay(2000);
  movementStartTime = millis();
  setServoMovement();
  delay(5000);
  movementStartTime = millis();
  setServoMovement();
}




void loop() {
  setServoMovement();
}

//changing between movements: set new direction, speed. check current servo values. calculate 8-10 lineary distributed samples during the new movement.
//compare samples with current values, find the closest match. set the legs to the new choosen position individually without changing the orientation of the spider
//continue movement from this position

unsigned int movementSpeed = 1000; //time for advancing for all 4 leg. bigger values are slower
int legMaxRaise = 25;
int legsOnGround = 70;
int legMovementDuration =  50; //for raising a leg
int hipMovementDuration =  75; //for moving the hip into a new position while the leg is raised

 //move forward values:
/*byte legOrder[] = {4, 1, 3, 2};
int hipMin[] = {-23, 45, -23, 45}; //for corresponding legs in the legOrder list
int hipMax[] = {45, -23, 45, -23};*/

 //move backward values:
/*byte legOrder[] = {2, 3, 1, 4};
int hipMin[] = {-23, 45, -23, 45}; //for corresponding legs in the legOrder list
int hipMax[] = {45, -23, 45, -23};*/

 //move left values:
/*byte legOrder[] = {1, 2, 4, 3};
int hipMin[] = {90, 23, 90, 23}; //for corresponding legs in the legOrder list
int hipMax[] = {23, 90, 23, 90};*/

 //move right values:
/*byte legOrder[] = {3, 4, 2, 1};
int hipMin[] = {90, 23, 90, 23}; //for corresponding legs in the legOrder list
int hipMax[] = {23, 90, 23, 90};*/

 //turn left values:
/*byte legOrder[] = {1, 2, 3, 4};
int hipMin[] = {68, 0, 68, 0}; //for corresponding legs in the legOrder list
int hipMax[] = {0, 68, 0, 68};*/

 //turn right values:
byte legOrder[] = {4, 3, 2, 1};
int hipMin[] = {68, 0, 68, 0}; //for corresponding legs in the legOrder list
int hipMax[] = {0, 68, 0, 68};

void setServoMovement() {
  unsigned long elapsedTime = millis()-movementStartTime;
  for ( int leg = 0 ; leg <= 3 ; leg++ ) {
    unsigned int currentTimePosition;
    currentTimePosition = (millis()-movementStartTime+((movementSpeed/4)*(4-leg)))%movementSpeed;
    Serial.println(map( currentTimePosition,0,movementSpeed,hipMin,hipMax));
    if (currentTimePosition <= legMovementDuration) { //a leg needs to be risen, no hip movement during this action
      setLeg(legOrder[leg], legMaxRaise); 
    }
    else { //hip can be moved again (during putting down the leg too)
      if ( currentTimePosition >= legMovementDuration+hipMovementDuration ) { //put down leg
        setLeg(legOrder[leg], legsOnGround);
      }
      //move hip
      setHip( legOrder[leg] , map(currentTimePosition,0,movementSpeed,hipMin[leg],hipMax[leg]) );
    }
  }
  
}

