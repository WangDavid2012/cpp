

DEBUG = 1

ifeq ($(DEBUG),1)
	DEBFLAGS = -g  -Wuninitialized -O0 -D__DEBUG 
else
	DEBFLAGS = -s -O2
endif

CC = g++
LIBNAME = libSDF.a

INC = -I./app -I./net -I./common 
CFLAGS = -DLINUX -D_UNIX $(DEBFLAGS) $(INC) -std=c++11 -fPIC


# LDFLAGS = -L../lib
LIBS = -lm -lpthread 
# BIN = server

DIR = ./app ./net ./common

# DIR := $(shell find . -maxdepth 3 -type d)
#将DIR中的值取出来（空格区分），赋值给dir，然后执行$(wildcard $(dir)/*.cpp)
CPP_SRCS = $(foreach dir,$(DIR),$(wildcard $(dir)/*.cpp))
C_SRCS = $(foreach dir,$(DIR),$(wildcard $(dir)/*.c))


C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))
CPP_OBJS = $(patsubst %.cpp,%.o,$(CPP_SRCS))

SRCS = $(C_SRCS) $(CPP_SRCS)
OBJS = $(C_OBJS) $(CPP_OBJS)



.PHONY: all clean  install test

%.o:%.c
	gcc -c $< -o $@ $(CFLAGS)  $(LIBS)
%.o:%.cpp
	g++ -c $< -o $@ $(CFLAGS)  $(LIBS)

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	ar crv $@ $(OBJS)
	ranlib $@
	$(CC) -s -o libSDF.so -lpthread  -shared $(OBJS)
	@echo "*********************************************"
	@echo "*  The LIB file is: $(LIBNAME)!!"
	@echo "*********************************************"



clean:
	@-rm $(BIN) -f
	@find  -name "*.o"  | xargs rm -rf

test:
	@echo "***************  printf info begin********************"
	@echo "CC" = $(CC) 
	@echo "BIN" = $(BIN) 
	@echo "OBJS" = $(OBJS) 
	@echo "LDFLAGS" = $(LDFLAGS) 
	@echo "CFLAGS" = $(CFLAGS) 
	@echo "LIBS" = $(LIBS) 	
	@echo " if use libevent,add macro USELIBEVENTG !"
	@echo "***************  printf info end ********************"





