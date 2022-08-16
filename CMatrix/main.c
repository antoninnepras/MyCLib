

#include "src/mat22.h"
#include "src/mat33.h"
#include <stdio.h>


void
vec2_print(Vec2 v);


void
vec3_print(Vec3 v);


void
mat22_print(Mat22 m);


void
mat33_print(Mat33 m);


int
main(int argc, const char** argv)
{
  Vec2 v = (Vec2){ 2l, 3l };
  Mat22 m1 = mat22_init(1, 2, 3, 4);
  Mat22 m2 = mat22_init(2, 3, 4, 5);
  Mat22 mr = mat22_mul_mat(m1, m2);
  mat22_print(mr);

  Vec2 vr = mat22_mul_vec(m1, v);
  vec2_print(vr);


  Vec3 v3 = (Vec3){ 5l, 6l, 7l };
  Mat33 m3 = mat33_init(1, 2, 1, 11, 3, 6, 7, 1, 9);
  mat33_print(m3);
  printf("%lf\n", mat33_det(m3));
  mat33_print(mat33_inverse(m3));


  return 0;
}


void
vec2_print(Vec2 v)
{
  printf("[%lf, %lf]\n", v.x, v.y);
}


void
vec3_print(Vec3 v)
{
  printf("[%lf, %lf, %lf]\n", v.x, v.y, v.z);
}


void
mat22_print(Mat22 m)
{
  printf("{[%lf, %lf], [%lf, %lf]}\n",
         m.data[0][0],
         m.data[0][1],
         m.data[1][0],
         m.data[1][1]);
}


void
mat33_print(Mat33 m)
{
  printf("{[%lf, %lf, %lf], [%lf, %lf, %lf], [%lf, %lf, %lf]}\n",
         m.data[0][0],
         m.data[0][1],
         m.data[0][2],
         m.data[1][0],
         m.data[1][1],
         m.data[1][2],
         m.data[2][0],
         m.data[2][1],
         m.data[2][2]);
}



