#include <MusafirBTS7960.h>             //Custom Library.
MusafirBTS7960 motorL(41, 42, 45, 5);   //enable-1 enable-2 pwm-1 pwm-2 -->> for Motor Left
MusafirBTS7960 motorR(49, 48, 46, 4);   //enable-1 enable-2 pwm-1 pwm-2 -->> for Motor Right

              //// ROS arduino Libraries : For Tutorial follow http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup
#include <Wire.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int16.h>

int leftMotorForward = 1;  // only two possibilities, 1 or -1
int rightMotorForward = 1;  // only two possibilities, 1 or -1

unsigned long timeOutPreviousMillis = 0;  //Velocity Time Out.
int velocityTimeOut = 2000; //ms
unsigned long currentMillis = 0;

ros::NodeHandle  nh;    // defining ROS Node

double requiredVelLeft = 0, requiredVelRight = 0;
#define  velConstrain  5

void left_wheel_desired_vel(const std_msgs::Int16& rate)
{
  requiredVelLeft = rate.data; 
  requiredVelLeft = constrain(requiredVelLeft, -velConstrain , velConstrain);  
  if(requiredVelLeft < 0) leftMotorForward = -1;
  else  leftMotorForward = 1;
  requiredVelLeft = abs(requiredVelLeft);
  requiredVelLeft = map(requiredVelLeft, 0, velConstrain, 0, 254);
  
  if(leftMotorForward == -1) motorL.backwardPWM(requiredVelLeft);
  else  motorL.forwardPWM(requiredVelLeft);
  
  timeOutPreviousMillis=  millis();
}

void right_wheel_desired_vel(const std_msgs::Int16& rate1)
{ 
  requiredVelRight = rate1.data ;
  requiredVelRight = constrain(requiredVelRight, -velConstrain , velConstrain);
  if(requiredVelRight < 0) rightMotorForward = -1;
  else  rightMotorForward = 1;
  requiredVelRight = abs(requiredVelRight);
  requiredVelRight = map(requiredVelRight, 0, velConstrain, 0, 254);

  if(rightMotorForward == -1) motorR.backwardPWM(requiredVelRight);
  else  motorR.forwardPWM(requiredVelRight);
  
  timeOutPreviousMillis= millis();
}

ros::Subscriber <std_msgs::Int16> subRateL("lwheel_desired_vel",left_wheel_desired_vel );
ros::Subscriber <std_msgs::Int16> subRateR("rwheel_desired_vel",right_wheel_desired_vel );

void setup() {
  // put your setup code here, to run once:
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
    motorL.disable();
    motorR.disable();
  }
  nh.spinOnce();
}

