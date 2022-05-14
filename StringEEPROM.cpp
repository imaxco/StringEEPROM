/*
 * StringEEPROM.cpp
 *
 * Created on: May 14, 2022
 * Author: IMAX
 */

#include "StringEEPROM.h"

bool StringEEPROM::Write_to_eeprom(char* stringIn , int startbit)
{
int sizebuffer = strlen(stringIn); 
EEPROM.write(startbit - 1, sizebuffer); 
for(int i = 0; i < sizebuffer; i++)
    {
    EEPROM.write(i+startbit, stringIn[i]); 
    }
EEPROM.commit();     
return true;      
}

int StringEEPROM::bit_size_eeprom(int number)
{
int size_bit = 0;   
for(int i = 0; i < (number - 1); i++) 
    {
    size_bit += EEPROM.read(size_bit) + 2;     
    }
return size_bit;      
}

int StringEEPROM::size_buffer_eeprom(int number)
{
int size_buf = 0;
size_buf = EEPROM.read(bit_size_eeprom(number));
return size_buf;      
}

void StringEEPROM::debug(bool debugSerial)      //send data to serial
{
_debugSerial = debugSerial;  
}

String StringEEPROM::read(int number)
{
int      num = bit_size_eeprom(number) + 1;   
int size_buf = size_buffer_eeprom(number);

char eeprom_buffer[size_buf + 1] = "";
for(int i = 0; i < size_buf; i++)
    {
    eeprom_buffer[i] = EEPROM.read(i+num);
    }
eeprom_buffer[size_buf] = '\0';    
if(_debugSerial) 
    {
    int size_buffer = strlen(eeprom_buffer);
    if(size_buf != size_buffer)Serial.println("EEPROM NOT MACHED! >" + String(size_buffer)); 
    else  Serial.println("EEPROM" + String(number) + " MACHED!!! >" + String(size_buffer)); 
    Serial.println("DATA: " + String(eeprom_buffer)); 
    Serial.println("SIZE: " + String(size_buf)); 
    Serial.println("--------------------"); 
    }
return String(eeprom_buffer);  
//return eeprom_buffer;   
}
bool StringEEPROM::write(char* stringIn , int number)
{
int num = 1; 
     if(number == 1)
    {
    num = 1; 
    bool debug1 = _debugSerial;
    _debugSerial = false;
    String buf2 = read(2);           // save buffer 2
    _debugSerial = debug1;
    
    Write_to_eeprom(stringIn , num);
    num = EEPROM.read(0) + 3;
    
    int size_buffer2 = buf2.length();
    char buffer2[size_buffer2];
    
    buf2.toCharArray(buffer2, size_buffer2);
    Write_to_eeprom(buffer2 , num);  //Write again buffer 2 to new start bit
    EEPROM.commit();
     
    return true; 
    }
else if(number == 2)
    {
    num = EEPROM.read(0) + 3;
    Write_to_eeprom(stringIn , num);
    EEPROM.commit(); 
    return true; 
    } 
else return false;      
}
void StringEEPROM::begin(int size_E)
{
EEPROM.begin(size_E + 5);  
}
