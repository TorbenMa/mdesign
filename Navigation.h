
#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "Kommunikation.h"
#include "Odometrie.h"
#include "Motor.h"
//#include "StateMachine.h"

class Navigation {
private:
    Kommunikation JSON;
    Odometrie Odo;
    Motor Moto;
private:

    // Attribute f�r die Motoransteuerung
    unsigned int maxTime = 5000; // Maximal 5s
    unsigned int maxTimeWait = 10000; // maximal 10s warten
    float speed = 150;		// MotorPWM-Signal f�r die Vorw�rtsfahrt eines Rades
    float speedturn = 50;
    char driveOffset = 1;//fliegt // Offset-Signal zum Gegensteuern der Geschwindigkeit bei (ZickZack-Kurs)
    float targetAngle = 0;	// zum Aktualisieren des Eingeschlagenen Winkel
    float ActualTargetAngle = 0;	// fliegt// aktueller Ziel-Winkel von aktueller Position zu Zielpunkt
    // Attribute f�r die Positionsbestimmung
    int X_Koordinaten[5] = {300, 300, 15, 20, 25};
    int Y_Koordinaten[5] = {300, 600, 10, 5, 9};
    int x_aktuell = 0; 		// Startwert in x-Richtung
    int y_aktuell = 0; 		// Startwert in y-Richtung
    int Position;				// Aktueller Anfahrpunkt
    int MaxPositions = 5;		// Maximal anfahrbare Punkt
    // Reglungswerkzeuge
	float controlDeviation = 0;
	float actualDeviation = 0;
	float differenceDeviation = 0;
	float amplifierKp = 1.5;
    float e = 0.0;
    int offsetDeviation = 10;
    // Ausweichverhalten
	unsigned long currentQuarter= 1;
	long AreaWidth = 2000;
	long AreaHigh = 3000;

public:	// Allgemeines
    Navigation();
    void turnToTargetAngle();
    void driveToTargetPosition();
    Odometrie& getOdometrie();
    Kommunikation& getJSON();
    Motor& getMotor();
private:	// Allgemeines
    int signum(float sign);
public: // Getter
    float getLengthToPosition(int x, int y);
    float getCalculateAngle(int x, int y);
    float getDeviation();
    float getTargetAngle();
    float getSpeed();
    void UpdateData();
    int getTargetCoordinateX();
    int getTargetCoordinateY();
    int getCurrentQuarter();
    int getPosition();
    int getyPosition();

public:	// Setter
    void setTargetAngle(float angle);
    void setSpeed(int speed);
    void setNextPosition();

private:

    void drive();					// kommt in die State
    void DriveStraightForward();	// kommt in die State
    void AvoidCrash();				// kommt in die State

};

#endif /* NAVIGATION_H */

