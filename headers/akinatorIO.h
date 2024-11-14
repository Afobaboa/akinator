#ifndef AKINATOR_IO_H
#define AKINATOR_IO_H


//--------------------------------------------------------------------------------------------------

#include <stddef.h>


typedef char* akinatorString_t;
static const size_t MAX_AKINATOR_STRING_LENGTH = 128;

akinatorString_t AkinatorStringCreate();
void AkinatorStringDelete(akinatorString_t string);


typedef akinatorString_t akinatorObject_t;
#define PRIakinObj "%s" // PRIakinatorObject

typedef akinatorString_t akinatorProperty_t;
#define PRIakinPpt "%s"

akinatorObject_t AkinatorObjectGet();
akinatorProperty_t AkinatorPropertyGet(const akinatorObject_t object);


//--------------------------------------------------------------------------------------------------


#endif // AKINATOR_IO_H