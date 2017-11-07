
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Kommunikation.h"
#include "Odometrie.h"
#include "Motor.h"

class Navigation {
private:
    Kommunikation JSON;
    Odometrie Odo;
    Motor Moto;
private:

    // Attribute f�r die Motoransteuerung
    int stopp = 0;				// Stopp-Signal an die Motoransteuerung
    float forward = 1;			// Motor-Signal f�r die Vorw�rtsfahrt eines Rades
    float backward = 1;			// Motor-Signal f�r die R�ckw�rtsfahrt eines Rades
    float driveOffset = 1;		// Offset-Signal zum Gegensteuern bei (ZickZack-Kurs)
    float TargetAngleOld = 0;	// alter Ziel-Winkel von aktueller Position zu Zielpunkt
    float TargetAngleNew = 0;	// neuer Ziel-Winkel von aktueller Position zu Zielpunkt

    // Attribute f�r die Positionsbestimmung
    int X_Koordinaten[5] = {0, 10, 15, 20, 25};
    int Y_Koordinaten[5] = {100, 25, 10, 5, 9};
    float x_aktuell = 0; 		// Startwert in x-Richtung
    float y_aktuell = 0; 		// Startwert in y-Richtung
    float angle_aktuell = 0;	// Startwert Drehwinkel
    int Position;				// Aktueller Anfahrpunkt
    int MaxPositions = 5;		// Maximal anfahrbare Punkt


    // Attribute f�r das Ausweichverhalten
    bool Master = true;
    int Spielfeldbreite = 2000;
    int Spielfeldhoehe = 3000;
    float AvoidAngle = 0;

    // �nderungen von Torben
    float angleTolerance = 0.4;			// Winkelabweichung beim fahren

public:

    Navigation();

private:

    double weglaenge(int x, int y);	// wird evtl nicht mehr gebraucht, erstmal dabei gelassen
    double CalculateAngle(int x, int y);

    void UpdateData();
    void drive();
    void DriveStraightForward();
    void StopDriving();
    void Rotate();
    void AvoidClash();
    void nextPosition();

    bool finished();
    bool NotAtPoint();

};

#endif /* NAVIGATION_H */

