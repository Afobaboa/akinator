#include <stdio.h>
#include <stdlib.h>

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


static int CompareObjects(const void* firstObject, const void* secondObject);
static void DeleteObject(void* objectPtr);
static void PrintObject(FILE* file, const void* object);

static akinatorMode_t AkinatorGetMode();

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
    akinator.mode    = AkinatorGetMode();

    AkinatorRunMode(&akinator);

    BinTreeDelete(&akinator.binTree, DeleteObject);
}


//--------------------------------------------------------------------------------------------------


static int CompareObjects(const void* firstObject, const void* secondObject)
{
    printf("Is it %s?\n"
           "[Y]es, [N]o.\n", 
           *((const char**) secondObject));
    
    char answer = (char) getchar();

    char tempChar = (char) getchar();
    printf(">~~~ %c [%d]\n\n", tempChar, tempChar);

    if (answer == 'Y')
        return 0;

    if (answer == (char) EOF)
        printf("EOF\n");
    
    printf("> %c [%d]\n\n", answer, answer);
    return -1;
}


static void DeleteObject(void* objectPtr)
{
    free(*((char**) objectPtr));
}


static void PrintObject(FILE* file, const void* object)
{
    fprintf(file, "%s", (const char*) object);
}


// TODO
static akinatorMode_t AkinatorGetMode()
{
    return AKINATOR_GUESS; 
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
        ColoredPrintf(RED, "Wrong mode: %d\n", akinator->mode);
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
    char* object = (char*) calloc(MAX_OBJECT_LENGTH, sizeof(char));
    GetObject(object);
    ColoredPrintf(YELLOW, "Object = %p at %p\n", object, &object);
    
    char* property = (char*) calloc(MAX_OBJECT_LENGTH, sizeof(char));
    GetProperty(property, object);

    if (!BIN_TREE_INIT(&akinator->binTree, sizeof(char*), &property, CompareObjects) ||
        !BinTreeInsert(akinator->binTree, &object, CompareObjects))
    {
        return false;
    }

    return true;
}


static bool AkinatorGuess(Akinator* akinator)
{
    ColoredPrintf(WHITE, "Guessing...\n");
    BinTreeNode* questionNode = NULL;
    treeDirection_t direction  = BinTreeNodeParentFind(akinator->binTree, NULL, CompareObjects, 
                                                                                    &questionNode);
    if (direction == RIGHT)
        printf("Yeah!\n");

    else if (direction == LEFT)
        printf("BAN\n");

    return false;
}
