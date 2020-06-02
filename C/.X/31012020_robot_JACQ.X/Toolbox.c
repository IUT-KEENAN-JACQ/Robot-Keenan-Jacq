#include "Toolbox.h"
#include "main.h"
#define PI 3.141592653589793

float Abs(float value)
{
if (value >= 0)
return value;
else return -value;
}

float Max(float value, float value2)
{
if (value > value2)
return value;
else
return value2;
}

float Min(float value, float value2)
{
    if (value < value2)
        return value;
    else
        return value2;
}

float LimitToInterval(float value, float lowLimit, float highLimit)
{
if (value > highLimit)
value = highLimit;
else if (value < lowLimit)
value = lowLimit;

return value;
}

float RadianToDegree(float value)
{
return value / PI * 180.0;
}

float DegreeToRadian(float value)
{
return value * PI / 180.0;
}
