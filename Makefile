PROG_NAME = Control
BUILD_DIR = $(CURDIR)/Build
OBJ_DIR= $(CURDIR)/Obj

DEPS = ControllerTesting.h
_OBJ = Program.o ControllerTesting.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

ROOTDIR = $(N64_INST)
GCCN64PREFIX = $(ROOTDIR)/bin/mips64-elf-

CC = $(GCCN64PREFIX)gcc
AS = $(GCCN64PREFIX)as
LD = $(GCCN64PREFIX)ld
OBJCOPY = $(GCCN64PREFIX)objcopy
N64TOOL = $(ROOTDIR)/bin/n64tool
CHKSUM64 = $(ROOTDIR)/bin/chksum64

ASFLAGS = -mtune=vr4300 -march=vr4300
CFLAGS = -std=gnu99 -march=vr4300 -mtune=vr4300 -O2 -Wall -Werror -I$(ROOTDIR)/mips64-elf/include
LDFLAGS = -L$(ROOTDIR)/mips64-elf/lib -ldragon -lc -lm -ldragonsys -Tn64.ld --gc-sections
N64TOOLFLAGS = -l 1M -h $(ROOTDIR)/mips64-elf/lib/header -t "Controller Test"

ifeq ($(N64_BYTE_SWAP),true)
$(PROG_NAME).v64: $(PROG_NAME).z64
	dd conv=swab if=$^ of=$@
endif

$(PROG_NAME).z64: $(PROG_NAME).bin
	$(N64TOOL) $(N64TOOLFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/$^
	$(CHKSUM64) $(BUILD_DIR)/$@

$(PROG_NAME).bin: $(PROG_NAME).elf
	$(OBJCOPY) $(BUILD_DIR)/$< $(BUILD_DIR)/$@ -O binary

$(PROG_NAME).elf: $(OBJ)
	$(LD) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(DEPS) MakeDirs
	$(CC) -c -o $@ $< $(CFLAGS)

MakeDirs:
	mkdir -p $(BUILD_DIR) $(OBJ_DIR)

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.v64 $(BUILD_DIR)/*.z64 $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.elf $(OBJ_DIR)/*.o

cp:
	cp $(BUILD_DIR)/$(PROG_NAME).z64 /media/sf_Shared/
