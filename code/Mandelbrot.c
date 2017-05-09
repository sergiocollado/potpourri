#define X (64)
#define Y (64)
#define X_STEP (0.5f/X)
#define Y_STEP (0.8f/Y)

int map[X][Y];

void mandelbrot_C(void)
{
  int i,j;
  float x,y;
  for (i=0,x=-1.8f;i<X;i++,x+=X_STEP)
  {
    for (j=0,y=-0.2f;j<Y/2;j++,y+=Y_STEP)
    {
      float sx,sy;
      int iter = 0;
      sx = x;
      sy = y;

      while (iter < 256)
      { 
        if (sx*sx + sy*sy >= 4.0f) break;
        float old_sx = sx;
        sx = x + sx*sx - sy*sy;
        sy = y + 2*old_sx*sy;
        iter++;
       }
      
      map[i][j] = iter;
    }
  }
}
