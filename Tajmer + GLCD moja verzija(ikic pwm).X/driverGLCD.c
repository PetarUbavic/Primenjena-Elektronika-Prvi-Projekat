#include "driverGLCD.h"
#include <stdlib.h>


unsigned char kursorX=0;
unsigned char kursorY=0;
unsigned char strana=0;

const  char fontBIG[] = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // space
 0x00, 0x00, 0x3E, 0xFF, 0xFF, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x0D, 0x00, 0x00, 0x00  , // ! 
 0x00, 0x04, 0x07, 0x03, 0x00, 0x04, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // "
 0x10, 0xFE, 0xFE, 0x10, 0x10, 0xFE, 0xFE, 0x10, 0x01, 0x0F, 0x0F, 0x01, 0x01, 0x0F, 0x0F, 0x01  , // #
 0x1C, 0x3E, 0x22, 0xFF, 0xFF, 0x42, 0xCE, 0x8C, 0x03, 0x07, 0x04, 0x0F, 0x0F, 0x04, 0x07, 0x03  , // $
 0x00, 0x00, 0x06, 0xC6, 0xF0, 0x3C, 0x0E, 0x02, 0x00, 0x04, 0x07, 0x03, 0x00, 0x06, 0x06, 0x00  , // %
 0x1E, 0x3F, 0xE1, 0xC1, 0x41, 0x21, 0x3F, 0x1E, 0x06, 0x0F, 0x09, 0x09, 0x0B, 0x0C, 0x1E, 0x16  , // &
 0x00, 0x00, 0x04, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // '
 0x00, 0x00, 0xF8, 0xFE, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x08, 0x00, 0x00  , // (
 0x00, 0x00, 0x01, 0x07, 0xFE, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0E, 0x07, 0x01, 0x00, 0x00  , // )
 0x20, 0xA8, 0xF8, 0x70, 0x70, 0xF8, 0xA8, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // *
 0x20, 0x20, 0x20, 0xFC, 0xFC, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00  , // +
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3C, 0x1C, 0x00, 0x00, 0x00  , // ,
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // -
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00  , // .
 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x3C, 0x0F, 0x03, 0x00, 0x0C, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00  , // /
 0xFE, 0xFF, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFE, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // 0
 0x00, 0x04, 0x06, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x00  , // 1
 0x02, 0x03, 0x81, 0xC1, 0x61, 0x31, 0x1F, 0x0E, 0x0E, 0x0F, 0x09, 0x08, 0x08, 0x08, 0x08, 0x0C  , // 2
 0x02, 0x03, 0x01, 0x21, 0x21, 0x21, 0xFF, 0xDE, 0x04, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // 3
 0xE0, 0xF0, 0x98, 0x8C, 0x86, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08  , // 4  
 0x3F, 0x3F, 0x21, 0x21, 0x21, 0x21, 0xE1, 0xC1, 0x04, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // 5
 0xFC, 0xFE, 0x23, 0x21, 0x21, 0x21, 0xE0, 0xC0, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // 6
 0x03, 0x03, 0x01, 0x81, 0xE1, 0x79, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00  , // 7
 0xDE, 0xFF, 0x21, 0x21, 0x21, 0x21, 0xFF, 0xDE, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // 8
 0x1E, 0x3F, 0x21, 0x21, 0x21, 0x21, 0xFF, 0xFE, 0x00, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x07, 0x03  , // 9
 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00  , // :
 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x1E, 0x0E, 0x00, 0x00, 0x00  , // ;
 0x40, 0xE0, 0xB0, 0x18, 0x0C, 0x06, 0x02, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x08, 0x00  , // <
 0x00, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // =
 0x00, 0x02, 0x06, 0x0C, 0x18, 0xB0, 0xE0, 0x40, 0x00, 0x08, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00  , // >
 0x02, 0x03, 0x01, 0xC1, 0xE1, 0x31, 0x1F, 0x0E, 0x00, 0x00, 0x00, 0x0D, 0x0D, 0x00, 0x00, 0x00  , // ?
 0x02, 0x03, 0x01, 0xC1, 0xE1, 0x31, 0x1F, 0x0E, 0x00, 0x00, 0x00, 0x0D, 0x0D, 0x00, 0x00, 0x00  , // @
 0xF8, 0xFC, 0x86, 0x83, 0x83, 0x86, 0xFC, 0xF8, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F  , // A
 0xFF, 0xFF, 0x21, 0x21, 0x21, 0x21, 0xFF, 0xDE, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // B
 0xFC, 0xFE, 0x03, 0x01, 0x01, 0x01, 0x03, 0x06, 0x03, 0x07, 0x0C, 0x08, 0x08, 0x08, 0x0C, 0x06  , // C
 0x01, 0xFF, 0xFF, 0x01, 0x01, 0x03, 0xFE, 0xFC, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x0C, 0x07, 0x03  , // D
 0x01, 0xFF, 0xFF, 0x21, 0x21, 0x71, 0x03, 0x03, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x0C, 0x0C  , // E
 0x01, 0xFF, 0xFF, 0x21, 0x21, 0x71, 0x03, 0x03, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x00, 0x00  , // F
 0xFC, 0xFE, 0x03, 0x01, 0x41, 0x41, 0xC3, 0xC6, 0x03, 0x07, 0x0C, 0x08, 0x08, 0x08, 0x07, 0x0F  , // G
 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0xFF, 0xFF, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F  , // H
 0x00, 0x01, 0x01, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x00  , // I
 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x01, 0x06, 0x0E, 0x08, 0x08, 0x08, 0x0F, 0x07, 0x00  , // J
 0x01, 0xFF, 0xFF, 0x70, 0xD8, 0x8C, 0x07, 0x03 ,0x08, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0E  , // K
 0x01, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x0C, 0x0C  , // L
 0xFF, 0xFF, 0x0C, 0x78, 0x78, 0x0C, 0xFF, 0xFF, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F  , // M
 0xFF, 0xFF, 0x1C, 0x38, 0x70, 0xE0, 0xFF, 0xFF, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F  , // N
 0xFE, 0xFF, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFE, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // O
 0x01, 0xFF, 0xFF, 0x21, 0x21, 0x21, 0x3F, 0x1E, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x00, 0x00  , // P
 0xFE, 0xFF, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFE, 0x07, 0x0F, 0x08, 0x0E, 0x1C, 0x38, 0x2F, 0x07  , // Q
 0x01, 0xFF, 0xFF, 0x21, 0x21, 0x61, 0xFF, 0x9E, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x0F, 0x0F  , // R
 0x0E, 0x1F, 0x31, 0x21, 0x21, 0x61, 0xC7, 0x86, 0x06, 0x0E, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // S
 0x03, 0x03, 0x01, 0xFF, 0xFF, 0x01, 0x03, 0x03, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00  , // T
 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // U
 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x03, 0x06, 0x0C, 0x0C, 0x06, 0x03, 0x01  , // V
 0xFF, 0xFF, 0x00, 0xE0, 0xE0, 0x00, 0xFF, 0xFF, 0x01, 0x0F, 0x0E, 0x03, 0x03, 0x0E, 0x0F, 0x01  , // W
 0x07, 0x0F, 0x98, 0xF0, 0xF0, 0x98, 0x0F, 0x07, 0x0E, 0x0F, 0x01, 0x00, 0x00, 0x01, 0x0F, 0x0E  , // X
 0x0F, 0x1F, 0x30, 0xE0, 0xE0, 0x30, 0x1F, 0x0F, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00  , // Y
 0x03, 0x83, 0xC1, 0x61, 0x31, 0x19, 0x0F, 0x07, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x0C  , // Z
 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x08, 0x00, 0x00  , // [
 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA  , // CHESS
 0x00, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x0F, 0x00, 0x00  , // ]
 0x08, 0x0C, 0x06, 0x03, 0x03, 0x06, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // ^
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10  , // _
 0x00, 0x00, 0x08, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  , // `
 0x00, 0x90, 0x90, 0x90, 0x90, 0xF0, 0xE0, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x07, 0x0F, 0x08  , // a
 0x01, 0xFF, 0xFF, 0x10, 0x10, 0x30, 0xE0, 0xC0, 0x08, 0x0F, 0x07, 0x08, 0x08, 0x08, 0x0F, 0x07  , // b
 0xE0, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x30, 0x20, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x04  , // c
 0xC0, 0xE0, 0x30, 0x10, 0x11, 0xFF, 0xFF, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x07, 0x0F, 0x08  , // d
 0xE0, 0xF0, 0x90, 0x90, 0x90, 0x90, 0xF0, 0xE0, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x04  , // e
 0x00, 0x10, 0xFE, 0xFF, 0x11, 0x11, 0x03, 0x02, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x00  , // f
 0xE0, 0xF0, 0x10, 0x10, 0x10, 0xE0, 0xF0, 0x10, 0x27, 0x6F, 0x48, 0x48, 0x48, 0x7F, 0x3F, 0x00  , // g
 0x01, 0xFF, 0xFF, 0x20, 0x10, 0x10, 0xF0, 0xE0, 0x08, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x0F  , // h
 0x00, 0x10, 0x10, 0xF6, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x00  , // i
 0x00, 0x00, 0x10, 0x10, 0xF6, 0xF6, 0x00, 0x00, 0x30, 0x60, 0x40, 0x40, 0x7F, 0x3F, 0x00, 0x00  , // j
 0x01, 0xFF, 0xFF, 0xC0, 0xC0, 0x60, 0x30, 0x10, 0x08, 0x0F, 0x0F, 0x00, 0x01, 0x03, 0x0E, 0x0C  , // k
 0x00, 0x01, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x00  , // l
 0xF0, 0xF0, 0x30, 0xE0, 0xE0, 0x30, 0xF0, 0xE0, 0x0F, 0x0F, 0x00, 0x07, 0x07, 0x00, 0x0F, 0x0F  , // m
 0x10, 0xF0, 0xE0, 0x10, 0x10, 0x10, 0xF0, 0xE0, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x0F  , // n
 0xE0, 0xF0, 0x10, 0x10, 0x10, 0x10, 0xF0, 0xE0, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x07  , // o
 0x10, 0xF0, 0xE0, 0x10, 0x10, 0x10, 0xF0, 0xE0, 0x40, 0x7F, 0x7F, 0x48, 0x08, 0x08, 0x0F, 0x07  , // p
 0xE0, 0xF0, 0x10, 0x10, 0x10, 0xE0, 0xF0, 0x10, 0x07, 0x0F, 0x08, 0x08, 0x48, 0x7F, 0x7F, 0x40  , // q
 0x10, 0xF0, 0xE0, 0x10, 0x10, 0x10, 0x30, 0x20, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00  , // r
 0x60, 0xF0, 0x90, 0x90, 0x90, 0x10, 0x30, 0x20, 0x04, 0x0C, 0x08, 0x08, 0x09, 0x09, 0x0F, 0x06  , // s
 0x10, 0x10, 0xFE, 0xFF, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x0C, 0x04, 0x00  , // t
 0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x07, 0x0F, 0x08  , // u
 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x01, 0x03, 0x06, 0x0C, 0x0C, 0x06, 0x03, 0x01  , // v
 0xF0, 0xF0, 0x00, 0x80, 0x80, 0x00, 0xF0, 0xF0, 0x07, 0x0F, 0x0C, 0x07, 0x07, 0x0C, 0x0F, 0x07  , // w
 0x10, 0x30, 0x60, 0xC0, 0xC0, 0x60, 0x30, 0x10, 0x08, 0x0C, 0x06, 0x03, 0x03, 0x06, 0x0C, 0x08  , // x
 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x47, 0x4F, 0x48, 0x48, 0x48, 0x68, 0x3F, 0x1F  , // y
 0x30, 0x30, 0x10, 0x90, 0xD0, 0x70, 0x30, 0x10, 0x0C, 0x0E, 0x0B, 0x09, 0x08, 0x08, 0x0C, 0x0C }   // z
