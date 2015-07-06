
TARGET		:= SNAKE
SOURCES		:= src
INCLUDES	:= src

CFILES   	:= $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CXXFILES    := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
OBJS     	:= $(CFILES:.c=.o) $(BUILD_APP) $(CXXFILES:.cpp=.o)

LIBS = -lc_stub -lstdc++_stub -lSceKernel_stub -lSceDisplay_stub -lSceGxm_stub 	\
	-lSceCtrl_stub -lSceTouch_stub

DEFINES	=	-DPSP -DLSB_FIRST -DWANT_CRC32

PREFIX   = arm-none-eabi
AS		 = $(PREFIX)-as
CC       = $(PREFIX)-gcc
CXX		 = $(PREFIX)-g++
READELF  = $(PREFIX)-readelf
OBJDUMP  = $(PREFIX)-objdump
CFLAGS   = -Wall -specs=$(PSP2SDK)/psp2.specs -I$(DATA)  $(DEFINES)
CXXFLAGS = $(CFLAGS) -O2 -mword-relocations  -fomit-frame-pointer -fno-unwind-tables -fno-rtti -Wno-deprecated -Wno-comment -Wno-sequence-point -std=c++11
ASFLAGS  = $(CFLAGS)



all: $(TARGET).velf

$(TARGET).velf: $(TARGET).elf
	psp2-fixup -q -S $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).elf $(TARGET).velf $(OBJS) $(DATA)/*.h

copy: $(TARGET).velf
	@cp $(TARGET).velf ~/shared/$(TARGET).elf
	
run:
	@C:\Users\Toni\Downloads\rejuvenate-0.2.1-beta\run_homebrew.bat $(TARGET).velf
	
