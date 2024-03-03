/**
* Author: Max Vega
* Assignment: Pong Clone
* Date due: 2024-03-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#define LOG(argument) std::cout << argument << '\n'

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "stb_image.h"
#include <iostream>
#include <time.h>

using namespace std;

const int WINDOW_WIDTH = 640,
          WINDOW_HEIGHT = 480;

float BG_RED = 0.0f,
      BG_BLUE = 0.0f,
      BG_GREEN = 0.0f,
      BG_OPACITY = 1.0f;

const int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

const char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

const float MILLISECONDS_IN_SECOND = 1000.0;
float g_previous_ticks = 0.0f;

const int NUMBER_OF_TEXTURES = 1; // to be generated, that is
const GLint LEVEL_OF_DETAIL = 0;  // base image level; Level n is the nth mipmap reduction image
const GLint TEXTURE_BORDER = 0;   // this value MUST be zero

const char BALL_SPRITE[] = "assets/poke.png",
           PLAYER_SPRITE[] = "assets/ash.png",
           ENEMY_SPRITE[] = "assets/rocket.png";

GLuint ball_id;
GLuint ash_id;
GLuint rocket_id;

SDL_Window* g_display_window;
bool g_game_is_running = true;

ShaderProgram g_shader_program;

int winner = -1;
int p1_score, p2_score = 0;

void printScore() {
    cout << "\n````````````````````````````````\n";
    cout << "\t\t P1: " << p1_score << "\t";
    cout << "P2: " << p2_score << "\n";
    cout << "````````````````````````````````\n\n";
}

// Important Globals
glm::mat4 g_view_matrix, g_projection_matrix, g_ash_model_matrix, g_rocket_model_matrix, g_ball_model_matrix, g_ball_2_model_matrix, g_ball_3_model_matrix;

// Ball Initialization
glm::vec3 g_ball_pos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 g_ball_mov = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 g_ball_2_pos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 g_ball_2_mov = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 g_ball_3_pos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 g_ball_3_mov = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 g_ball_scale = glm::vec3(0.75f, 0.75f, 1.0f);

float ball_height = 1.0f * g_ball_scale.y;
float ball_width = 1.0f * g_ball_scale.x;

float ball_speed = 5.0f;
int g_num_balls = 12;
bool ball_path_reversed = false;

bool is_auto = false;
bool is_extra_balls = false;


glm::vec3 g_player_pos = glm::vec3(-4.5, 0.0f, 0.0f);
glm::vec3 g_player_mov = glm::vec3(0.0f, 0.0f, 0.0f);
float g_player_speed = 3.85f;

glm::vec3 g_enemy_pos = glm::vec3(4.5, 0.0f, 0.0f);
glm::vec3 g_enemy_mov = glm::vec3(0.0f, 0.0f, 0.0f);
float g_enemy_speed = 3.85f;

glm::vec3 p_scale = glm::vec3(0.65f, 2.55f, 1.0f);
float p_height = 1.0f * p_scale.y;
float p_width = 1.0f * p_scale.x;

GLuint load_texture(const char* filepath){
    //loading the image file
    int width, height, num_components;
    unsigned char* image = stbi_load(filepath, &width, &height, &num_components, STBI_rgb_alpha);
    
    if (image == NULL){
        LOG("Unable to load image. Make sure the path is correct.");
        LOG(filepath);
        assert(false);
    }
    
    //generating and binding a texture ID to our image
    GLuint textureID;
    glGenTextures(NUMBER_OF_TEXTURES, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, LEVEL_OF_DETAIL, GL_RGBA, width, height, TEXTURE_BORDER, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    // STEP 3: Setting our texture filter parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // STEP 4: Releasing our file from memory and returning our texture id
    stbi_image_free(image);
    
    return textureID;
}

void initialise()
{
    // Initialise video and joystick subsystems
    SDL_Init(SDL_INIT_VIDEO);
    
    g_display_window = SDL_CreateWindow("Team Rocket Rally!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    
    g_view_matrix = glm::mat4(1.0f);  // Defines the position (location and orientation) of the camera
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);  // Defines the characteristics of your camera, such as clip planes, field of view, projection method etc.
    
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);

    
    glUseProgram(g_shader_program.get_program_id());
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
    
    ball_id = load_texture(BALL_SPRITE);
    ash_id = load_texture(PLAYER_SPRITE);
    rocket_id = load_texture(ENEMY_SPRITE);
    
    
    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


bool is_touching_top(glm::vec3 position, float height, float top) {
    return !((position.y + (height / 2.0f)) < top);
}

bool is_touching_bottom(glm::vec3 position, float height, float bottom) {
    return !((position.y - (height / 2.0f)) > bottom);
}

void process_input() {
    g_player_mov = glm::vec3(0.0f);
    g_enemy_mov = glm::vec3(0.0f);
    
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                
            case SDL_WINDOWEVENT_CLOSE:
                g_game_is_running = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        break;
                    case SDLK_q:
                        g_game_is_running = false;
                        break;
                    case SDLK_t:
                        is_auto = not is_auto;
                        break;
                    case SDLK_1:
                       g_num_balls = 1;
                       break;
                   case SDLK_2:
                       g_num_balls = 2;
                       break;
                   case SDLK_3:
                       g_num_balls = 3;
                       break;
                }
                break;
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    // Ball
    if (keys[SDL_SCANCODE_SPACE]) {
        int slope = (rand() % 3) - 1;  // ~ randomizing play ~
        g_ball_mov.x = 1.0f * slope;
        g_ball_mov.y = 1.0f * slope;
    }
    if (glm::length(g_ball_mov) > 1.0f) {
        g_ball_mov = glm::normalize(g_ball_mov);
    }
    
    // Paddle 1
    if ((keys[SDL_SCANCODE_W]) && !is_touching_top(g_player_pos, p_height, 3.7f)) {
        g_player_mov.y = 1.0f;
    } else if ((keys[SDL_SCANCODE_S]) && !is_touching_bottom(g_player_pos, p_height, -3.7f)) {
        g_player_mov.y = -1.0f;
    }
    if (glm::length(g_player_mov) > 1.0f) {
        g_player_mov = glm::normalize(g_player_mov);
    }
    
    if(!is_auto){
        if ((keys[SDL_SCANCODE_UP]) && !is_touching_top(g_enemy_pos, p_height, 3.7f)) {
            g_enemy_mov.y = 1.0f;
        } else if ((keys[SDL_SCANCODE_DOWN]) && !is_touching_bottom(g_enemy_pos, p_height, -3.7f)) {
            g_enemy_mov.y = -1.0f;
        }
        if (glm::length(g_enemy_mov) > 1.0f) {
            g_enemy_mov = glm::normalize(g_enemy_mov);
        }
    } else {
        glm::vec3 ball_position = g_ball_pos;

        float rand_value = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random value between 0 and 1
        //giving the AI a 70% chance to respond correctly to the balls position
        if (rand_value < 0.7) {
            float vertical_distance = ball_position.y - g_enemy_pos.y + 0.5f;
            
            if (vertical_distance > 0 && !is_touching_top(g_enemy_pos, p_height, 3.7f)) {
                g_enemy_mov.y = 1.0f;
            } else if (vertical_distance < 0 && !is_touching_bottom(g_enemy_pos, p_height, -3.7f)) {
                g_enemy_mov.y = -1.0f;
            } else {
                g_enemy_mov.y = 0.0f;
            }
        } else {
            g_enemy_mov.y = static_cast<float>(rand() % 3 - 1); // Random value between -1 and 1
        }

        // Normalize movement vector if necessary
        if (glm::length(g_enemy_mov) > 1.0f) {
            g_enemy_mov = glm::normalize(g_enemy_mov);
        }
    }
}

bool is_colliding(glm::vec3 ball_pos, glm::vec3 player_pos) {
    
    // Ball Info
    float x_1 = ball_pos.x;
    float y_1 = ball_pos.y;
    
    float w_1 = ball_width - 0.2f;
    float h_1 = ball_height - 0.2f;

    // Paddle Info
    float x_2 = player_pos.x;
    float y_2 = player_pos.y;
    
    float w_2 = p_width;
    float h_2 = p_height;

    float x_diff = fabs(x_2 - x_1);
    float y_diff = fabs(y_2 - y_1);

    float x_dist = x_diff - ((w_1 + w_2) / 2);
    float y_dist = y_diff - ((h_1 + h_2) / 2);

    return ((x_dist < 0) && (y_dist < 0));
}

bool is_past_paddles(glm::vec3 ball_position) {
    float right = 4.6f;
    float left = -4.6f;
    
    if (ball_position.x > right) {
        p1_score += 1;
        if (p1_score == 3)
            winner = 1;
        
        printScore();
        
        return true;
    }
    else if (ball_position.x < left) {
        p2_score += 1;
        if (p1_score == 3)
            winner = 2;
        
        printScore();
        
        return true;
    }
    return false;
}

void update() {
    if (is_past_paddles(g_ball_pos)) {
        if ((p1_score == 3) || (p2_score == 3))
            g_game_is_running = false;
        else
            g_ball_pos = glm::vec3(0, 0, 0);
    }
    
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    g_ball_model_matrix = glm::mat4(1.0f);

    g_player_pos += g_player_mov * g_player_speed * delta_time;
    g_ash_model_matrix = glm::mat4(1.0f);
    g_ash_model_matrix = glm::translate(g_ash_model_matrix, g_player_pos);
    g_ash_model_matrix = glm::scale(g_ash_model_matrix, p_scale);

    g_enemy_pos += g_enemy_mov * g_enemy_speed * delta_time;
    g_rocket_model_matrix = glm::mat4(1.0f);
    g_rocket_model_matrix = glm::translate(g_rocket_model_matrix, g_enemy_pos);
    g_rocket_model_matrix = glm::scale(g_rocket_model_matrix, p_scale);
    
    
    if(!is_extra_balls){
        if(g_num_balls >= 1){
            if ((is_touching_top(g_ball_pos, ball_height, 3.7f) || is_touching_bottom(g_ball_pos, ball_height, -3.7f))) {
                g_ball_mov.y *= -1.0f;
            }
            else if ((is_colliding(g_ball_pos, g_player_pos)) || (is_colliding(g_ball_pos, g_enemy_pos))) {
                g_ball_mov.x *= -1.0f;
            }
            g_ball_pos += g_ball_mov * ball_speed * delta_time;
            g_ball_model_matrix = glm::translate(g_ball_model_matrix, g_ball_pos);
            g_ball_model_matrix = glm::scale(g_ball_model_matrix, g_ball_scale);
        }
        
        if(g_num_balls >= 2){
            
            g_ball_2_model_matrix = glm::mat4(1.0f);
            if ((is_touching_top(g_ball_2_pos, ball_height, 3.7f) || is_touching_bottom(g_ball_2_pos, ball_height, -3.7f))) {
                g_ball_mov.y *= -1.0f;
            }
            else if ((is_colliding(g_ball_2_pos, g_player_pos)) || (is_colliding(g_ball_2_pos, g_enemy_pos))) {
                g_ball_mov.x *= -1.0f;
            }
            g_ball_2_pos += g_ball_2_mov * ball_speed * delta_time;
            g_ball_2_model_matrix = glm::translate(g_ball_2_model_matrix, g_ball_2_pos);
            g_ball_2_model_matrix = glm::scale(g_ball_2_model_matrix, g_ball_scale);
        }
        
        if(g_num_balls >= 3){
            
            g_ball_3_model_matrix = glm::mat4(1.0f);
            if ((is_touching_top(g_ball_3_pos, ball_height, 3.7f) || is_touching_bottom(g_ball_3_pos, ball_height, -3.7f))) {
                g_ball_3_mov.y *= -1.0f;
            }
            else if ((is_colliding(g_ball_3_pos, g_player_pos)) || (is_colliding(g_ball_3_pos, g_enemy_pos))) {
                g_ball_3_mov.x *= -1.0f;
            }
            g_ball_3_pos += g_ball_3_mov * ball_speed * delta_time;
            g_ball_3_model_matrix = glm::translate(g_ball_3_model_matrix, g_ball_3_pos);
            g_ball_3_model_matrix = glm::scale(g_ball_3_model_matrix, g_ball_scale);
        }
    }
}

void render_object(glm::mat4 model_matrix, GLuint textureID) {
    
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f
    };

    float texture_coordinates[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    };
    
    g_shader_program.set_model_matrix(model_matrix);
    
    glVertexAttribPointer(g_shader_program.get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(g_shader_program.get_position_attribute());
    glVertexAttribPointer(g_shader_program.get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texture_coordinates);
    glEnableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(g_shader_program.get_position_attribute());
    glDisableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    render_object(g_ball_model_matrix, ball_id);
    render_object(g_ash_model_matrix, ash_id);
    render_object(g_rocket_model_matrix, rocket_id);
    
    SDL_GL_SwapWindow(g_display_window);
}

void shutdown() {
    cout << "\n================================\n";
    cout << "\t\t Player " << winner << " wins!\n";
    cout << "\t\t Final Scores:\n";
    printScore();
    cout << " Thanks for playing, game over!\n";
    cout << "================================\n\n";
    SDL_Quit();
}

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
