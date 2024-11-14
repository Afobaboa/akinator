#include <stdio.h>
#include <stdlib.h>

#include "binTree.h"
#include "akinator.h"
#include "akinatorIO.h"


//--------------------------------------------------------------------------------------------------


enum AKINATOR_MODES
{
    AKINATOR_WRONG_MODE,

    AKINATOR_GUESS,
    AKINATOR_COMPARE,
    AKINATOR_GET_DEFINITION, 

    AKINATOR_MODE_COUNT
};
typedef enum AKINATOR_MODES akinatorMode_t;


enum END_STATUSES
{
    END_STATUS_WRONG,

    REPEAT,
    EXIT,

    END_STATUSES_COUNT
};
typedef enum END_STATUSES endStatus_t;


struct Akinator
{
    binTree_t binTree;
    akinatorMode_t mode;
};


//--------------------------------------------------------------------------------------------------


static int CompareObjects(const void* firstObject, const void* secondObject);
static inline void __AkinatorStringDelete(void* akinatorStringPtr);
static void PrintObject(FILE* file, const void* object);

static akinatorMode_t AkinatorGetMode();

static void AkinatorRunMode(Akinator* akinator);

static void AkinatorRunGuess(Akinator* akinator);
static void AkinatorRunCompare(Akinator* akinator);
static void AkinatorRunDefine(Akinator* akinator);
// TODO change name

static bool AkinatorSetFirstObject(Akinator* akinator);
static bool AkinatorGuess(Akinator* akinator);

static void AkinatorAddObject(Akinator* akinator, BinTreeNode* questionNode);


//--------------------------------------------------------------------------------------------------


void AkinatorPlay()
{
    ColoredPrintf(WHITE, "It is Akinator!\n");
    Akinator akinator = {};
    
    akinator.binTree = NULL;

    for(;;)
    {
        akinator.mode = AkinatorGetMode();
        AkinatorRunMode(&akinator);

        
        printf("%d - choose mode.\n" // endStatus = EndStatusGet("choose mode.", "exit.");
               "%d - exit.\n",
               REPEAT,
               EXIT);

        endStatus_t endStatus = END_STATUS_WRONG;
        
    }

    BinTreeDelete(&akinator.binTree, __AkinatorStringDelete);
}


//--------------------------------------------------------------------------------------------------

// TODO enum
// TODO change name
static int CompareObjects(const void* firstObject, const void* secondObject)
{
    printf("Is it %s?\n"
           "[Y]es, [N]o.\n", 
           *((const char**) secondObject));
    
    // TODO think scanf("%c ");
    char answer = (char) getchar();

    char tempChar = (char) getchar(); // to skip '\n', // TODO: add skipping spaces
    // printf(">~~~ %c [%d]\n\n", tempChar, tempChar);

    if (answer == 'Y')
        return 0;

    if (answer == (char) EOF)
        printf("EOF\n");
    
    // printf("> %c [%d]\n\n", answer, answer);
    return -1;
}


static inline void __AkinatorStringDelete(void* akinatorStringPtr)
{
    AkinatorStringDelete(*((akinatorString_t*) akinatorStringPtr));
}


// TODO
static akinatorMode_t AkinatorGetMode()
{
    printf("Choose mode:\n");

    for (;;)
    {
        printf("%d - guess your objects.\n"
               "%d - compare your objects.\n"
               "%d - get definition of your object.\n",
               AKINATOR_GUESS,
               AKINATOR_COMPARE,
               AKINATOR_GET_DEFINITION);

        akinatorMode_t mode = AKINATOR_WRONG_MODE;
        scanf("%d", &mode);
        if (mode > AKINATOR_WRONG_MODE && mode < AKINATOR_MODE_COUNT)
            return mode;
        else
            printf("You wrote wrong mode. Try choose again.\n");
    }
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

    case AKINATOR_GET_DEFINITION:
        AkinatorRunDefine(akinator);
        break;

    case AKINATOR_WRONG_MODE:
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
    ColoredPrintf(WHITE, "Setting first object\n");

    const akinatorObject_t   object = AkinatorObjectGet();
    const akinatorProperty_t property = AkinatorPropertyGet(object);

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

    else
        AkinatorAddObject(akinator, questionNode);

    return true;
}


// TODO typedef char* akinatorObject_t; and property_t. I can use inheritance
// TODO add NULL checkers when I create objects
// TODO add getting of child object
static void AkinatorAddObject(Akinator* akinator, BinTreeNode* questionNode)
{
    akinatorObject_t   newObject   = AkinatorObjectGet();
    akinatorProperty_t newProperty = AkinatorPropertyGet(newObject);

    BinTreeNode* newNode =  BinTreeInsertAfter(akinator->binTree, &newProperty, questionNode, 
                                               CompareObjects, CompareObjects);

    BinTreeInsertAfter(akinator->binTree, &newObject, newNode, CompareObjects, CompareObjects);
}
