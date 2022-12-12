#include<IBusBM.h>
#include <Dynamixel_Serial.h>

#define CH1 A0
#define CH2 A1
#define CH3 A2
#define CH4 A3
#define CH5 A4
#define CH6 A5

//#define a 0
//#define b 1
#define c 0
#define d 1

#define Serial_Baud_Rate 23040

#define SERVO_ID1 7
#define SERVO_ID2 3
#define SERVO_ID3 7                   // ID of which we will set Dynamixel too
#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode

const int echo1 = 2;
const int trig1 = 4;
double duration1, distance1;
int program = 1;
//
uint16_t motor1_step = 10;
uint16_t motor2_step = 10;
uint16_t claw_step = 10;
uint16_t Sspeed = 500;

uint16_t motor1_current = 0;
uint16_t motor2_current = 0;
uint16_t clawmotor_current = 0;
uint16_t reset_motor2 = 0;

int angle_closed = 30;
int angle_open = 30;
int position = Dynamixel.readPosition(SERVO_ID3);
uint16_t close_angle = position + angle_closed;
uint16_t open_angle = position - angle_open;

int ch1;
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;

bool Jaw_isopened = 1;

int multiplier = 1;
void move_arm1() {
  while (ch1>10 || ch1<-10) 
  {
    Dynamixel.servo(SERVO_ID1, motor1_current, Sspeed);
    motor1_current += (ch1)*multiplier;
  }
}
//
//void move_claw() {
//  if (Jaw_isopened) {
//      while(true) 
//      {
//        Dynamixel.servo(SERVO_ID3, close_angle, Sspeed);
//        Jaw_isopened = false;
//        if (Dynamixel.checkMovement(SERVO_ID3) == 0) break;
//        else if (!Jaw_isopened) 
//        {
//          Dynamixel.servo(SERVO_ID3, open_angle, Sspeed);
//          Jaw_isopened = true;
//        }
//      }
//    }
//}


IBusBM ibus;



int readchannel(int channelInput,int min,int max,int defaultvalue)
{
  int ch=pulseIn(channelInput,HIGH,30000);
  //if(ch<100) return defaultvalue;
  return map(ch,1000,2000,min,max);
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  pinMode(CH1,INPUT);
  pinMode(CH2,INPUT);
  pinMode(CH3,INPUT);
  pinMode(CH4,INPUT);
  pinMode(CH5,INPUT);
  pinMode(CH6,INPUT);

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  //SET ID Dynamixel.setID(0xFE,SERVO_ID1);  
  //Dynamixel.begin(SERVO_SET_Baudrate);
  //Dynamixel.setMode(SERVO_ID1, SERVO, CW_LIMIT_ANGLE, CCW_LIMIT_ANGLE);
  //Dynamixel.setMode(SERVO_ID2, SERVO, CW_LIMIT_ANGLE, CCW_LIMIT_ANGLE);
  //Dynamixel.setMode(SERVO_ID3, SERVO, CW_LIMIT_ANGLE, CCW_LIMIT_ANGLE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  ch1=readchannel(CH1,-100,100,0);
  ch2=readchannel(CH2,-100,100,0);
  ch3=readchannel(CH3,-100,100,0);
  ch4=readchannel(CH4,-100,100,0);
  ch5=readchannel(CH5,-100,100,0);
  ch6=readchannel(CH6,-100,100,0);

  //move_arm1();



  if(ch1<0)//ARM1 DOWN
  {
    
  }
  
  if(ch2>0)//ARM2 UP
  {
    
  }
  else if(ch2<0)//ARM2 DOWN
  {
    
  }
  
  if(ch3>0)//MOVE FORWARD
  {
//    digitalWrite(a , HIGH);
//    digitalWrite(b , HIGH);
    digitalWrite(c , HIGH);
    digitalWrite(d , HIGH);
  }
  else if(ch3<0)//MOVE BACKWARD
  {
//    digitalWrite(a , LOW);
//    digitalWrite(b , LOW);
    digitalWrite(c , LOW);
    digitalWrite(d , LOW);
  }

  if(ch4>0)//MOVE RIGHT
  {
//    digitalWrite(a , HIGH);
//    digitalWrite(b , LOW);
    digitalWrite(c , HIGH);
    digitalWrite(d , LOW);
  }
  else if(ch4<0)//MOVE LEFT
  {
//    digitalWrite(a , LOW);
//    digitalWrite(b , HIGH);
    digitalWrite(c , LOW);
    digitalWrite(d , HIGH);
  }
  
  if(ch5>0)//AUTO MODE ON
  {
     while (program == 1)
    {
    //sensor 1 measure
    digitalWrite(trig1, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);

    duration1 = pulseIn(echo1, HIGH);
    distance1 = (duration1 / 2) * 0.0343 * 10; // from cm to mm
    }

   while (distance1 < 295)
  {
    //move straight code
//    digitalWrite(a , HIGH);
//    digitalWrite(b , HIGH);
    digitalWrite(c , HIGH);
    digitalWrite(d , HIGH);
  }

    //turn right
//    digitalWrite(a , HIGH);
//    digitalWrite(b , LOW);
    digitalWrite(c , HIGH);
    digitalWrite(d , LOW);
}
  else if(ch5<0)//AUTO MODE OFF
  {
    
  }

    if(ch6>0)//CLAW OPEN
  {
    
  }
  else if(ch6<0)//CLAW CLOSE
  {
    
  }


  Serial.print("CH1=");
  Serial.print(ch1);

  Serial.print("| CH2=");
  Serial.print(ch2);

  Serial.print("| CH3=");
  Serial.print(ch3);

  Serial.print("| CH4=");
  Serial.print(ch4);

  Serial.print("| CH5=");
  Serial.print(ch5);

  Serial.print("| CH6=");
  Serial.println(ch6);
  


}
