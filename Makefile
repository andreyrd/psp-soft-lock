TARGET = lock
OBJS = main.o

BUILD_PRX = 1

INCDIR =
LIBDIR =
LIBS = 

LDFLAGS =
CFLAGS = -Os -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti 
ASFLAGS = $(CFLAGS)

PSPSDK	= $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak