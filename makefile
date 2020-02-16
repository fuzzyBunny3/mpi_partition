CXX = mpicxx
CLINKER = $(CXX)

EXTRA_CPP_COMPILE_FLAGS = 
EXTRA_CPP_LINK_FLAGS =

# Automatically detect all the examples:
CPP_SRC_FILES = $(wildcard *.cpp)
CPP_OBJ_FILES = $(patsubst %.cpp, %.cpp.o, $(CPP_SRC_FILES))
TESTS_CPP_SRC_FILES = $(wildcard *_tests.cpp)
TESTS_CPP_OBJ_FILES = $(patsubst %.cpp, %.cpp.o, $(TESTS_CPP_SRC_FILES))
TESTS_CPP_BIN_FILES = $(patsubst %.cpp, %, $(TESTS_CPP_SRC_FILES))


.PHONY: all clean test test_make

all: libmango.a $(TESTS_CPP_BIN_FILES)

export

# For info about the "Static pattern rules" below, see e.g.
# https://www.gnu.org/savannah-checkouts/gnu/make/manual/html_node/Static-Usage.html
# https://stackoverflow.com/questions/4320416/how-to-use-a-variable-list-as-a-target-in-a-makefile

$(CPP_OBJ_FILES): %.cpp.o: %.cpp mango.hpp
	$(CXX) $(EXTRA_CPP_COMPILE_FLAGS) -c $< -o $@

$(TESTS_CPP_BIN_FILES): %: %.cpp.o libmango.a
	$(CLINKER) -o $@ $< libmango.a $(EXTRA_CPP_LINK_FLAGS)

libmango.a: $(CPP_OBJ_FILES)
	ar rcs libmango.a $(CPP_OBJ_FILES)

clean:
	rm -f *.o *~ libmango.a $(TESTS_CPP_BIN_FILES)

test: $(TARGET)
	@echo "Beginning functional tests." && cd examples && export MANGO_RETEST=no && ./run_examples

test_make:
	@echo CXX is $(CXX)
	@echo CPP_SRC_FILES is $(CPP_SRC_FILES)
	@echo CPP_OBJ_FILES is $(CPP_OBJ_FILES)
	@echo TESTS_CPP_SRC_FILES is $(TESTS_CPP_SRC_FILES)
	@echo TESTS_CPP_OBJ_FILES is $(TESTS_CPP_OBJ_FILES)
	@echo TESTS_CPP_BIN_FILES is $(TESTS_CPP_BIN_FILES)
	@echo CLINKER is $(CLINKER)
	@echo EXTRA_CPP_COMPILE_FLAGS is $(EXTRA_CPP_COMPILE_FLAGS)
	@echo EXTRA_CPP_LINK_FLAGS is $(EXTRA_CPP_LINK_FLAGS)
