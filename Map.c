//Eric Grant
//ewgrant
//map stats and logic 

#include "Map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//have avatar interact with gem or key on same tile
void mapCheckGetItem(Map* map, Avatar* avatar){
    if (map->tiles[map->avatarRow][map->avatarCol] == TileGem)
    {
        map->tiles[map->avatarRow][map->avatarCol] = TileEmpty;
        avatarAddGem(avatar);
    }
    if (map->tiles[map->avatarRow][map->avatarCol] == TileKey)
    {
        map->tiles[map->avatarRow][map->avatarCol] = TileEmpty;
        avatarAddKey(avatar);
    }
}

//init map
bool mapInit(Map* map, const char* filename){
    //open file
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }
     
    //populate map meta data from file
    if(!fscanf(file, "%d", &map->rows)){
        printf("ERROR: no row num found.");
    }
    if(!fscanf(file, "%d", &map->cols)){
        printf("ERROR: no col num found.");
    }
    if(!fscanf(file, "%d", &map->avatarRow)){
        printf("ERROR: no avatar row num found.");
    }
    if(!fscanf(file, "%d", &map->avatarCol)){
        printf("ERROR: no avatar col num found.");
    }

    //populate 2D array with tiles from file
    char temp;
    map->tiles = malloc(sizeof(Tile*) * map->rows);
    for (int x = 0; x < map->rows; x++)
    {
        map->tiles[x] = malloc(sizeof(Tile) * map->cols);
        for (int y = 0; y < map->cols; y++)
        { 
            if(!fscanf(file, "%s", &temp)){
                printf("ERROR: no tile found.");
            } 
            map->tiles[x][y] = tileFromChar(temp);
        }
    }

    //close file
    fclose(file);
    return 1;
}

//clear map
void mapUninit(Map* map){
    for (int i = 0; i < map->rows; i++)
    {
        free(map->tiles[i]);
        map->tiles[i] = NULL;
    }

    free(map->tiles);
    map->tiles = NULL;
}

//display map
void mapDisplay(const Map* map){
    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
        {
            if (i == map->avatarRow && j == map->avatarCol)
            {
                printf("@");
            } else {
                tileDisplay(map->tiles[i][j]);
            }
        }
        printf("\n");
    }
}

//move avatar on map and interact with objects in map (I'm sorry about this one)
bool mapMoveAvatar(Map* map, Avatar* avatar, Action action){
    //switch over each possible direction selected.
    //if direction is valid move player and check for items on floor, return true
    //if direction collides with door, check if avatar has a key
    //  if avatar does have key open door and move avatar, return true
    //if direction invalid return false
    switch (action)
    {
    case ActionNorth:
        if (map->avatarRow-1 >= 0 && tilePassable(map->tiles[map->avatarRow-1][map->avatarCol]))
        {
            map->avatarRow--;
            mapCheckGetItem(map, avatar);
            return 1;
        } 
        else if (map->avatarRow-1 >= 0 && map->tiles[map->avatarRow-1][map->avatarCol] == TileLockedDoor && avatarUseKey(avatar)) 
        {
            map->avatarRow--;
            map->tiles[map->avatarRow][map->avatarCol] = TileDoor;
            return 1;
        }
        break;
    case ActionSouth:
        if (map->avatarRow+1 < map->rows && tilePassable(map->tiles[map->avatarRow+1][map->avatarCol]))
        {
            map->avatarRow++;
            mapCheckGetItem(map, avatar);
            return 1;
        }
        else if (map->avatarRow+1 < map->rows && map->tiles[map->avatarRow+1][map->avatarCol] == TileLockedDoor && avatarUseKey(avatar)) 
        {
            map->avatarRow++;
            map->tiles[map->avatarRow][map->avatarCol] = TileDoor;
            return 1;
        }
        break;
    case ActionEast:
        if (map->avatarCol+1 < map->cols && tilePassable(map->tiles[map->avatarRow][map->avatarCol+1]))
        {
            map->avatarCol++;
            mapCheckGetItem(map, avatar);
            return 1;
        }
        else if (map->avatarCol+1 < map->cols && map->tiles[map->avatarRow][map->avatarCol+1] == TileLockedDoor && avatarUseKey(avatar)) 
        {
            map->avatarCol++;
            map->tiles[map->avatarRow][map->avatarCol] = TileDoor;
            return 1;
        }
        break;
    case ActionWest:
        if (map->avatarCol-1 >= 0 && tilePassable(map->tiles[map->avatarRow][map->avatarCol-1]))
        {
            map->avatarCol--;
            mapCheckGetItem(map, avatar);
            return 1;
        }
        else if (map->avatarCol-1 >= 0 && map->tiles[map->avatarRow][map->avatarCol-1] == TileLockedDoor && avatarUseKey(avatar)) 
        {
            map->avatarCol--;
            map->tiles[map->avatarRow][map->avatarCol] = TileDoor;
            return 1;
        }
        break;
    default:
        return 0;
        break;
    }
    return 0;
}

//return remaining gems on map
int mapGemsRemaining(const Map* map){
    int count = 0;
    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
        {
            if (map->tiles[i][j] == TileGem)
            {
                count++;   
            }
        }
    }
    return count;
}
