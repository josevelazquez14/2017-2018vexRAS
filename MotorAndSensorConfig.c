#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    lift,           sensorPotentiometer)
#pragma config(Sensor, in3,    movingGoal,     sensorPotentiometer)
#pragma config(Sensor, in4,    chainBar,       sensorPotentiometer)
#pragma config(Sensor, dgtl1,  baseLeft,       sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  baseRight,      sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  highDetector,   sensorSONAR_cm)
#pragma config(Sensor, dgtl10, ,               sensorDigitalOut)
#pragma config(Sensor, dgtl11, MGPiston,       sensorDigitalOut)
#pragma config(Sensor, dgtl12, claw,           sensorDigitalOut)
#pragma config(Motor,  port1,           baseTopLeft,   tmotorVex393HighSpeed_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           baseTopRight,  tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           torreTopLeft,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           torreTopRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           torreBottomLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           torreBottomRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           baseMG,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           chainPivot,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           baseBottomLeft, tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          baseBottomRight, tmotorVex393HighSpeed_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//TODO change this file's name to Main.c

#include "baseRUMrobot.c"// base code for everything competition related
