# Install mongodb

sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 0C49F3730359A14518585931BC711F9BA15703C6

# For ubuntu 16.04
echo "deb [ arch=amd64,arm64 ] http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.4 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.4.list

sudo apt-get update

sudo apt-get install -y mongodb-org

mkdir /data
mkdir /data/db

# Install mongoc

sudo apt-get install pkg-config libssl-dev libsasl2-dev

wget https://github.com/mongodb/mongo-c-driver/releases/download/1.6.1/mongo-c-driver-1.6.1.tar.gz
tar xzf mongo-c-driver-1.6.1.tar.gz
cd mongo-c-driver-1.6.1

./configure --disable-automatic-init-and-cleanup
make
sudo make install

# Install redis
wget http://download.redis.io/redis-stable.tar.gz
tar xvzf redis-stable.tar.gz
cd redis-stable
make
make test
sudo make install

# Hiredis
wget https://github.com/redis/hiredis/archive/v0.13.3.tar.gz
tar xzf hiredis-0.13.3.tar.gz
cd hiredis-0.13.3
make
sudo make install

#SDL
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
sudo apt-get install libsdl-image1.2-dev
