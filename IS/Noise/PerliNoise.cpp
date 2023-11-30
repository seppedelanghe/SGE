#include <cmath>

#include "PerlinNoise.hpp"


const int PerlinNoise::permutations[256] = { 
            151,160,137,91,90,15,
            131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
            190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
            88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
            77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
            102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
            135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
            5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
            223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
            129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
            251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
            49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
        };

double PerlinNoise::Noise3D(const double x, const double y, const double z) 
{
    // Find unit cube that contains point
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
   
    // Find relative x,y,z of point in cube
    double rx = x - floor(x);
    double ry = y - floor(y);
    double rz = z - floor(z);

    // Compute fade of curves
    double u = fade(rx);
    double v = fade(ry);
    double w = fade(rz);

    // Hash coordinates of 8 cube corners
    int A =  p[X  ] + Y;
    int AA = p[A  ] + Z;
    int AB = p[A+1] + Z;
    int B =  p[X+1] + Y;
    int BA = p[B  ] + Z;
    int BB = p[B+1] + Z;

    // add blended results from 8 corners of cube
    return lerp(w, lerp(v,   lerp(u, grad(p[AA  ], x  , y  , z   ),
                                     grad(p[BA  ], x-1, y  , z   )),
                             lerp(u, grad(p[AB  ], x  , y-1, z   ),
                                     grad(p[BB  ], x-1, y-1, z   ))),
                     lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  
                                     grad(p[BA+1], x-1, y  , z-1 )),
                             lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
                                     grad(p[BB+1], x-1, y-1, z-1 ))));

};

double PerlinNoise::Noise2D(const double x, const double y)  {
    // Find unit grid cell containing point
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;

    // Get relative xy coordinates of point within that cell
    double rx = x - floor(x);
    double ry = y - floor(y);

    // Compute fade curves for rx, ry
    double u = fade(rx);
    double v = fade(ry);

    // Hash coordinates of the 4 square corners
    int A = p[X] + Y;
    int AA = p[A];
    int AB = p[A + 1];
    int B = p[X + 1] + Y;
    int BA = p[B];
    int BB = p[B + 1];

    // Add blended results from 4 corners of the square
    return lerp(v, lerp(u, grad(p[AA], rx, ry),
                           grad(p[BA], rx - 1, ry)),
                   lerp(u, grad(p[AB], rx, ry - 1),
                           grad(p[BB], rx - 1, ry - 1)));
}

