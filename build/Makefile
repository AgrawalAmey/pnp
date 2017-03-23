# Master build file
# To be replaced by Cmake

CFLAGS = -g -Wall -Wextra $(shell pkg-config --cflags libmongoc-1.0)

LDFLAGS = $(shell pkg-config --libs libmongoc-1.0)

client:
	gcc ../src/client/login/login.c \
	../src/client/index.c \
	-o client.exe

login_server:
	gcc $(CFLAGS) \
	$(LDFLAGS) \
	../src/utils/rand.c \
	../src/utils/split_string.c \
	../src/login_server/index.c \
	../src/login_server/signup.c \
	-o server.exe
