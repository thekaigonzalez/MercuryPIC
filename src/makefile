SOURCES=mbyte.c mpool.c mcpu.c mreg.c mctx.c mrunl.c msec.c mrt.c msyscalls.c
WIZARD=wiz/wArgParser.c wiz/wFlag.c wiz/wMem.c wiz/wName.c wiz/wOptions.c wiz/wStraggly.c wiz/wValue.c -Iwiz 
DEBUG=-Ofast -Wno-unused-result -march=native -finline-functions -fomit-frame-pointer -flto -mtune=native -fprefetch-loop-arrays
WARNS=-Wall

all:
	gcc mtest.c -o mtest $(SOURCES) $(WARNS) $(DEBUG)
	gcc mpic.c -o mpic32 $(SOURCES) $(WARNS) $(DEBUG) $(WIZARD)
