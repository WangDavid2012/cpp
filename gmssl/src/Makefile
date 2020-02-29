DEBUG = 1

ifeq ($(DEBUG),1)
	DEBFLAGS = -g  -Wuninitialized -O0
else
	DEBFLAGS = -s -O2
endif

CC = g++

INC = -I../gmssl_lib_linux64/include
CFLAGS = $(DEBFLAGS) $(INC) -fPIC -std=c++11 
#如果在程序中开启 LINUX 这个宏定义的话
#CFLAGS += -DLINUX


#使用到的库文件的路径
LDFLAGS = -L../gmssl_lib_linux64/lib

#使用到的库文件
LIBS = -lm -lpthread -lcrypto


#生成的库文件
BIN = gmssltest

DIR := $(shell find . -maxdepth 3 -type d)
#将DIR中的值取出来（空格区分），赋值给dir，然后执行$(wildcard $(dir)/*.cpp)
CPP_SRCS = $(foreach dir,$(DIR),$(wildcard $(dir)/*.cpp))
C_SRCS = $(foreach dir,$(DIR),$(wildcard $(dir)/*.c))

C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))
CPP_OBJS = $(patsubst %.cpp,%.o,$(CPP_SRCS))

SRCS = $(C_SRCS) $(CPP_SRCS)
OBJS = $(C_OBJS) $(CPP_OBJS)


.PHONY: all clean test

%.o:%.c
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)
%.o:%.cpp
	g++ -c $< -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)


all:$(BIN)
$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS) 
clean:
	find . -name "*.o"  | xargs rm -f

test:
	@echo "***************  printf info begin********************"
	@echo "CC" = $(CC) 
	@echo "BIN" = $(BIN) 
	@echo "INC" = $(INC)
	@echo "OBJS" = $(OBJS) 
	@echo "LDFLAGS" = $(LDFLAGS) 
	@echo "CFLAGS" = $(CFLAGS) 
	@echo "LIBS" = $(LIBS) 	
	@echo " if use libevent,add macro USELIBEVENTG !"
	@echo "***************  printf info end ********************"





