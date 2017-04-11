/***************************************************/
/////////////////////////////////////////////////////
///                                               ///
///    Code for printed Mini 9G Quadruped         ///
///    http://www.thingiverse.com/thing:38159     ///
///    TheCase v.1 Dec2012                        ///
///                                               ///
///    derived from Chopstick Junior 1.0          ///
///    version 1.0.6                              ///
///    by Lutz Michaelis, November 2011           ///  
///    more about this robot and contact form:    ///
///    http://letsmakerobots.com/node/29708       ///
///    powered by                                 ///
///    http://www.roboter-selbstgebaut.com        ///
/////////////////////////////////////////////////////

#include <Servo.h>
// set the names of the servos
/*
frh = front right hip
 frl = front right leg
 flh = front left hip
 fll = front left leg
 rlh = rear left hip
 rll = rear left leg
 rrh = rear right hip
 rrl = rear right leg
 eye = sevor for sensor
 */
Servo frh;
Servo frl;
Servo flh;
Servo fll;
Servo rlh;
Servo rll;
Servo rrh;
Servo rrl;
Servo eye;

// set variables needed for some tasks

//set logical values for physical home position (cheap Chinese servos are cheap!)
#define frh0 90
#define frl0 70
#define flh0 81
#define fll0 103
#define rlh0 81
#define rll0 85
#define rrh0 105
#define rrl0 93

#define home_frh 90
#define home_frl 70
#define home_flh 81
#define home_fll 103
#define home_rlh 81
#define home_rll 85
#define home_rrh 105
#define home_rrl 93

#define frh22 118
#define flh22 58
#define rlh22 108
#define rrh22 80

#define frh45 135
#define frl45 108
#define flh45 45
#define fll45 53
#define rlh45 125
#define rll45 130
#define rrh45 65
#define rrl45 50

#define frl70 140
#define fll70 28
#define rll70 168
#define rrl70 24

#define frh90 180
#define frl90 155
#define flh90 0
#define fll90 18
#define rlh90 170
#define rll90 180
#define rrh90 25
#define rrl90 13



#define frhm22 63
#define frlm22 50
#define flhm22 105
#define fllm22 118
#define rlhm22 55
#define rllm22 70
#define rrhm22 125
#define rrlm22 112

#define frhm45 41
#define flhm45 127
#define rlhm45 33
#define rrhm45 147

int delaybw = 50; //high current draw protection

int b;
int x;
int w;
int up;
int up2;
int up3;
int down;
int down2;
int steps;
int rightsteps;
int leftsteps;
int back;
int pos;
int sensor = A0;
int distance = 0;

unsigned long echo = 0;
int ultraSoundPulse = 13;
int ultraSoundEcho = 3; // Ultrasound signal pin
unsigned long ultrasoundValue = 0;

const int buttonPin = 2;     
int buttonState = 0;

//////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);  // LED pin
  pinMode(buttonPin, INPUT);   
  // assign servos to pins and center servos
  frh.attach(5); delay(delaybw);
  frl.attach(6); delay(delaybw);
  flh.attach(7); delay(delaybw);
  fll.attach(8); delay(delaybw);
  rlh.attach(9); delay(delaybw);
  rll.attach(10); delay(delaybw);
  rrh.attach(11); delay(delaybw);
  rrl.attach(12); delay(delaybw);

 

  delay(2000);
  frl.write(frl70); delay(delaybw);
  fll.write(fll70); delay(delaybw);
  rll.write(rll70); delay(delaybw);
  rrl.write(rrl70); delay(delaybw);

  frh.write(frh45); delay(delaybw);
  flh.write(flh45); delay(delaybw);
  rlh.write(rlh45); delay(delaybw);
  rrh.write(rrh45); delay(delaybw);

  delay(2000);
}


void loop() 
{ 
  fw2(); fw2(); fw2();
  delay(5000);
  fw3(); fw3(); fw3();
  delay(5000);
  stand();
  delay(5000);
  gym();
  delay(5000);
  wink();
  delay(5000);
  laydown();
  delay(5000);
  standup();
  delay(5000); 

}





void frontlegs(int value) //+85 -- -85
{
  frl.write(value); delay(delaybw);
  fll.write(value); delay(delaybw);
}