;

const  char font[1024] = {
0x00, 0x00, 0x00, 0x00, 0x00,// (space)
0x00, 0x00, 0x5F, 0x00, 0x00,// !
0x00, 0x07, 0x00, 0x07, 0x00,// "
0x14, 0x7F, 0x14, 0x7F, 0x14,// #
0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
0x23, 0x13, 0x08, 0x64, 0x62,// %
0x36, 0x49, 0x55, 0x22, 0x50,// &
0x00, 0x05, 0x03, 0x00, 0x00,// '
0x00, 0x1C, 0x22, 0x41, 0x00,// (
0x00, 0x41, 0x22, 0x1C, 0x00,// )
0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
0x08, 0x08, 0x3E, 0x08, 0x08,// +
0x00, 0x50, 0x30, 0x00, 0x00,// ,
0x08, 0x08, 0x08, 0x08, 0x08,// -
0x00, 0x30, 0x30, 0x00, 0x00,// .
0x20, 0x10, 0x08, 0x04, 0x02,// /
0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
0x00, 0x42, 0x7F, 0x40, 0x00,// 1
0x42, 0x61, 0x51, 0x49, 0x46,// 2
0x21, 0x41, 0x45, 0x4B, 0x31,// 3
0x18, 0x14, 0x12, 0x7F, 0x10,// 4
0x27, 0x45, 0x45, 0x45, 0x39,// 5
0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
0x01, 0x71, 0x09, 0x05, 0x03,// 7
0x36, 0x49, 0x49, 0x49, 0x36,// 8
0x06, 0x49, 0x49, 0x29, 0x1E,// 9
0x00, 0x36, 0x36, 0x00, 0x00,// :
0x00, 0x56, 0x36, 0x00, 0x00,// ;
0x00, 0x08, 0x14, 0x22, 0x41,// <
0x14, 0x14, 0x14, 0x14, 0x14,// =
0x41, 0x22, 0x14, 0x08, 0x00,// >
0x02, 0x01, 0x51, 0x09, 0x06,// ?
0x32, 0x49, 0x79, 0x41, 0x3E,// @
0x7E, 0x11, 0x11, 0x11, 0x7E,// A
0x7F, 0x49, 0x49, 0x49, 0x36,// B
0x3E, 0x41, 0x41, 0x41, 0x22,// C
0x7F, 0x41, 0x41, 0x22, 0x1C,// D
0x7F, 0x49, 0x49, 0x49, 0x41,// E
0x7F, 0x09, 0x09, 0x01, 0x01,// F
0x3E, 0x41, 0x41, 0x51, 0x32,// G
0x7F, 0x08, 0x08, 0x08, 0x7F,// H
0x00, 0x41, 0x7F, 0x41, 0x00,// I
0x20, 0x40, 0x41, 0x3F, 0x01,// J
0x7F, 0x08, 0x14, 0x22, 0x41,// K
0x7F, 0x40, 0x40, 0x40, 0x40,// L
0x7F, 0x02, 0x04, 0x02, 0x7F,// M
0x7F, 0x04, 0x08, 0x10, 0x7F,// N
0x3E, 0x41, 0x41, 0x41, 0x3E,// O
0x7F, 0x09, 0x09, 0x09, 0x06,// P
0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
0x7F, 0x09, 0x19, 0x29, 0x46,// R
0x46, 0x49, 0x49, 0x49, 0x31,// S
0x01, 0x01, 0x7F, 0x01, 0x01,// T
0x3F, 0x40, 0x40, 0x40, 0x3F,// U
0x1F, 0x20, 0x40, 0x20, 0x1F,// V
0x7F, 0x20, 0x18, 0x20, 0x7F,// W
0x63, 0x14, 0x08, 0x14, 0x63,// X
0x03, 0x04, 0x78, 0x04, 0x03,// Y
0x61, 0x51, 0x49, 0x45, 0x43,// Z
0x00, 0x00, 0x7F, 0x41, 0x41,// [
0x02, 0x04, 0x08, 0x10, 0x20,// "\"
0x41, 0x41, 0x7F, 0x00, 0x00,// ]
0x04, 0x02, 0x01, 0x02, 0x04,// ^
0x40, 0x40, 0x40, 0x40, 0x40,// _
0x00, 0x01, 0x02, 0x04, 0x00,// `
0x20, 0x54, 0x54, 0x54, 0x78,// a
0x7F, 0x48, 0x44, 0x44, 0x38,// b
0x38, 0x44, 0x44, 0x44, 0x20,// c
0x38, 0x44, 0x44, 0x48, 0x7F,// d
0x38, 0x54, 0x54, 0x54, 0x18,// e
0x08, 0x7E, 0x09, 0x01, 0x02,// f
0x08, 0x14, 0x54, 0x54, 0x3C,// g
0x7F, 0x08, 0x04, 0x04, 0x78,// h
0x00, 0x44, 0x7D, 0x40, 0x00,// i
0x20, 0x40, 0x44, 0x3D, 0x00,// j
0x00, 0x7F, 0x10, 0x28, 0x44,// k
0x00, 0x41, 0x7F, 0x40, 0x00,// l
0x7C, 0x04, 0x18, 0x04, 0x78,// m
0x7C, 0x08, 0x04, 0x04, 0x78,// n
0x38, 0x44, 0x44, 0x44, 0x38,// o
0x7C, 0x14, 0x14, 0x14, 0x08,// p
0x08, 0x14, 0x14, 0x18, 0x7C,// q
0x7C, 0x08, 0x04, 0x04, 0x08,// r
0x48, 0x54, 0x54, 0x54, 0x20,// s
0x04, 0x3F, 0x44, 0x40, 0x20,// t
0x3C, 0x40, 0x40, 0x20, 0x7C,// u
0x1C, 0x20, 0x40, 0x20, 0x1C,// v
0x3C, 0x40, 0x30, 0x40, 0x3C,// w
0x44, 0x28, 0x10, 0x28, 0x44,// x
0x0C, 0x50, 0x50, 0x50, 0x3C,// y
0x44, 0x64, 0x54, 0x4C, 0x44,// z
0x00, 0x08, 0x36, 0x41, 0x00,// {
0x00, 0x00, 0x7F, 0x00, 0x00,// |
0x00, 0x41, 0x36, 0x08, 0x00,// }
0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};

