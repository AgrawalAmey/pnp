// Definations for all util functions
#ifndef TYPES
#define TYPES

// Define struct for mongo connection
typedef struct{
    mongoc_client_t *mongoClient;
    mongoc_database_t *database;
    mongoc_collection_t *users;
    mongoc_collection_t *pokemons;
    mongoc_collection_t *pokedex;
    mongoc_collection_t *moves;
} MongoConnection;


typedef struct{
    char move0[50];
    char move1[50];
    char move2[50];
    char move3[50];
    char name[50];
    char type0[50];
    char type1[50];
    double defense;
    double poison;
    double speed ;
    double ground;
    double spDefense ;
    double psychic;
    double flying;
    double ice;
    double fight;
    double attack;
    double steel;
    double electric;
    double normal;
    double fire;
    double spAttack;
    double hp;
    double dark;
    double bug;
    double ghost;
    double water;
    double grass;
    double capturerate;
    double dragon;
    double rock;
    double expgrowth;
    int xp;
    int level;
    int health;
} pokemon;

typedef struct{
    char type[50];
    int bp;
} move;


typedef struct {
    int level;
    int xp;
    char name[20];
} user;
#endif // TYPES
