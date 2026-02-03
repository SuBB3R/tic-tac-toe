// new gcc  src/main.c -Wall -Wextra -o app -L .\src\raylib\lib -lraylib -lwinmm -lopengl32 -lgdi32
#include <stdio.h>
#include "raylib/include/raylib.h"
#define WIDTH 3
#define HEIGHT 3

typedef enum Figure{
    EMPTY = 0,
    CIRCLE,
    CROSS,
}Figure;
typedef struct Button {
    Rectangle rect;
    Figure figure;
}Button;

typedef struct GameState {
    bool is_game_active;
    bool is_circle_turn;
    int used_tiles;
    Button buttons[HEIGHT][WIDTH]; 
}GameState;

void reset_gamu(GameState *game_state)
{             
    printf("%i GAME RESET \n", game_state->is_game_active);
    game_state->is_game_active = true;
    game_state->used_tiles = 0;
    game_state->is_circle_turn = true;
    game_state->is_game_active = true;
    for(int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            game_state->buttons[y][x].figure = EMPTY;
        }
    }               
}

bool check_win(Button buttons[HEIGHT][WIDTH], Figure figure_to_check)
{
    if(buttons[0][0].figure == figure_to_check && buttons[0][1].figure == figure_to_check && buttons[0][2].figure == figure_to_check )
    {
        return true;
    }
    if(buttons[1][0].figure == figure_to_check && buttons[1][1].figure == figure_to_check && buttons[1][2].figure == figure_to_check )
    {
        return true;
    }
    if(buttons[2][0].figure == figure_to_check && buttons[2][1].figure == figure_to_check && buttons[2][2].figure == figure_to_check )
    {
        return true;
    }
    if(buttons[0][0].figure == figure_to_check && buttons[1][0].figure == figure_to_check && buttons[2][0].figure == figure_to_check )
    {
        return true;
    }
    if(buttons[0][1].figure == figure_to_check && buttons[1][1].figure == figure_to_check && buttons[2][1].figure == figure_to_check )
    {
        return true;
    }
    if(buttons[0][2].figure == figure_to_check && buttons[1][2].figure == figure_to_check && buttons[2][2].figure == figure_to_check )
    {
        return true;
    }
    if(buttons[0][0].figure == figure_to_check && buttons[1][1].figure == figure_to_check && buttons[2][2].figure == figure_to_check )
    {
        return true;
    }
    if(buttons[0][2].figure == figure_to_check && buttons[1][1].figure == figure_to_check && buttons[2][0].figure == figure_to_check )
    {
        return true;
    }
    return false;
}

int main()
{
    
    GameState game_state;
    reset_gamu(&game_state);
    const float rect_size = 200;
    InitWindow(900, 900, "TIC TAC TOE");
    SetTargetFPS(60);
    Texture2D texture_circle = LoadTexture("assets/textures/circle.png");
    Texture2D texture_cross = LoadTexture("assets/textures/cross.png");
    Texture2D texture_restart = LoadTexture("assets/textures/restart.png");
    int margin = 10;
    Vector2 mouse_pos;
    Rectangle reset_button_rect;
    reset_button_rect.height = 200;
    reset_button_rect.width = 200;
    reset_button_rect.x = 220;
    reset_button_rect.y = 640;

    for(int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            game_state.buttons[y][x].rect = (Rectangle){
                margin * x + rect_size * x + margin,
                margin * y + rect_size * y + margin,
                rect_size,
                rect_size
            }; 
            
        }
    }
        
    while (!WindowShouldClose())
    {
        
        mouse_pos = GetMousePosition();
        BeginDrawing();
            ClearBackground(GRAY);
            bool circle_won =  check_win(game_state.buttons, CIRCLE);
            bool cross_won = check_win(game_state.buttons, CROSS);
            if(circle_won == true && game_state.is_game_active == true)
            {
                printf("Kolko wygralo \n");
                game_state.is_game_active = false;
            }
            if(cross_won == true && game_state.is_game_active == true)
            {
                printf("Krzyzyk wygral \n");
                game_state.is_game_active = false;
                
            }
            if(game_state.used_tiles == 9 && game_state.is_game_active == true)
            {
                printf("Remis \n");
                game_state.is_game_active = false;
            }
            
            for(int y = 0; y < HEIGHT; y++)
            {
               
                for(int x = 0; x < WIDTH; x++)
                {
                    
                    Color button_color = {255, 255, 255, 255};
                    bool mouse_is_hovered = CheckCollisionPointRec(mouse_pos, game_state.buttons[y][x].rect);
                    if(mouse_is_hovered == true && game_state.buttons[y][x].figure == EMPTY && game_state.is_game_active == true)
                    {
                        button_color =(Color){240, 240, 240, 255};
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true)
                        {
                            if(game_state.is_circle_turn == true)
                            {
                                printf("Tura krzyzyka \n");
                                game_state.buttons[y][x].figure = CIRCLE;
                                game_state.used_tiles = game_state.used_tiles + 1;
                            }
                            else
                            {
                                printf("Tura kolka \n");

                                game_state.buttons[y][x].figure = CROSS;
                                printf("Jebac Anke  %i %i\n", y, x);
                                game_state.used_tiles = game_state.used_tiles + 1;
                            }
                            game_state.is_circle_turn = !game_state.is_circle_turn;
                        }  
                    }
                    bool mouse_is_hovered_for_reset = CheckCollisionPointRec(mouse_pos, reset_button_rect);
                    if(mouse_is_hovered_for_reset == true  && game_state.is_game_active == false && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true)
                    {
                        reset_gamu(&game_state);                      
                    }
                    DrawRectangleRec(game_state.buttons[y][x].rect, button_color);
                    if(game_state.buttons[y][x].figure == CIRCLE)
                    {
                        DrawTextureEx(texture_circle, (Vector2){game_state.buttons[y][x].rect.x, game_state.buttons[y][x].rect.y}, 0,game_state.buttons[y][x].rect.width / texture_circle.width , ORANGE);
                        
                    }
                    if(game_state.buttons[y][x].figure == CROSS)
                    {
                        DrawTextureEx(texture_cross, (Vector2){game_state.buttons[y][x].rect.x, game_state.buttons[y][x].rect.y}, 0,game_state.buttons[y][x].rect.width / texture_cross.width , ORANGE);
                        
                    }
                    if(game_state.is_game_active == false && game_state.buttons[y][x].figure != EMPTY)
                    {
                        DrawTextureEx(texture_restart, (Vector2){reset_button_rect.x, reset_button_rect.y}, 0,reset_button_rect.width / reset_button_rect.height, LIGHTGRAY);
                    }                    
                } 
            }
            
            DrawText(TextFormat("Mouse X:%.0f Y:%.0f", mouse_pos.x, mouse_pos.y), mouse_pos.x, mouse_pos.y, 45, DARKBLUE);
            
        DrawFPS(10, 10);  
        EndDrawing();
    }


    CloseWindow();
    
}