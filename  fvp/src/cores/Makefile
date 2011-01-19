
CROSS_COMPILE=arm-hismall-linux-
GCC:=$(CROSS_COMPILE)gcc
GXX:=$(CROSS_COMPILE)g++
AR:=$(CROSS_COMPILE)ar

LIB_NAME:=./libcores.a

INCLUDE_DIR+=-I../common

SRC = cores.c \
      parameter.c  \
      cores.h \
      parameter.h 

OBJ := $(SRC:.c=.o)

CFLAGS+=$(INCLUDE_DIR)

all:$(LIB_NAME)
$(LIB_NAME):$(OBJ)
	$(AR) -r $(LIB_NAME) $(OBJ)
	@echo "ok"
	@rm -f *.bak *.o
	@cd test;make clean;make;
%.o:%.c
	$(GCC) $(CFLAGS) -Wall -g -o $@ -c $<

clean:
	rm -f $(LIB_NAME)
	rm -f *.o 
