#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

float rand_float(void)
{
  return (float)rand() / (float)RAND_MAX;
}

int main(void)
{
  int factor = 70;
  float screen_width = 9 * factor;
  float screen_height = 9 * factor;
  float scalar = 0.5;
  float texture_width = screen_width * scalar;
  float texture_height = screen_height * scalar;
  InitWindow(screen_width, screen_height, "SmoothLife");
  SetTargetFPS(60);

  // textures
  /* Image image = GenImagePerlinNoise(texture_width, texture_height, 0, 0, 5.0f); */
  /* Image image = GenImageWhiteNoise(texture_width, texture_height, 0.5f); */
  /* Image image = GenImageCellular(texture_width, texture_height, texture_width / 6); */

  Image image = GenImageColor(texture_width, texture_height, BLACK);
  for (int y = 0; y < texture_height * 3 / 4; ++y) {
    for (int x = 0; x < texture_width * 3 / 4; ++x) {
      uint8_t v = rand_float() * 255.0f;
      Color color = {v, v, v, 255};
      ImageDrawPixel(&image, x, y, color);
    }
  }

  // initial state
  RenderTexture2D state[2];

  // init state 0
  state[0] = LoadRenderTexture(texture_width, texture_height);
  SetTextureWrap(state[0].texture, TEXTURE_WRAP_REPEAT);
  SetTextureFilter(state[0].texture, TEXTURE_FILTER_BILINEAR);
  UpdateTexture(state[0].texture, image.data);

  // state 1 + texture repeat
  state[1] = LoadRenderTexture(texture_width, texture_height);
  SetTextureWrap(state[1].texture, TEXTURE_WRAP_REPEAT);
  SetTextureFilter(state[1].texture, TEXTURE_FILTER_BILINEAR);

  // load & set shader
  Shader shader = LoadShader(NULL, "./smoothlife.fs");
  Vector2 resolution = {texture_width, texture_height};
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

    // swap textures around
    i = 1 - i;

    // render state1 to the screen
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureEx(state[i].texture, CLITERAL(Vector2){0}, 0, 1 / scalar, WHITE);
    /* DrawTexture(state[i].texture, 0, 0, WHITE); */
    EndDrawing();
  }

  // cleans things up
  CloseWindow();

  // exit success
  return 0;
}
