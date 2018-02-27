
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#include "AutonFiles.c"
#include "EncoderLogic.c"
#include "MovementLogic.c"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////	 GLOBAL VARIABLES  	///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
		bool active = false;

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////	 FUNCTIONS  	/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

	int liftHight[14];

/////////////////////////////////////////
///////	RESSETING ENCODERS	///////////////
/////////////////////////////////////////

//void resetEncoders()
//{
//	SensorValue[baseBottomLeft] = 0;
//	SensorValue[baseBottomRight] = 0;


//	getAbsLeft() = abs(SensorValue[baseBottomLeft]);
//	getAbsRight()  = abs(SensorValue[baseBottomRight]);

//}
/////////////////////////////////////////
///////	END RESETING ENCODERS	///////////
/////////////////////////////////////////


/////////////////////////////////////////
///////	RESETING Gyro	///////////////
/////////////////////////////////////////

void resetGyro()
{
	 SensorType[gyro] = sensorNone;
 		wait1Msec(1000);
 	 SensorType[gyro] = sensorGyro;
 		wait1Msec(1000);
}
/////////////////////////////////////////
///////	END RESETING Gyro	///////////
/////////////////////////////////////////

/////////////////////////////////////////
//////////////  FOWARD  /////////////////
/////////////////////////////////////////

void Foward(int forward)
{
	resetEncoders();

	while((getAbsLeft()<forward)&&(getAbsRight()<forward))
	{
				setAbsLeft(abs(SensorValue[baseLeft]));
				setAbsRight(abs(SensorValue[baseRight]));


		if(getAbsLeft() > getAbsRight())
		{
			motor[baseTopLeft]= 58;
    	motor[baseTopRight]= -60;
    	motor[baseBottomLeft]= 58;
    	motor[baseBottomRight]= -60;

		}
  	else if(getAbsLeft() < getAbsRight())
		{

			motor[baseTopLeft]= 60;
    	motor[baseTopRight]= -58;
    	motor[baseBottomLeft]= 60;
    	motor[baseBottomRight]= -58;

		}
		else if(getAbsLeft()==getAbsRight())
		{
			motor[baseTopLeft]= 60;
    	motor[baseTopRight]= -60;
    	motor[baseBottomLeft]= 60;
    	motor[baseBottomRight]= -60;
		}
	}
			motor[baseTopLeft]= 0;
    	motor[baseTopRight]= 0;
    	motor[baseBottomLeft]= 0;
    	motor[baseBottomRight]= 0;
}
/////////////////////////////////////////
///////////  END FOWARD   ///////////////
/////////////////////////////////////////





/////////////////////////////////////////
////////////  BACKWARD  /////////////////
/////////////////////////////////////////

