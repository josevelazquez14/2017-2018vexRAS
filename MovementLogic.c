#include "SensorLogic.h"
#include "EncoderLogic.c"

#if META_KNIGHT
#include "MetaKnightBaseBuild.c"
#elif KIRBY
#include "MotorAndSensorConfig.c"
#endif

//constants
#define MOTOR_STOP 40
#define ROTATION 60
#define LEFT 'L'
#define RIGHT 'R'

//globals
int direction = 1;//why is this here???//LEGACY

//function to move the base, controlled by speed
void baseMove(int leftSide, int rightSide){

	//Kirby
	motor[baseTopLeft]= leftSide;
	motor[baseTopRight]= -rightSide;
	motor[baseBottomLeft]= leftSide;
	motor[baseBottomRight]= -rightSide;

}

//stops base
void suddenBrakes(){
	//for use when turning
	//stops instantly

	baseMove(0,0);
}

//to avoid exceeding desired distance
/**********************************************
gradualBrakes - returns new speed based on distance remaining. Used when going to fast
	currentSpeed - speed currently sent to motors
	distRemaining - distance remaining to be traveled, can be in any unit
	origDist - distance to travel originally

	distRemaining and origDist HAVE to be the same units
**********************************************/
int gradualBrakes(int currentSpeed, int distRemaining, int origDist){
  //for use when moving forward or back at speed
  //stops the robot gradually so it doesnt tip over

  //runs on every iteration of moveForward loop

  int speed = currentSpeed;

  if(origDist == 0){
    return 0;
  }

  if(distRemaining < origDist/4
      && currentSpeed > MOTOR_STOP){

    float reductCoeff = distRemaining/origDist;
    float decimalSpeed = reductCoeff * currentSpeed;
    speed = (int) ceil(decimalSpeed);
  }
  else if(currentSpeed <= MOTOR_STOP){
    //return MOTOR_STOP;
		return 0;
  }

  //returns new speed
  return speed;
}


/*************************
	Move Forward
*************************/

//legacy move forward function
void moveForward(int ticks)//ticks: dist in ticks
{
	resetEncoders();
	direction = 1;

	while((getAbsLeft()<ticks)&&(getAbsRight()<ticks))
	{
				//setAbsLeft(abs(SensorValue[baseLeft]));
				//setAbsRight(abs(SensorValue[baseRight]));


		if(getAbsLeft() > getAbsRight())
		{
			baseMove(58, 60);

		}
  	else if(getAbsLeft() < getAbsRight())
		{
			baseMove(60, 58);

		}
		else if(getAbsLeft()==getAbsRight())
		{
			baseMove(60,60);
		}
	}

	//use brake function instead of this stop
			suddenBrakes();
}

//use inches as input to move
void moveFrontIN(float inches){//TODO still using legacy functs must change
	moveForward(inToTicks(inches));
}

//TODO: move front with speed percentage

/**************************
	Move Back
***************************/

//legacy reverse funct
void moveBackward(int ticks)//I think this is redundant
{
	resetEncoders();
	direction = -1;

	while((getAbsLeft()<ticks)&&(getAbsRight()<ticks))
	{
				//setAbsLeft(abs(SensorValue[baseBottomLeft]));
				//setAbsRight(abs(SensorValue[baseBottomRight]));


		if(getAbsLeft() > getAbsRight())
		{
			motor[baseTopLeft]= -58;
    	motor[baseTopRight]= 60;
    	motor[baseBottomLeft]= -58;
    	motor[baseBottomRight]= 60;

		}
  	else if(getAbsLeft() < getAbsRight())
		{

			motor[baseTopLeft]= -60;
    	motor[baseTopRight]= 58;
    	motor[baseBottomLeft]= -60;
    	motor[baseBottomRight]= 58;

		}
		else if(getAbsLeft()==getAbsRight())
		{
			motor[baseTopLeft]= -60;
    	motor[baseTopRight]= 60;
    	motor[baseBottomLeft]= -60;
    	motor[baseBottomRight]= 60;
		}
	}
	//use brakes funct instead of this stop
	motor[baseTopLeft]= 0;
  motor[baseTopRight]= 0;
  motor[baseBottomLeft]= 0;
  motor[baseBottomRight]= 0;
}


//new functions
/********************
move - basic linear movement function
	ticks - is a direction vector (includes direction)
	speed - speed of motors 0 - 127 inclusive
********************/
void move(int ticks, int speed){
	//TODO make speed eq'ing dynamic
	//	check bug: robot might not travel full distance

	int dir = 1;

	if(ticks < 0){
		dir = -1;
	}

	if(speed < 0){
		speed = abs(speed);
	}

	if(speed<=MOTOR_STOP){
		baseMove(0,0);
		return;
	}

	resetEncoders();

	while((getAbsLeft()<ticks)&&(getAbsRight()<ticks))
	{
		int distRemaining = ticks - getAbsLeft();
		speed = gradualBrakes(speed, distRemaining, ticks);

		if (speed == 0) {	//try this first since it might give a bug
			// try using a getSpeed function instead
			break;
		}

		if(getAbsLeft() > getAbsRight())
		{
			baseMove(speed - 2, speed);

		}
  	else if(getAbsLeft() < getAbsRight())
		{
			baseMove(speed, speed - 2);

		}
		else if(getAbsLeft()==getAbsRight())
		{
			baseMove(speed,speed);
		}
	}

	suddenBrakes();

}

//TODO place side equalizer appart from the move functions using encoder difference
//this way we can make equalizing more dynamic and that way more efficient

