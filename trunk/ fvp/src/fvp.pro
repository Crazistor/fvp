TEMPLATE = app

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
			../mpp/include \
			./common 

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
	   ./common/fvp_function.h \
	   ./common/array_list.h \
       ./common/parameter_define.h

SOURCES += ./common/fvp_function.c \
	   ./common/array_list.c



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


LIBS=./cores/libcores.a\
	 ../mpp/lib/lib_aacdec.a \
	 ../mpp/lib/lib_aacenc.a \
	 ../mpp/lib/lib_aec.a \
	 ../mpp/lib/lib_amr_fipop.a \
	 ../mpp/lib/lib_amr_spc.a \
	 ../mpp/lib/lib_VoiceEngine.a \
	 ../mpp/lib/libloadbmp.a \
	 ../mpp/lib/libmpi.a \
	 ../mpp/lib/libresampler.a \
	 ../mpp/lib/libtde.a


RESOURCES   += ./gui/configdialog.qrc

INCLUDEPATH  +=./gui \
			./controller \
			./cores \ 
			../mpp/include \
			./common 

CONFIG += qt warn_on -O2 release

OBJECTS_DIR += ./objs



target.path = $$[QT_INSTALL_DEMOS]/books
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro images
sources.path = $$[QT_INSTALL_DEMOS]/books
INSTALLS += target sources

	
