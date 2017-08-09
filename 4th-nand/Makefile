all : start.o main.o init.o uart.o nand.o
	arm-linux-ld -Ttext 0x30000000 -o nand.elf $^
	arm-linux-objcopy -O binary nand.elf nand.bin
	arm-linux-objdump -D -S -h -m arm nand.elf >nand.dis

%.o : %.S
	arm-linux-gcc -g -c $^
	
%.o : %.s
	arm-linux-gcc -g -c $^
	
%.o : %.c
	arm-linux-gcc -g -c $^

.PHONY: clean
clean:
	rm -rf *.o *.elf *.dis *.bin

install:
	cp *.bin  /tftpboot

