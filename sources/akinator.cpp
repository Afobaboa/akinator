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
    printf("Is it %s?\n"
           "[Y]es, [N]o.\n", 
           (const char*) secondObject);
    
    char answer = '\0';
    scanf("%c", &answer);

    if (answer == 'Y')
        return 0;

    if (answer == (char) EOF)
        printf("EOF\n");
    
    printf("> %c [%d]\n\n", answer, answer);
    return -1;
}


static void PrintObject(FILE* file, const void* object)
{
    fprintf(file, "%s", (const char*) object);
}


// TODO
static akinatorMode_t AkinatorGetMode(Akinator* akinator)
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
    char object[MAX_OBJECT_LENGTH] = "";
    GetObject(object);
    
    char property[MAX_OBJECT_LENGTH] = "";
    GetProperty(property, object);

    if (!BIN_TREE_INIT(&akinator->binTree, sizeof(char*), &property, CompareObjects) ||
        !BinTreeInsert(akinator->binTree, &object))
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
