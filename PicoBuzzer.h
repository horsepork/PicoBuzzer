#ifndef PICOBUZZER_H
#define PICOBUZZER_H

#include "Arduino.h"

class PicoBuzzer{
    private:
        uint8_t buzzPin;
        uint32_t timer;
        uint16_t frequency;
        uint32_t duration;
        bool buzzing = false;

    public:
        PicoBuzzer(uint8_t _buzzPin){
            buzzPin = _buzzPin;
        }
        
        void errorTone(){
            ::tone(buzzPin, 2093);
            delay(125);
            ::noTone(buzzPin);
            ::tone(buzzPin, 1480);
            delay(250);
            ::noTone(buzzPin);
        }
        void tone(uint16_t _frequency = 2000, int16_t _duration = 50){
            if(buzzing) noTone();
            ::tone(buzzPin, _frequency);
            buzzing = true;
            duration = _duration;
            timer = millis();
        }

        void noTone(){
            ::noTone(buzzPin);
            buzzing = false;
        }

        void update(){
            if(buzzing){
                if(millis() - timer > 5000) { } // cap out buzzing at 5 seconds
                else if(millis() - timer < duration) return;
            }
            noTone();
            buzzing = false;
        }

        void tone(uint8_t* buzzerDataArray){
            int frequency = buzzerDataArray[0] + (buzzerDataArray[1] << 8);
            uint32_t duration = buzzerDataArray[2] + (buzzerDataArray[3] << 8);
            buzzer.tone(frequency, duration);
        }
};

PicoBuzzer buzzer(2);

#endif