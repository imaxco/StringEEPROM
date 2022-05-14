/*
 * StringEEPROM.h
 *
 * Created on: May 14, 2022
 * Author: IMAX
 */

#ifndef STRINGEEPROM_H_
#define STRINGEEPROM_H_
#include <EEPROM.h>
class StringEEPROM
{
public:
        void begin(int size_E);
        void debug(bool debugSerial);
        bool write(char* stringIn , int number);
        String read(int number);
private:
        bool Write_to_eeprom(char* stringIn , int startbit);
        int size_buffer_eeprom(int number);
        int bit_size_eeprom(int number);
        bool _debugSerial;
};       
#endif /* StringEEPROM.h */
