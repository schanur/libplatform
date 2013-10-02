CC=clang
#CC=colorgcc
#CC=gcc
#CC=ccomp

MODULES = raytracer.o debug.o image.o image_io.o octree_io.o octree_mem.o array.o thread_pool.o test.o
BIN_FILES = c_test
CREATE_ASM=NO
UNITTESTING=NO

ifeq ($(CC),clang)
	WARNINGS = -Weverything -Wno-padded -Wno-unused-macros -Wno-missing-noreturn -Wno-disabled-macro-expansion -ferror-limit=3
#	WARNINGS = -Weverything -ferror-limit=3
#	WARNINGS = -Weverything -Wno-padded -Wno-unused-macros -Wno-missing-noreturn -Wno-disabled-macro-expansion -Werror -ferror-limit=3
#	WARNINGS = -Weverything -Wno-padded -Wno-unused-macros -Wno-missing-noreturn -Wno-disabled-macro-expansion -Wno-unused-parameter -Werror -ferror-limit=3
	CSTD= -std=c99
#	CSTD= -std=c11

else
	WARNINGS = -Wall -Wextra -Wformat
	CSTD= -std=c99
endif

ifeq ($(CREATE_ASM),YES)
		ASM_FLAGS= -S
endif
ifeq ($(UNITTESTING),YES)
		STUB=_stub
		UNITTEST= -DUNITTEST
endif

#IGNORE_PATH=unused
# -std=c99
#CFLAGS= -Os -Wall -Wextra -pedantic
#CFLAGS= -g -pg -O0 -Wall -Wextra -rdynamic
# -pedantic -rdynamic
#CFLAGS= -std=c99 -O2 -Wall
#-DNDEBUG
#CFLAGS= -O3 -Wall -Wextra -pedantic -DNDEBUG
#-std=c++99

#CFLAGS +=$(CARCH)

OPT_LVL_FAST_RELEASE= -O3
OPT_LVL_SIZE_RELEASE= -Os
OPT_LVL_FAST_DEBUG= -O0
OPT_LVL_SIZE_DEBUG= -O0

THREAD_FLAGS= -pthread
DEBUG_FLAGS= -g -rdynamic
NO_DEBUG_FLAGS = -DNDEBUG 
#-rdynamic
POSIX_FLAGS= -D_POSIX_C_SOURCE=200809L

CFLAGS+=$(THREAD_FLAGS)
CFLAGS+=$(POSIX_FLAGS)
CFLAGS+=$(ASM_FLAGS)
CFLAGS+=$(WARNINGS)
#CFLAGS
#CFLAGS+=$(CSTD)

#DIRS=src
#VPATH=$(DIRS)

.PHONY: clean release debug

MODULES    := src/raytracer.o src/debug.o src/image.o src/image_io.o src/array.o src/test.o src/octree_mem.o src/octree_io.o src/thread_pool.o

#release :	OUTDIR=../build/release/
release :	OPT_LVL_FAST= $(OPT_LVL_FAST_RELEASE)
release :	OPT_LVL_SIZE= $(OPT_LVL_SIZE_RELEASE)
release :	CFLAGS+= $(NO_DEBUG_FLAGS)
release :	all

#debug :		OUTDIR=../build/debug
debug :		OPT_LVL_FAST= $(OPT_LVL_FAST_DEBUG)
debug :		OPT_LVL_SIZE= $(OPT_LVL_SIZE_DEBUG)
debug :		CFLAGS+= $(DEBUG_FLAGS)
debug :		all

#all : MODULE_FILES=$(addsuffix(.o, $(MODULES)))
all : MODULE_FILES:=$(MODULES)
all : c_test

#define make-goal
#$1/%.o: %.c
#	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@
#endef

SOURCE_DIR=src
#BUILD_DIR=build
#BIN_DIR=build/release

#BIN_FILES=$(BIN_DIR)\c_test

vpath src/

#MODULES := $(addprefix src/, $(MODULES))

#echo $(MODULES)

