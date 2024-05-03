/**
* Author: Max Vega
* Assignment: Platformer
* Date due: 2024-04-13, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 50
#define LEVEL_HEIGHT 38
#define MAX_HEALTH 3
#define PLAYER_IDX_R 6
#define PLAYER_IDX_G 0
#define PLAYER_IDX_B 12

GLuint m_font;

int projectile_a_idx = 0;

unsigned int LEVEL_A_DATA[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0
};


LevelA::~LevelA()
{
    delete [] m_state.enemies;
    delete [] m_state.player_projectiles;
    //delete [] m_state.projectile_1;
    //delete [] m_state.projectile_2;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.attack_sfx);
    Mix_FreeChunk(m_state.lose_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelA::initialise()
{
    
    GLuint map_texture_id = Utility::load_texture("assets/images/test_tiles.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_A_DATA, map_texture_id, 1.0f, 2, 1);
    
    // ————— FONT SET-UP ————— //
    m_font = Utility::load_texture("assets/images/font1.png");
    
    // LEVEL IMAGE
    m_state.background = new Entity();
    m_state.background->set_health(10000);
    m_state.background->set_position(glm::vec3(25.0f, -21.0f, 0.0f));
    m_state.background->set_size(glm::vec3(41.1*1.3137, 41.1f, 0.0f));
    m_state.background->m_texture_id = Utility::load_texture("assets/images/Level1.png");
    m_state.background->update(0.0f, m_state.background, NULL, 0, m_state.map);
    
    
    // ————— PLAYER SET-UP ————— //
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(7.4f, -32.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_health(MAX_HEALTH);
    m_state.player->set_experience(0);
    m_state.player->m_texture_id = Utility::load_texture("assets/images/Player_SS.png");

    // Walking
    m_state.player->m_walking[m_state.player->UP]    = new int[2] { 72,72 };
    m_state.player->m_walking[m_state.player->DOWN]  = new int[2] { 72,72 };
    m_state.player->m_walking[m_state.player->LEFT]  = new int[2] { 72,72 };
    m_state.player->m_walking[m_state.player->RIGHT] = new int[2] { 72,72 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 2;
    m_state.player->m_animation_index = 0;
    m_state.player->m_animation_time = 0.0f;
    m_state.player->m_animation_cols = 18;
    m_state.player->m_animation_rows = 5;
    m_state.player->set_height(1.0f);
    m_state.player->set_width(1.0f);
    m_state.player->set_size(glm::vec3(2.0f, 2.0f, 0.0f));

    // Jumping
    m_state.player->m_jumping_power = 7.0f;
    
    m_state.enemies = new Entity[ENEMY_COUNT];
    
    
    // ————— RATATA SET-UP (index 0) ————— //
    // Existing
    m_state.enemies[0].set_position(glm::vec3(13.0f, -22.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(2.5f);
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_ai_type(RATATA);
    m_state.enemies[0].set_health(1);
    m_state.enemies[0].m_texture_id = Utility::load_texture("assets/images/PoliwagSS.png");
    
    // Walking
    m_state.enemies[0].m_walking[m_state.enemies[0].UP]     = new int[2] { 0, 1};
    m_state.enemies[0].m_walking[m_state.enemies[0].DOWN]   = new int[2] { 2, 3};
    m_state.enemies[0].m_walking[m_state.enemies[0].LEFT]   = new int[2] { 4, 5};
    m_state.enemies[0].m_walking[m_state.enemies[0].RIGHT]  = new int[2] { 6, 7};
    
    m_state.enemies[0].m_animation_indices = m_state.enemies[1].m_walking[m_state.enemies[1].LEFT];
    m_state.enemies[0].m_animation_frames = 2;
    m_state.enemies[0].m_animation_index = 0;
    m_state.enemies[0].m_animation_time = 0.0f;
    m_state.enemies[0].m_animation_cols = 2;
    m_state.enemies[0].m_animation_rows = 4;
    m_state.enemies[0].set_height(1.0f);
    m_state.enemies[0].set_width(1.0f);
    m_state.enemies[0].set_size(glm::vec3(2.0, 2.0, 0.0f));
    
    // ————— RATATA SET-UP (index 0) ————— //
    // Existing
    m_state.enemies[1].set_position(glm::vec3(38.0f, -30.0f, 0.0f));
    m_state.enemies[1].set_movement(glm::vec3(0.0f));
    m_state.enemies[1].set_speed(1.5f);
    m_state.enemies[1].set_entity_type(ENEMY);
    m_state.enemies[1].set_ai_type(RATATA);
    m_state.enemies[1].set_health(1);
    m_state.enemies[1].m_texture_id = Utility::load_texture("assets/images/OdishSS.png");
    
    // Walking
    m_state.enemies[1].m_walking[m_state.enemies[1].UP]     = new int[2] { 0, 1};
    m_state.enemies[1].m_walking[m_state.enemies[1].DOWN]    = new int[2] { 2, 3};
    m_state.enemies[1].m_walking[m_state.enemies[1].LEFT]       = new int[2] { 4, 5};
    m_state.enemies[1].m_walking[m_state.enemies[1].RIGHT]     = new int[2] { 6, 7};
    
    m_state.enemies[1].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].LEFT];
    m_state.enemies[1].m_animation_frames = 2;
    m_state.enemies[1].m_animation_index = 0;
    m_state.enemies[1].m_animation_time = 0.0f;
    m_state.enemies[1].m_animation_cols = 2;
    m_state.enemies[1].m_animation_rows = 4;
    m_state.enemies[1].set_height(1.0f);
    m_state.enemies[1].set_width(1.0f);
    m_state.enemies[1].set_size(glm::vec3(2.0, 2.0, 0.0f));
    
    
    // ————— RATATA SET-UP (index 0) ————— //
    // Existing
    m_state.enemies[2].set_position(glm::vec3(21.0f, -14.0f, 0.0f));
    m_state.enemies[2].set_movement(glm::vec3(0.0f));
    m_state.enemies[2].set_speed(1.5f);
    m_state.enemies[2].set_entity_type(ENEMY);
    m_state.enemies[2].set_ai_type(RATATA);
    m_state.enemies[2].set_health(1);
    m_state.enemies[2].m_texture_id = Utility::load_texture("assets/images/ButterfreeSS.png");
    
    // Walking
    m_state.enemies[2].m_walking[m_state.enemies[2].UP]     = new int[2] { 0, 1 };
    m_state.enemies[2].m_walking[m_state.enemies[2].DOWN]   = new int[2] { 2, 3 };
    m_state.enemies[2].m_walking[m_state.enemies[2].LEFT]   = new int[2] { 4, 5 };
    m_state.enemies[2].m_walking[m_state.enemies[2].RIGHT]  = new int[2] { 6, 7 };
    
    m_state.enemies[2].m_animation_indices = m_state.enemies[2].m_walking[m_state.enemies[2].LEFT];
    m_state.enemies[2].m_animation_frames = 2;
    m_state.enemies[2].m_animation_index = 0;
    m_state.enemies[2].m_animation_time = 0.0f;
    m_state.enemies[2].m_animation_cols = 2;
    m_state.enemies[2].m_animation_rows = 4;
    m_state.enemies[2].set_height(1.0f);
    m_state.enemies[2].set_width(1.0f);
    m_state.enemies[2].set_size(glm::vec3(2.0, 2.0, 0.0f));
    
    // PROJECTILE SET UP - PLAYER //
    m_state.player_projectiles = new Entity[PROJECTILE_COUNT];
    
    for(int i = 0; i < PROJECTILE_COUNT; i++){
        m_state.player_projectiles[i].set_speed(5.5f);
        m_state.player_projectiles[i].set_health(1);
        m_state.player_projectiles[i].set_entity_type(PROJECTILE);
        m_state.player_projectiles[i].set_size(glm::vec3(1.5f,1.5f,0.0f));
        m_state.player_projectiles[i].deactivate();
    }
    
    // PROJECTILE SET UP - POLIWAG //
    m_state.projectile_1 = new Entity[PROJECTILE_COUNT];
    
    for(int i = 0; i < PROJECTILE_COUNT; i++){
        m_state.projectile_1[i].set_speed(3.5f);
        m_state.projectile_1[i].set_health(1);
        m_state.projectile_1[i].set_entity_type(PROJECTILE);
        m_state.projectile_1[i].set_size(glm::vec3(0.8f,0.8f,0.0f));
        m_state.projectile_1[i].m_texture_id = Utility::load_texture("assets/images/whirlpool.png");
        m_state.projectile_1[i].deactivate();
    }
    
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_state.bgm = Mix_LoadMUS("assets/audio/field.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    m_state.attack_sfx = Mix_LoadWAV("assets/audio/Slash.mp3");
    m_state.lose_sfx = Mix_LoadWAV("assets/audio/Defeat!.mp3");
    m_state.evolve_sfx = Mix_LoadWAV("assets/audio/Evolve.mp3");
}

void LevelA::update(float delta_time)
{
    
    if(m_state.player->get_experience() == 3) {
        evo_stage = 1;
        
    }
    
    m_state.player->m_walking[m_state.player->UP] =
        new int[2] { (0 + (current_character * 6)) + (evo_stage * 2), (1 + (current_character * 6)) + (evo_stage * 2) };
    m_state.player->m_walking[m_state.player->DOWN] =
        new int[2] { (18 + (current_character * 6)) + (evo_stage * 2), (19 + (current_character * 6)) + (evo_stage * 2) };
    m_state.player->m_walking[m_state.player->LEFT] =
        new int[2] { (36 + (current_character * 6)) + (evo_stage * 2), (37 + (current_character * 6)) + (evo_stage * 2) };
    m_state.player->m_walking[m_state.player->RIGHT] =
        new int[2] { (54 + (current_character * 6)) + (evo_stage * 2), (55 + (current_character * 6)) + (evo_stage * 2) };
    
    for(int i = 0; i < PROJECTILE_COUNT; i++){
        if (current_character == 0){
            m_state.player_projectiles[i].m_texture_id = Utility::load_texture("assets/images/GrassAtk.png");
        } else if (current_character == 1){
            m_state.player_projectiles[i].m_texture_id = Utility::load_texture("assets/images/FireAtk.png");
        } else if (current_character == 2){
            m_state.player_projectiles[i].m_texture_id = Utility::load_texture("assets/images/WaterAtk.png");
        }
    }
    
    
    if (m_state.player->get_health() <= 0) return;
    
    if (m_state.player->get_position().y == -8.5f && m_state.player->get_position().x == 37.5f) {
        m_state.next_scene_id = 1;
    }
    
    m_state.player->update(delta_time, m_state.player, m_state.projectile_1, PROJECTILE_COUNT, m_state.map);
    
    for(int i = 0; i < PROJECTILE_COUNT; i++){
        m_state.player_projectiles[i].update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    }
    
    for(int i = 0; i < ENEMY_COUNT; i ++){
        m_state.enemies[0].update(delta_time, m_state.player, NULL, NULL, m_state.map);
        if(m_state.enemies[0].m_spawn_atk){
            m_state.enemies[0].m_spawn_atk = false;
            Mix_PlayChannel(-1, m_state.attack_sfx,0);
            m_state.projectile_1[projectile_a_idx].activate();
            m_state.projectile_1[projectile_a_idx].set_position(glm::vec3(m_state.enemies[0].get_position().x, m_state.enemies[0].get_position().y - 0.5f, 0));
            m_state.projectile_1[projectile_a_idx].set_movement(glm::vec3(0.0f, -1.2f, 0));
            projectile_a_idx++;
        }
    }
    
    for(int i = 0; i < PROJECTILE_COUNT; i++){
        m_state.projectile_1[i].update(delta_time, m_state.player, NULL, 0, m_state.map);
    }
    
    for(int i = 1; i < ENEMY_COUNT; i ++){
        m_state.enemies[i].update(delta_time, m_state.player, NULL, NULL, m_state.map);
    }
    
    for( int i = 0; i < ENEMY_COUNT; i ++){
        if (m_state.enemies[i].get_health() == 0 && !ping[i]){
            m_state.player->set_experience(m_state.player->get_experience()+1);
            ping[i] = true;
            experience += 1;
        }
    }
    
    if (m_state.player->get_health() <= 0 || player_projectile_idx == PROJECTILE_COUNT) {
        lose_screen = true;
    }

}


void LevelA::render(ShaderProgram *program)
{
    if (lose_screen) {
        Mix_HaltMusic();
        Utility::draw_text(program, m_font, std::string("Game Over!"), 2.8f, -0.8f, glm::vec3(-10.0f, 0.0f, 0.0f));
        if (!ping[9]) {
            Mix_PlayChannel(-1, m_state.lose_sfx, 0);
            ping[9] = true;
        }
    } else {
        m_state.background->render(program);
        m_state.player->render(program);
        
        
        std::stringstream ss;
        ss << std::fixed << std::setprecision(0) << m_state.player->get_experience();
        std::string exp = ss.str();
        
        float exp_x = m_state.player->get_position().x;
        float exp_y = m_state.player->get_position().y;
        if(m_state.player->get_position().x < 15.5){ exp_x = 15.5; }
        if(m_state.player->get_position().x > 34.5){ exp_x = 34.5; }
        if(m_state.player->get_position().y < -28.3){ exp_y = -28.3; }
        if(m_state.player->get_position().y > -13.7){ exp_y = -13.7; }
        Utility::draw_text(program, m_font, std::string("Experience: ") + exp, 1.3f, -0.6f, glm::vec3(exp_x - 17.0f, exp_y + 12.0f, 0.0f));
        
        std::stringstream ss2;
        ss2 << std::fixed << std::setprecision(0) << m_state.player->get_health();
        std::string health = ss2.str();
        
        float health_x = m_state.player->get_position().x;
        float health_y = m_state.player->get_position().y;
        if(m_state.player->get_position().x < 15.5){ health_x = 15.5; }
        if(m_state.player->get_position().x > 34.5){ health_x = 34.5; }
        if(m_state.player->get_position().y < -28.3){ health_y = -28.3; }
        if(m_state.player->get_position().y > -13.7){ health_y = -13.7; }
        Utility::draw_text(program, m_font, std::string("Health: ") + health, 1.3f, -0.6f, glm::vec3(health_x + 10.0f, health_y + 12.0f, 0.0f));
    
        for(int i = 0; i < ENEMY_COUNT; i ++){
            m_state.enemies[i].render(program);
        }
        for(int i = 0; i < PROJECTILE_COUNT; i++){
            m_state.player_projectiles[i].render(program);
            m_state.projectile_1[i].render(program);
        }
    }
}
