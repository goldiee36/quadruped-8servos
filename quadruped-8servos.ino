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

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);  // LED pin
  
  // assign servos to pins and reposition
  frh.attach(5); frh.write(getfrh(45)); delay(delaybw);
  frl.attach(6); frl.write(getfrl(70)); delay(delaybw);
  flh.attach(7); flh.write(getflh(45)); delay(delaybw);
  fll.attach(8); fll.write(getfll(70)); delay(delaybw);
  rlh.attach(9); rlh.write(getrlh(45)); delay(delaybw);
  rll.attach(10); rll.write(getrll(70)); delay(delaybw);
  rrh.attach(11); rrh.write(getrrh(45)); delay(delaybw);
  rrl.attach(12); rrl.write(getrrl(70)); delay(delaybw);
  
  delay(2000);
}





void loop() 
{ 

}




