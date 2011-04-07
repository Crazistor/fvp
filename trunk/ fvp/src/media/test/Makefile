CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc

SOURCE = access_file_test.c ../access/access_file.c 


INCLUDE_PATH =  -I../access -I../../misc -I../../common
all:
		$(CC) -o access_file_test $(SOURCE) $(INCLUDE_PATH)
			@./access_file_test
clean:
		rm -f access_file_test
