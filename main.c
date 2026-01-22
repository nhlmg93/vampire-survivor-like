#include "raylib.h"
#include <stdio.h>

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define TILE_SRC 16
#define TILE_DST 48

static Rectangle tileSrc(int col, int row) {
  return (Rectangle){col * TILE_SRC, row * TILE_SRC, TILE_SRC, TILE_SRC};
}

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
  Texture2D dungeon = LoadTexture("dungeon_sheet.png");
  SetTextureFilter(dungeon, TEXTURE_FILTER_POINT);
  // DEBUG
  const int cols = dungeon.width / TILE_SRC;
  const int rows = dungeon.height / TILE_SRC;
  static int tileIndex = 190;

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

      Vector2 worldPos = (Vector2){600, 320};

      DrawRectanglePro((Rectangle){worldPos.x, worldPos.y, 100, 100},
                       (Vector2){50, 50}, 0.0f, GREEN);

      Rectangle src = tileSrc(tileIndex % cols, tileIndex / cols);
      DrawTexturePro(dungeon, src, player, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

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
  UnloadTexture(dungeon);

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
