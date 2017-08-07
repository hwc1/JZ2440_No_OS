objs := start.o main.o

led.bin : led.elf
	arm-linux-objcopy -O binary led.elf led.bin
	
led.elf : $(objs)
	arm-linux-ld -Ttext 0 -o led.elf $^

led.dis : led.elf	
	arm-linux-objdump -D -S -h -m arm led.elf >led.dis

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