/src/raytracer.o : raytracer.c raytracer.h octree.c octree.h octree_node.c octree_node.h raytracer_ray_trav.c raytracer_ray_trav.h
#echo "RULE: raytracer.o : raytracer.c raytracer.h octree.c octree.h octree_node.c octree_node.h raytracer_ray_trav.c raytracer_ray_trav.h"
#echo "$(CC) $(CFLAGS) $(OPT_LVL_FAST) $(CSTD) $(ASM) -c $< -o raytracer$(APPENDIX).o"
#$@_$(APPENDIX).o"
	raytacer
	exit 1
	$(CC) $(CFLAGS) $(OPT_LVL_FAST) $(CSTD) $(ASM) -c $< -o raytracer.o
#$@_$(APPENDIX).o

#all : $(MODULES) c_test
all : 	c_test
full : 	c_test lint


#$(CC) $(CFLAGS) -lrt -lm -o c_test debug.o image.o image_io.o array.o raytracer.o test.c


#c_test : test.o debug.o array.o image.o image_io.o raytracer.o
c_test : $(MODULES)
#build/obj/release/test : $(OBJ)
	@echo c_test
	$(CC) $(CFLAGS) -lrt -lm src/*.o -o c_test

#test.o : debug.o array.o image.o image_io.o raytracer.o test.c
#	echo blah
#	$(CC) $(CFLAGS) $(CSTD) -c test.c

raytracer.o : raytracer.c raytracer.h octree.c octree.h octree_node.c octree_node.h raytracer_ray_trav.c raytracer_ray_trav.h


%.o : %.c %.h
#echo 1 "%.o : %.c %.h"
#echo 2 "$<" "$@" "$1"
#$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@
	$(CC) $(CFLAGS) $(CSTD) -c $< -o $@

#%.o : %.c
#echo 3 "%.o : %.c"
#$(CC) $(CFLAGS) -c $(<) -o $(BUILD_DIR)/$(@)
#	$(CC) $(CFLAGS) -c $(<) -o $(@)

clean:
		for i in *.o *.h.gch *.gcda *.gcno *.c.gcov *~ *.orig; do find -name $$i -exec rm -v {} \;; done
		rm -f $(BIN_FILES)
		rm -f c_test
		rm -f gmon.out
		rm -f *.plist
		(cd build/lint && rm -rfv *)

install:
		mkdir -p /usr/include/platform
		rm -fv /usr/include/platform/*
		cp -v src/*.h /usr/include/platform

lint_cppcheck:
		cppcheck -f --enable=all -q src/*.[hc]
lint_clang:
		clang --analyze src/*.c
lint_flint:
		flint -i /usr/local/etc/flint -i /usr/include co-gcc.lnt src/*.c

lint_module_compile:
#(cd src && for i in *.h; do clang -c -Weverything -Wno-unused-macros -Wno-padded $i; done)
#(cd src && for i in *.c; do clang -c -Weverything -Wno-unused-macros -Wno-padded $i; done)
#(cd src && for i in *.h; do clang -c -Weverything -Wno-unused-macros -Wno-padded $i; done)
#chdir src
		@echo == lint_module_compile ==
		@echo compiler:      $(CC)
		@echo warning flags: $(WARNING)
		for i in src/*.h; do $(CC) -c $(WARNING) $$i -o build/lint/$$i; done
		for i in src/*.c; do $(CC) -c $(WARNING) $$i -o build/lint/$$i; done

lint:		lint_cppcheck lint_clang lint_flint lint_module_compile

leak_check:	
		valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./c_test

indent_c :
		@ if [ -f last_indent_c.time ]; then                   \
			TIMESTR=-newer last_indent_c.time;             \
		fi;                                                    \
		for i in $$(find -name "*.[ch]" $$TIMESTR); do         \
			echo $$i;                                      \
			astyle -A10 -s 
		done;                                                  \
		touch last_indent_c.time

full: lint leak_check

#$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$($bdir))))
