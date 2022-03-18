#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

Vector3 *create_vector(double x, double y, double z)
{
  Vector3 *vector = malloc(sizeof(Vector3));
  vector->x = x;
  vector->y = y;
  vector->z = z;
}

void rotateX(Vector3 *vector, double amount)
{
  double y = vector->y * cos(amount) - vector->z * sin(amount);
  double z = vector->y * sin(amount) + vector->z * cos(amount);

  vector->y = y;
  vector->z = z;
}

void rotateY(Vector3 *vector, double amount)
{
  double x = vector->x * cos(amount) + vector->z * sin(amount);
  double z = -vector->x * sin(amount) + vector->z * cos(amount);

  vector->x = x;
  vector->z = z;
}

void rotateZ(Vector3 *vector, double amount)
{
  double x = vector->x * cos(amount) - vector->y * sin(amount);
  double y = vector->x * sin(amount) + vector->y * cos(amount);

  vector->x = x;
  vector->y = y;
}

void rotate(Vector3 *vector, Vector3 *rotation)
{
  rotateX(vector, rotation->x);
  rotateY(vector, rotation->y);
  rotateZ(vector, rotation->z);
}

void add(Vector3 *vector, Vector3 *to_add)
{
  vector->x += to_add->x;
  vector->y += to_add->y;
  vector->z += to_add->z;
}

void sub(Vector3 *vector, Vector3 *to_sub)
{
  vector->x -= to_sub->x;
  vector->y -= to_sub->y;
  vector->z -= to_sub->z;
}

Vector3 *clone(Vector3 *vector)
{
  return create_vector(
      vector->x,
      vector->y,
      vector->z);
}

double vector_length(Vector3 *vector)
{
  return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}

double dot(Vector3 *vectorA, Vector3 *vectorB)
{
  return (vectorA->x * vectorB->x) + (vectorA->y * vectorB->y) + (vectorA->z * vectorB->z);
}

void normalize(Vector3 *vector)
{
  double length = vector_length(vector);

  vector->x /= length;
  vector->y /= length;
  vector->z /= length;
}

void print_vector(Vector3 *vector)
{
  printf("(%.5f, %.5f, %.5f)\n", vector->x, vector->y, vector->z);
}