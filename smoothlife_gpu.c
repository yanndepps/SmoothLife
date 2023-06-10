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
  /* Image image = GenImagePerlinNoise(screen_width, screen_height, 0, 0, 5.0f); */
  /* Image image = GenImageWhiteNoise(screen_width, screen_height, 0.2f); */
  Image image = GenImageCellular(screen_width, screen_height, screen_width / 6);

  // initial state
  RenderTexture2D state[2];

  // init state 0
  state[0] = LoadRenderTexture(screen_width, screen_height);
  SetTextureWrap(state[0].texture, TEXTURE_WRAP_MIRROR_REPEAT);
  UpdateTexture(state[0].texture, image.data);

  // state 1 + texture repeat
  state[1] = LoadRenderTexture(screen_width, screen_height);
  SetTextureWrap(state[1].texture, TEXTURE_WRAP_MIRROR_REPEAT);

  // load & set shader
  Shader shader = LoadShader(NULL, "./smoothlife.fs");
  Vector2 resolution = {screen_width, screen_height};
  int resolution_loc = GetShaderLocation(shader, "resolution");
  SetShaderValue(shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);

  // flip-flop between 0 & 1 -> i = 1 - i
  size_t i = 0;

  // organize the event loop
  while (!WindowShouldClose()) {
    // render state0 into state1
    BeginTextureMode(state[1 - i]);
    ClearBackground(BLACK);
    BeginShaderMode(shader);
    DrawTexture(state[i].texture, 0, 0, WHITE);
    EndShaderMode();
    EndTextureMode();

    // render state1 to the screen
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(state[1 - i].texture, 0, 0, WHITE);
    EndDrawing();

    // swap textures around
    i = 1 - i;
  }

  // cleans things up
  CloseWindow();

  // exit success
  return 0;
}
