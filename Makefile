# Compiler
CC=g++-11


# Flags for debugging compilation
DEBUG_FLAGS=-D_DEBUG -ggdb3 -std=c++17 -Wall $\
-Wextra -Weffc++ -Waggressive-loop-optimizations $\
-Wc++14-compat -Wmissing-declarations -Wcast-align $\
-Wcast-qual -Wchar-subscripts -Wconditionally-supported $\
-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal $\
-Wformat-security -Wformat-signedness $\
-Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor $\
-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith $\
-Winit-self -Wredundant-decls -Wshadow -Wsign-conversion $\
-Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 $\
-Wsuggest-attribute=noreturn -Wsuggest-final-methods $\
-Wsuggest-final-types -Wsuggest-override -Wswitch-default $\
-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code $\
-Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix $\
-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast $\
-Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation $\
-fstack-protector -fstrict-overflow -flto-odr-type-merging $\
-fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 $\
-pie -fPIE -mavx2 -fsanitize=address,alignment,bool,$\
bounds,enum,float-cast-overflow,float-divide-by-zero,$\
integer-divide-by-zero,leak,nonnull-attribute,null,object-size,$\
return,returns-nonnull-attribute,shift,signed-integer-overflow,$\
undefined,unreachable,vla-bound,vptr $\
-Iheaders -IbinTree/headers -IbinTree/logPrinter -IbinTree/stack/headers


# Flags for release version compilation
RELEASE_FLAGS=-Wmissing-declarations -Wempty-body -DNDEBUG -DLOG_SWITCH_OFF $\
-Iheaders -IbinTree/headers -IbinTree/logPrinter -IbinTree/stack/headers


FLAGS=


#---------------------------------------------------------------------------------------------------


OBJECTS_DIR=objects


# Make OBJECTS_DIR if it doesn't exist
objects_dir:
	@if [ ! -d $(OBJECTS_DIR) ]; \
	then                         \
		mkdir $(OBJECTS_DIR);    \
	fi


