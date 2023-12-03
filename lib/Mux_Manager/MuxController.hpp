#include <Arduino.h>
#include <vector>
class MuxController
{
private:
    const uint8_t s0;
    const uint8_t s1;
    const uint8_t s2;
    const uint8_t s3;
    const uint8_t sig;
    std::vector<uint8_t> bits; // Declara el vector 'bits'



public:
    MuxController(uint8_t _s0, uint8_t _s1, uint8_t _s2, uint8_t _s3, uint8_t _sig)
        : s0(_s0), s1(_s1), s2(_s2), s3(_s3), sig(_sig) {}

void selectChannel(uint8_t channel1, uint8_t channel2, uint8_t sigState)
{

    // Configurar los pines de selección s0, s1, s2, y s3 para el primer canal
    digitalWrite(s0, channel1 & 0x01);
    digitalWrite(s1, (channel1 >> 1) & 0x01);
    digitalWrite(s2, (channel1 >> 2) & 0x01);
    digitalWrite(s3, (channel1 >> 3) & 0x01);

    // Establecer el estado del pin sig para el primer canal
    digitalWrite(sig, sigState);
    delay(100); // Ajusta según sea necesario

    // Configurar los pines de selección s0, s1, s2, y s3 para el segundo canal
    digitalWrite(s0, channel2 & 0x01);
    digitalWrite(s1, (channel2 >> 1) & 0x01);
    digitalWrite(s2, (channel2 >> 2) & 0x01);
    digitalWrite(s3, (channel2 >> 3) & 0x01);
}

    void write(uint8_t channel, uint8_t state)
    {
        delay(100);
    }

    void read()
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            int value = digitalRead(sig);
            bits.push_back(value);
        }
        for (auto it = bits.begin(); it != bits.end(); ++it)
        {
            Serial.print(*it);
            Serial.print(' ');
        }
        bits.clear();
        
    }
};

MuxController gnd_mux(23, 32, 2, 0, 25);
MuxController vcc_mux(14, 27, 0, 4, 12);