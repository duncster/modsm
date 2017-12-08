CC		:= gcc
LD		:= gcc
CCFLG	:=
LDFLG	:=

all:  modsm

modsm:  modsm.o
	$(LD) $(LDFLG) $< -o $@

modsm.o: modsm.c
	$(CC) $(CCFLG) -c $^ -o $@

clean:
	rm -f modsm
	rm -f modsm.o
	rm -f core*
