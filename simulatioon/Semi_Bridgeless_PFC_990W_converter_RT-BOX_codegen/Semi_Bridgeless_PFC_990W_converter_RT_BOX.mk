CROSS            ?= "C:/Users/A50807/Downloads/20250526/Coder Targets/PLECS_RT_Box/bin/win/aarch64-none-elf/bin/aarch64-none-elf-"
CFLAGS           := -Wall -O3 -g  -c -fmessage-length=0 -DEXTERNAL_MODE=1 \
   -fgcse-after-reload \
   -finline-functions \
   -fipa-cp-clone \
   -floop-interchange \
   -floop-unroll-and-jam \
   -fpeel-loops \
   -fpredictive-commoning \
   -fsplit-paths \
   -ftree-loop-distribute-patterns \
   -ftree-loop-distribution \
   -ftree-loop-vectorize \
   -ftree-partial-pre \
   -ftree-slp-vectorize \
   -funswitch-loops \
   -fvect-cost-model \
   -ffast-math \
   -mtune=cortex-a53 -march=armv8-a -mcpu=cortex-a53 \
   -Wno-unused-variable \
   -funsafe-math-optimizations -fopt-info-vec --param max-completely-peeled-insns=1000 --param max-completely-peel-times=100
CC               = $(CROSS)gcc
LD               = $(CROSS)ld
STRIP            = $(CROSS)strip
OBJCOPY          = $(CROSS)objcopy
INCLUDE          := -I"C:/Users/A50807/Downloads/20250526/Coder Targets/PLECS_RT_Box/include/rtbox2"
LDFLAGS          := -T "C:/Users/A50807/Downloads/20250526/Coder Targets/PLECS_RT_Box/build/rtbox2.lds"        
LIBS             := "C:/Users/A50807/Downloads/20250526/Coder Targets/PLECS_RT_Box/lib/rtbox2/librtbox2.a" -L"C:/Users/A50807/Downloads/20250526/Coder Targets/PLECS_RT_Box/lib/rtbox2/Xilinx" -lrpumsg_a53 -lmetal -lxil \
   -L"C:/Users/A50807/Downloads/20250526/Coder Targets/PLECS_RT_Box/bin/win/aarch64-none-elf/bin/../aarch64-none-elf/lib" \
   -L"C:/Users/A50807/Downloads/20250526/Coder Targets/PLECS_RT_Box/bin/win/aarch64-none-elf/bin/../lib/gcc/aarch64-none-elf/8.3.0" \
   -lm -lm --start-group -lc -lgcc -lnosys --end-group

undefine GCC_EXEC_PREFIX

ifeq ($(OS),Windows_NT)
 SHELL            := cmd.exe
 RM               := DEL /F
 CP               := COPY /Y
else
 RM               := rm -f
 CP               := cp
endif

APP = Semi_Bridgeless_PFC_990W_converter_RT_BOX_linked.elf
BIN = Semi_Bridgeless_PFC_990W_converter_RT_BOX.elf

HEADERS += Semi_Bridgeless_PFC_990W_converter_RT_BOX.h
C_SRCFILES += Semi_Bridgeless_PFC_990W_converter_RT_BOX_main.c Semi_Bridgeless_PFC_990W_converter_RT_BOX.c

OBJFILES := $(patsubst %.c, %.o, $(C_SRCFILES))
DEPFILES := $(patsubst %.c, %.d, $(C_SRCFILES))

all: $(BIN)

$(APP): $(OBJFILES)
	@echo Linking $@
	@$(LD) -o $@ $(OBJFILES) $(LIBS) $(LDFLAGS) 

$(BIN): $(APP)
	@echo Creating $@
	@$(OBJCOPY) -O binary $< $@

%.o:%.c $(HEADERS)
	@echo Compiling $(<:.c=.o)
	@$(CC) $(CFLAGS) $(ARCH_CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-$(RM) $(LIB) $(OBJFILES)

FORCE:

PHONY: all clean
