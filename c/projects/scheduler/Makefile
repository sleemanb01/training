
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = scheduler.c test_scheduler.c

# list of directories containing header files
PROJ_INC_DIR = ../include ../priority_queue ../uid ../sorted_list ../dlist

# the executable file
PROJ_OUT = scheduler.out

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = priority_queue.o uid.o sorted_list.o dlist.o 

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../uid/Makefile ../priority_queue/Makefile  

include $(ROOT_DIR)/make/Project.mak
