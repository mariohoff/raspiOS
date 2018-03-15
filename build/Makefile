
TOOLCHAIN = arm-none-eabi
CC = $(TOOLCHAIN)-gcc
OBJCOPY = $(TOOLCHAIN)-objcopy
GDB = $(TOOLCHAIN)-gdb

#raspi model 1
CPU = arm1176jzf-s
#raspi model2
#CPU = cortex-a7

CFLAGS= -mcpu=$(CPU) -fpic -ffreestanding -g
CSRCFLAGS= -O2 -Wall -Wextra
LFLAGS= -L../libs -lcsud -ffreestanding -O2 -nostdlib

LINKER = linker.ld
KER_SRC = ../src/kernel
HEAD = ../include
COMMON_SRC = ../src/common
OBJ_DIR = objects
SOURCES = $(wildcard $(KER_SRC)/*.c)
COMMONSOURCES = $(wildcard $(COMMON_SRC)/*.c)
#SOURCES += $(wildcard $(KER_SRC)/$(ARCHDIR)/*.c)
ASMSOURCES = $(wildcard $(KER_SRC)/*.S)
OBJECTS = $(patsubst $(KER_SRC)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
OBJECTS += $(patsubst $(COMMON_SRC)/%.c, $(OBJ_DIR)/%.o, $(COMMONSOURCES))
OBJECTS += $(patsubst $(KER_SRC)%.S, $(OBJ_DIR)/%.o, $(ASMSOURCES))
HEADERS = $(wildcard $(HEAD)/*.h)

IMG_NAME=kernel

build: $(OBJECTS) $(HEADERS)
	$(CC) -T $(LINKER) -o $(IMG_NAME).elf $(OBJECTS) $(LFLAGS)
	$(OBJCOPY) $(IMG_NAME).elf -O binary $(IMG_NAME).img

$(OBJ_DIR)/%.o: $(KER_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(HEAD) -c $< -o $@ $(CSRCFLAGS)

$(OBJ_DIR)/%.o: $(KER_SRC)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -c $< -o $@

$(OBJ_DIR)/%.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(HEAD) -c $< -o $@ $(CSRCFLAGS)

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