void Backwards(int backward)
{
	resetEncoders();

	while((getAbsLeft()<backward)&&(getAbsRight()<backward))
	{
				setAbsLeft(abs(SensorValue[baseBottomLeft]));
				setAbsRight(abs(SensorValue[baseBottomRight]));


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
			motor[baseTopLeft]= 0;
    	motor[baseTopRight]= 0;
    	motor[baseBottomLeft]= 0;
    	motor[baseBottomRight]= 0;
		}
/////////////////////////////////////////
///////////  END BACKWARD   /////////////
/////////////////////////////////////////



/////////////////////////////////////////
///////////  TURN   /////////////////////
/////////////////////////////////////////

int gyroscope;

void Giro(char Side, int value){/////////////////////////////////////////////////////////////////////////////////////FUNCION#8: Giro

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
void moveMG(char direction, int height){

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


task stackCone(){

		if(vexRT[Btn8U]==1){
				coneLift('U',700);
    		hightControl(2100);
    		coneLift('U',2900);
    		stack(2100);
    		SensorValue(claw) = 1;
    		wait1Msec(500);
    		hightControl(2100);
    		SensorValue(claw) = 0;
				wait1Msec(500);
				coneLift('D',1000);  // dont works perfectly
			}

			return;
}

task base(){

			motor[baseTopLeft]= vexRT[Ch3] + vexRT[Ch1];
    	motor[baseTopRight]= -vexRT[Ch3] + vexRT[Ch1];
    	motor[baseBottomLeft]= vexRT[Ch3] + vexRT[Ch1];
    	motor[baseBottomRight]= -vexRT[Ch3] + vexRT[Ch1];

    	return;

}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

  SensorType[gyro]= sensorNone;

	SensorType[gyro]= sensorGyro;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{

	//Red autonomous pre loads side
  //	moveMG('D',0);  //potentiometer its reading 0 before its reach lowest point
		motor[baseMG]= 127;
		wait1Msec(2250);
		motor[baseMG]= 0;
		Foward(1450);
		moveMG('U', 1630);
		coneLift('U',2900);
		SensorValue(claw)=1;
		wait1Msec(500);
		SensorValue(claw)=0;
		coneLift('D',700);
	/*Foward(150);
		coneLift('D',0);
		coneLift('U',700);
    hightControl(2100);
    coneLift('U',2900);
    stack(2100);
    SensorValue(claw) = 1;
    wait1Msec(250);
    hightControl(2100);
    SensorValue(claw) = 0;
		wait1Msec(250);
		coneLift('D',2350);
		Backwards(600);
		Giro('R',450);
		Foward(150);
		Giro('R',450);
		moveMG('D',200);
		Foward(300);
		Backwards(500);
		Giro('L',450);
		Foward(200);
		Giro('L',450);
		moveMG('D',0);
		Foward(500);
		moveMG('U',1630);*/


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
  	//base
    	motor[baseTopLeft]= vexRT[Ch3] + vexRT[Ch1];
    	motor[baseTopRight]= -vexRT[Ch3] + vexRT[Ch1];
    	motor[baseBottomLeft]= vexRT[Ch3] + vexRT[Ch1];
    	motor[baseBottomRight]= -vexRT[Ch3] + vexRT[Ch1];


    //arcadeControl(Ch3, Ch1);// didnt have to do anything found pre existing functions

    	//transmition pneumatic
		   	if (vexRT[Btn7U] == 1){
		   		SensorValue[MGPiston] = 0;
		   	}

		   	else if (vexRT[Btn7D] == 1) {
		   		SensorValue[MGPiston] = 1;
		   	}


    //base extra motor
    if(SensorValue[MGPiston] == 1){
   		 motor[baseMG]= -vexRT[Ch3];
  	}

    //moving goal mech
 		if(SensorValue[MGPiston] == 0){
   		 if(vexRT[Btn7R] == 1){
   		 motor[baseMG]= -127;
   		}


   		else if(vexRT[Btn7L] == 1){
   		 motor[baseMG]= 127;
   		}

   		else{
   			motor[baseMG]= 0;
   		}
  	}

    //torre
    if((vexRT[Btn6U] == 1) && (vexRT[Btn6D] == 0)){
   	  motor(torreTopRight)= -127;
   	  motor(torreTopLeft) = 127;
    	motor(torreBottomLeft)= -127;
    	motor(torreBottomRight)= 127;
    }

    else if((vexRT[Btn6D] == 1) && (vexRT[Btn6U] == 0)){
    	motor(torreTopRight)= 127;
    	 motor(torreTopLeft) = -127;
    	motor(torreBottomLeft)= 127;
    	motor(torreBottomRight)= -127;
    }

    else {
    	motor(torreTopRight)= 0;
    	 motor(torreTopLeft) = 0;
    	motor(torreBottomLeft)= 0;
    	motor(torreBottomRight)= 0;
    }


    //chainBar pivot
    if((vexRT[Btn5U] == 1) && (vexRT[Btn5D] == 0)){
   	  motor(chainPivot) = -127;
    }

    else if((vexRT[Btn5D] == 1) && (vexRT[Btn5U] == 0)){
    	motor(chainPivot) = 127;
    }

    else {
    	motor(chainPivot) = 0;
    }


    //cone intake
    if(vexRT[Btn8D] == 1){
    	SensorValue[claw] = 1;
    }
    else {
    	SensorValue[claw] = 0;
    }

    //stack cones
    	if(vexRT[Btn8U] == 1){

				//startTask(stackCone);
    		startTask(base);


    		coneLift('U',700);
    		hightControl(2100);
    		coneLift('U',2900);
    		stack(2100);
    		SensorValue(claw) = 1;
    		wait1Msec(250);
    		hightControl(2100);
    		SensorValue(claw) = 0;
				wait1Msec(250);
				coneLift('D',2350);



				EndTimeSlice();



    	}

  }
}
