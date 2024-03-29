
// https://cs.nyu.edu/~perlin/noise/
class PerlinNoise
{

    public:
        double Noise2D(const double x, const double y);
        double Noise3D(const double x, const double y, const double z);
        
        PerlinNoise() {
            for (int i=0; i < 256 ; i++) {
                p[256+i] = p[i] = permutations[i];
            }
        }

    private:
        static const int permutations[256];
        int p[512];

        static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); };
        static double lerp(double t, double a, double b) { return a + t * (b - a); };

        // 3D
        static double grad(int hash, double x, double y, double z) {
            int h = hash & 15;
            double u = h<8 ? x : y;
            double v = h<4 ? y : h==12 || h == 14 ? x : z;

            return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
        };

        // 2D
        static double grad(int hash, double x, double y) {
            int h = hash & 3; // Now only have four possible values: 0, 1, 2, 3
            double u = (h < 2) ? x : y;
            double v = (h < 2) ? y : x;

            // Compute the dot product between the gradient, (u, v), and (x, y)
            return (((h&1) != 0) ? -u : u) + (((h&2) != 0) ? -v : v);
        }
};
