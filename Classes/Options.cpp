#ifndef CONST_OPTIONS
#define CONST_OPTIONS

#include "Options.h"

#include "Entity.h"

int Options::CENTER_X = 0;
int Options::CENTER_Y = 0;

int Options::SCREEN_WIDTH = 0;
int Options::SCREEN_HEIGHT = 0;

int Options::SCREEN_CENTER_X = 0;
int Options::SCREEN_CENTER_Y = 0;

int Options::CAMERA_WIDTH = 0;
int Options::CAMERA_HEIGHT = 0;

int Options::CAMERA_CENTER_X = 0;
int Options::CAMERA_CENTER_Y = 0;

float Options::MIN_Z = 1.0f;

bool Options::MUSIC_ENABLE = false;

Entity* Options::BASE = new Entity();

#endif