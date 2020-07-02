//Eric Grant
//ewgrant
//game actions

#include "Action.h"

//take char and return action it represents
Action actionFromChar(char ch){
    switch (ch)
    {
    case 'w':
        return ActionNorth;
        break;
    case 's':
        return ActionSouth;
        break;
    case 'a':
        return ActionWest;
        break;
    case 'd':
        return ActionEast;
        break;
    case 'q':
        return ActionQuit;
        break;
    default:
        return ActionInvalid;
        break;
    }
}

//take action and return string name
const char* actionToString(Action a){
    switch (a)
    {
    case ActionInvalid:
        return "invalid";
        break;
    case ActionNorth:
        return "north";
        break;
    case ActionSouth:
        return "south";
        break;
    case ActionEast:
        return "east";
        break;
    case ActionWest:
        return "west";
        break;
    case ActionQuit:
        return "quit";
        break;
    default:
        return "invalid";
        break;
    }
}