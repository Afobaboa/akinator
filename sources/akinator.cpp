#include <stdio.h>

#include "binTree.h"
#include "akinator.h"
#include "akinatorIO.h"


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


static int CompareObjects(void* firstObject, void* secondObject);
static void PrintObject(FILE* file, void* object);

static akinatorMode_t AkinatorGetMode(Akinator* akinator);

static void AkinatorRunMode(Akinator* akinator);

static void AkinatorRunGuess(Akinator* akinator);
static void AkinatorRunCompare(Akinator* akinator);
static void AkinatorRunDefine(Akinator* akinator);

static bool AkinatorSetFirstObject(Akinator* akinator);
static bool AkinatorGuess(Akinator* akinator);


//--------------------------------------------------------------------------------------------------


void AkinatorPlay()
{
    Akinator akinator = {};
    
    akinator.binTree = NULL;
    akinator.mode    = AkinatorGetMode(&akinator);

    AkinatorRunMode(&akinator);

    BinTreeDelete(&akinator.binTree);
}


//--------------------------------------------------------------------------------------------------


static int CompareObjects(const void* firstObject, const void* secondObject)
{

}


static void PrintObject(FILE* file, const void* object)
{

}


// TODO
static akinatorMode_t AkinatorGetMode(Akinator* akinator)
{
    akinator->mode = AKINATOR_GUESS; 
}


static void AkinatorRunMode(Akinator* akinator)
{
    switch (akinator->mode)
    {
    case AKINATOR_GUESS:
        AkinatorRunGuess(akinator);
        break;
    
    case AKINATOR_COMPARE:
        AkinatorRunCompare(akinator);
        break;

    case AKINATOR_DEFINE:
        AkinatorRunDefine(akinator);
        break;

    default:
        ColoredPrintf(RED, "Wrong mode\n");
    }
}


static void AkinatorRunGuess(Akinator* akinator)
{
    if (akinator->binTree == NULL)
        if (!AkinatorSetFirstObject(akinator))
            return;

    for (;;)
    {
        if (!AkinatorGuess(akinator))
            return;
    }
}


// TODO
static void AkinatorRunCompare(Akinator* akinator)
{

}


// TODO
static void AkinatorRunDefine(Akinator* akinator)
{

}


static bool AkinatorSetFirstObject(Akinator* akinator)
{
    char object[MAX_OBJECT_LENGTH] = "";
    GetObject(object);
    
    char property[MAX_OBJECT_LENGTH] = "";
    GetProperty(property, object);

    BIN_TREE_INIT(&akinator->binTree, sizeof(char*), &property, CompareObjects);
    BinTreeInsert(akinator->binTree, &object);
}


static bool AkinatorGuess(Akinator* akinator)
{
    
}
