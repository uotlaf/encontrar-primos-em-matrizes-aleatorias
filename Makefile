# Configuração do programa
ORDEM_MATRIZ = 30000
THREADS=1
IMPRIMIR_MATRIZ=0
SEED=457155320
USAR_MATRIZ_ALEATORIA = 1
RANDOM_MAX=29999
VERNOFINAL=0
DEBUGLEVEL = 0

# Início do makefile
PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OUT     = ./out
SOURCE  = ./src
INCLUDE = ./include
OBJECTS = $(SOURCE)/tempo.c $(SOURCE)/main.c  $(SOURCE)/primos.c $(SOURCE)/matriz.c $(SOURCE)/handlers/thread.c $(SOURCE)/visualizacao.c

LIBS = -lm -pg

CFLAGS  = $(LIBS) \
	-DSEED=$(SEED) \
	-DORDEM_MATRIZ=$(ORDEM_MATRIZ) \
	-DTHREADS=$(THREADS) \
	-DVERNOFINAL=$(VERNOFINAL) \
	-DCONF_USAR_MATRIZ_ALEATORIA=$(USAR_MATRIZ_ALEATORIA) \
	-DRANDOM_MAX_CAP=$(RANDOM_MAX) \
	-DIMPRIMIR_MATRIZ=$(IMPRIMIR_MATRIZ) \
	-DCOLOR_DEBUG \
	-DTRUE=1 \
	-DFALSE=0

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -fdiagnostics-color=always -pg -g -mcmodel=medium
	BUILD_DIR=$(PROJECT_ROOT)/build/debug
else ifeq ($(BUILD_MODE),release)
	CFLAGS += -march=native -O3 -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=4
	BUILD_DIR=$(PROJECT_ROOT)/build/release
else ifeq ($(BUILD_MODE),run) # Eclipse run
	CFLAGS += -march=native -O3 -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=4
	BUILD_DIR=$(PROJECT_ROOT)/build/debug
else
	CFLAGS += -march=native -O3 -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=4
        BUILD_DIR=$(PROJECT_ROOT)/build/release
endif

ifeq ($(DEBUGLEVEL), 1)
	CFLAGS += -DDEBUG
else ifeq ($(DEBUGLEVEL), 2)
	CFLAGS += -DDEBUG -DPRIMODEBUG
else ifeq ($(DEBUGLEVEL), 3)
	CFLAGS += -DEBUG -DPRIMODEBUG -DTHREADDEBUG
else ifeq ($(DEBUGLEVEL), 4)
	CFLAGS += -DEBUG -DPRIMODEBUG -DTHREADDEBUG -DCONTROLDEBUG
endif


all: program # link

program:
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/main -I $(INCLUDE) $(CFLAGS) $(OBJECTS) -lm -pthread

	
clean:
	rm -fr build/debug	/main build/release/main
