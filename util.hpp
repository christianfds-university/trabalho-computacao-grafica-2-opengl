#include <cmath>
#include <cstdlib>
#include <time.h>

class util
{
  public:
    static const float DEG2RAD;
    static const float RAD2DEG;

    static int randomNumberI();

    static double mapValueD(double v, double min, double max, double r_min, double r_max);

    static int mapValueI(int v, int min, int max, int r_min, int r_max);
};

const float util::DEG2RAD = 3.14159 / 180;
const float util::RAD2DEG = 180 / 3.14159;

int util::randomNumberI()
{
    return (int) rand();
}

double util::mapValueD(double v, double min, double max, double r_min, double r_max)
{
    double slope = (r_max - r_min) / (max - min);
    return r_min + slope * (v - min);
}

int util::mapValueI(int v, int min, int max, int r_min, int r_max)
{
    int slope = (r_max - r_min) / (max - min);
    return (int)(r_min + slope * (v - min));
}