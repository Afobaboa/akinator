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
static void AkinatorRunGetDefinition(Akinator* akinator);
// TODO change name

static bool AkinatorSetFirstObject(Akinator* akinator);
static bool AkinatorGuess(Akinator* akinator);

static void AkinatorAddObject(Akinator* akinator, BinTreeNode* questionNode);


//--------------------------------------------------------------------------------------------------


void AkinatorPlay()
{
    setvbuf(stdin, NULL, _IONBF, 0);

    ColoredPrintf(WHITE, "It is Akinator!\n");
    Akinator akinator = {};
    
    akinator.binTree = NULL;

    for(;;)
    {
        akinator.mode = AkinatorGetMode();
        AkinatorRunMode(&akinator);

        endStatus_t endStatus = EndStatusGet("choose mode.", "exit.");
        if (endStatus == EXIT)
            break;
    }

    ColoredPrintf(WHITE, "Goodbye!\n");
    BinTreeDelete(&akinator.binTree, __AkinatorStringDelete);
}


//--------------------------------------------------------------------------------------------------


static int CompareObjects(const void* firstObject, const void* secondObject)
{
    printf("Is it %s?\n"
           "[Y]es, [N]o.\n", 
           *((const char**) secondObject));
    
    // TODO think scanf("%c ");
    int answer = getchar();
    SkipSpaces();

    if (answer == 'Y')
        return EQUAL;
    
    // printf("> %c [%d]\n\n", answer, answer);
    return LESS;
}


static inline void __AkinatorStringDelete(void* akinatorStringPtr)
{
    AkinatorStringDelete(*((akinatorString_t*) akinatorStringPtr));
}


// TODO
static akinatorMode_t AkinatorGetMode()
{
    for (;;)
    {
        printf("%d - guess your objects.\n"
               "%d - compare your objects.\n"
               "%d - get definition of your object.\n",
               AKINATOR_GUESS,
               AKINATOR_COMPARE,
               AKINATOR_GET_DEFINITION);

        akinatorMode_t mode = AKINATOR_WRONG_MODE;
        scanf("%d", (int*) &mode);
        SkipSpaces();
        printf("\n");

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
        AkinatorRunGetDefinition(akinator);
        break;

    case AKINATOR_MODE_COUNT:
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
        AkinatorGuess(akinator);

        printf("\n");
        endStatus_t endStatus = EndStatusGet("repeat.", "choose other mode.");
        if (endStatus == EXIT)
            break;
        
        printf("\n");
    }
}


// TODO
static void AkinatorRunCompare(Akinator* akinator)
{

}


// TODO
static void AkinatorRunGetDefinition(Akinator* akinator)
{

}


static bool AkinatorSetFirstObject(Akinator* akinator)
{
    ColoredPrintf(WHITE, "Setting first object\n");

    const akinatorObject_t   object   = AkinatorObjectGet();
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
