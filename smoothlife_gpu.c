#include <raylib.h>
#include <stdio.h>

int main(void)
{
  // smol RL inits
  int screen_width = 800;
  int screen_height = 600;
  InitWindow(screen_width, screen_height, "SmoothLife");
  SetTargetFPS(60);

  // organize the event loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }

  //---
  return 0;
}
