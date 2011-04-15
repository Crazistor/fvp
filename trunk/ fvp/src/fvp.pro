TEMPLATE = app

TARGET = ./release/fvp

UI_DIR+=./gui/form
RCC_DIR+=./gui/qrc
MOC_DIR+=./gui/moc
subdirs = . 
HEADERS     = ./gui/configdialog.h \
              ./gui/pages.h		\
	          ./gui/setuppage.h \
			  ./gui/fvp_gui.h \
			  ./fvp_globals.h 

SOURCES     = ./gui/configdialog.cpp \
              ./gui/pages.cpp		\
	      ./gui/setuppage.cpp \
	      ./gui/fvp_gui.cpp\
	      ./fvp_globals.c \
               main.cpp 

INCLUDEPATH  =./gui \
			./cores \ 
			./common 

#########msic###########
HEADERS += ./misc/fvp_screen.h\
	   ./misc/fvp_function.h \
	   ./misc/array_list.h  \
	   ./misc/fvp_settings.h \
	   ./misc/ini_parser.h \
	   ./misc/ini_builder.h \
	   ./misc/fvp_mmap.h  \
	   ./misc/fvp_mutex.h \
	   ./misc/block.h \
	   ./misc/fvp_msg.h


SOURCES += ./misc/fvp_screen.c \
		./misc/fvp_function.c \
	   ./misc/array_list.c \
		./misc/fvp_settings.c \
	   ./misc/ini_parser.c \
	   ./misc/ini_builder.c \
	   ./misc/fvp_mmap.c \
	   ./misc/fvp_mutex.c\
	   ./misc/block.c \
	   ./misc/fvp_msg.c

INCLUDEPATH +=./misc

#########gui###############
HEADERS += ./gui/searchdevicepage.h\
			./gui/searchdialog.h 

SOURCES += ./gui/searchdevicepage.cpp \
			./gui/searchdialog.cpp

FORMS	= ./gui/ui/searchdevice.ui

############controller#####
HEADERS += ./controller/controller.h

SOURCES += ./controller/controller.cpp

INCLUDEPATH +=./controller 

###########COMMON##########
HEADERS += ./common/fvp_common.h \
	   ./common/fvp_config.h \
       ./common/parameter_define.h

##########framebuffer#######
HEADERS += ./fb/framebuffer.h\
			./fb/hifb.h
SOURCES += ./fb/framebuffer.c

INCLUDEPATH +=./fb
######search_device_client###
HEADERS += ./search_device/search_device_client.h \
		   ./search_device/search_device_data.h

SOURCES += ./search_device/search_device_client.c 

INCLUDEPATH +=./search_device

###############media##########
HEADERS += ./media/access/access.h \
			./media/access/access_file.h \
			./media/input/demuxer.h \
			./media/decoder/decoder.h \
			./media/media_player.h


SOURCES += ./media/access/access_file.c  \	
			./media/input/demuxer.c \
			./media/decoder/decoder.c \
			./media/media_player.c 

INCLUDEPATH +=./media/access/ \
				./media/decoder \
				./media/input \
				./media 

LIBS=./cores/libcores.a

RESOURCES   += ./gui/configdialog.qrc

INCLUDEPATH  +=./gui \
			./controller \
			./cores \ 
			../mpp/include \
			./common 

CONFIG += qt warn_on -O2 release

OBJECTS_DIR += ./objs


	