# Clean objects dir
clean:
	@rm -f $(OBJECTS_DIR)/*.o $(EXECUTABLE)


#---------------------------------------------------------------------------------------------------


# Log files and directory
LOG_SUBDIR=binTree/logPrinter

LOG_SOURCE_FILES=logPrinter.cpp
LOG_HEADER_FILES=logPrinter.h logPrinterConfigs.h

LOG_SOURCES=$(patsubst %.cpp,$(LOG_SUBDIR)/%.cpp,$(LOG_SOURCE_FILES))
LOG_HEADERS=$(patsubst %.h,$(LOG_SUBDIR)/%.h,$(LOG_HEADER_FILES))
LOG_OBJECTS=$(patsubst %.cpp,$(OBJECTS_DIR)/%.o,$(LOG_SOURCE_FILES))


$(OBJECTS_DIR)/%.o: $(LOG_SUBDIR)/%.cpp $(LOG_HEADERS)
	@$(CC) -c $(FLAGS) $< -o $@


# Clean log files
log_clean:
	@rm -f logs/log.txt logs/emergencyLog.txt


#---------------------------------------------------------------------------------------------------


# binTree
BIN_TREE_SOURCE_DIR=binTree/sources
BIN_TREE_HEADER_DIR=binTree/headers

BIN_TREE_SOURCE_FILES=binTree.cpp binTreeDumper.cpp
BIN_TREE_HEADER_FILES=binTree.h binTreeDumper.h binTreeStructs.h

BIN_TREE_SOURCES=$(patsubst %.cpp,$(BIN_TREE_SOURCE_DIR)/%.cpp,$(BIN_TREE_SOURCE_FILES))
BIN_TREE_HEADERS=$(patsubst %.h,$(BIN_TREE_HEADER_DIR)/%.h,$(BIN_TREE_HEADER_FILES))
BIN_TREE_OBJECTS=$(patsubst %.cpp,$(OBJECTS_DIR)/%.o,$(BIN_TREE_SOURCE_FILES)) 


$(OBJECTS_DIR)/%.o: $(BIN_TREE_SOURCE_DIR)/%.cpp $(BIN_TREE_HEADERS) $(LOG_HEADERS)
	@$(CC) -c $(FLAGS) $< -o $@


#---------------------------------------------------------------------------------------------------


# stack
STACK_SOURCE_DIR=binTree/stack/sources
STACK_HEADER_DIR=binTree/stack/headers

STACK_SOURCE_FILES=canary.cpp hash.cpp myRecalloc.cpp stack.cpp
STACK_HEADER_FILES=canary.h hash.h myRecalloc.h stack.h stackConfigs.h

STACK_SOURCES=$(patsubst %.cpp,$(STACK_SOURCE_DIR)/%.cpp,$(STACK_SOURCE_FILES))
STACK_HEADERS=$(patsubst %.h,$(STACK_HEADER_DIR)/%.h,$(STACK_HEADER_FILES))
STACK_OBJECTS=$(patsubst %.cpp,$(OBJECTS_DIR)/%.o,$(STACK_SOURCE_FILES))


$(OBJECTS_DIR)/%.o: $(STACK_SOURCE_DIR)/%.cpp $(STACK_HEADERS) $(LOG_HEADERS)
	@$(CC) -c $(FLAGS) $< -o $@


#---------------------------------------------------------------------------------------------------


# akinator
AKINATOR_SOURCE_DIR=sources
AKINATOR_HEADER_DIR=headers

AKINATOR_SOURCE_FILES=akinator.cpp akinatorIO.cpp
AKINATOR_HEADER_FILES=akinator.h akinatorIO.h

AKINATOR_SOURCES=$(patsubst %.cpp,$(AKINATOR_SOURCE_DIR)/%.cpp,$(AKINATOR_SOURCE_FILES))
AKINATOR_HEADERS=$(patsubst %.h,$(AKINATOR_HEADER_DIR)/%.h,$(AKINATOR_HEADER_FILES))
AKINATOR_OBJECTS=$(patsubst %.cpp,$(OBJECTS_DIR)/%.o,$(AKINATOR_SOURCE_FILES)) 


$(OBJECTS_DIR)/%.o: $(AKINATOR_SOURCE_DIR)/%.cpp $(AKINATOR_HEADERS) $(BIN_TREE_HEADER_DIR) $\
																					$(LOG_HEADERS)
	@$(CC) -c $(FLAGS) $< -o $@


#---------------------------------------------------------------------------------------------------

MAIN_SOURCE_DIR=$(AKINATOR_SOURCE_DIR)

MAIN_SOURCE=$(MAIN_SOURCE_DIR)/main.cpp
MAIN_OBJECT=$(patsubst $(MAIN_SOURCE_DIR)/%.cpp, $(OBJECTS_DIR)/%.o, $(MAIN_SOURCE))

OBJECTS=$(MAIN_OBJECT) $(AKINATOR_OBJECTS) $(BIN_TREE_OBJECTS) $(STACK_OBJECTS) $(LOG_OBJECTS)
HEADERS=$(AKINATOR_HEADERS) $(BIN_TREE_HEADERS) $(STACK_HEADERS) $(LOG_HEADERS)

print:
	echo $(OBJECTS)

EXECUTABLE=akinator


# Make release version of program
all: release


# Run program
run: $(EXECUTABLE)
	@./$<


# Make release version
release_flags:
	@$(eval FLAGS = $(RELEASE_FLAGS))

release: release_flags objects_dir $(OBJECTS) $(HEADERS)
	@$(CC) $(FLAGS) $(OBJECTS) -o $(EXECUTABLE)

release_run: release run


# Make debug version
debug_flags:
	@$(eval FLAGS = $(DEBUG_FLAGS))
	@$(eval FLAGS += -D_BIN_TREE_DEBUG)

debug: debug_flags objects_dir $(OBJECTS) $(HEADERS)
	@$(CC) $(FLAGS) $(OBJECTS) -o $(EXECUTABLE)

debug_run: debug run