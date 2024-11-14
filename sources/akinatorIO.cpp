#include <stdio.h>
#include <stdlib.h>

#include "akinatorIO.h"


//--------------------------------------------------------------------------------------------------


static akinatorString_t AkinatorStringInit();


//--------------------------------------------------------------------------------------------------


akinatorString_t AkinatorStringCreate()
{
    return (akinatorString_t) calloc(MAX_AKINATOR_STRING_LENGTH, sizeof(char));
}


void AkinatorStringDelete(akinatorString_t string)
{
    free(string);
}


akinatorObject_t AkinatorObjectGet()
{
    printf("Enter name of your object.\n");
    return AkinatorStringInit();
}


akinatorProperty_t AkinatorPropertyGet(const akinatorObject_t object)
{
    printf("Enter any property of " PRIakinObj ".\n", object);
    return AkinatorStringInit();
}


//--------------------------------------------------------------------------------------------------


static akinatorString_t AkinatorStringInit()
{
    akinatorString_t string = AkinatorStringCreate();
    if (string == NULL)
        return NULL;

    bool gettingResult = false;
    for (size_t charIndex = 0; charIndex < MAX_AKINATOR_STRING_LENGTH; charIndex++)
    {
        int nextChar = getchar();
        if (nextChar == '\n')
        {
            gettingResult = true;
            string[charIndex] = '\0';
            break;
        }

        if (nextChar == EOF)
            break;

        string[charIndex] = (char) nextChar;
    }

    string[MAX_AKINATOR_STRING_LENGTH - 1] = '\0';

    if (!gettingResult)
    {
        AkinatorStringDelete(string);
        return NULL;
    }

    return string;
}
