/**
* Author: Max Vega
* Assignment: Platformer
* Date due: 2024-04-13, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Menu.h"
#include "Utility.h"

#define MENU_WIDTH 1
#define MENU_HEIGHT 1

unsigned int MENU_DATA[] = { 0 };

GLuint m_font_texture_id;

Menu::~Menu()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.background;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void Menu::initialise()
{
    // ————— MAP SET-UP ————— //
    GLuint map_texture_id = Utility::load_texture("assets/images/tilemap_packed.png");
    m_state.map = new Map(MENU_WIDTH, MENU_HEIGHT, MENU_DATA, map_texture_id, 1.0f, 4, 1);
    
    // ————— FONT SET-UP ————— //
    m_font_texture_id = Utility::load_texture("assets/images/font1.png");
    
    // ————— BACKGROUND SET-UP ————— //
    m_state.background = new Entity();
    m_state.background->set_health(10000);
    m_state.background->set_position(glm::vec3(18.0f, -13.0f, 0.0f));
    m_state.background->set_size(glm::vec3(37.0f, 27.0f, 0.0f));
    m_state.background->m_texture_id = Utility::load_texture("assets/images/VentureBG.png");
    m_state.background->update(0.0f, m_state.background, NULL, 0, m_state.map);
    
    // ————— PLAYER SET-UP ————— //
    m_state.player = new Entity();
    
    // ————— MUSIC AND SFX SET-UP ————— //
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/audio/titlescreen.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
}

void Menu::update(float delta_time)
{
    
}


void Menu::render(ShaderProgram *program)
{
    m_state.background->render(program);
    m_state.map->render(program);
    Utility::draw_text(program, m_font_texture_id, std::string("Press Enter to Start"), 2.0f, -0.7f, glm::vec3(6.0f, -22.0f, 0.0f));

}