/********************
rotate - basic turning function
	side - direction of rotation LEFT (CCW) or RIGHT (CW)
	angle - degrees of rotation
********************/
void rotate(char side, int angle){//FUNCION#8: Giro

	int r = 1;
	int l = 1;
	int speed = ROTATION;

	if(side==LEFT){
		l = -1;
	}
	else{
		r = -1;
	}

	if(speed<MOTOR_STOP){
		baseMove(0,0);
		return;
	}

	resetGyro(gyro);

	while(gyroToDegree(getAbsGyro(gyro)) < angle){

		int distRemaining = angle - gyroToDegree(getAbsGyro(gyro));
		speed = gradualBrakes(speed, distRemaining, angle);

		if(speed == 0){
			break;
		}
		baseMove(l*speed, r*speed);
	}

	suddenBrakes();

}


/*****************************************************************
******************************************************************
******************************************************************
******************************************************************/
/************************************
TODO from this point on code is legacy, and not scalable.
has to be modified
************************************/
/////////////////////////////////////////
///////////  TURN   /////////////////////
/////////////////////////////////////////

int gyroscope;

void Giro(char Side, int value){//FUNCION#8: Giro

	SensorType[gyro] = sensorNone;
	SensorType[gyro] = sensorGyro;
	wait1Msec(1500);
	gyroscope = abs(SensorValue[gyro]);

	if(Side=='L'){
		while(gyroscope < value){

			gyroscope = abs(SensorValue[gyro]);
			motor[baseTopLeft]= 60;
			motor[baseTopRight]= 60;
			motor[baseBottomLeft]= 60;
			motor[baseBottomRight]= 60;
		}
		motor[baseTopLeft]= -15;
		motor[baseTopRight]= -15;
		motor[baseBottomLeft]= -15;
		motor[baseBottomRight]= -15;
		wait1Msec(250);

	}

	else if(Side=='R'){
		while(gyroscope < value){

			gyroscope = abs(SensorValue[gyro]);
			motor[baseTopLeft]= -60;
			motor[baseTopRight]= -60;
			motor[baseBottomLeft]= -60;
			motor[baseBottomRight]= -60;
		}
		motor[baseTopLeft]= 15;
		motor[baseTopRight]= 15;
		motor[baseBottomLeft]= 15;
		motor[baseBottomRight]= 15;
		wait1Msec(250);

	}
}

/////////////////////////////////////////
///////////  END TURN  ////////////////
/////////////////////////////////////////

/////////////////////////////////////////
/////////High ultra control /////////////
/////////////////////////////////////////

void hightControl(int maxHigh){
//lowest point 670
//max point 2100
bool run = false;
		while((SensorValue(highDetector)<16) && (SensorValue(lift)<maxHigh)){
	   	  motor(torreTopRight)= -127;
	   	  motor(torreTopLeft) = 127;
	    	motor(torreBottomLeft)= -127;
	    	motor(torreBottomRight)= 127;

	    	run = true;
	    }

	    if (run){
	    	motor(torreTopRight)= -50;
	    	 motor(torreTopLeft) = 50;
	    	motor(torreBottomLeft)= -50;
	    	motor(torreBottomRight)= 50;
	    }

}
/////////////////////////////////////////
/////////// END High ultra control //////
/////////////////////////////////////////


/***********************************************
FROM THIS POINT ON THESE FUNCTIONS SHOULD BE IN AutomatedMotions.c
THEY ARE PLACED HERE FOR THE TIME BEING UNTIL THEY ARE ABSTRACTED
************************************************/
/////////////////////////////////////////
/////////// PUT CONE IN STACK///// //////
/////////////////////////////////////////

void stack (int high){
bool run = false;
	if(SensorValue(lift)>750){
		while((SensorValue(highDetector)>16) && (SensorValue(lift)<high)){
	   	  motor(torreTopRight)= 60;
	   	  motor(torreTopLeft) = -60;
	    	motor(torreBottomLeft)= 60;
	    	motor(torreBottomRight)= -60;

	    	run = true;
	    }
	  }


	    if (run){
	    	motor(torreTopRight)= -50;
	    	 motor(torreTopLeft) = 50;
	    	motor(torreBottomLeft)= -50;
	    	motor(torreBottomRight)= 50;
	    }
}

/////////////////////////////////////////
/////////// END PUT CONE IN STACK/ //////
/////////////////////////////////////////

/////////////////////////////////////////
/////////// CONE LIFT /////////////////////
/////////////////////////////////////////

void coneLift(char direction, int height){
	//lowest point 0
	//max high 2900-3050
		if(direction == 'U'){
				while(SensorValue(chainBar)<height){
					motor(chainPivot) = -90;
				}
			}

		if(direction == 'D'){
			while((SensorValue(chainBar)>height)){
				motor(chainPivot) = 127;
			}
		}

		motor(chainPivot) = 0;
	}

/////////////////////////////////////////
/////////// END CONE LIFT/////////// ////
/////////////////////////////////////////

/////////////////////////////////////////
/////////// MOVING GOAL /////////////////
/////////////////////////////////////////
void moveMG(char direction, int height){//height param needs to be removed

SensorValue[MGPiston] =0;

		while(SensorValue[movingGoal]<height && 'U'){
		   		 motor[baseMG]= -127;
		 }


		while(SensorValue[movingGoal]>height && 'D'){
		    motor[baseMG]= 127;
 		}


		motor[baseMG]= 0;

}
/////////////////////////////////////////
/////////// END MOVING GOAL//////////////
/////////////////////////////////////////