void SetRST(unsigned char vrednost)
{
	if (vrednost)
		RF5_1
	else
		RF5_0
}

void SetE(unsigned char vrednost)
{
	if (vrednost)
		RF4_1
	else
		RF4_0
}

void SetRW(unsigned char vrednost)
{
	if (vrednost)
		RF1_1
	else
		RF1_0
}

void SetRS(unsigned char vrednost)
{
	if (vrednost)
		RF0_1
	else
		RF0_0
}

void SetCS2(unsigned char vrednost)
{
	if (vrednost)
		RB5_1
	else
		RB5_0
}

void SetCS1(unsigned char vrednost)
{
	if (vrednost)
		RB4_1
	else
		RB4_0
}


void ConfigureLCDPins (void)
{
	TRISFbits.TRISF5=0;//LCD_RST izlaz
	TRISFbits.TRISF4=0;//LCD_E izlaz
	TRISFbits.TRISF1=0;//LCD_RW izlaz
	TRISFbits.TRISF0=0;//LCD_DI izlaz
	ADPCFGbits.PCFG5=1;
	TRISBbits.TRISB5=0;//LCD_CS2 izlaz				
	ADPCFGbits.PCFG4=1;
	TRISBbits.TRISB4=0;//LCD_CS1 izlaz
					
	
	//LCD_DATA	P2//RB0 RB1 RB2 RB3 RD0 RD1 RD2 RD3
	ADPCFGbits.PCFG0=1;
    
	TRISBbits.TRISB0=0;//RB0
	ADPCFGbits.PCFG1=1;
	TRISBbits.TRISB1=0;//RB1
	ADPCFGbits.PCFG2=1;
	TRISBbits.TRISB2=0;//RB2
	ADPCFGbits.PCFG3=1;
	TRISBbits.TRISB3=0;//RB3

	TRISDbits.TRISD0=0;//RD0
	TRISDbits.TRISD1=0;//RD1
	TRISDbits.TRISD2=0;//RD2
	TRISDbits.TRISD3=0;//RD3
	
}

