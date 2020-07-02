//Eric Grant
//ewgrant
//player character stats and logic 

#include "Avatar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//init avatar
void avatarInit(Avatar* avatar, const char* name){
    avatar->name = malloc(sizeof(char) * 256);
    strcpy(avatar->name, name);
    avatar->gems = 0;
    avatar->keys = 0;
}

//clear avatar
void avatarUninit(Avatar* avatar){
    free(avatar->name);
    avatar->name = NULL;
    avatar = NULL;
}

//check if avatar can use key, use if possible
bool avatarUseKey(Avatar* avatar){
    if (avatar->keys > 0)
    {
        avatar->keys--;
        return true;
    }
    return false;
}

//add key to avatar
void avatarAddKey(Avatar* avatar){
    avatar->keys++;
}

//add gem to avatar
void avatarAddGem(Avatar* avatar){
    avatar->gems++;
}

//display avatar info
void avatarDisplay(const Avatar* avatar){
    printf("%s's inventory: gems %d, keys %d\n", avatar->name, avatar->gems, avatar->keys);
}