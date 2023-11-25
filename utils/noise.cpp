#include "../IS/Physics/Vector2.hpp"
#include <cstdlib>


Vector2 randomGradient(int ix, int iy) {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> (w - s);
    b *= 1911520717;

    a ^= b << s | b >> (w - s);
    float random = a * (3.14159265 / ~(~0u >> 1)); 

    return Vector2(sin(random), cos(random));
}

float dotGridGradient(int ix, int iy, float x, float y) {
    Vector2 gradient = randomGradient(ix, iy);

    // distance
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // compute dot product
    return (dx * gradient.x + dy * gradient.y);
}

float interpolate(float a0, float a1, float w) 
{
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float perlin(float x, float y)
{
    // Determine grid cell coordinates
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Compute interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;
    
    // top two corners        
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    // bottow two corners
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    // interpolate between two previously interpolated values
    float value = interpolate(ix0, ix1, y);

    return value;

}