void ConfigureLcdData(unsigned char direction)
{
	//LCD_DATA	P2//RB0 RB1 RB2 RB3 RD0 RD1 RD2 RD3
	if(direction==output)
	{
		//LCD_DATA OUTPUT
		TRISDbits.TRISD0=output;//RD0
		TRISDbits.TRISD1=output;//RD1
		TRISDbits.TRISD2=output;//RD2
		TRISDbits.TRISD3=output;//RD3
		TRISBbits.TRISB3=output;//RB3
		TRISBbits.TRISB2=output;//RB2
		TRISBbits.TRISB1=output;//RB1
		TRISBbits.TRISB0=output;//RB0
	}
	if (direction==input)
	{
		//LCD_DATA INPUT
		TRISDbits.TRISD0=input;//RD0
		TRISDbits.TRISD1=input;//RD1
		TRISDbits.TRISD2=input;//RD2
		TRISDbits.TRISD3=input;//RD3
		TRISBbits.TRISB3=input;//RB3
		TRISBbits.TRISB2=input;//RB2
		TRISBbits.TRISB1=input;//RB1
		TRISBbits.TRISB0=input;//RB0
	}

}

void SetLcdData(unsigned char vrednost)
{
	unsigned char pomocna,pomocna2;
	//LCD_DATA	lsb RB0 RB1 RB2 RB3 RD0 RD1 RD2 RD3 msb
	pomocna=vrednost;
	LATD&=0xfff0;
	LATB&=0xfff0;
	pomocna2=pomocna&0x0f;
	LATB|=pomocna2;
	pomocna=pomocna/16;
	LATD|=pomocna;
}

