SOURCES=mbyte.c mpool.c mcpu.c mreg.c mctx.c mrunl.c msec.c mrt.c msyscalls.c
WIZARD=wiz/wArgParser.c wiz/wFlag.c wiz/wMem.c wiz/wName.c wiz/wOptions.c wiz/wStraggly.c wiz/wValue.c -Iwiz
DEBUG=-O2
WARNS=-Wall

all:
	gcc mtest.c -o mtest $(SOURCES) $(WARNS) $(DEBUG)
	gcc mpic.c -o mpic $(SOURCES) $(WARNS) $(DEBUG) $(WIZARD)
