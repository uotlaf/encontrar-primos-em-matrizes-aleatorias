
# Configuração do programa
ORDEM_MATRIZ = 10000
THREADS=2
SEED=457155320
USAR_MATRIZ_ALEATORIA = 1
RANDOM_MAX=29999
VERNOFINAL=0
DEBUGLEVEL = 0

# Início do makefile
PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OUT     = $(PROJECT_ROOT)/out
SOURCE  = $(PROJECT_ROOT)/src
INCLUDE = $(PROJECT_ROOT)/include
OBJECTS = $(SOURCE)/tempo.c $(SOURCE)/main.c  $(SOURCE)/primos.c $(SOURCE)/matriz.c  #$(SOURCE)/visualizacao.c


CFLAGS  = -lm \
	-DSEED=$(SEED) \
	-DORDEM_MATRIZ=$(ORDEM_MATRIZ) \
	-DTHREADS=$(THREADS) \
	-DVERNOFINAL=$(VERNOFINAL) \
	-DCONF_USAR_MATRIZ_ALEATORIA=$(USAR_MATRIZ_ALEATORIA) \
	-DRANDOM_MAX_CAP=$(RANDOM_MAX) \
	-DTRUE=1 \
	-DFALSE=0

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -fdiagnostics-color=always -g -Werror 
	BUILD_DIR=$(PROJECT_ROOT)/build/debug
else ifeq ($(BUILD_MODE),release)
	CFLAGS += -march=native -O3 -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=4
	BUILD_DIR=$(PROJECT_ROOT)/build/release
else ifeq ($(BUILD_MODE),run) # Eclipse run
	CFLAGS += -march=native -O3 -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=4
	BUILD_DIR=$(PROJECT_ROOT)/build/debug
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
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
	$(CC) -o $(BUILD_DIR)/main -I $(INCLUDE) $(CFLAGS) $(OBJECTS)
	
	
link: $(OUT)
	$(CC) -o $(BUILD_DIR)/main $(LDFLAGS) $(OUT)/*
	
clean:
	rm -fr out/*.o build/debug/main build/release/main