unsigned char ReadLcdData(void)
{
	//LCD_DATA	P2//RB0 RB1 RB2 RB3 RD0 RD1 RD2 RD3
	unsigned char pomocna,vrednost;
	pomocna=PORTD;
	pomocna=pomocna*16;
	vrednost=PORTB;
	vrednost&=0x0f;
	vrednost+=pomocna;
	return vrednost;
	
}


/*-------------------------------------------------------------------------------
Tempo for the LCD timing
	pause()
-------------------------------------------------------------------------------*/



void strobe_data(void)
{
	SetE(1);		/* Strobe */
  //	LcdDelay(1);//////////radi cak i bez njega--------------------------------------------------------------------------------------
	SetE(0);
}

void LcdInstructionWrite (unsigned char u8Instruction)
{
  	//LcdWaitBusy ();		// wait until LCD not busy --------------------------------------------------------------------------------
   	SetRS(0);       	/* Instruction mode */
  	SetRW(0);       	/* Write mode */
  	SetLcdData(u8Instruction);/* outbyte */
	strobe_data();
}


/*-------------------------------------------------------------------------------
Tempo for the LCD timing
	pause()
-------------------------------------------------------------------------------*/
void LcdDelay(unsigned int u32Duration)
{
	unsigned int u32Delay;
	for (u32Delay=0; u32Delay<(u32Duration); u32Delay++);
}

/*-------------------------------------------------------------------------------
Wait as long as the LCD is busy
	LcdWaitBusy();
-------------------------------------------------------------------------------*/
void LcdWaitBusy (void)
{
	unsigned char temp;
	SetRS(0);       	/* Instruction mode */
  	SetRW(1);       	/* Read mode */
  	
	ConfigureLcdData(input);		/* set LCD_DATA port in input mode */
	SetE(1); 
	temp=ReadLcdData();
	SetE(0); 
	
	while (temp & 0x80) 
	{
			temp=ReadLcdData();
	}

}
/*--------------------------------------------------------------------------------
GOTO X
---------------------------------------------------------------------------------*/

void GoToX(unsigned char x)
{
	if (x<64)
	{
		LcdSelectSide(LEFT);
		LcdInstructionWrite (Y_ADRESS | x);
		strana=LEFT;
	}
	else if(x<128)
	{
		LcdSelectSide(RIGHT);
		LcdInstructionWrite (Y_ADRESS | (x-64));
		strana=RIGHT;
	}
	kursorX=x;
}

/*--------------------------------------------------------------------------------
GOTO Y
---------------------------------------------------------------------------------*/

void GoToY(unsigned char y)
{
	if(y<8)
	{
		LcdInstructionWrite (PAGE_ADRESS | y);
		kursorY=y;
	}
}

/*--------------------------------------------------------------------------------
GOTO XY
---------------------------------------------------------------------------------*/

void GoToXY(unsigned char x,unsigned char y)
{
	GoToX(x);
	GoToY(y);
}

