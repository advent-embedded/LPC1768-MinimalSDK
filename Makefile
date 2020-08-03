########################################################################################################
#COMPILATION SCRIPT Using arm-gcc, CodeSourcery G++ Lite Toolchain
#AUTHOR : Kannan P
#E-Mail: kannanetech@gmail.com
#TARGET: Cortex-M3, LPC1768
########################################################################################################
HOM=$(shell echo $(HOME))
WD= $(shell echo $(PWD))
DIR= $(HOM)/LPC1768-MinimalSDK
LD_SCRIPT = $(DIR)/link.ld
CPU_TYPE = cortex-m3
TARGET = LPC17xx
OPTDEFINES = -D __NEWLIB__

INC_DIRS=$(DIR)/includes

INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

#SDK Specific Source Files
SRC= $(DIR)/src/startup_LPC17xx.c
SRC += $(DIR)/src/core_cm3.c
SRC += $(DIR)/src/system_LPC17xx.c
#Application Specific Source Files are overridden in local directory Makefile


OBJS =$(addprefix $(WD)/build/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
AOBJS =$(addprefix $(WD)/build/, $(addsuffix .o, $(notdir $(basename $(ASRC)))))
CFLAGS  = -mcpu=$(CPU_TYPE) -mthumb -g -Wall -O0 -c  $(INC_DIRS_F)
#CXXFLAGS= -c -Os $(INC_DIRS_F) -fno-common -fmessage-length=0 -Wall -fno-exceptions -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections
LDFLAGS = -mcpu=cortex-m3 -mthumb -g2 -nostartfiles -Wl,-Map=$(WD)/build/memory.map -O0 -Wl,--gc-sections -L $(DIR) -Wl,-T $(LD_SCRIPT)
LDFLAGS += --specs=rdimon.specs -lc -lrdimon
OCFLAGS = --strip-unneeded
LDLIBS  = -lgcc -lc -lm 

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


all: dir firmware

dir:	
	@if test ! -d  $(WD)/build; \
	then mkdir  $(WD)/build; \
	fi; \

%.o : %.c
	@echo Building $@
	$(GC) $(CFLAGS) -o $@ $<

$(OBJS):$(WD)/build/%.o:$(DIR)/src/%.c
	$(GC) $(CFLAGS) -o $@ $<

$(AOBJS):$(WD)/build/%.o:%.c
	$(GC) $(CFLAGS) -o $@ $<

firmware: $(OBJS) $(AOBJS)
	@echo Linking $(OUTFILE).o for $(OUTFILE).elf
	$(LD) $(LDFLAGS) $(LDLIBS)  -g -o $(WD)/build/$(OUTFILE).elf $(OBJS) $(AOBJS)
	$(SIZE) $(WD)/build/$(OUTFILE).elf
	-@echo ""
	@$(OBJCOPY) -O binary $(WD)/build/$(OUTFILE).elf $(WD)/build/$(OUTFILE).bin
	@$(OBJCOPY) -O ihex $(WD)/build/$(OUTFILE).elf $(WD)/build/$(OUTFILE).hex
	-@echo Firmware Built Successfully!!!
	-@echo ""
clean:
	@rm -rf $(WD)/build
	@echo Cleared all Binaries and Objects!!!
