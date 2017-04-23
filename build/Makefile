# Master build file
# To be replaced by Cmake

client:
	gcc -g ../src/client/login/login.c \
	../src/utils/hash.c \
	../src/client/index.c \
	../src/client/GUIUtils/load_image.c \
	../src/client/GUIUtils/append.c \
	../src/client/GUIUtils/apply_surface.c \
	../src/client/GUIUtils/handle_input.c \
	-D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer \
	-I/usr/local/include/libmongoc-1.0 \
	-I/usr/local/include/libbson-1.0 \
	-L/usr/local/lib -lmongoc-1.0 -lsasl2 -lssl -lcrypto -lrt -lbson-1.0 \
	-D_FILE_OFFSET_BITS=64 -I/usr/local/include/hiredis -L/usr/local/lib -lhiredis \
	-o client.exe

login_server:
	gcc -g ../src/utils/mongo.c \
	../src/utils/redis.c \
	../src/utils/rand.c \
	../src/utils/split_string.c \
	../src/login_server/tcp_server.c \
	../src/login_server/index.c \
	../src/login_server/load_balancer.c \
	../src/login_server/session_key.c \
	../src/login_server/signup.c \
	../src/login_server/login.c \
	-I/usr/local/include/libmongoc-1.0 \
	-I/usr/local/include/libbson-1.0 \
	-L/usr/local/lib -lmongoc-1.0 -lsasl2 -lssl -lcrypto -lrt -lbson-1.0 \
	-D_FILE_OFFSET_BITS=64 -I/usr/local/include/hiredis -L/usr/local/lib -lhiredis \
	-o login_server.exe

game_server:
	gcc ../src/utils/mongo.c \
	../src/utils/redis.c \
	../src/utils/rand.c \
	../src/utils/split_string.c \
	../src/game_server/index.c \
	../src/game_server/tcp_server.c \
	../src/game_server/udp_server.c \
	../src/game_server/validate_user.c \
	-I/usr/local/include/libmongoc-1.0 \
	-I/usr/local/include/libbson-1.0 \
	-L/usr/local/lib -lmongoc-1.0 -lsasl2 -lssl -lcrypto -lrt -lbson-1.0 \
	-D_FILE_OFFSET_BITS=64 -I/usr/local/include/hiredis -L/usr/local/lib -lhiredis \
	-o game_server.exe
