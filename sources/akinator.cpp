#include <stdio.h>

#include "binTree.h"
#include "akinator.h"


//--------------------------------------------------------------------------------------------------


enum AKINATOR_MODES
{
    AKINATOR_GUESS,
    AKINATOR_COMPARE,
    AKINATOR_DEFINE
};
typedef enum AKINATOR_MODES akinatorMode_t;


struct Akinator
{
    binTree_t binTree;
    akinatorMode_t mode;
};


//--------------------------------------------------------------------------------------------------


void AkinatorPlay()
{
    Akinator akinator = {};
    
    akinator.binTree = NULL;
    akinator.mode    = AkinatorGetMode(&akinator);

    AkinatorRunMode(&akinator);
}


//--------------------------------------------------------------------------------------------------


