#include "characters.h"

const byte ASCII[][8] PROGMEM = {
    { // 000
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 001
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 002
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 003
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 004
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 005
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 006
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 007
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 008
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 009
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 010
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 011
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 012
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 013
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 014
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 015
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 016
        B00000000,
        B00011100,
        B00111110,
        B00101010,
        B00111110,
        B00011100,
        B00011100,
        B00000000 },
    { // 017
        B00000000,
        B01100110,
        B01100110,
        B00000000,
        B00000000,
        B01000010,
        B00111100,
        B00000000 },
    { // 018
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 019
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 020
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 021
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 022
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 023
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 024
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 025
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 026
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 027
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 028
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 029
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 030
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 031
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 032
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 033
        B00000000,
        B00001100,
        B00001100,
        B00001100,
        B00001100,
        B00000000,
        B00001100,
        B00000000 },
    { // 034
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 035
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 036
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 037
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 038
        B00000000,
        B00110000,
        B01001000,
        B01010000,
        B00100000,
        B01010100,
        B01001000,
        B00110100 },
    { // 039
        B00000000,
        B00001100,
        B00000100,
        B00000100,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 040
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 041
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 042
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 043
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 044
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 045
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B01111110,
        B01111110,
        B00000000,
        B00000000 },
    { // 046
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B01100000,
        B01100000 },
    { // 047
        B00000000,
        B00000110,
        B00000110,
        B00001100,
        B00011000,
        B00110000,
        B01100000,
        B01100000 },
    { // 048
        B00000000,
        B00111100,
        B01100110,
        B01101110,
        B01110110,
        B01100110,
        B01100110,
        B00111100 },
    { // 049
        B00000000,
        B00011000,
        B00011000,
        B00111000,
        B00011000,
        B00011000,
        B00011000,
        B01111110 },
    { // 050
        B00000000,
        B00111100,
        B01100110,
        B00000110,
        B00001100,
        B00110000,
        B01100000,
        B01111110 },
    { // 051
        B00000000,
        B00111100,
        B01100110,
        B00000110,
        B00011100,
        B00000110,
        B01100110,
        B00111100 },
    { // 052
        B00000000,
        B00001100,
        B00011100,
        B00101100,
        B01001100,
        B01111110,
        B00001100,
        B00001100 },
    { // 053
        B00000000,
        B01111110,
        B01100000,
        B01111100,
        B00000110,
        B00000110,
        B01100110,
        B00111100 },
    { // 054
        B00000000,
        B00111100,
        B01100110,
        B01100000,
        B01111100,
        B01100110,
        B01100110,
        B00111100 },
    { // 055
        B00000000,
        B01111110,
        B01100110,
        B00001100,
        B00001100,
        B00011000,
        B00011000,
        B00011000 },
    { // 056
        B00000000,
        B00111100,
        B01100110,
        B01100110,
        B00111100,
        B01100110,
        B01100110,
        B00111100 },
    { // 057
        B00000000,
        B00111100,
        B01100110,
        B01100110,
        B00111110,
        B00000110,
        B01100110,
        B00111100 },
    { // 058
        B00000000,
        B00010000,
        B00111000,
        B00010000,
        B00000000,
        B00010000,
        B00111000,
        B00010000 },
    { // 059
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 060
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 061
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 062
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 063
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 064
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 065
        B00000000,
        B00111100,
        B01100110,
        B01100110,
        B01111110,
        B01100110,
        B01100110,
        B01100110 },
    { // 066
        B00000000,
        B01111100,
        B01100110,
        B01100110,
        B01111100,
        B01100110,
        B01100110,
        B01111100 },
    { // 067
        B00000000,
        B00111100,
        B01100110,
        B01100000,
        B01100000,
        B01100000,
        B01100110,
        B00111100 },
    { // 068
        B00000000,
        B01111100,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B01111100 },
    { // 069
        B00000000,
        B01111110,
        B01100000,
        B01100000,
        B01111100,
        B01100000,
        B01100000,
        B01111110 },
    { // 070
        B00000000,
        B01111110,
        B01100000,
        B01100000,
        B01111100,
        B01100000,
        B01100000,
        B01100000 },
    { // 071
        B00000000,
        B00111100,
        B01100110,
        B01100000,
        B01100000,
        B01101110,
        B01100110,
        B00111100 },
    { // 072
        B00000000,
        B01100110,
        B01100110,
        B01100110,
        B01111110,
        B01100110,
        B01100110,
        B01100110 },
    { // 073
        B00000000,
        B00111100,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00111100 },
    { // 074
        B00000000,
        B00011110,
        B00001100,
        B00001100,
        B00001100,
        B01101100,
        B01101100,
        B00111000 },
    { // 075
        B00000000,
        B01100110,
        B01101100,
        B01111000,
        B01110000,
        B01111000,
        B01101100,
        B01100110 },
    { // 076
        B00000000,
        B01100000,
        B01100000,
        B01100000,
        B01100000,
        B01100000,
        B01100000,
        B01111110 },
    { // 077
        B00000000,
        B01100011,
        B01110111,
        B01111111,
        B01101011,
        B01100011,
        B01100011,
        B01100011 },
    { // 078
        B00000000,
        B01100011,
        B01110011,
        B01111011,
        B01101111,
        B01100111,
        B01100011,
        B01100011 },
    { // 079
        B00000000,
        B00111100,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B00111100 },
    { // 080
        B00000000,
        B01111100,
        B01100110,
        B01100110,
        B01100110,
        B01111100,
        B01100000,
        B01100000 },
    { // 081
        B00000000,
        B00111100,
        B01100110,
        B01100110,
        B01100110,
        B01101110,
        B00111100,
        B00000110 },
    { // 082
        B00000000,
        B01111100,
        B01100110,
        B01100110,
        B01111100,
        B01111000,
        B01101100,
        B01100110 },
    { // 083
        B00000000,
        B00111100,
        B01100110,
        B01100000,
        B00111100,
        B00000110,
        B01100110,
        B00111100 },
    { // 084
        B00000000,
        B01111110,
        B01011010,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000 },
    { // 085
        B00000000,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B00111110 },
    { // 086
        B00000000,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B00111100,
        B00011000 },
    { // 087
        B00000000,
        B01100011,
        B01100011,
        B01100011,
        B01101011,
        B01111111,
        B01110111,
        B01100011 },
    { // 088
        B00000000,
        B01100011,
        B01100011,
        B00110110,
        B00011100,
        B00110110,
        B01100011,
        B01100011 },
    { // 089
        B00000000,
        B01100110,
        B01100110,
        B01100110,
        B00111100,
        B00011000,
        B00011000,
        B00011000 },
    { // 090
        B00000000,
        B01111110,
        B00000110,
        B00001100,
        B00011000,
        B00110000,
        B01100000,
        B01111110 },
    { // 091
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 092
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 093
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 094
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 095
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 096
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 097
        B00000000,
        B00000000,
        B00000000,
        B00111100,
        B00000110,
        B00111110,
        B01100110,
        B00111110 },
    { // 098
        B00000000,
        B01100000,
        B01100000,
        B01100000,
        B01111100,
        B01100110,
        B01100110,
        B01111100 },
    { // 099
        B00000000,
        B00000000,
        B00000000,
        B00111100,
        B01100110,
        B01100000,
        B01100110,
        B00111100 },
    { // 100
        B00000000,
        B00000110,
        B00000110,
        B00000110,
        B00111110,
        B01100110,
        B01100110,
        B00111110 },
    { // 101
        B00000000,
        B00000000,
        B00000000,
        B00111100,
        B01100110,
        B01111110,
        B01100000,
        B00111100 },
    { // 102
        B00000000,
        B00011100,
        B00110110,
        B00110000,
        B00110000,
        B01111100,
        B00110000,
        B00110000 },
    { // 103
        B00000000,
        B00000000,
        B00111110,
        B01100110,
        B01100110,
        B00111110,
        B00000110,
        B00111100 },
    { // 104
        B00000000,
        B01100000,
        B01100000,
        B01100000,
        B01111100,
        B01100110,
        B01100110,
        B01100110 },
    { // 105
        B00000000,
        B00000000,
        B00011000,
        B00000000,
        B00011000,
        B00011000,
        B00011000,
        B00111100 },
    { // 106
        B00000000,
        B00001100,
        B00000000,
        B00001100,
        B00001100,
        B01101100,
        B01101100,
        B00111000 },
    { // 107
        B00000000,
        B01100000,
        B01100000,
        B01100110,
        B01101100,
        B01111000,
        B01101100,
        B01100110 },
    { // 108
        B00000000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000 },
    { // 109
        B00000000,
        B00000000,
        B00000000,
        B01100011,
        B01110111,
        B01111111,
        B01101011,
        B01101011 },
    { // 110
        B00000000,
        B00000000,
        B00000000,
        B01111100,
        B01111110,
        B01100110,
        B01100110,
        B01100110 },
    { // 111
        B00000000,
        B00000000,
        B00000000,
        B00111100,
        B01100110,
        B01100110,
        B01100110,
        B00111100 },
    { // 112
        B00000000,
        B00000000,
        B01111100,
        B01100110,
        B01100110,
        B01111100,
        B01100000,
        B01100000 },
    { // 113
        B00000000,
        B00000000,
        B00111100,
        B01101100,
        B01101100,
        B00111100,
        B00001100,
        B00001100 },
    { // 114
        B00000000,
        B00000000,
        B00000000,
        B01111100,
        B01100110,
        B01100110,
        B01100000,
        B01100000 },
    { // 115
        B00000000,
        B00000000,
        B00000000,
        B00111110,
        B01000000,
        B00111100,
        B00000010,
        B01111100 },
    { // 116
        B00000000,
        B00000000,
        B00011000,
        B00011000,
        B01111110,
        B00011000,
        B00011000,
        B00011000 },
    { // 117
        B00000000,
        B00000000,
        B00000000,
        B01100110,
        B01100110,
        B01100110,
        B01100110,
        B00111110 },
    { // 118
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B01100110,
        B01100110,
        B00111100,
        B00011000 },
    { // 119
        B00000000,
        B00000000,
        B00000000,
        B01100011,
        B01101011,
        B01101011,
        B01101011,
        B00111110 },
    { // 120
        B00000000,
        B00000000,
        B00000000,
        B01100110,
        B00111100,
        B00011000,
        B00111100,
        B01100110 },
    { // 121
        B00000000,
        B00000000,
        B00000000,
        B01100110,
        B01100110,
        B00111110,
        B00000110,
        B00111100 },
    { // 122
        B00000000,
        B00000000,
        B00000000,
        B00111100,
        B00001100,
        B00011000,
        B00110000,
        B00111100 },
    { // 123
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 124
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 125
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 126
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 },
    { // 127
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000 }
};
const int ASCII_LEN = sizeof(ASCII) / 8;