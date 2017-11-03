// Includes
#include "Odometrie.h"
#include <Encoder.h>
#include <Arduino.h>

// Globale Encoder, werden f�r die Bibliothek ben�tigt um die Stellung der R�der zu erfassen
// Es war nicht m�glich diese als Attribute der Klasse um zu setzen
Encoder leftWheel(2, 4);
Encoder rightWheel(3, 5);

Odometrie::Odometrie() {

	// Die Startposition und der Startwinkel m�ssen hier festgelegt werden
	// Diese unterscheiden sich je nach Fahrzeug, sind aber wichtig damit diese korrekt arbeiten
	// bis jetzt nur Testwerte:
	x_odometrie = 0;
	y_odometrie = 0;
	alpha_odometrie = 0;

}

void Odometrie::updateOdometrie() {

	// Variablen
	float leftWheelChange;
	float rightWheelChange;
	float d_center = 0; // relative Bewegung der Mitte des Roboters

	// Werte updaten, aktuelle Werte aus den Encodern holen
	getDiffWheelDistance(leftWheelChange, rightWheelChange);

	// Bewegung, Differenz in der Position des Fahrzeuges berechnen
	d_center = (rightWheelChange - leftWheelChange) / 2;

	// Ver�nderungen der x und y Position des Fahrzeugs
	// Updaten der Attribute
	x_odometrie = d_center * cos((alpha_odometrie*PI)/180);
	y_odometrie = d_center * sin((alpha_odometrie*PI)/180);

	//Winkel des Fahrzeugs berechnen und Attribute updaten
	alpha_odometrie += (-1.0 * (leftWheelChange + rightWheelChange) * 180) / (Achsabstand * PI);
}

float Odometrie::getAngle() {

	return alpha_odometrie;

}

float Odometrie::getX_position() {

	return x_odometrie;

}

float Odometrie::getY_position() {

	return y_odometrie;

}

/*
 * Gibt die Difference der aktuellen und seit der letzten berechnugn zur�ck gelegten Strecke zur�ck
 * TODO: M�glicherweise m�ssen die vorzeichen ge�ndert werden um die Drehrichtung der R�der zu ber�cksichtigen
 */
void Odometrie::getDiffWheelDistance(float& leftWheelChange,
		float& rightWheelChange) {

	// Variablen für Winkek
	float leftRotaryChange;
	float rightRotaryChange;

	// Winkelwerte mit getRotaryChange abrufen
	getDiffWheelAngle(leftRotaryChange, rightRotaryChange);

	// Berechnung zurück gelegte Strecke mit dem Umfang der Räder
	leftWheelChange = leftRotaryChange / 360.0 * radUmfang;
	rightWheelChange = rightRotaryChange / 360.0 * radUmfang;

}

/*
 * Berechnet die �nderung des Drehwinkels der R�der
 */
void Odometrie::getDiffWheelAngle(float& leftRotaryChange,
		float& rightRotaryChange) {

	// Variablen für die Encoder Werte anlegen
	float leftRotary;
	float rightRotary;

	// Werte der Encoder abrufen
	leftRotary = leftWheel.read();
	rightRotary = rightWheel.read();

	// Winkel berechnen und zurück geben
	// Linkes Rad ist negiert, aufgrund der definition Uhrzeigersin = positiv
	// Rechtes Rad ist negiert, aufgrund der definition Uhrzeigersin = positiv
	leftRotaryChange = -1.0 * leftRotary * 360.0 / 2400.0;
	rightRotaryChange = -1.0 * rightRotary * 360.0 / 2400.0;

	// Wieder auf 0 setzen
	leftWheel.write(0);
	rightWheel.write(0);

}

/*
 * Testet die Funktionalit�t der Funktion
 * getDiffWheelDistance
 */
void Odometrie::testRotary() {

	float left;
	float right;

	static float xLast = -999;
	static float yLast = -999;

	// nur 10 mal pro sekunde abfragen
	static unsigned long timeLast = millis();
	unsigned long timeCur = millis();

	if (timeCur >= timeLast + 500) {

		timeLast = timeCur;

		getDiffWheelDistance(left, right);

		if ((left != xLast || right != yLast)) {

			Serial.print(left, 4);
			Serial.print("    ");
			Serial.print(right, 4), Serial.println(" ");

			xLast = left;
			yLast = right;
		}

	}

}

void Odometrie::testBerechnung(float diffLeft[], float diffRight[], int arraySize) {

	float d_center = 0; // relative Bewegung der Mitte des Roboters

	int i = 0;
	for(i = 0; i < arraySize; i++){

	// Bewegung, Differenz in der Position des Fahrzeuges berechnen
	d_center = (diffRight[i] - diffLeft[i]) / 2;

	// Ver�nderungen der x und y Position des Fahrzeugs
	// Updaten der Attribute
	x_odometrie += d_center * cos((alpha_odometrie*PI)/180);
	y_odometrie += d_center * sin((alpha_odometrie*PI)/180);

	//Winkel des Fahrzeugs berechnen und Attribute updaten
	alpha_odometrie += (-1.0 *(diffLeft[i] + diffRight[i]) * 180 )/ (Achsabstand * PI);

	// Alles ausgeben und mal schauen wie es so aussieht
	Serial.print("x_Pos: ");
	Serial.print(x_odometrie);
	Serial.print(", ");
	Serial.print("y_Pos: ");
	Serial.print(y_odometrie);
	Serial.print(", ");
	Serial.print("Alpha: ");
	Serial.print(alpha_odometrie);
	Serial.println();
	Serial.println();

	}
}