void rearlegs(int value) //+85 -- -85
{
  rll.write(value); delay(delaybw);
  rrl.write(value); delay(delaybw);
}

void fronthips(int value) //+85 -- -22
{
  frh.write(value); delay(delaybw);
  flh.write(value); delay(delaybw);
}

void rearhips(int value) //+85 -- -22
{
  rlh.write(value); delay(delaybw);
  rrh.write(value); delay(delaybw);
}

void allhips(int offset) //+85 -- -22
{
  frh.write(offset); delay(delaybw);
  flh.write(offset); delay(delaybw);
  rlh.write(offset); delay(delaybw);
  rrh.write(offset); delay(delaybw);
}

void fw2() {
 // RL lab fel, h'tra dol, fr telejsen elore, keresytben ugyanez,
  //mjad ugrás elől eredetibe vissza, átul teljesn hátra,
  //majd hátsó lábakta egyeésvel eredetibe hozni

  rll.write(rll45); delay(delaybw);
  frh.write(frh90); delay(delaybw);
  rll.write(rll70); delay(delaybw);
  rrl.write(rrl45); delay(delaybw);
  flh.write(flh90); delay(delaybw);
  rrl.write(rrl70); delay(delaybw);

  delay(delaybw*2);

  frh.write(frh45);
  flh.write(flh45);
  rlh.write(rlh90);
  rrh.write(rrh90);
  
  delay(delaybw*2);

  rll.write(rll45); delay(delaybw);
  rlh.write(rlh45); delay(delaybw);
  rll.write(rll70); delay(delaybw);
  rrl.write(rrl45); delay(delaybw);
  rrh.write(rrh45); delay(delaybw);
  rrl.write(rrl70); delay(delaybw);


  delay(delaybw*2);
}


void fw3() {
  frl.write(frl0);
  rll.write(rll0);
  frh.write(frh90);
  rlh.write(rlh90);
  flh.write(flh0);
  rrh.write(rrh0);
  delay(250);
  frl.write(frl70);
  rll.write(rll70);
  delay(250);
  fll.write(fll0);
  rrl.write(rrl0);
  flh.write(flh90);
  rrh.write(rrh90);
  frh.write(frh0);
  rlh.write(rlh0);
  delay(250);
  fll.write(fll70);
  rrl.write(rrl70);
  delay(250);
}











/*




void loop2()
{
  //distance = analogRead(sensor);
  buttonState = digitalRead(buttonPin);
  distance = ping();
  distance = 100;
  Serial.println(distance);
  
  if (distance > 5)  // oh, there is an obstacle in my path but no need to panic it's still not in the danger zone, just steer to the left to avoid a crash
   {
   test();
   while(back < 5){        // just a loop for 5 steps backwards since he run into an obstacle
   backward();
   back++;
   }
   test();
   while(leftsteps < 5){        // just a loop for 5 steps left turn since he run into an obstacle
   leftturn();
   leftsteps++;
   }
   if (back == 5 && leftsteps == 5)
   {
   if (distance > 5)  // oh, there is an obstacle in my path but no need to panic it's still not in the danger zone, just steer to the left to avoid a crash
   {   
   stand();
   delay(1000);
   gym();
   delay(1000);
   wink();
   delay(3000);
   laydown();
   delay(3000);
   standup();
   while(back < 10){        // just a loop for 5 steps backwards since he run into an obstacle
   backward();
   back++;
   }
   back = 0;
   leftsteps = 0;
   }
   test();
   }
   }
   else
   {
   forward2(); 
   }
   


 debug area 
  if  (buttonState == HIGH){
    flatout();
  //}else if (distance > 2){
    //backward();
   // flatout();
  }else{ 
    forward();
  }

}
*/

 void idle() {
    delay(150);
  }

