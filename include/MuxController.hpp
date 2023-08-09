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

    void selectChannel(uint8_t channel)
    {
        if (channel < 0 || channel > 13)
            return; // Canal inválido
        digitalWrite(s0, (channel & 0b0001) ? HIGH : LOW);
        digitalWrite(s1, (channel & 0b0010) ? HIGH : LOW);
        digitalWrite(s2, (channel & 0b0100) ? HIGH : LOW);
        digitalWrite(s3, (channel & 0b1000) ? HIGH : LOW);
    }

public:
    MuxController(uint8_t _s0, uint8_t _s1, uint8_t _s2, uint8_t _s3, uint8_t _sig)
        : s0(_s0), s1(_s1), s2(_s2), s3(_s3), sig(_sig) {}

    void write(uint8_t channel)
    {
        selectChannel(channel);
        digitalWrite(sig, HIGH);
        delay(100);
    }

    void read()
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            selectChannel(i);
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

MuxController ctrl_mux(27, 26, 25, 23, 32);
MuxController row_mux(15, 2, 0, 4, 21);
MuxController bit_mux(17, 5, 18, 19, 34);