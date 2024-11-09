#ifndef AKINATOR_IO_H
#define AKINATOR_IO_H


//--------------------------------------------------------------------------------------------------

#include <stddef.h>


static const size_t MAX_OBJECT_LENGTH = 128;


bool GetObject(char* objectBuffer);
bool GetProperty(char* propertyBuffer, const char* object);


//--------------------------------------------------------------------------------------------------


#endif // AKINATOR_IO_H