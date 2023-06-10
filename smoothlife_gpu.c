#include <raylib.h>
#include <stdio.h>

int main(void)
{
  // smol RL inits
  int screen_width = 800;
  int screen_height = 600;
  InitWindow(screen_width, screen_height, "SmoothLife");
  SetTargetFPS(60);

  // textures
  Image image = GenImagePerlinNoise(screen_width, screen_height, 0, 0, 5.0f);
  /* Image image = GenImageWhiteNoise(screen_width, screen_height, 0.2f); */
  Texture2D texture = LoadTextureFromImage(image);

  // load shader
  Shader shader = LoadShader(NULL, "./smoothlife.fs");

  // organize the event loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginShaderMode(shader);
    DrawTexture(texture, 0, 0, WHITE);
    EndShaderMode();
    EndDrawing();
  }

  // cleans things up
  CloseWindow();

  // exit success
  return 0;
}
