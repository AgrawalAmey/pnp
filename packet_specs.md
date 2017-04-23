# Pacekt specifications of PNP

### Login server

Login/Signup requests

|Index  | Feild Name  | Explanation  |
|:---:|:---:|:---:|
|0   | Type  | "login"  or "signup"|
|1  |  Name |  - |
|2   |  Username | -  |
|3   |  Password | -  |

Login/Signup response

|Index  | Feild Name  | Explanation  |
|:---:|:---:|:---:|
|0   | Status Code  | "success", "error" |
|1   | Session Key | -|
|2   | Game Server IP Address | -|
|3   | Game Server Port | -|

Position request

|Index  | Feild Name  | Explanation  |
|:---:|:---:|:---:|
|0 | Type | "position"|
|1 | username  | -|
|2 | Session Key| -|
|3 | timestamp | -|
|4 | position | positionX:positionY |

Position response

|Index  | Feild Name  | Explanation  |
|:---:|:---:|:---:|
|0 | User Count | Number of users in visinity of the player |
|1 | username[0]  | Username of 0th player in visinity |
|2 | position[0] | positionX:positionY of 0th player in visinity|


Battle initialization request
|Index  | Feild Name  | Explanation  |
|:---:|:---:|:---:|
