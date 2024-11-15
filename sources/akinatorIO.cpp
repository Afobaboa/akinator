#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "akinatorIO.h"


//--------------------------------------------------------------------------------------------------


static akinatorString_t AkinatorStringInit();


//--------------------------------------------------------------------------------------------------


endStatus_t EndStatusGet(const char* repeatDescription, const char* exitDescription)
{
    for (;;)
    {
        printf("%d - %s\n"
               "%d - %s\n", 
               REPEAT, repeatDescription,
               EXIT,   exitDescription);

        endStatus_t endStatus = END_STATUS_WRONG;
        scanf("%d", (int*) &endStatus);
        if (endStatus > END_STATUS_WRONG && endStatus < END_STATUSES_COUNT)
            return endStatus;
        
        printf("Wrong! Choose again.");
    }
}


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
    printf("Enter any property of %" PRIakinObj ".\n", object);
    return AkinatorStringInit();
}


void SkipSpaces()
{
    int nextChar = 0;
    for (;;)
    {
        nextChar = getchar();
        if (!isspace(nextChar))
        {
            ungetc(nextChar, stdin);
            break;
        }

        if (nextChar == '\n')
            break;
    }
}


//--------------------------------------------------------------------------------------------------


static akinatorString_t AkinatorStringInit()
{
    akinatorString_t string = AkinatorStringCreate();
    if (string == NULL)
        return NULL;

    // TODO scanf
    // char buffer[5] = {1, 2, 3, 4};
    // scanf(" %4[^\n]s", buffer);
    // for (int i = 0; i < 4; i++)
    //     printf("%d ", buffer[i]);
    
    // printf("\nbuffer = <%s>\n", buffer);

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
