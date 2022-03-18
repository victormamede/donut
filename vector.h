#pragma once

#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415
#endif

typedef struct
{
  double x;
  double y;
  double z;
} Vector3;

Vector3 *create_vector(double x, double y, double z);

void rotateX(Vector3 *vector, double amount);
void rotateY(Vector3 *vector, double amount);
void rotateZ(Vector3 *vector, double amount);

void rotate(Vector3 *vector, Vector3 *rotation);

void add(Vector3 *vector, Vector3 *to_add);
void sub(Vector3 *vector, Vector3 *to_sub);

double vector_length(Vector3 *vector);
double dot(Vector3 *vectorA, Vector3 *vectorB);
void normalize(Vector3 *vector);

Vector3 *clone(Vector3 *vector);

void print_vector(Vector3 *vector);