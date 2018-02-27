
TOOLCHAIN = arm-none-eabi
CC = $(TOOLCHAIN)-gcc
OBJCOPY = $(TOOLCHAIN)-objcopy
GDB = $(TOOLCHAIN)-gdb

CPU = arm1176jzf-s

CFLAGS= -mcpu=$(CPU) -fpic -ffreestanding $(DIRECTIVES) -g -std=gnu99
CSRCFLAGS= -O2 -Wall -Wextra
LFLAGS= -L../libs -lcsud -static -ffreestanding -O2 -nostdlib

LINKER = linker.ld
SRC = ../src/kernel
HEAD = ../include
COMMON = ../src/common
OBJ_DIR = objects
SOURCES = $(wildcard $(SRC)/*.c)
#SOURCES += $(wildcard $(SRC)/$(ARCHDIR)/*.c)
ASMSOURCES = $(wildcard $(SRC)/*.S)
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
OBJECTS += $(patsubst $(SRC)%.S, $(OBJ_DIR)/%.o, $(ASMSOURCES))
HEADERS = $(wildcard $(HEAD)/*.h)

IMG_NAME=kernel

build: $(OBJECTS) $(HEADERS)
	$(CC) -T $(LINKER) -o $(IMG_NAME).elf $(OBJECTS) $(LFLAGS)
	$(OBJCOPY) $(IMG_NAME).elf -O binary $(IMG_NAME).img

$(OBJ_DIR)/%.o: $(SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LFLAGS) -I$(SRC) -I$(HEAD) -c $< -o $@ $(CSRCFLAGS)

#$(OBJ_DIR)/%.o: $(SRC)/$(ARCHDIR)/%.c
#	mkdir -p $(@D)
#	$(CC) $(CFLAGS) -I$(SRC) -I$(HEAD) -c $< -o $@ $(CSRCFLAGS)

$(OBJ_DIR)/%.o: $(SRC)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm $(IMG_NAME).elf
	rm $(IMG_NAME).img

run: build
	qemu-system-arm -m 128 -no-reboot -M raspi2 -serial stdio -kernel kernel.elf

dbg:
	$(GDB) kernel.elf
dbgrun: build gdbinit
	qemu-system-arm -m 128 -no-reboot -M raspi2 -serial stdio -kernel kernel.elf -S -s

.PHONY: gdbinit
gdbinit:
	echo "target remote localhost:1234" > .gdbinit
	echo "break kernel_main" >> .gdbinit
