########################################################################################################
#COMPILATION SCRIPT Using arm-gcc, CodeSourcery G++ Lite Toolchain
#AUTHOR : Kannan P
#E-Mail: kannanetech@gmail.com
#TARGET: Cortex-M3, LPC1768
########################################################################################################
HOM=$(shell echo $(HOME))
DIR= $(HOM)/LPC1768_blueboard
LD_SCRIPT = $(DIR)/link.ld
CPU_TYPE = cortex-m3
TARGET = LPC17xx
OPTDEFINES = -D __NEWLIB__

INC_DIRS=$(DIR)/includes
INC_DIRS+=$(DIR)

INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

OBJ= $(DIR)/objs/startup_LPC17xx.o
OBJ+= $(DIR)/objs/core_cm3.o
OBJ+= $(DIR)/objs/system_LPC17xx.o


LIB_DIRS=$(DIR)

CFLAGS  = -mcpu=$(CPU_TYPE) -mthumb -g -Wall -O0 -c  $(INC_DIRS_F)
#CXXFLAGS= -c -Os $(INC_DIRS_F) -fno-common -fmessage-length=0 -Wall -fno-exceptions -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections
LDFLAGS = -mcpu=cortex-m3 -mthumb -g2 -nostartfiles -Wl,-Map=memory.map -O0 -Wl,--gc-sections -L $(DIR) -Wl,-T $(LD_SCRIPT)
LDFLAGS += --specs=rdimon.specs -lc -lrdimon
OCFLAGS = --strip-unneeded
LDLIBS  = -lgcc -lc -lm 
OBJS=main.o 
#-L $(LIB_DIRS) $(LDLIBS) 

##########################################################################
# GNU GCC compiler prefix and location
##########################################################################

CROSS_COMPILE = arm-none-eabi-
GC = $(CROSS_COMPILE)gcc
GCP = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)gcc
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
OUTFILE = firmware
##########################################################################


all: firmware

%.o : %.c
	@echo Building $@
	$(GC) $(CFLAGS) -o $@ $<

firmware: $(OBJS)
	@echo Linking $(OUTFILE).o for $(OUTFILE).elf
	$(LD) $(LDFLAGS) $(LDLIBS)  -g -o $(OUTFILE).elf $(OBJ) $(OBJS)
	$(SIZE) $(OUTFILE).elf
	-@echo ""
	$(OBJCOPY) -O binary $(OUTFILE).elf $(OUTFILE).bin
	$(OBJCOPY) -O ihex $(OUTFILE).elf $(OUTFILE).hex
	-@echo ""
	-@echo Firmware Built Successfully!!!
	-@echo ""
clean:
	rm -f main.o $(OUTFILE).elf $(OUTFILE).bin memory.map $(OUTFILE).hex
	-@echo ""
	@echo Cleared all Binaries and Objects!!!
