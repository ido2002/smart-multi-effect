#ifndef CONF_H
#define CONF_H

#include <stdlib.h>
#include <stdint.h>

#define DEF_INC_PIN 17
#define DEF_UD_PIN 27
#define DEF_P1_PIN 4
#define DEF_P2_PIN 23
#define DEF_P3_PIN 18
#define DEF_P4_PIN 12
#define DEF_P5_PIN 22
#define DEF_P6_PIN 24
#define DEF_RELAY_1 20
#define DEF_RELAY_2 21
#define DEF_RELAY_3 16
#define DEF_BUTTON1 5
#define DEF_BUTTON2 6
#define DEF_BUTTON3 13
#define DEF_BUTTON4 19
#define DEF_BUTTON5 26

struct Conf
{
    uint8_t INC_PIN = 17;
    uint8_t UD_PIN  = 27;
    uint8_t P1_PIN  = 4 ;
    uint8_t P2_PIN  = 23;
    uint8_t P3_PIN  = 18;
    uint8_t P4_PIN  = 12;
    uint8_t P5_PIN  = 22;
    uint8_t P6_PIN  = 24;
    uint8_t RELAY_1 = 20;
    uint8_t RELAY_2 = 21;
    uint8_t RELAY_3 = 16;
    uint8_t BUTTON1 = 5 ;
    uint8_t BUTTON2 = 6 ;
    uint8_t BUTTON3 = 13;
    uint8_t BUTTON4 = 19;
    uint8_t BUTTON5 = 26;
};

#endif // CONF_H
