objs := start.o main.o init.o uart.o

uart.bin : uart.elf
	arm-linux-objcopy -O binary uart.elf uart.bin
	
uart.elf : $(objs)
	arm-linux-ld -Ttext 0 -o uart.elf $^

uart.dis : uart.elf	
	arm-linux-objdump -D -S -h -m arm uart.elf >uart.dis

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

