#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

#define THICKNESS_POINTS 30
#define RADIUS_POINTS 100

#define CAMERA_CLIP_PLANE 60
#define CAMERA_ZOOM 1

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) ((a) > (b) ? (b) : (a))
#endif

const char luminance_char[] = ".,-~:;=!*#$@";

typedef struct
{
  double radius;
  double thickness;
  Vector3 *position;
  Vector3 *rotation;
} Torus;

typedef struct
{
  int width;
  int height;
  char *contents;
  double *z_buffer;
} Screen;

void clearScreen(Screen *screen)
{
  for (int j = 0; j < screen->height; j++)
  {
    for (int i = 0; i < screen->width; i++)
    {
      screen->contents[i + j * screen->width] = ' ';
      screen->z_buffer[i + j * screen->width] = 0;
    }
  }
}

void drawTorus(Torus *torus, Screen *screen, Vector3 *light)
{
  double theta_step = 2 * M_PI / THICKNESS_POINTS;

  for (int i = 0; i < THICKNESS_POINTS; i++)
  {
    double theta = theta_step * i;

    double phi_step = 2 * M_PI / RADIUS_POINTS;

    for (int j = 0; j < RADIUS_POINTS; j++)
    {
      double phi = phi_step * j;

      double cos_r = cos(theta) * torus->thickness;

      // TODO: Refactor this, a bunch of repeated calculations
      Vector3 *circle_point = create_vector(
          cos(phi) * (torus->radius + cos_r),
          sin(theta) * torus->thickness,
          -sin(phi) * (torus->radius + cos_r));

      rotate(circle_point, torus->rotation);
      add(circle_point, torus->position);

      double ooz = 1.0 / circle_point->z;
      double x = circle_point->x * CAMERA_CLIP_PLANE * ooz;
      double y = circle_point->y * CAMERA_CLIP_PLANE * ooz;

      int x_pos = (int)x + screen->width / 2;
      int y_pos = (int)y + screen->height / 2;

      if (x_pos < screen->width && x_pos >= 0 && y_pos < screen->height && y_pos >= 0)
      {
        int pos_index = x_pos + y_pos * screen->width;
        if (ooz >= screen->z_buffer[pos_index])
        {
          Vector3 *normal = create_vector(
              cos(phi) * cos(theta),
              sin(theta),
              -sin(phi) * cos(theta));
          rotate(normal, torus->rotation);

          double luminance = dot(normal, light);
          int luminance_index = min(max((int)ceil(luminance * 11), 0), 11);

          screen->contents[pos_index] = luminance_char[luminance_index];
          screen->z_buffer[pos_index] = ooz;

          free(normal);
        }
      }

      free(circle_point);
    }
  }
}

void printScreen(Screen *screen)
{
  for (int i = 0; i < screen->height; i++)
  {
    for (int j = 0; j < screen->width; j++)
    {
      printf("%c", screen->contents[j + i * screen->width]);
    }
    printf("\n");
  }
}

int main()
{
  Torus torus;
  torus.position = create_vector(0, 0, 70);
  torus.rotation = create_vector(0, 0, 0);
  torus.radius = 10;
  torus.thickness = 4;

  Screen screen;
  screen.width = 40;
  screen.height = 40;
  screen.contents = malloc(screen.width * screen.height * sizeof(char));
  screen.z_buffer = malloc(screen.width * screen.height * sizeof(double));

  Vector3 *light = create_vector(0, -1, -1);
  normalize(light);

  while (1)
  {
    torus.rotation->z += 0.001;
    torus.rotation->x += 0.0012;

    clearScreen(&screen);
    drawTorus(&torus, &screen, light);
    printScreen(&screen);
  }

  return 0;
}