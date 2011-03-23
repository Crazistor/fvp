SOURCE = fvp_settings_test.c ../fvp_settings.c ../fvp_mmap.c ../ini_parser.c

all:
	gcc -o settings_test $(SOURCE) -I../ -I../../common 
	@./settings_test 
clean:
	rm -f fb_test
