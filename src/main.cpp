#include <avr/io.h>			// Einbinden von Einstellungen/Definitionen/usw. für den Mikrocontroller
#define F_CPU 8000000UL			// Frequenz des Microcontrollers fuer delay.h festlegen
#include <util/delay.h>			// Einbinden der _delay_ms()-Funktion um Wartezeiten zu erzeugen
#include "../lib/i2c_driver/i2c_driver.h"

int main (void)				// Hauptprogramm, hier startet der Mikrocontroller
{
	i2c_pfusch();					// Wartezeit von 500ms
}
