#include "raylib.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "raylib [core] example - basic screen manager");

  GameScreen currentScreen = GAMEPLAY;

  // TODO: Initialize all required variables and load all required data here!
  Rectangle player = {400, 280, 40, 40};

  Camera2D camera = {0};
  camera.target = (Vector2){player.x + 20.0f, player.y + 20.0f};
  camera.offset = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    switch (currentScreen) {
    case LOGO: {
      // TODO: Update LOGO screen variables here!
    } break;
    case TITLE: {
      // TODO: Update TITLE screen variables here!
    } break;
    case GAMEPLAY: {
      // TODO: Update GAMEPLAY screen variables here!
      if (IsKeyDown(KEY_RIGHT))
        player.x += 2;
      else if (IsKeyDown(KEY_LEFT))
        player.x -= 2;
      else if (IsKeyDown(KEY_UP))
        player.y += 2;
      else if (IsKeyDown(KEY_DOWN))
        player.y -= 2;

      camera.target = (Vector2){player.x + 20, player.y + 20};
    } break;
    case ENDING: {
      // TODO: Update ENDING screen variables here!
    } break;
    default:
      break;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (currentScreen) {
    case LOGO: {
      // TODO: Draw LOGO screen here!
    } break;
    case TITLE: {
      // TODO: Draw TITLE screen here!
    } break;
    case GAMEPLAY: {
      // TODO: Draw GAMEPLAY screen here!
      BeginMode2D(camera);

      DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
      DrawRectangle(600, 320, 50, 50, GREEN);

      DrawRectangleRec(player, RED);

      EndMode2D();
    } break;
    case ENDING: {
      // TODO: Draw ENDING screen here!
    } break;
    default:
      break;
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------

  // TODO: Unload all loaded data (textures, fonts, audio) here!

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
