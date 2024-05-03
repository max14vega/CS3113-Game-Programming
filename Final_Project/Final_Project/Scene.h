#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Util.h"
#include "Entity.h"
#include "Map.h"

/**
    Notice that the game's state is now part of the Scene class, not the main file.
*/
struct GameState
{
    // ————— GAME OBJECTS ————— //
    Map *map;
    Entity *player;
    Entity *enemies;
    Entity *background;
    Entity *player_projectiles;
    Entity *projectile_1;
    Entity *projectile_2;
    
    // ————— AUDIO ————— //
    Mix_Music *bgm;
    Mix_Chunk *attack_sfx;
    Mix_Chunk *victory_sfx;
    Mix_Chunk *lose_sfx;
    Mix_Chunk *evolve_sfx;
    
    // ————— POINTERS TO OTHER SCENES ————— //
    int next_scene_id;
};

class Scene {
public:
    // ————— ATTRIBUTES ————— //
    int m_number_of_enemies = 3;
    int evo_stage = 0;
    int experience = 0;
    int current_character = 0;
    bool ping[10] = {false, false, false, false, false, false, false, false, false, false};
    
    int player_projectile_idx = 0;
    int projectile_idx_1 = 0;
    int projectile_idx_2 = 0;
    
    GameState m_state;
    
    // ————— METHODS ————— //
    virtual void initialise() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(ShaderProgram *program) = 0;
    
    // ————— GETTERS ————— //
    GameState const get_state()             const { return m_state;             }
    int       const get_number_of_enemies() const { return m_number_of_enemies; }
};
