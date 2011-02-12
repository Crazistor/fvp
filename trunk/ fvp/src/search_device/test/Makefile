CROSS_COMPILE=arm-hismall-linux-
#CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++

COMM_DIR=../../common

SOURCES=search_device_client_test.c \
		../search_device_client.c \
		../array_list.c \
		$(COMM_DIR)/fvp_function.c

INCLUDES=-I../ \
		 -I$(COMM_DIR)/

CFLAGS=-lpthread

all:
	$(CC) -o search_device_test $(SOURCES) $(INCLUDES) $(CFLAGS)
clean:
	rm -f *.o search_device_test


