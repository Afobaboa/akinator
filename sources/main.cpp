#include <stdio.h>

#include "akinator.h"
#include "binTreeDumper.h"


int main()
{
    BIN_TREE_DUMPER_INIT("dump.dot", "dump.png");

    AkinatorPlay();

    BIN_TREE_DUMPER_DELETE();
    return 0;
}