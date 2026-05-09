#pragma once

// Window dimensions
const float WINDOW_WIDTH = 1280.f;
const float WINDOW_HEIGHT = 720.f;

// HUD zone height - player and spawns are blocked above this
const float HUD_HEIGHT = 80.f;

// Player settings
const float PLAYER_RADIUS = 10.f;
const float PLAYER_START_SPEED = 5.5f;
const float PLAYER_MAX_RADIUS = 25.f;
const float PLAYER_GROW_AMOUNT = 1.5f;

// Enemy settings
const float ENEMY_RADIUS = 8.f;
const float ENEMY_SPEED_RATIO = 0.6f;

// Score point settings
const float SCOREPOINT_RADIUS = 5.f;

// Difficulty scaling per pickup
const float SPEED_INCREMENT = 0.3f;
const float GLOBAL_START_SPEED = 5.5f;

// Score values
const int SCORE_PICKUP = 10;
const int SCORE_ENEMY_COLLISION = 5;

const float EASY_SPEED = 3.5f;
const float MEDIUM_SPEED = 5.5f;
const float HARD_SPEED = 8.0f;