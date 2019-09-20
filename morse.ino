#include <stdio.h> // For printf, scanf
#include <string.h> // For strcpy
#include <ctype.h> // tolower

// Arduino: Upload Alt + Cmd + U or Alt + Ctrl + U
// Arduino: Verify Alt + Cmd + R or Alt + Ctrl + R

const int ledRedPin = 4; 
const int ledGreenPin = 5; 
char incomingBytes[50];

void setup() {
  Serial.begin(9600);

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
}

// morse -> gets a string from serial and encodes every charachter as morse

void pinBeep(int pin, int isOn)
{
  digitalWrite(pin, isOn);
}

void pause(int millisec)
{
    Serial.println("pause "); 
    Serial.print(millisec); 
    delay(millisec);
}

void beepSomeTime(int pin, int millisec)
{
    pinBeep(pin, 1);
    pause(millisec);
    pinBeep(pin, 0);
    pause(millisec/10);
}

void beepShort(int pin)
{
    beepSomeTime(pin, 150);
    Serial.println("short beep"); 
}

void beepLong(int pin)
{
    beepSomeTime(pin, 500);
    Serial.println("long beep"); 
}

void encodeChar(char charToEncode, char res[6])
{    
    switch(tolower(charToEncode))
    {
        case 'a':
            strlcpy(res, "01", sizeof("99999"));
        break;

        case 'b':
            strlcpy(res, "1000", sizeof("99999"));
        break;

        case 'c':
            strlcpy(res, "1010", sizeof("99999"));
        break;

        case 'd':
            strlcpy(res, "100", sizeof("99999"));
        break;

        case 'e':
            strlcpy(res, "0", sizeof("99999"));
        break;

        case 'f':
            strlcpy(res, "0010", sizeof("99999"));
        break;

        case 'g':
            strlcpy(res, "110", sizeof("99999"));
        break;

        case 'h':
            strlcpy(res, "0000", sizeof("99999"));
        break;

        case 'i':
            strlcpy(res, "00", sizeof("99999"));
        break;

        case 'j':
            strlcpy(res, "0111", sizeof("99999"));
        break;

        case 'k':
            strlcpy(res, "101", sizeof("99999"));
        break;

        case 'l':
            strlcpy(res, "0100", sizeof("99999"));
        break;

        case 'm':
            strlcpy(res, "11", sizeof("99999"));
        break;

        case 'n':
            strlcpy(res, "10", sizeof("99999"));
        break;

        case 'o':
            strlcpy(res, "111", sizeof("99999"));
        break;

        case 'p':
            strlcpy(res, "0110", sizeof("99999"));
        break;

        case 'q':
            strlcpy(res, "1101", sizeof("99999"));
        break;

        case 'r':
            strlcpy(res, "010", sizeof("99999"));
        break;

        case 's':
            strlcpy(res, "000", sizeof("99999"));
        break;

        case 't':
            strlcpy(res, "1", sizeof("99999"));
        break;

        case 'u':
            strlcpy(res, "001", sizeof("99999"));
        break;

        case 'v':
            strlcpy(res, "0001", sizeof("99999"));
        break;

        case 'w':
            strlcpy(res, "011", sizeof("99999"));
        break;

        case 'x':
            strlcpy(res, "1001", sizeof("99999"));
        break;

        case 'y':
            strlcpy(res, "1011", sizeof("99999"));
        break;

        case 'z':
            strlcpy(res, "1100", sizeof("99999"));
        break;

        case '1':
            strlcpy(res, "01111", sizeof("99999"));
        break;

        case '2':
            strlcpy(res, "00111", sizeof("99999"));
        break;

        case '3':
            strlcpy(res, "00011", sizeof("99999"));
        break;

        case '4':
            strlcpy(res, "00001", sizeof("99999"));
        break;

        case '5':
            strlcpy(res, "00000", sizeof("99999"));
        break;

        case '6':
            strlcpy(res, "10000", sizeof("99999"));
        break;

        case '7':
            strlcpy(res, "11000", sizeof("99999"));
        break;

        case '8':
            strlcpy(res, "11100", sizeof("99999"));
        break;

        case '9':
            strlcpy(res, "11111", sizeof("99999"));
        break;

        default:
            strlcpy(res, "2", sizeof("99999"));
        break;
    }
}

void encodeMessage(char message[], char result[][6])
{
    for(int i = 0; i < strlen(message); i++)
    {
        char encoded[6] = "99999";
        encodeChar(message[i], encoded);
        strlcpy(result[i], encoded, sizeof("99999"));
    }
}

void displayEncodedChar(int pin, char message[])
{    
    for(int i = 0; i < strlen(message); i++)
    {
        Serial.println(message[i]); 
        if(message[i] == '0')
        {
            beepShort(pin);
        }
        else if(message[i] == '1')
        {
            beepLong(pin);
        }
        else
        {
            pause(1000);
        }
    }

    pause(50);
}

void displayEncodedMessage(int pin, char message[][6], int messageLength)
{
    for(int i = 0; i < messageLength; i++)
    {
        displayEncodedChar(pin, message[i]);
    }
}

void loop() {
  if (Serial.available() > 0) {
    strlcpy(incomingBytes, Serial.readString().c_str(), sizeof(incomingBytes));
    Serial.println("read:"); 
    Serial.println(incomingBytes); 
    
    /*char message[] = "Quick"; //"Quick fox jumps over the lasy dog";
    Serial.println(message); */
    
    int messageLength = strlen(incomingBytes);
    char result[messageLength + 1][6];
    //int pin = 13;

    encodeMessage(incomingBytes, result);
        
    displayEncodedMessage(ledRedPin, result, messageLength);
    digitalWrite(ledGreenPin, 1);
    // pause(4000);
  }
}
