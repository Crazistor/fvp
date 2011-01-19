subdirs = . 
HEADERS     = ./gui/configdialog.h \
              ./gui/pages.h		\
	          ./gui/setuppage.h \
			  ./controller/controller.h \	
			  ./fvp_globals.h 

SOURCES     = ./gui/configdialog.cpp \
              ./gui/pages.cpp		\
	      	  ./gui/setuppage.cpp \
			   ./controller/controller.c\
			  ./fvp_globals.c \
               main.cpp 

###########COMMON##########
HEADERS += ./common/fvp_common.h \
	   ./common/fvp_config.h \
           ./common/parameter_define.h



LIBS=./cores/libcores.a

RESOURCES   += ./gui/configdialog.qrc

INCLUDEPATH  =./gui \
			./controller \
			./cores \ 
			./common
