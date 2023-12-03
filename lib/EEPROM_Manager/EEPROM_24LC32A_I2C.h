#include <Arduino.h>
#include <Wire.h>

using namespace std;

class EEPROM_24LC32A_I2C
{

public:
    
    EEPROM_24LC32A_I2C(int eeprom_addres_) : eeprom_addres(eeprom_addres_){};

    void writeEEPROM(unsigned int eeaddress, char *data)
    {
        Wire.beginTransmission(eeprom_addres);
        Wire.write((eeaddress >> 8));   // MSB
        Wire.write((eeaddress & 0xFF)); // LSB
        for (int i = 0; i < strlen(data); i++)
        {
            Wire.write(data[i]);
        }
        Wire.endTransmission();
        delay(6); // Necesario para la escritura de página
    }
    
    void readDataFromEEPROM()
    {
        int address = 0; // Dirección de inicio en la EEPROM
        char data[5];    // Donde se almacenará la cadena leída

        // Leer la cadena desde la memoria EEPROM
        Wire.beginTransmission(eeprom_addres);
        Wire.write((address >> 8));   // Envía el byte más significativo de la dirección
        Wire.write((address & 0xFF)); // Envía el byte menos significativo de la dirección
        Wire.endTransmission();

        Wire.requestFrom(eeprom_addres, 4); // Solicita 4 bytes de datos desde la EEPROM
        for (int i = 0; i < 4; i++)
        {
            if (Wire.available())
            {
                data[i] = Wire.read(); // Lee los bytes de datos
            }
            else
            {
                Serial.println("NO SE ENCONTRO EEPROM...");
                return;
            }
        }
        data[4] = '\0'; // Agrega un carácter nulo al final para formar una cadena

        Serial.print("Datos leídos: ");
        Serial.println(data);
    }

private:
    int eeprom_addres;
};