/*---------------------------------------------------
koristimo za skroolovanje ekrana tj tu polovinu koju postavimo startline
ona celu polovinu translira gore dole da joj je vrh na liniji koju postavimo
prosledjujemo vrednost 0-64
------------------------------------------------*/

void LcdSelectStartline(unsigned char startna_linija)
{
	LcdInstructionWrite (START_LINE | startna_linija);
}

/*-------------------------------------------------------------------------------
Select the side of the LCD
	LcdSelectSide(U8 u8LcdSide)
		u8LcdSide = LEFT or RIGHT
-------------------------------------------------------------------------------*/

void LcdSelectSide(unsigned char u8LcdSide)
{
	SetRS(0);  	
	if(u8LcdSide == RIGHT)
	{
    		SetRW(0);
   		SetCS1(1); 	
    		SetCS2(0);
	  	LcdInstructionWrite(DISPLAY_ON);
		strana=RIGHT;
   	}
	else
	{
		SetRW(0);
   		SetCS1(0); 	
   		SetCS2(1);
	 	LcdInstructionWrite(DISPLAY_ON);     
    		strana=LEFT;
 	}
}


/*-------------------------------------------------------------------------------
Read data from LCD
	U8 = LcdDataRead();
-------------------------------------------------------------------------------*/

unsigned char LcdDataRead (void)
{
	unsigned char temp;
	//LcdWaitBusy ();		// wait until LCD not busy --------------------------------------------------------------------
 	 ConfigureLcdData(input);
	SetRS(1);      	/* Data mode */
	SetRW(1);      	/* read mode */
	//LcdDelay(5);
	strobe_data();//ne znma zasto ali trazi ovo sto je u sustino dupli strobe da bi dobro iscitao bajt..
	//LcdDelay(5);
	SetE(1);
	//LcdDelay(5);
	temp=ReadLcdData();
	SetE(0);
	ConfigureLcdData(output);
	//LcdDelay(5);
	SetRS(0);      	/* Data mode */
	SetRW(0);      	/* read mode */
	return temp;/* return the data read */


/*

	SetE(1);
//	LcdWaitBusy ();// opsrobano radi radi-----------------------------------------------------------------
	SetRW(1);       	
 	SetRS(1);  
  ConfigureLcdData(input);
	SetE(0);
	LcdDelay(1);
	SetE(1);
	//	LcdWaitBusy ();// samo ovde ne radi kako treba----------------------------------------------------------------------
	//SetE(0);
	LcdDelay(1);
//	SetE(1);

	SetE(0);
	temp=ReadLcdData();
//	SetE(1);
	return temp; */
}
/*-------------------------------------------------------------------------------
LCD Initialization
	GLCD_LcdINIT()
-------------------------------------------------------------------------------*/
void GLCD_LcdInit(void)	
{
	SetLcdData(0);
	SetRS(0);
  	SetRW(0);
  	SetE(0);
  	SetCS1(0);
  	SetCS2(0);
  	
  	SetRST(1);
  	LcdDelay(10);
  	SetRST(0);
  	LcdDelay(10);
  	SetRST(1);
  	  	
  	LcdSelectSide(LEFT);
  	LcdInstructionWrite(DISPLAY_OFF); /* Display OFF */
  	LcdInstructionWrite(START_LINE);
  	LcdInstructionWrite(PAGE_ADRESS);
  	LcdInstructionWrite(Y_ADRESS);
  	LcdInstructionWrite(DISPLAY_ON); /* Display ON */
  	
  	LcdSelectSide(RIGHT);
  	LcdInstructionWrite(DISPLAY_OFF); /* Display OFF */
  	LcdInstructionWrite(START_LINE);
  	LcdInstructionWrite(PAGE_ADRESS);
  	LcdInstructionWrite(Y_ADRESS);
  	LcdInstructionWrite(DISPLAY_ON); /* Display ON */
  	
  //	GLCD_ClearScreen();++++++++++++++++++++++++++++++++++++++
}  	



/*-------------------------------------------------------------------------------
Send datas to the LCD
	LcdDataWrite (U8 u8Data)
		u8Data = data to send to the LCD
-------------------------------------------------------------------------------*/
void LcdDataWrite (unsigned char u8Data)
{
	//LcdWaitBusy ();		// wait until LCD not busy --------------------------------------------------------------------
	SetRS(1);      	/* Data mode */
	SetRW(0);      	/* write mode */
	SetLcdData(u8Data);	/* outbyte */
	strobe_data();

}


/*brisanje ekrana---------------*/

void GLCD_ClrScr (void)
{
	unsigned char q,vert;

	for (vert = 0; vert< 8; vert++) 
    	{
		GoToXY(0,vert);
		for (q = 0; q < 64; q++)
		{
			LcdDataWrite(0);
		}
		GoToXY(64,vert);
		for (q = 0; q < 64; q++)
		{
			LcdDataWrite(0);
		}
	}
}

/*ispuni ceo ekran ekrana---------------*/

