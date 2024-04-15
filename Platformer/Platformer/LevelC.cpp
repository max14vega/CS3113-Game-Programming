#include "LevelC.h"
#include "Utility.h"

#define LEVEL_WIDTH 37
#define LEVEL_HEIGHT 29
#define MAX_HEALTH 3

GLuint m_font_c;
bool winner = false;

unsigned int LEVEL_C_DATA[] =
{
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,141,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,122,
    143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,122,
    24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,122,
    122,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    122,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    122,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,63,0,0,0,0,0,0,0,0,0,0,0,0,0,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,24,62,62,62,62,62,62,62,62,62,62,62,62,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,
    122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122
};


LevelC::~LevelC()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeChunk(m_state.victory_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelC::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/images/tilemap_packed.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_C_DATA, map_texture_id, 1.0f, 20, 9);
    
    // ————— FONT SET-UP ————— //
    m_font_c = Utility::load_texture("assets/images/font1.png");
    
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
    m_state.player->set_position(glm::vec3(35.0f, -23.38f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(3.5f);
    m_state.player->set_health(1000);
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
    // Existing
    m_state.enemies[0].set_position(glm::vec3(1.3f, -13.38f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(1.5f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -11.81f, 0.0f));
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_ai_type(MAGBY);
    m_state.enemies[0].set_ai_state(IDLE);
    m_state.enemies[0].set_health(3);
    m_state.enemies[0].m_texture_id = Utility::load_texture("assets/images/MagbySpriteSheet.png");
    
    // Walking
    m_state.enemies[0].m_walking[m_state.enemies[0].RIGHT]   = new int[2] { 0, 1 };
    m_state.enemies[0].m_walking[m_state.enemies[0].LEFT]    = new int[2] { 2, 3 };
    
    m_state.enemies[0].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].RIGHT];
    m_state.enemies[0].m_animation_frames = 2;
    m_state.enemies[0].m_animation_index = 0;
    m_state.enemies[0].m_animation_time = 0.0f;
    m_state.enemies[0].m_animation_cols = 2;
    m_state.enemies[0].m_animation_rows = 2;
    m_state.enemies[0].set_height(0.8f);
    m_state.enemies[0].set_width(0.8f);
    m_state.enemies[0].set_size(glm::vec3(1.3f * 1.4, 2.0f * 1.3, 0.0f));
    
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/audio/CaveBGM.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/audio/Jump.mp3");
    m_state.victory_sfx = Mix_LoadWAV("assets/audio/Victory.mp3");
}

void LevelC::update(float delta_time)
{
    if (m_state.player->get_health() <= 0) return;
    
    if(m_state.enemies[0].get_health() == 0) {winner = true;}
    
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    m_state.enemies[0].update(delta_time, m_state.player, NULL, NULL, m_state.map);
}


void LevelC::render(ShaderProgram *program)
{
    if (m_state.player->get_health() <= 0) {
        Utility::draw_text(program, m_font_c, std::string("Game Over!"), 2.8f, -0.8f, glm::vec3(11.5f, -15.0f, 0.0f));
    } else if (winner){
        Utility::draw_text(program, m_font_c, std::string("You Win!"), 2.8f, -0.8f, glm::vec3(11.5f, -15.0f, 0.0f));
        Mix_HaltMusic();
        Mix_PlayChannel(-1, m_state.victory_sfx, 0);
    } else {
        m_state.background->render(program);
        m_state.map->render(program);
        m_state.player->render(program);
        m_state.enemies[0].render(program);
    }
}
