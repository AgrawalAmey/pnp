# Pacekt specifications of PNP

## Login server

Login/Signup requests

Index | Feild Name |     Explanation
:---: | :--------: | :-----------------:
  0   |    Type    | "login" or "signup"
  1   |    Name    |          -
  2   |  Username  |          -
  3   |  Password  |          -

Login/Signup response

Index |       Feild Name       |    Explanation
:---: | :--------------------: | :----------------:
  0   |      Status Code       | "success", "error"
  1   |      Session Key       |         -
  2   | Game Server IP Address |         -
  3   |    Game Server Port    |         -

Signout request

Index | Feild Name | Explanation
:---: | :--------: | :---------:
  0   |    Type    |  "signout"
  1   |  Username  |      -

Signout response

Index |  Feild Name   | Explanation
:---: | :-----------: | :---------:
  0   | "dasvisaniya" |      -

## Game Server

Position request

Index | Feild Name  |     Explanation
:---: | :---------: | :-----------------:
  0   |    Type     |     "position"
  1   |  Username   |          -
  2   | Session Key |          -
  3   |  Timestamp  |          -
  4   |  Position   | positionX:positionY

Position response

Index | Feild Name  |                  Explanation
:---: | :---------: | :-------------------------------------------:
  0   | User Count  |   Number of users in visinity of the player
  1   | Username[0] |      Username of 0th player in visinity
  2   | Position[0] | positionX:positionY of 0th player in visinity

Get pokemon list request

Index | Feild Name  |   Explanation
:---: | :---------: | :-------------:
  0   |    Type     | "list_pokemons"
  0   |  Username   |        -
  1   | Session Key |        -

Get pokemon list response

Index |     Feild Name     | Explanation
:---: | :----------------: | :---------:
  0   | Number of pokemons |      -
  1   |    PokemonId[0]    |      -
  2   |    PokedexId[0]    |      -
  3   |       XP[0]        |      -
  4   |      Level[0]      |      -

Battle initialization request

Index |    Feild Name     |                  Explanation
:---: | :---------------: | :-------------------------------------------:
  0   |       Type        |                "battle_start"
  1   |     Username      |                       -
  2   |    Session Key    |                       -
  3   | Opponent Username |                       -
  4   |    Pokemon ID     | ID of the pokemon selected by user for battle

Battle initialization response/brodcast

Index |     Feild Name     |    Explanation
:---: | :----------------: | :---------------:
  0   |       status       | "start" or "lite"
  1   | Battle Session Key |         -
  2   |     Username0      |         -
  3   |     User0 Name     |         -
  4   |    Username0 XP    |         -
  5   |  Username0 Level   |         -
  6   |   Pokemon0 Name    |         -
  7   |    Pokemon0 XP     |         -
  8   |   Pokemon0 Level   |         -
  9   |     Username1      |         -
 10   |     User1 Name     |         -
 11   |    Username1 XP    |         -
 12   |  Username1 Level   |         -
 13   |   Pokemon1 Name    |         -
 14   |    Pokemon1 XP     |         -
 15   |   Pokemon1 Level   |         -

Battle move request

Index |     Feild Name     |    Explanation
:---: | :----------------: | :----------------:
  0   |        Type        | "battle_make_move"
  1   |      Username      |         -
  2   |    Session Key     |         -
  3   | Battle Session Key |         -
  4   | Opponent Username  |         -
  5   |     move name      |         -

Battle move response/brodcast

Index |    Feild Name     |                     Explanation
:---: | :---------------: | :--------------------------------------------------:
  0   |      status       |                 "ongoing" or "over"
  1   |     username      |                 username of actaker
  2   |      health       |               new health of defendent
  3   |    user new xp    |    new xp of the attacking user if battle is over
  4   |  user new level   |  new level of the attacking user if battle is over
  5   |  pokemon new xp   |  new xp of the attacking pokemon if battle is over
  6   | pokemon new level | new level of the attacking pokemon if battle is over

Scoreboard Request

Index |     Feild Name     |    Explanation
:---: | :----------------: | :------------------:
  0   |        Type        | "get_leader_board"
  1   |      Username      |         -
  2   |    Session Key     |         -


Scoreboard Response

Index |     Feild Name     | Explanation
:---: | :----------------: | :---------:
  0   | Number of players  |      -
  1   |    PlayersId[0]    |      -
  2   |    PokedexId[0]    |      -
  3   |       XP[0]        |      -
  4   |      Level[0]      |      -