void GLCD_FillScr (void)
{
unsigned char q,vert;

	for (vert = 0; vert< 8; vert++) 
    	{
		GoToXY(0,vert);
		for (q = 0; q < 64; q++)
		{
			LcdDataWrite(0xff);
		}
		GoToXY(64,vert);
		for (q = 0; q < 64; q++)
		{
			LcdDataWrite(0xff);
		}
	}
}


/*-------------------------------------------------------------------------------
Send an image to the LCD
	GLCD_DisplayPicture (U8 *au8PictureData)
		au8PictureData = contains datas for picture
-------------------------------------------------------------------------------*/
//void GLCD_DisplayPicture (unsigned char  *au8PictureData)
void GLCD_DisplayPicture (unsigned char *slika)
{

unsigned char q,vert;

	for (vert = 0; vert< 8; vert++) /* loop on the 8 pages */
    	{
      		GoToXY(0,vert);
      		for (q = 0; q < 64; q++)
		{
			LcdDataWrite(slika[vert*128+q]);
		}
		GoToXY(64,vert);
      		for (q = 0; q < 64; q++)
		{
			LcdDataWrite(slika[vert*128+q+64]);
		}
	}
}



/*-------------------------------------------------------------------------------
Draw a dot on the LCD
	LcdSetDoc (U8 u8Xaxis, U8 u8Yaxis)
		u8Xaxis = absciss
		u8Yaxis = ordinate
-------------------------------------------------------------------------------*/	
void LcdSetDot (unsigned char u8Xaxis, unsigned char u8Yaxis)
{
 
	unsigned char u8DataRead=0;

	GoToXY(u8Xaxis,(u8Yaxis / 8));
	u8DataRead = LcdDataRead (); 
	GoToXY(u8Xaxis,(u8Yaxis / 8));
	LcdDataWrite (u8DataRead | (1 << (u8Yaxis % 8)));/* plot the dot */
}

/*-------------------------------------------------------------------------------
Draw a prazno on the LCD
	LcdSetDoc (U8 u8Xaxis, U8 u8Yaxis)
		u8Xaxis = absciss
		u8Yaxis = ordinate
-------------------------------------------------------------------------------*/	
void LcdResDot (unsigned char u8Xaxis, unsigned char u8Yaxis)
{
 
	unsigned char u8DataRead=0;

	GoToXY(u8Xaxis,(u8Yaxis / 8));
	u8DataRead = LcdDataRead (); 
	GoToXY(u8Xaxis,(u8Yaxis / 8));
	LcdDataWrite (u8DataRead & (0xff^(1 << (u8Yaxis % 8)))  );/* plot the dot */
}



/*-------------------------------------------------------------------------------
Draw a circle on the LCD
	GLCD_Circle (U8 u8CenterX, U8 u8CenterY, U8 u8Radius)
		u8CenterX = Center absciss (in pixels)
		u8CenterY = Center ordinate (in pixels) 
		u8Radius  = Radius (in pixels)
-------------------------------------------------------------------------------*/
void GLCD_Circle (unsigned char u8CenterX, unsigned char u8CenterY, unsigned char u8Radius)
{
	int s16tswitch=0, s16y=0, s16x=0;
	unsigned char u8d;

	u8d = u8CenterY - u8CenterX;
	s16y = u8Radius;
	s16tswitch = 3 - 2 * u8Radius;
	while (s16x <= s16y) 
	{
		LcdSetDot(u8CenterX + s16x, u8CenterY + s16y);
		LcdSetDot(u8CenterX + s16x, u8CenterY - s16y);
		
		LcdSetDot(u8CenterX - s16x, u8CenterY + s16y);
		LcdSetDot(u8CenterX - s16x, u8CenterY - s16y);
		
		LcdSetDot(u8CenterY + s16y - u8d, u8CenterY + s16x);
		LcdSetDot(u8CenterY + s16y - u8d, u8CenterY - s16x);
		LcdSetDot(u8CenterY - s16y - u8d, u8CenterY + s16x); 
		LcdSetDot(u8CenterY - s16y - u8d, u8CenterY - s16x);

		if (s16tswitch < 0) 
			s16tswitch += (4 * s16x + 6);
		else 
		{
			s16tswitch += (4 * (s16x - s16y) + 10);
			s16y--;
		}
	
		s16x++;
	}
}


/*-------------------------------------------------------------------------------
Draw a rectangle on the LCD
	GLCD_Rectangle (U8 u8Xaxis1,U8 u8Yaxis1,U8 u8Xaxis2,U8 u8Yaxis2)
		u8Xaxis1 = absciss top-left (in pixels)
		u8Yaxis1 = ordinate top-left (in pixels)
		u8Xaxis2 = absciss bottom-right (in pixels)
		u8Yaxis2 = ordinate bottom-right (in pixels)
-------------------------------------------------------------------------------*/
void GLCD_Rectangle (unsigned char u8Xaxis1,unsigned char u8Yaxis1,unsigned char u8Xaxis2,unsigned char u8Yaxis2)
{
  	unsigned char u8CurrentValue=0;

	/* Draw the two horizontal lines */
  	for (u8CurrentValue = 0; u8CurrentValue < u8Xaxis2 - u8Xaxis1+ 1; u8CurrentValue++) 
  	{
		LcdSetDot(u8Xaxis1 + u8CurrentValue, u8Yaxis1);
		LcdSetDot(u8Xaxis1 + u8CurrentValue, u8Yaxis2);
	}
  	
  	/* draw the two vertical lines */
  	for (u8CurrentValue = 0; u8CurrentValue < u8Yaxis2 - u8Yaxis1 + 1; u8CurrentValue++)	
  	{
		LcdSetDot(u8Xaxis1, u8Yaxis1 + u8CurrentValue);
		LcdSetDot(u8Xaxis2, u8Yaxis1 + u8CurrentValue);
	}
}
 

