#include <stdio.h>

#include "akinatorIO.h"


//--------------------------------------------------------------------------------------------------


static bool GetLine(char* buffer, const size_t bufferSize);


//--------------------------------------------------------------------------------------------------


bool GetObject(char* objectBuffer)
{
    printf("Enter name of your ogject.\n");
    if (GetLine(objectBuffer, MAX_OBJECT_LENGTH))
        return true;

    return false;
}


bool GetProperty(char* propertyBuffer, const char* object)
{
    printf("Enter any property of %s\n.", object);
    if (GetLine(propertyBuffer, MAX_OBJECT_LENGTH))
        return true;

    return false;
}


//--------------------------------------------------------------------------------------------------


static bool GetLine(char* buffer, const size_t bufferSize)
{
    bool gettingResult = false;
    for (size_t charIndex = 0; charIndex < bufferSize; charIndex++)
    {
        char nextChar = getchar();
        if (nextChar == '\n')
        {
            gettingResult = true;
            buffer[charIndex] = '\0';
            break;
        }

        buffer[charIndex] = nextChar;
    }

    return gettingResult;
}
