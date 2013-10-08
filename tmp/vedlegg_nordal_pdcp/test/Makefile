
SOCKTEST_SRC:=socktest.c ../src/socket.c
SOCKTEST_HED:=../src/socket.h ../src/config.h
CFLAGS:=-Wall -Werror -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums $(CFLAGS)
LDFLAGS:=-lpthread

TARGETS:=$(patsubst %.c, %, $(wildcard *.c)) fifopipe

all: $(TARGETS)
test: all
	./offsetof
	dd if=socktest bs=1 count=$$(($$RANDOM % $$(stat -c %s socktest))) | tee fifopipe | ./socktest | diff - fifopipe
clean:
	rm -f $(TARGETS)
socktest: $(SOCKTEST_SRC) $(SOCKTEST_HED)
	$(CC) $(CFLAGS) $(SOCKTEST_SRC) $(LDFLAGS) -o $@
fifopipe:
	mkfifo $@

.PHONY:all clean test