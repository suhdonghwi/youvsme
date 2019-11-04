#pragma once
#include "GameScene.h"

typedef GameScene* (*CreateScene)();

GameScene* create_readystart_scene(CreateScene create_scene, HBITMAP* slides,
                                   int size, Pos pos);
