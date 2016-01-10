# This Makefile is for Linux. It needs a little tweaking (e.g. for port settings) on Windows.
# If using something other than an arduino nano board, do not forget to setup programmer type and cpu type below.

# project name, also name of main file (ending omitted):
NAME=example1

# names of additional C files:
MORE=ws2812b

# name of settings file:
SETTINGS=ws2812b_config.h

# additional files, changings of which are of importance to the compiler
NOTICE=$(SETTINGS) Makefile

# choose CPU, e.g. attiny13, attiny2313, atmega8, atmega8515:
CPU=atmega328p
# Choose clock frequency:
#F_CPU=128000UL
F_CPU=16000000UL

# choose preferred editor:
EDITOR=joe
#EDITOR=nano
#EDITOR=gedit
#EDITOR=geany
#EDITOR=leafpad
#EDITOR=emacs
#EDITOR=vim

# choose programming interface (type, e.g bsd, stk200, usbasp, usbtiny, and port, e.g. USB, /dev/parport0, /dev/ttyS0):
## Arduino via USB:
PROGRAMMER=arduino
PORT=/dev/ttyUSB0 -b 57600 -D
#
## USBTINY:
#PROGRAMMER=usbtiny
#PORT=usb -B 3
#PORT=usb -B 32
#
## AVR-DRAGON, different variants:
#PORT=usb -B 1 -u
#PROGRAMMER=dragon-dw
#PORT=usb ...
#PROGRAMMER=dragon-jtag ...
#PORT=usb -B 10
#PROGRAMMER=dragon-isp
#
## if using avrusboot, uncomment below instead (-> prog target)

# if needed, choose fuse settings (examples given indicate standard values for some chips):
#
##atmega8/48/88/168:
#HFUSE=0xFF
#LFUSE=0x3A
#
##atmega8515
#HFUSE=0xD9
#LFUSE=0xE1
#
##atmega162:
#HFUSE=0xD1
#LFUSE=0xE2
#EFUSE=0xFF
#
##attiny13:
#HFUSE=0xFF
#1.2MHz:
#LFUSE=0x6A
#9.6MHz:
#LFUSE=0x7A
#
##attiny2313:
#HFUSE=99
#LFUSE=E2
#EFUSE=FF
#
##atmega16/32
#with JTAG (default):
#HFUSE=0x99
#without JTAG (!):
#HFUSE=0xD9
#LFUSE=0xE1
#
##atmega644P:
#HFUSE=0x99
#LFUSE=0x62
#EFUSE=0xFF

### end of user configuration ###

# more standard settings:
REAL_PREFIX=
#REAL_PREFIX=alt
REAL_CFLAGS=-g -mmcu=$(CPU) -DF_CPU=$(F_CPU) $(PAUSENMETHOD) $(INT0VECTSIMULATE) -Os -mcall-prologues -I/usr/local/avr/include/avr -I/usr/local/avr/avrlib -I/.
REAL_LDFLAGS=-Wl,-Map,$(NAME).map,--section-start=.text=$(LADEORT)

# corresponding files:
SRCREAL=$(NAME).c $(REAL:%=%.c) $(MORE:%=%.c)
OBJREAL=$(SRCREAL:%.c=%.o_real)
NOTICE+=$(MORE:%=%.h) $(REAL:%=%.h) Makefile

# make targets:
all: avr
avr:	$(NAME).bin

$(NAME).bin	:	$(OBJREAL) $(NOTICE)
	$(REAL_PREFIX)avr-gcc $(REAL_CFLAGS) -o $(NAME).bin $(OBJREAL)
$(NAME).hex : $(NAME).bin $(NOTICE)
	rm -f $(NAME).hex $(NAME).eep.hex
	$(REAL_PREFIX)avr-objcopy -R .eeprom -O ihex $(NAME).bin $(NAME).hex
%.o_real : %.c $(NOTICE)
	rm -f $@
	$(REAL_PREFIX)avr-gcc $(REAL_CFLAGS) -c $< -o $@ || echo "Compiler error" > /dev/stderr

prog: $(NAME).hex
	avrdude -p $(CPU) -c $(PROGRAMMER) -P $(PORT) -V -U flash:w:$(NAME).hex:i
	# uncomment below and comment above in order to use avrusbboot:
	#sudo $(HOME)/batch/avrusbboot $(NAME).hex

fuse:
	# (please uncomment FUSE settings above)
ifdef EFUSE
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(CPU) -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m -U efuse:w:$(EFUSE):m
else
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(CPU) -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m
endif

disasm:	$(NAME).bin
	$(REAL_PREFIX)avr-objdump -d $(NAME).bin

size: $(NAME).bin
	$(REAL_PREFIX)avr-size -d $(NAME).bin

clean:
	rm -f $(OBJREAL) *.out D???JOE *~ *.map *.hex *.lst *.bin *.o *.o_real _*.c *.bak

reset:
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(CPU)

edit:
	$(EDITOR) -nosta +2 $(NAME).c

editall:
	$(EDITOR) *.c *.h

config:
	$(EDITOR) -nosta +22 $(SETTINGS)

make:
	$(EDITOR) +18 Makefile

.SILENT:
.PHONY: all clean edit editall make prog avr fuse disasm size reset config
