CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c2x -Ofast
LIBS=

INCLUDE_PATH=/usr/include/
LIB_PATH=/usr/lib64/

TARGET=libutest.a
CACHE=.cache
OUTPUT=$(CACHE)/release


MODULES += utest.o

TEST += test.o


OBJ=$(addprefix $(CACHE)/,$(MODULES))
T_OBJ=$(addprefix $(CACHE)/,$(TEST))


$(CACHE)/%.o:
	$(CC) $(CFLAGS) -c $< -o $@


all: env $(OBJ)
	ar -crs $(OUTPUT)/$(TARGET) $(OBJ)


-include dep.list


.PHONY: env dep clean install


dep:
	$(CC) -MM src/*.c test/*.c | sed 's|[a-zA-Z0-9_-]*\.o|$(CACHE)/&|' > dep.list


exec: env $(T_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(T_OBJ) $(OBJ) $(LIBS) -o $(OUTPUT)/test
	$(OUTPUT)/test


install:
	cp -v $(OUTPUT)/$(TARGET) $(LIB_PATH)/$(TARGET)
	cp -v src/utest.h $(INCLUDE_PATH)/utest.h


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(OUTPUT)


clean: 
	rm -rvf $(CACHE)



