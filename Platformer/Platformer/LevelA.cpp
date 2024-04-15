#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 37
#define LEVEL_HEIGHT 29
#define MAX_HEALTH 3

GLuint m_font;

unsigned int LEVEL_A_DATA[] =
{
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    24,62,62,62,62,62,62,62,62,62,62,62,62,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    122,122,122,122,122,122,122,122,122,4,142,142,143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    122,122,122,122,122,122,122,4,142,143,0,0,0,0,0,0,47,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    122,122,122,122,122,4,142,143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    4,142,142,142,142,143,0,0,0,0,0,0,0,0,0,0,0,0,41,62,62,62,62,62,62,43,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,142,142,142,142,143,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,47,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,47,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,61,62,62,62,62,62,62,62,25,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,121,122,122,122,122,122,122,122,122,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,61,62,62,62,25,122,122,122,122,122,122,122,122,
    24,62,62,62,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,121,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,24,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,25,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122
};


LevelA::~LevelA()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelA::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/images/tilemap_packed.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_A_DATA, map_texture_id, 1.0f, 20, 9);
    
    // ————— FONT SET-UP ————— //
    m_font = Utility::load_texture("assets/images/font1.png");
    
    // ————— BACKGROUND SET-UP ————— //
    m_state.background = new Entity();
    m_state.background->set_health(1000);
    m_state.background->set_position(glm::vec3(15.0f, -13.0f, 0.0f));
    m_state.background->set_size(glm::vec3(45.0f, 30.0f, 0.0f));
    m_state.background->m_texture_id = Utility::load_texture("assets/images/cave.png");
    m_state.background->update(0.0f, m_state.background, NULL, 0, m_state.map);
    
    // ————— PLAYER SET-UP ————— //
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.4f, -18.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(3.5f);
    m_state.player->set_health(MAX_HEALTH);
    m_state.player->set_acceleration(glm::vec3(0.0f, -11.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/images/ClefairySpriteSheet.png");

    // Walking
    m_state.player->m_walking[m_state.player->LEFT] = new int[2] { 0, 1 };
    m_state.player->m_walking[m_state.player->RIGHT] = new int[2] { 2, 3 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 2;
    m_state.player->m_animation_index = 0;
    m_state.player->m_animation_time = 0.0f;
    m_state.player->m_animation_cols = 2;
    m_state.player->m_animation_rows = 2;
    m_state.player->set_height(0.8f);
    m_state.player->set_width(0.8f);
    m_state.player->set_size(glm::vec3(1.3f * 1.3, 2.0f * 1.4, 0.0f));

    // Jumping
    m_state.player->m_jumping_power = 7.0f;
    
    m_state.enemies = new Entity[ENEMY_COUNT];
    
    // ————— RATATA SET-UP (index 0) ————— //
    // Existing
    m_state.enemies[0].set_position(glm::vec3(17.0f, -18.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(1.5f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -11.81f, 0.0f));
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_ai_type(RATATA);
    m_state.enemies[0].set_health(1);
    m_state.enemies[0].m_texture_id = Utility::load_texture("assets/images/RatataSpriteSheet.png");
    
    // Walking
    m_state.enemies[0].m_walking[m_state.enemies[0].LEFT]     = new int[2] { 0, 1};
    m_state.enemies[0].m_walking[m_state.enemies[0].RIGHT]    = new int[2] { 2, 3};
    
    m_state.enemies[0].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].LEFT];
    m_state.enemies[0].m_animation_frames = 2;
    m_state.enemies[0].m_animation_index = 0;
    m_state.enemies[0].m_animation_time = 0.0f;
    m_state.enemies[0].m_animation_cols = 2;
    m_state.enemies[0].m_animation_rows = 2;
    m_state.enemies[0].set_height(0.8f);
    m_state.enemies[0].set_width(0.8f);
    m_state.enemies[0].set_size(glm::vec3(1.3f * 1.4, 2.0f * 1.3, 0.0f));
    
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_state.bgm = Mix_LoadMUS("assets/audio/CaveBGM.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    m_state.jump_sfx = Mix_LoadWAV("assets/audio/Jump.mp3");
}

void LevelA::update(float delta_time)
{
    if (m_state.player->get_health() <= 0) return;
    
    if (m_state.player->get_position().y > -18.0f && m_state.player->get_position().x < 1.0f) {
        if(m_state.enemies[0].get_health() == 0) {m_state.next_scene_id = 1;}
    }
    
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    m_state.enemies[0].update(delta_time, m_state.player, NULL, NULL, m_state.map);

}


void LevelA::render(ShaderProgram *program)
{
    if (m_state.player->get_health() <= 0) {
        Utility::draw_text(program, m_font, std::string("Game Over!"), 2.8f, -0.8f, glm::vec3(4.5f, -10.0f, 0.0f));
    } else {
        m_state.background->render(program);
        m_state.map->render(program);
        m_state.player->render(program);
        m_state.enemies[0].render(program);
    }
}
