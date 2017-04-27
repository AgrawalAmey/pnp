// Definations for all parser functions
#ifndef GAME_SERVER
#define GAME_SERVER

// Validate the session of user
int validateSession(char * username, char * sessionKey, redisContext * redisConnection);

// TCP Server
void tcpServer(MongoConnection mongoConnection, redisContext ** redisConnection);

// UDP Server
void udpServer(MongoConnection mongoConnection, redisContext ** redisConnection);

// Store the position of user and returns position of nearby users
void handlePositionRequest(char * outBuffer, char * username, char * position, long int timestamp,
  redisContext * redisConnection);

// Fetch pokemon data from mongo
void
fetchPokemonData(pokemon pok, char * pokemonId, MongoConnection mongoConnection);

// Fetch move data from mongo
void
fetchMoveData(move * m, char * move, MongoConnection mongoConnection);

void
updatePokemonInfo(char * pokemonId, int new_xp, int new_level, MongoConnection mongoConnection);

int
addPokemon(char * username, int pokedexId, int level, int xp, MongoConnection mongoConnection);
#endif // GAME_SERVER
