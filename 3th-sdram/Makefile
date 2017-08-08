all : start.o main.o init.o uart.o
	arm-linux-ld -Ttext 0x30000000 -o sdram.elf $^
	arm-linux-objcopy -O binary sdram.elf sdram.bin
	arm-linux-objdump -D -S -h -m arm sdram.elf >sdram.dis

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

