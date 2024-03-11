/**
* Author: Max Vega
* Assignment: Lunar Lander
* Date due: 2024-03-09, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#define LOG(argument) std::cout << argument << '\n'
#define STB_IMAGE_IMPLEMENTATION
#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define NUMBER_OF_ENEMIES 3
#define BORDER_COUNT 1

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "stb_image.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.hpp"

// Constants
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 820;
const int PLATFORM_COUNT = 4;
const int FONTBANK_SIZE = 16;
const float FIXED_TIMESTEP = 0.0166666f;
const float ACC_OF_GRAVITY = -9.81f;
const char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";
const char BACKGROUND_FILEPATH[] = "assets/background.png",
           PLATFORM_FILEPATH[] = "assets/tree.png",
           SPRITESHEET_FILEPATH[] = "assets/emolga_sheet.png",
           FONT_FILEPATH[] = "assets/font1.png";
const float MILLISECONDS_IN_SECOND = 1000.0;

// Structs and Enums
struct GameState {
    Entity* background;
    Entity* player;
    Entity* platforms;
};

// Global Variables
GameState g_game_state;
SDL_Window* g_display_window;
bool g_game_is_running = true;
ShaderProgram g_shader_program;
GLuint g_font_texture_id, g_emolga_id;
glm::mat4 g_view_matrix, g_projection_matrix;
float g_previous_ticks = 0.0f;
float g_time_accumulator = 0.0f;
bool is_left = true;

// Function Prototypes
void initialise();
void process_input();
void update();
void render();
void shutdown();

int main(int argc, char* argv[]) {
    initialise();

    while (g_game_is_running) {
        process_input();
        update();
        render();
    }

    shutdown();
    return 0;
}

// Function to load a texture from file
GLuint load_texture(const char* filepath) {
    int width, height, number_of_components;
    unsigned char* image = stbi_load(filepath, &width, &height, &number_of_components, STBI_rgb_alpha);

    if (image == NULL) {
        LOG("Unable to load image. Make sure the path is correct.");
        assert(false);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(image);

    return textureID;
}

// Function to draw text on the screen
void draw_text(ShaderProgram *program, GLuint font_texture_id, std::string text, float screen_size, float spacing, glm::vec3 position)
{
    float width = 1.0f / FONTBANK_SIZE;
    float height = 1.0f / FONTBANK_SIZE;

    std::vector<float> vertices;
    std::vector<float> texture_coordinates;

    for (int i = 0; i < text.size(); i++) {
        int spritesheet_index = (int) text[i];
        float offset = (screen_size + spacing) * i;
        
        float u_coordinate = (float) (spritesheet_index % FONTBANK_SIZE) / FONTBANK_SIZE;
        float v_coordinate = (float) (spritesheet_index / FONTBANK_SIZE) / FONTBANK_SIZE;

        vertices.insert(vertices.end(), {
            offset + (-0.5f * screen_size), 0.5f * screen_size,
            offset + (-0.5f * screen_size), -0.5f * screen_size,
            offset + (0.5f * screen_size), 0.5f * screen_size,
            offset + (0.5f * screen_size), -0.5f * screen_size,
            offset + (0.5f * screen_size), 0.5f * screen_size,
            offset + (-0.5f * screen_size), -0.5f * screen_size,
        });

        texture_coordinates.insert(texture_coordinates.end(), {
            u_coordinate, v_coordinate,
            u_coordinate, v_coordinate + height,
            u_coordinate + width, v_coordinate,
            u_coordinate + width, v_coordinate + height,
            u_coordinate + width, v_coordinate,
            u_coordinate, v_coordinate + height,
        });
    }

    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, position);
    
    program->set_model_matrix(model_matrix);
    glUseProgram(program->get_program_id());
    
    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices.data());
    glEnableVertexAttribArray(program->get_position_attribute());
    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texture_coordinates.data());
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());
    
    glBindTexture(GL_TEXTURE_2D, font_texture_id);
    glDrawArrays(GL_TRIANGLES, 0, (int) (text.size() * 6));
    
    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

// Function Definitions
void initialise() {
    // SDL Initialization
    SDL_Init(SDL_INIT_VIDEO);
    g_display_window = SDL_CreateWindow("Emolga Drop!",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        WINDOW_WIDTH, WINDOW_HEIGHT,
                                        SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);

#ifdef _WINDOWS
    glewInit();
#endif

    // OpenGL Initialization
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Shader Program Initialization
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);

    // Font Texture Initialization
    g_font_texture_id = load_texture(FONT_FILEPATH);

    // Background Initialization
    g_game_state.background = new Entity();
    g_game_state.background->set_position(glm::vec3(0.0f));
    g_game_state.background->set_size(glm::vec3(12.0f, 8.0f, 0.0f));
    g_game_state.background->m_texture_id = load_texture(BACKGROUND_FILEPATH);
    g_game_state.background->update(0.0f, NULL, 0);

    // Player Initialization
    g_game_state.player = new Entity();
    g_game_state.player->set_position(glm::vec3(0.0f, 3.5f, 0.0f));
    g_game_state.player->set_movement(glm::vec3(0.0f));
    g_game_state.player->set_acceleration(glm::vec3(0.0f, ACC_OF_GRAVITY * 0.01, 0.0f));
    g_game_state.player->set_speed(1.0f);
    g_game_state.player->set_score(100);
    g_game_state.player->set_size(glm::vec3(0.5f, 0.5f, 0.0f));
    g_game_state.player->m_texture_id = load_texture(SPRITESHEET_FILEPATH);
    g_game_state.player->m_walking[g_game_state.player->LEFT] = new int[2] {0, 1};
    g_game_state.player->m_walking[g_game_state.player->RIGHT] = new int[2] {1, 0};
    g_game_state.player->m_animation_indices = g_game_state.player->m_walking[g_game_state.player->LEFT];
    g_game_state.player->m_animation_frames = 2;
    g_game_state.player->m_animation_index = 0;
    g_game_state.player->m_animation_time = 0.0f;
    g_game_state.player->m_animation_cols = 2;
    g_game_state.player->m_animation_rows = 1;
    g_game_state.player->update(0.0f, NULL, 0);

    // Trees Initialization
    g_game_state.platforms = new Entity[PLATFORM_COUNT];
    glm::vec3 g_platform_locations[] = {glm::vec3(-4.0f, -2.6f, 0.0f),
                                        glm::vec3(0.5f, -4.0f, 0.0f),
                                        glm::vec3(4.0f, -4.0f, 0.0f)};
    
    float g_platform_scores[] = {1.5f, 1.0f, 2.0f};
    
    // Tree 1
    g_game_state.platforms[0].set_size(glm::vec3(2.0f, 2.8f, 0.0f));
    g_game_state.platforms[0].set_position(g_platform_locations[0]);
    g_game_state.platforms[0].set_score(g_platform_scores[0]);
    g_game_state.platforms[0].set_type("platform");
    g_game_state.platforms[0].m_texture_id = load_texture(PLATFORM_FILEPATH);
    g_game_state.platforms[0].update(0.0f, NULL, 0);
    
    
    // Tree 2
    g_game_state.platforms[1].set_size(glm::vec3(2.5f, 2.5f, 0.0f));
    g_game_state.platforms[1].set_position(g_platform_locations[1]);
    g_game_state.platforms[1].set_score(g_platform_scores[1]);
    g_game_state.platforms[1].set_type("platform");
    g_game_state.platforms[1].m_texture_id = load_texture(PLATFORM_FILEPATH);
    g_game_state.platforms[1].update(0.0f, NULL, 0);
    
    
    // Tree 3
    g_game_state.platforms[2].set_size(glm::vec3(1.0f, 1.5f, 0.0f));
    g_game_state.platforms[2].set_position(g_platform_locations[2]);
    g_game_state.platforms[2].set_score(g_platform_scores[2]);
    g_game_state.platforms[2].set_type("platform");
    g_game_state.platforms[2].m_texture_id = load_texture(PLATFORM_FILEPATH);
    g_game_state.platforms[2].update(0.0f, NULL, 0);
    
    
    // Base (bottom edge of screen)
    g_game_state.platforms[3].set_position(glm::vec3(0.0f, -4.5f, 0.0f));
    g_game_state.platforms[3].set_size(glm::vec3(20.0f, 0.0f, 0.0f));
    g_game_state.platforms[3].set_type("edge");
    g_game_state.platforms[3].update(0.0f, NULL, 0);

    // General OpenGL Settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void process_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_game_is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        g_game_is_running = false;
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }

    const Uint8* key_state = SDL_GetKeyboardState(NULL);

    // Reset acceleration if no arrow keys are pressed
    if (!key_state[SDL_SCANCODE_LEFT] && !key_state[SDL_SCANCODE_RIGHT]) {
        g_game_state.player->set_acceleration(glm::vec3(0.0f, ACC_OF_GRAVITY * 0.01, 0.0f));
    }

    // Apply acceleration based on arrow key presses
    if (g_game_state.player->get_score() > 0) {
        if (key_state[SDL_SCANCODE_LEFT]) {
            g_game_state.player->move_left();
            is_left = true;
            g_game_state.player->m_animation_indices = g_game_state.player->m_walking[g_game_state.player->LEFT];
        } else if (key_state[SDL_SCANCODE_RIGHT]) {
            g_game_state.player->move_right();
            is_left = false;
            g_game_state.player->m_animation_indices = g_game_state.player->m_walking[g_game_state.player->RIGHT];
        }
    }
    // Normalize movement if moving diagonally
    if (glm::length(g_game_state.player->get_movement()) > 1.0f) {
        g_game_state.player->set_movement(glm::normalize(g_game_state.player->get_movement()));
    }
}

void update() {
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    delta_time += g_time_accumulator;
    if (delta_time < FIXED_TIMESTEP) {
        g_time_accumulator = delta_time;
        return;
    }

    while (delta_time >= FIXED_TIMESTEP) {
        if (g_game_state.player->get_collision() == "") {
            g_game_state.player->update(FIXED_TIMESTEP, g_game_state.platforms, PLATFORM_COUNT);
        }
        delta_time -= FIXED_TIMESTEP;
    }
    g_time_accumulator = delta_time;
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    g_game_state.background->render(&g_shader_program);
    g_game_state.player->render(&g_shader_program);
    
    if (!is_left){
        g_game_state.player->draw_sprite_from_texture_atlas(&g_shader_program, g_emolga_id, 1);
    }
    if (is_left){
        g_game_state.player->draw_sprite_from_texture_atlas(&g_shader_program, g_emolga_id, 0);
    }

    if (g_game_state.player->get_collision() == "") {
        g_game_state.player->render(&g_shader_program);
        for (int i = 0; i < PLATFORM_COUNT; i++) g_game_state.platforms[i].render(&g_shader_program);
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << g_game_state.player->get_score();
        std::string score = ss.str();
        draw_text(&g_shader_program, g_font_texture_id, std::string("Energy:") + score, 0.4f, -0.15f, glm::vec3(1.65f, 3.5f, 0.0f));
    }
    
    if (g_game_state.player->get_collision() == "platform") {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << g_game_state.player->get_score();
        std::string score = ss.str();
        draw_text(&g_shader_program, g_font_texture_id, std::string("Score:") + score, 0.8f, -0.3f, glm::vec3(-2.4f, -0.5f, 0.0f));
        draw_text(&g_shader_program, g_font_texture_id, std::string("Vctory!"),0.8f, -0.3f, glm::vec3(-1.65f, 0.5f, 0.0f));
    }
    
    if (g_game_state.player->get_collision() == "edge") {
        draw_text(&g_shader_program, g_font_texture_id, std::string("Game Over!"),
                  0.8f, -0.3f, glm::vec3(-1.85f, 0.0f, 0.0f));
    }

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown() {
    delete g_game_state.background;
    delete g_game_state.player;
    delete[] g_game_state.platforms;
    SDL_Quit();
}


