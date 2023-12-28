# Gyrocelery
## Aufgabenstellung: 
Auslesen eines 6 Achsen- Gyroskops bzw. Beschleunigungssensors, wie z.B. MPU 6050 oder LSM6DOX mit I2C

- Die Daten werden auf einem LCD angezeigt.
- Eine Kalibrierung des Sensors wird durchgeführt.
- Weiteres Verarbeiten der Daten, um z.B. eine aktuelle Geschwindigkeit oder eine relative Position zu bestimmen

## Hardware:
- Beschleunigungssensor z.B. MPU 6050 oder LSM6DOX
- ATmega32
- STK500
- Display

## Resources
- Sensor fusion: https://www.youtube.com/watch?v=6qV3YjFppuc&list=PLn8PRpmsu08ryYoBpEKzoMOveSTyS-h4a&index=2

## Display usage

The intended use of the display is as follows:

```C++
#include <util/delay.h>
#include <Display/display.h>

int main(void)
{
    constexpr uint8_t displayI2CAddress = 0x28;
    Display display(displayI2CAddress);

    for (;;)
    {
        const Page page("Hello, World!\n How are you?");
        display.show(page);
        _delay_ms(1000);
    }

    return 0;
}
```
