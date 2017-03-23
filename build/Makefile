# Master build file
# To be replaced by Cmake

client:
	gcc ../src/client/login/login.c \
	../src/utils/hash.c \
	../src/client/index.c \
	-I/usr/local/include/libmongoc-1.0 \
	-I/usr/local/include/libbson-1.0 \
	-L/usr/local/lib -lmongoc-1.0 -lsasl2 -lssl -lcrypto -lrt -lbson-1.0 \
	-o client.exe

login_server:
	gcc ../src/utils/mongo.c \
	../src/utils/rand.c \
	../src/utils/split_string.c \
	../src/login_server/index.c \
	../src/login_server/signup.c \
	../src/login_server/login.c \
	-I/usr/local/include/libmongoc-1.0 \
	-I/usr/local/include/libbson-1.0 \
	-L/usr/local/lib -lmongoc-1.0 -lsasl2 -lssl -lcrypto -lrt -lbson-1.0 \
	-o server.exe
