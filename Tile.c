//Eric Grant
//ewgrant
//Tile types and logic

#include "Tile.h"
#include <stdlib.h>
#include <stdio.h>

//return tile type from char
Tile tileFromChar(char ch){
    switch (ch)
    {
    case '.':
        return TileEmpty;
        break;
    case '#':
        return TileWall;
        break;
    case '-':
        return TileDoor;
        break;
    case '=':
        return TileLockedDoor;
        break;
    case 'S':
        return TileSecretPassage;
        break;
    case '*':
        return TileGem;
        break;
    case '+':
        return TileKey;
        break;
    default:
        return TileInvalid;
        break;
    }
}

//print what tile looks like
void tileDisplay(Tile tile){
    switch (tile)
    {
    case TileEmpty:
        printf(" ");
        break;
    case TileWall:
        printf("#");
        break;
    case TileDoor:
        printf("-");
        break;
    case TileLockedDoor:
        printf("=");
        break;
    case TileSecretPassage:
        printf("#");
        break;
    case TileGem:
        printf("*");
        break;
    case TileKey:
        printf("+");
        break;
    default:
        break;
    }
}

//check if tile can be passed
bool tilePassable(Tile tile){
    switch (tile)
    {
    case TileEmpty:
        return 1;
        break;
    case TileWall:
        return 0;
        break;
    case TileDoor:
        return 1;
        break;
    case TileLockedDoor:
        return 0;
        break;
    case TileSecretPassage:
        return 1;
        break;
    case TileGem:
        return 1;
        break;
    case TileKey:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}