/*-------------------------------------------------------------------------------
ispisuje 1 karakter na display-u sa prebacivanjem u novi red pri preteku i vracanjem na 0-ti red kada prodje poslednji
-------------------------------------------------------------------------------*/
void Glcd_PutChar (char AskiKod)
{
unsigned char trm;

if ((kursorX+FONT_LENGHT)>127)
	{
	kursorY++;
	if (kursorY>7)
		kursorY=0;
	kursorX=0;
	}
GoToXY(kursorX,kursorY);
for (trm=0;trm<FONT_LENGHT;trm++)
	{
	LcdDataWrite(font[((AskiKod-32)*FONT_LENGHT)+trm]);
	kursorX++;
	GoToXY(kursorX,kursorY);
	}
	LcdDataWrite(0);
	kursorX++;
}

/*-------------------------------------------------------------------------------
ispisuje 1 veliki karakter na display-u sa prebacivanjem u novi red pri preteku i vracanjem na 0-ti red kada prodje poslednji
-------------------------------------------------------------------------------*/
void Glcd_PutCharBig (char AskiKod)
{
unsigned char trm;

if ((kursorX+8)>127)
	{
	kursorY++;
	kursorY++;
	if (kursorY>7)
		kursorY=0;
	kursorX=0;
	}

for (trm=0;trm<8;trm++)
	{
	GoToXY(kursorX,kursorY);
	LcdDataWrite(fontBIG[(((AskiKod-32)*16)+trm)]);
	LcdInstructionWrite (PAGE_ADRESS | (kursorY+1));
if (kursorX<64)
	{
	LcdSelectSide(LEFT);
	LcdInstructionWrite (Y_ADRESS | kursorX);
	strana=LEFT;
	}
else if(kursorX<128)
	{
	LcdSelectSide(RIGHT);
	LcdInstructionWrite (Y_ADRESS | (kursorX-64));
	strana=RIGHT;
	}
	LcdDataWrite(fontBIG[(((AskiKod-32)*16)+trm+8)]);

	kursorX++;
	GoToXY(kursorX,kursorY);
	}






//	LcdDataWrite(0);
//	kursorX++;
}


/*-------------------------------------------------------------------------------
Print a string on the LCD
	GLCD_Printf (U8 *au8Text) 
		*au8Text = string to display
-------------------------------------------------------------------------------*/
void GLCD_Printf (char *au8Text) 
{
	while(*au8Text != 0)
	{
		Glcd_PutChar (*au8Text);
		au8Text++;
	}
}


/*-------------------------------------------------------------------------------
crta greed na display-u
-------------------------------------------------------------------------------*/
void GLCD_ShowGreed(unsigned char razmak_greeda) 
{
unsigned char x_greed,y_greed,deljeno;

deljeno=razmak_greeda/odnos_pravougaonosti_piksela;

for (x_greed=0;x_greed<127;x_greed=x_greed+3)
	for (y_greed=deljeno;y_greed<64-deljeno;y_greed=y_greed+deljeno)
		{
		LcdSetDot (x_greed,y_greed);
		}

for (x_greed=(razmak_greeda-2);x_greed<124;x_greed=x_greed+razmak_greeda)
	for (y_greed=0;y_greed<63;y_greed=y_greed+2)
		{
		LcdSetDot (x_greed,y_greed);
		}
}

//#else 
//#warning "Does not build on this target"
//#endif


void GLCD_Clr_Rectangle (unsigned char u8Xaxis1,unsigned char u8Yaxis1,unsigned char u8Xaxis2,unsigned char u8Yaxis2)
{
          unsigned char u8CurrentValue=0;

        /* Draw the two horizontal lines */
          for (u8CurrentValue = 0; u8CurrentValue < u8Xaxis2 - u8Xaxis1+ 1; u8CurrentValue++) 
          {
                LcdResDot(u8Xaxis1 + u8CurrentValue, u8Yaxis1);
                LcdResDot(u8Xaxis1 + u8CurrentValue, u8Yaxis2);
        }
          
          /* draw the two vertical lines */
          for (u8CurrentValue = 0; u8CurrentValue < u8Yaxis2 - u8Yaxis1 + 1; u8CurrentValue++)        
          {
                LcdResDot(u8Xaxis1, u8Yaxis1 + u8CurrentValue);
                LcdResDot(u8Xaxis2, u8Yaxis1 + u8CurrentValue);
        }
}


