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

#define frh22p5 (frh90-frh0)/4
#define flh22p5 (flh90-flh0)/4
#define rlh22p5 (rlh90-rlh0)/4
#define rrh22p5 (rrh90-rrh0)/4

//LEGS
#define frl90 155
#define fll90 17
#define rll90 145
#define rrl90 10

#define frl0 68
#define fll0 101
#define rll0 54
#define rrl0 95

#define frl22p5 (frl90-frl0)/4
#define fll22p5 (fll90-fll0)/4
#define rll22p5 (rll90-rll0)/4
#define rrl22p5 (rrl90-rrl0)/4

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);  // LED pin
  // assign servos to pins and center servos
  frh.attach(5); frh.write(frh0+frh22p5*2); delay(delaybw);
  frl.attach(6); frl.write(frl90-frl22p5); delay(delaybw);
  flh.attach(7); flh.write(flh0+flh22p5*2); delay(delaybw);
  fll.attach(8); fll.write(fll90-fll22p5); delay(delaybw);
  rlh.attach(9); rlh.write(rlh0+rlh22p5*2); delay(delaybw);
  rll.attach(10); rll.write(rll90-rll22p5); delay(delaybw);
  rrh.attach(11); rrh.write(rrh0+rrh22p5*2); delay(delaybw);
  rrl.attach(12); rrl.write(rrl90-rrl22p5); delay(delaybw);
  

  delay(2000);
}



void loop() 
{ 

}




