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
fetchPokemonData(pokemon * pok, char * pokemonId, MongoConnection mongoConnection);

// Fetch move data from mongo
void
fetchMoveData(move * m, char * move, MongoConnection mongoConnection);

void
updatePokemonInfo(char * pokemonId, int new_xp, int new_level, MongoConnection mongoConnection);

int
addPokemon(char * username, int pokedexId, int level, int xp, MongoConnection mongoConnection);

void
fetchUserData(user * u, char * username, MongoConnection mongoConnection);

void
updateUserInfo(char * username, int new_xp, int new_level, MongoConnection mongoConnection);

void fetchPokemonList(char * outBuffer, char * username, MongoConnection mongoConnection);

void
makeBattleSession(char * outBuffer, char * username0, char * username1, char * pokemonId,
  int count, MongoConnection mongoConnection, redisContext * redisConnection);

void
battleStep(char * outBuffer, char * username0, char * username1, char * move, char * battleSessionKey,
redisContext * redisConnection,
MongoConnection mongoConnection);

void
fetchLeaderBoard(char * outBuffer, MongoConnection mongoConnection);
#endif // GAME_SERVER
