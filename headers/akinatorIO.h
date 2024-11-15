#ifndef AKINATOR_IO_H
#define AKINATOR_IO_H


//--------------------------------------------------------------------------------------------------

#include <stddef.h>


enum END_STATUSES
{
    END_STATUS_WRONG,

    REPEAT,
    EXIT,

    END_STATUSES_COUNT
};
typedef enum END_STATUSES endStatus_t;


endStatus_t EndStatusGet(const char* repeatDescription, const char* exitDescription);


//--------------------------------------------------------------------------------------------------


typedef char* akinatorString_t;
static const size_t MAX_AKINATOR_STRING_LENGTH = 128;

akinatorString_t AkinatorStringCreate();
void AkinatorStringDelete(akinatorString_t string);


typedef akinatorString_t akinatorObject_t;
#define PRIakinObj "s" // PRIakinatorObject

typedef akinatorString_t akinatorProperty_t;
#define PRIakinPpt "s" // PRIakinatorProperty

akinatorObject_t AkinatorObjectGet();
akinatorProperty_t AkinatorPropertyGet(const akinatorObject_t object);


//--------------------------------------------------------------------------------------------------


void SkipSpaces();


//--------------------------------------------------------------------------------------------------


#endif // AKINATOR_IO_H