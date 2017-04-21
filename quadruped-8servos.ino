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

int currHipValues[4] = {-100, -100, -100, -100};

void setHip(byte hip, int degree) {
  switch (hip) {
        case 1:
          frh.write(getfrh(degree));
          currHipValues[0] = degree;
          break;
        case 2:
          flh.write(getflh(degree));
          currHipValues[1] = degree;
          break;
        case 3:
          rlh.write(getrlh(degree));
          currHipValues[2] = degree;
          break;
        case 4:
          rrh.write(getrrh(degree));
          currHipValues[3] = degree;
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
  frh.attach(5); setHip(1, 45); delay(50);
  frl.attach(6); setLeg(1, 70); delay(50);
  flh.attach(7); setHip(2, 45); delay(50);
  fll.attach(8); setLeg(2, 70); delay(50);
  rlh.attach(9); setHip(3, 45); delay(50);
  rll.attach(10); setLeg(3, 70); delay(50);
  rrh.attach(11); setHip(4, 45); delay(50);
  rrl.attach(12); setLeg(4, 70); delay(50);
  
  delay(2000);
  initMovement(1, 2000);
  //movementStartTime = millis();
  //setServoMovement();
  //delay(1000000);
}


//changing between movements: set new direction, speed. check current servo values. calculate 8-10 lineary distributed samples during the new movement.
//compare samples with current values, find the closest match. set the legs to the new choosen position individually without changing the orientation of the spider
//continue movement from this position

unsigned int movementSpeed = 10000; //time for advancing for all 4 leg. bigger values are slower

byte legOrder[4];
int hipMin[4];
int hipMax[4];

int calcHipValues[4];

void loop() {  
  setServoMovement();
}

void setDirectionVariables(byte desDirection) {
  switch (desDirection) {
        case 1: //move forward
          legOrder[0] = 4; legOrder[1] = 1; legOrder[2] = 3; legOrder[3] = 2;
          hipMin[0] = -23; hipMin[1] = 45; hipMin[2] = -23; hipMin[3] = 45; //for corresponding legs in the legOrder list
          hipMax[0] = 45; hipMax[1] = -23; hipMax[2] = 45; hipMax[3] = -23;
          break;
        case 2: //move backward
          legOrder[0] = 2; legOrder[1] = 3; legOrder[2] = 1; legOrder[3] = 4;
          hipMin[0] = -23; hipMin[1] = 45; hipMin[2] = -23; hipMin[3] = 45; 
          hipMax[0] = 45; hipMax[1] = -23; hipMax[2] = 45; hipMax[3] = -23;
          break;
        case 3: //move left
          legOrder[0] = 1; legOrder[1] = 2; legOrder[2] = 4; legOrder[3] = 3;
          hipMin[0] = 90; hipMin[1] = 23; hipMin[2] = 90; hipMin[3] = 23; 
          hipMax[0] = 23; hipMax[1] = 90; hipMax[2] = 23; hipMax[3] = 90;
          break;
        case 4: //move right
          legOrder[0] = 3; legOrder[1] = 2; legOrder[2] = 2; legOrder[3] = 1;
          hipMin[0] = 90; hipMin[1] = 23; hipMin[2] = 90; hipMin[3] = 23; 
          hipMax[0] = 23; hipMax[1] = 90; hipMax[2] = 23; hipMax[3] = 90;
          break;
        case 5: //turn left
          legOrder[0] = 1; legOrder[1] = 2; legOrder[2] = 3; legOrder[3] = 4;
          hipMin[0] = 68; hipMin[1] = 0; hipMin[2] = 68; hipMin[3] = 0; 
          hipMax[0] = 0; hipMax[1] = 68; hipMax[2] = 0; hipMax[3] = 68;
          break;
        case 6: //turn right
          legOrder[0] = 4; legOrder[1] = 3; legOrder[2] = 2; legOrder[3] = 1;
          hipMin[0] = 68; hipMin[1] = 0; hipMin[2] = 68; hipMin[3] = 0; 
          hipMax[0] = 0; hipMax[1] = 68; hipMax[2] = 0; hipMax[3] = 68;
          break;
      }

}


void initMovement(byte desiredDirection, unsigned int newMovementSpeed) {
  //A: calculate new hip positions (finds closest match) based on:
    //- the current hip positions
    //- and the desired movement 
  //B: move hips into the new positions without changing the body direction
  //C: calculate the new movementStartTime so the desired movement can be continued from the new hip positions - and set the new movementStartTime as well
  
  setDirectionVariables(desiredDirection);
  movementSpeed = newMovementSpeed;
  
  int closestHipValues[4];
  int savedCalcTime;

  // A:
  // find the closest match between current hip positions and possible hip positions in a movement
  int minDiffHips = 5000;
  Serial.print(currHipValues[0]); Serial.print(" # "); Serial.print(currHipValues[1]); Serial.print(" # "); Serial.print(currHipValues[2]); Serial.print(" # "); Serial.println(currHipValues[3]);
  unsigned long startmicro = micros();
  for ( int calctime = 0 ; calctime < 1000 ; calctime=calctime+(1000/70) ) {
    servoValues(0, 0, calctime, 1000, legOrder, hipMin, hipMax);
    int allHipDiff = 0;
    for ( int hip = 0 ; hip < 4 ; hip++ ) {
      int oneHipDiff = (calcHipValues[hip] - currHipValues[hip]);
      allHipDiff += abs(oneHipDiff); //abs function advice: keep other math outside the function
    }
    if (minDiffHips > allHipDiff) {
      minDiffHips = allHipDiff;
      closestHipValues[0] = calcHipValues[0];
      closestHipValues[1] = calcHipValues[1];
      closestHipValues[2] = calcHipValues[2];
      closestHipValues[3] = calcHipValues[3];
      savedCalcTime = calctime;
    }
    if (minDiffHips == 0) break;
    
    /*Serial.print(calctime); Serial.print(" ::: ");
    Serial.print(allHipDiff); Serial.print(" <> "); 
    Serial.print(calcHipValues[0]); Serial.print(" # "); Serial.print(calcHipValues[1]); Serial.print(" # ");
    Serial.print(calcHipValues[2]); Serial.print(" # "); Serial.println(calcHipValues[3]);*/
    
  }
  unsigned long endmicro = micros();
  Serial.print("Min hip diff: ");Serial.println(minDiffHips);
  //Serial.print("Calc time: ");Serial.println(endmicro-startmicro);


  // B:
  // closestHipValues[] contains the new hip positions
  // lift two opposite legs (1 and 3), turn the hips and put the legs down
  if (minDiffHips > 0) {
    int legMaxRaise = 25;
    int legsOnGround = 70;
    int legMovementDuration =  200; //for raising a leg
    int hipMovementDuration =  200; //for moving the hip into a new position while the leg is raised
  
    setLeg(1, legMaxRaise);
    setLeg(3, legMaxRaise);
    delay(legMovementDuration);
    setHip(1, closestHipValues[0]);
    setHip(3, closestHipValues[2]);
    delay(hipMovementDuration);
    setLeg(1, legsOnGround);
    setLeg(3, legsOnGround);
    delay(legMovementDuration);
    delay(2000);
  
    // lift the other two opposite legs (2 and 4), turn the hips and put the legs down
    setLeg(2, legMaxRaise);
    setLeg(4, legMaxRaise);
    delay(legMovementDuration);
    setHip(2, closestHipValues[1]);
    setHip(4, closestHipValues[3]);
    delay(hipMovementDuration);
    setLeg(2, legsOnGround);
    setLeg(4, legsOnGround);
    delay(legMovementDuration);
    delay(5000);
  }

  //C:
  movementStartTime = millis() - ((savedCalcTime/float(1000))*movementSpeed);
  
}



void setServoMovement() {
  servoValues(1, movementStartTime, millis(), movementSpeed, legOrder, hipMin, hipMax);
}

void servoValues(byte action, unsigned long movementStartTime_fun, unsigned long currentTime_fun, int movementSpeed_fun, byte legOrder_fun[], int hipMin_fun[], int hipMax_fun[]) {
  //action 1 means issue servo change, else write into the calcHipValues[] array
  int legMaxRaise = 0 ;
  int legsOnGround = 70;
  int legMovementDuration =  100; //for raising a leg
  int hipMovementDuration =  100; //for moving the hip into a new position while the leg is raised
    
  unsigned long elapsedTime = currentTime_fun-movementStartTime_fun;
  for ( byte leg = 0 ; leg <= 3 ; leg++ ) {
    unsigned int currentTimePosition = (elapsedTime+((movementSpeed_fun/4)*(4-leg)))%movementSpeed_fun;
    int calculatedHipValue = map(currentTimePosition,0,movementSpeed_fun,hipMin_fun[leg],hipMax_fun[leg]);
    if (action == 1) { // issue the servo changes
      if (currentTimePosition <= legMovementDuration) { //a leg needs to be risen, no hip movement during this action
        setLeg(legOrder_fun[leg], legMaxRaise);
      }
      else { //hip can be moved again (during putting down the leg too)
        if ( currentTimePosition >= legMovementDuration+hipMovementDuration ) { //put down leg
          setLeg(legOrder_fun[leg], legsOnGround);
        }
        //move hip
        setHip(legOrder_fun[leg] , calculatedHipValue);
        //Serial.print(legOrder_fun[leg]); Serial.print("->"); Serial.println(calculatedHipValue);
      }
    }
    else { //just put the results in the array - we need the hip value in every position even when we the leg should be lifted up
      calcHipValues[legOrder_fun[leg]-1] = calculatedHipValue;
    }
    
  }
}

