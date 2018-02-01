#include <MusafirBTS7960.h>             //Custom Library. https://github.com/maazmobin/YellowBlockBot/tree/master/MusafirBTS7960
MusafirBTS7960 motorL(41, 42, 45, 5);   //enable-1 enable-2 pwm-1 pwm-2 -->> for Motor Left
MusafirBTS7960 motorR(49, 48, 46, 4);   //enable-1 enable-2 pwm-1 pwm-2 -->> for Motor Right

// part of coding below, that only save the state of direction to move.
int leftMotorForward = 1;  // only two possibilities, 1 or -1   
int rightMotorForward = 1;  // only two possibilities, 1 or -1

// Part of coding below, that will stop the motor if the velocity doesnt receive in a period of "velocityTimeOut". 
unsigned long timeOutPreviousMillis = 0; 
int velocityTimeOut = 2000; //ms  -->> CAN CHANGE THIS
unsigned long currentMillis = 0;

double requiredVelLeft = 0, requiredVelRight = 0;

//will truncate the value of velocity greater then the define below
#define  velConstrain  5  //      -->>  CAN CHANGE THIS

              ////Soft Start
#define   SOFTSTART   1   //1=en , -1=en
#define   STEP        10  //PWM
int   STEPTIME = 10;  //ms
unsigned long softStartPreviousMillis = 0; 
int softPwmLeft = 0;
int softPwmRight = 0;
              ////
              
              //// ROS arduino Libraries : For Tutorial follow http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup
#include <Wire.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int16.h>
            ////
ros::NodeHandle  nh;      // defining ROS Node

            //// ROS Subscriber Functions
void left_wheel_desired_vel(const std_msgs::Int16& rate)
{
  requiredVelLeft = rate.data;  //Getting Velocity
  requiredVelLeft = constrain(requiredVelLeft, -velConstrain , velConstrain); //Constrain the velocity  
        //Set the direction variable
  if(requiredVelLeft < 0) leftMotorForward = -1;
  else  leftMotorForward = 1;
        //Mapping the Value
  requiredVelLeft = abs(requiredVelLeft);
  requiredVelLeft = map(requiredVelLeft, 0, velConstrain, 0, 254);
  
  timeOutPreviousMillis=  millis();
}

void right_wheel_desired_vel(const std_msgs::Int16& rate1)
{ 
  requiredVelRight = rate1.data ;   //Getting Velocity
  requiredVelRight = constrain(requiredVelRight, -velConstrain , velConstrain); //Constrain the velocity
        //Set the direction variable
  if(requiredVelRight < 0) rightMotorForward = -1;
  else  rightMotorForward = 1;
        //Mapping the Value
  requiredVelRight = abs(requiredVelRight);
  requiredVelRight = map(requiredVelRight, 0, velConstrain, 0, 254);
  
  timeOutPreviousMillis= millis();
}
                ////
                
ros::Subscriber <std_msgs::Int16> subRateL("lwheel_desired_vel",left_wheel_desired_vel );   // subscriber defination
ros::Subscriber <std_msgs::Int16> subRateR("rwheel_desired_vel",right_wheel_desired_vel );  // subscriber defination

void setup() {
  nh.initNode();
  motorL.brakePWM(100);
  motorR.brakePWM(100);

  nh.subscribe(subRateL);
  nh.subscribe(subRateR);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  if (currentMillis - timeOutPreviousMillis >= velocityTimeOut ) {  // Break Velocity after Certain Time.
    requiredVelLeft = 0;
    requiredVelRight = 0;
  }

  if(SOFTSTART == 1)
  {
    if(currentMillis - softStartPreviousMillis >= STEPTIME )  {
    softPwmLeft =softPwmLeft + ((requiredVelLeft - softPwmLeft)/10);
    softPwmRight =softPwmRight + ((requiredVelRight - softPwmRight)/10);
          
          //Set the velocity Left
      if(leftMotorForward == -1) motorL.backwardPWM(softPwmLeft);
      else  motorL.forwardPWM(softPwmLeft);
          //Set the velocity Right
      if(rightMotorForward == -1) motorR.backwardPWM(softPwmRight);
      else  motorR.forwardPWM(softPwmRight);
      
      softStartPreviousMillis = currentMillis;
      }
    }
  else
  {          //Set the velocity Left
      if(leftMotorForward == -1) motorL.backwardPWM(requiredVelLeft);
      else  motorL.forwardPWM(requiredVelLeft);
          //Set the velocity Right
      if(rightMotorForward == -1) motorR.backwardPWM(requiredVelRight);
      else  motorR.forwardPWM(requiredVelRight);
    }
  nh.spinOnce();
}