void standup()
{
  up2 = 0;
  up3 = 0;
  frh.write(home_frh+22);
  flh.write(home_flh-22);
  rlh.write(home_rlh+22);
  rrh.write(home_rrh-22);
  for(up = 0; up < 80; up++)
  {
    frl.write(up+home_frl);
    up2 = up2 - 1;
    fll.write(up2+home_fll);
    delay(20);
  }

  for(up = 0; up < 90; up++)
  {
    rll.write(up+home_rll);
    up3 = up3 - 1;
    rrl.write(up3+home_rrl);
    delay(15);
  }
}
//////////////////////////////////////
void sleep()
{
  // hips
  frh.write(home_frh-20);
  flh.write(home_flh);
  rlh.write(home_rlh-20);
  rrh.write(home_rrh);
  // legs
  frl.write(home_frl-90);
  fll.write(home_fll+90);
  rll.write(home_rll-90);
  rrl.write(home_rrl+90);
}
//////////////////////////////////////
void stand()
{
  frh.write(home_frh-20);
  frl.write(home_frl+80);
  delay(20);
  flh.write(home_flh-10);
  fll.write(home_fll-70);
  delay(20);
  rlh.write(home_rlh-10);
  rll.write(home_rll+80);
  delay(20);
  rrh.write(home_rrh-20);
  rrl.write(home_rrl-70); 
  delay(20);
}
//////////////////////////////////////
void forward()
{
  // lift front right leg, move front right hip forward and rear right hip backward, lower front right leg
  rll.write(home_rll+50);  // lower the diagonal opposite leg a bit to keep the balance
  frl.write(home_frl+30);  //orig 140
  idle();
  frh.write(home_frh-45);
  rrh.write(home_rrh+60); // orig 90
  idle();
  frl.write(home_frl+80);  //orig 170
  rll.write(home_rll+60);  //orig 170  //put the diagonal opposite leg down to keep the balance
  // lift rear left leg, move rear left hip forward and front right hip backward, lower rear left leg 
  frl.write(home_frl+80);  //orig 140 //lower the diagonal opposite leg a bit to keep the balance
  rll.write(home_rll+50); 
  idle();
  rlh.write(home_rlh+30); //orig 120
  frh.write(home_frh+20);
  idle();
  rll.write(home_rll+60);  // orig 170
  fll.write(home_fll+80);  // put the diagonal opposite leg down to keep the balance
  // lift front left leg, move front left hip forward and rear left hip backward, lower front left leg
  rrl.write(home_rrl-20);  // orig 50  //lower the diagonal opposite leg a bit to keep the balance
  fll.write(home_fll-40);
  idle();
  flh.write(home_flh+60); //orig 110
  rlh.write(home_rlh-50);//orig 60
  idle();
  fll.write(home_fll-70);
  rrl.write(home_rrl-70);  // put the diagonal opposite leg down to keep the balance
  // lift rear right leg, move rear right hip forward and front left hip backward, lower rear right leg 
  fll.write(home_fll-40);  // lower the diagonal opposite leg a bit to keep the balance 
  rrl.write(home_rrl-40); 
  idle();
  rrh.write(home_rrh-20); //orig 30
  flh.write(home_flh); //orig 50
  idle();
  rrl.write(home_rrl-50); //orig 20
  fll.write(home_fll-70);  // orig 20 //put the diagonal opposite leg down to keep the balance
  idle();
}
/////////////////////////////////////
void rightturn()
{
  // lift front right leg, move front right hip forward and rear right hip backward, lower front right leg
  frl.write(home_frl+60);
  idle();
  frh.write(home_frh-60);
  rrh.write(home_rrh);
  idle();
  frl.write(home_frl+80);
  // lift rear left leg, move rear left hip forward and front right hip backward, lower rear left leg 
  rll.write(home_rll+60); 
  idle();
  rlh.write(home_rlh+40);
  frh.write(home_frh+10);
  idle();
  rll.write(home_rll+80);
  // lift front left leg, move front left hip forward and rear left hip backward, lower front left leg
  fll.write(home_fll-50);
  idle();
  flh.write(home_flh+40);
  rlh.write(home_rlh-40);
  idle();
  fll.write(home_fll-70);
  // lift rear right leg, move rear right hip forward and front left hip backward, lower rear right leg  
  rrl.write(home_rrl-30); 
  idle();
  rrh.write(home_rrh-20);
  flh.write(home_flh-40);
  idle();
  rrl.write(home_rrl-70);
  idle();
}
/////////////////////////////////////
void leftturn()
{
  // lift front right leg, move front right hip forward and rear right hip backward, lower front right leg
  frl.write(home_frl+60);
  idle();
  frh.write(home_frh-60);
  rrh.write(home_rrh+10);
  idle();
  frl.write(home_frl+80);
  // lift rear left leg, move rear left hip forward and front right hip backward, lower rear left leg 
  rll.write(home_rll+60); 
  idle();
  rlh.write(home_rlh);
  frh.write(home_frh+30);
  idle();
  rll.write(home_rll+80);
  // lift front left leg, move front left hip forward and rear left hip backward, lower front left leg
  fll.write(home_fll-30);
  idle();
  flh.write(home_flh);
  rlh.write(home_rlh-30);
  idle();
  fll.write(home_fll-70);
  // lift rear right leg, move rear right hip forward and front left hip backward, lower rear right leg  
  rrl.write(home_rrl-30); 
  idle();
  rrh.write(home_rrh-60);
  flh.write(home_flh-10);
  idle();
  rrl.write(home_rrl-70);
  idle();
}
/////////////////////////////////////
void backward()
{
  // lift front right leg, move front right hip backward and rear right hip forward, lower front right leg
  frl.write(home_frl+60);
  idle();
  frh.write(home_frh+10);
  rrh.write(home_rrh-40);
  idle();
  frl.write(home_frl+80);
  // lift rear left leg, move rear left hip backward and front right hip forward, lower rear left leg 
  rll.write(home_rll+40); 
  idle();
  rlh.write(home_rlh-30);
  frh.write(home_frh-45);
  idle();
  rll.write(home_rll+80);
  // lift front left leg, move front left hip backward and rear left hip forward, lower front left leg
  fll.write(home_fll-50);
  idle();
  flh.write(home_flh-20);
  rlh.write(home_rlh+30);
  idle();
  fll.write(home_fll-70);
  // lift rear right leg, move rear right hip backward and front left hip forward, lower rear right leg  
  rrl.write(home_rrl-30); 
  idle();
  rrh.write(home_rrh+20);
  flh.write(home_flh+20);
  idle();
  rrl.write(home_rrl-70);
  idle();
}
/////////////////////////////////////
void laydown() // lay down
{
  frh.write(home_frh-20);
  flh.write(home_flh-10); 
  for (down = 80; down > 0; down = down - 1){
    frl.write(home_frl+down);
    down2 = 100 - down;
    fll.write(home_fll+down2);
    delay(15);
  } 
  delay(1000);
  rlh.write(home_rlh-10);
  rrh.write(home_rrh-20);
  for (down = 80; down > 0; down = down - 1){
    rll.write(home_rll+down);
    down2 = 100 - down;
    rrl.write(home_rrl+down2);
    delay(15);
  }
}
/////////////////////////////////////
void gym() // ok, this is not very serious but I needed to cheer me up a bit ;-) just see...
{
  int y;
  frh.write(home_frh-20);
  rll.write(home_rll+40);
  delay(200);
  fll.write(home_fll-50);
  flh.write(home_flh+20);
  fll.write(home_fll-70);
  delay(20);
  frl.write(home_frl-30);
  delay(20);
  rlh.write(home_rlh+30);
  delay(20);
  rrh.write(home_rrh-20);
  rrl.write(home_rrl-70); 
  delay(20);   
}
/////////////////////////////////////
void wink()
{
  for (b = 0; b < 3; b++){
    for (w = -30; w < -70; w = w -1)
    {
      frl.write(home_frl+w);
      delay(10);
    }
    for (w = -70; w < -30; w++)
    {
      frl.write(home_frl+w);
      delay(10);
    }
    delay(200);
  }
}
/////////////////////////////////////
void sweep()
{  
  for(pos = 20; pos < 160; pos += 1)   // goes from 0 degrees to 180 degrees 
  {                                    // in steps of 1 degree 
    eye.write(pos);                    // tell servo to go to position in variable 'pos' 
    delay(10);                         // waits 15ms for the servo to reach the position 
    distance = analogRead(sensor);
    //Serial.print(distance);
    //Serial.print(" - Position ");
    //Serial.print(pos);
    //Serial.println();
  } 
  for(pos = 160; pos >= 20; pos -= 1)      // goes from 180 degrees to 0 degrees 
  {                                
    eye.write(pos);                    // tell servo to go to position in variable 'pos' 
    delay(10);                         // waits 15ms for the servo to reach the position 
    distance = analogRead(sensor);
    //Serial.print(distance);
    //Serial.print(" - Position ");
    //Serial.print(pos);  
    //Serial.println();
  }       
}


