#ifndef XBEE_H_INCLUDED
#define XBEE_H_INCLUDED

#include <Windows.h>


HANDLE initXbee(HANDLE hSerial);

void initSio(HANDLE hSerial);
int readByte(HANDLE hSerial, char *buffRead);
int writeByte(HANDLE hSerial, char *buffWrite);

#endif // XBEE_H_INCLUDED
