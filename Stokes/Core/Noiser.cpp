#include <cmath>

#include <Stokes/Core/Noiser.hpp>

ENTER_NAMESPACE_STOKES

static Integer32 p[512] = 
{
	151, 160, 137,  91,  90,  15, 131,  13,
	201,  95,  96,  53, 194, 233,   7, 225,
	140,  36, 103,  30,  69, 142,   8,  99,
	 37, 240,  21,  10,  23, 190,   6, 148,
	247, 120, 234,  75,   0,  26, 197,  62,
	 94, 252, 219, 203, 117,  35,  11,  32,
	 57, 177,  33,  88, 237, 149,  56,  87,
	174,  20, 125, 136, 171, 168,  68, 175,
	 74, 165,  71, 134, 139,  48,  27, 166,
	 77, 146, 158, 231,  83, 111, 229, 122,
	 60, 211, 133, 230, 220, 105,  92,  41,
	 55,  46, 245,  40, 244, 102, 143,  54,
	 65,  25,  63, 161,   1, 216,  80,  73,
	209,  76, 132, 187, 208,  89,  18, 169,
	200, 196, 135, 130, 116, 188, 159,  86,
	164, 100, 109, 198, 173, 186,   3,  64,
	 52, 217, 226, 250, 124, 123,   5, 202,
	 38, 147, 118, 126, 255,  82,  85, 212,
	207, 206,  59, 227,  47,  16,  58,  17,
	182, 189,  28,  42, 223, 183, 170, 213,
	119, 248, 152,   2,  44, 154, 163,  70,
	221, 153, 101, 155, 167,  43, 172,   9,
	129,  22,  39, 253,  19,  98, 108, 110,
	 79, 113, 224, 232, 178, 185, 112, 104,
	218, 246,  97, 228, 251,  34, 242, 193,
	238, 210, 144,  12, 191, 179, 162, 241,
	 81,  51, 145, 235, 249,  14, 239, 107,
	 49, 192, 214,  31, 181, 199, 106, 157,
	184,  84, 204, 176, 115, 121,  50,  45,
	127,   4, 150, 254, 138, 236, 205,  93,
	222, 114,  67,  29,  24,  72, 243, 141,
	128, 195,  78,  66, 215,  61, 156, 180,
	151, 160, 137,  91,  90,  15, 131,  13,
	201,  95,  96,  53, 194, 233,   7, 225,
	140,  36, 103,  30,  69, 142,   8,  99,
	 37, 240,  21,  10,  23, 190,   6, 148,
	247, 120, 234,  75,   0,  26, 197,  62,
	 94, 252, 219, 203, 117,  35,  11,  32,
	 57, 177,  33,  88, 237, 149,  56,  87,
	174,  20, 125, 136, 171, 168,  68, 175,
	 74, 165,  71, 134, 139,  48,  27, 166,
	 77, 146, 158, 231,  83, 111, 229, 122,
	 60, 211, 133, 230, 220, 105,  92,  41,
	 55,  46, 245,  40, 244, 102, 143,  54,
	 65,  25,  63, 161,   1, 216,  80,  73,
	209,  76, 132, 187, 208,  89,  18, 169,
	200, 196, 135, 130, 116, 188, 159,  86,
	164, 100, 109, 198, 173, 186,   3,  64,
	 52, 217, 226, 250, 124, 123,   5, 202,
	 38, 147, 118, 126, 255,  82,  85, 212,
	207, 206,  59, 227,  47,  16,  58,  17,
	182, 189,  28,  42, 223, 183, 170, 213,
	119, 248, 152,   2,  44, 154, 163,  70,
	221, 153, 101, 155, 167,  43, 172,   9,
	129,  22,  39, 253,  19,  98, 108, 110,
	 79, 113, 224, 232, 178, 185, 112, 104,
	218, 246,  97, 228, 251,  34, 242, 193,
	238, 210, 144,  12, 191, 179, 162, 241,
	 81,  51, 145, 235, 249,  14, 239, 107,
	 49, 192, 214,  31, 181, 199, 106, 157,
	184,  84, 204, 176, 115, 121,  50,  45,
	127,   4, 150, 254, 138, 236, 205,  93,
	222, 114,  67,  29,  24,  72, 243, 141,
	128, 195,  78,  66, 215,  61, 156, 180
};

inline static Float fade(Float t) 
{
    return (t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f));
}

inline static Float lerp(Float t, Float a, Float b) 
{ 
    return (a + t * (b - a)); 
}

inline static Float grad(Integer32 hash, Float x, Float y, Float z) 
{
    Integer32 h = hash & 15;
    Float u = h < 8 ? x : y;
    Float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return (((h & 1) == 0 ? u : - u) + ((h & 2) == 0 ? v : - v));
}

Float Noiser::Noise(Float x, Float y, Float z)
{
    Integer32 X, Y, Z;
    Integer32 A, B, AA, AB, BA, BB;
    Float u, v, w;

	X = static_cast<Integer32>(x) & 255;
    Y = static_cast<Integer32>(y) & 255;
    Z = static_cast<Integer32>(z) & 255;
	
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

    u = fade(x);
    v = fade(y);
    w = fade(z);

    A = p[X    ] + Y; AA = p[A] + Z; AB = p[A + 1] + Z;
    B = p[X + 1] + Y; BA = p[B] + Z; BB = p[B + 1] + Z;

    return (lerp(w, lerp(v, lerp(u, grad(p[AA    ], x    , y    , z    ),
                                    grad(p[BA    ], x - 1, y    , z    )),
                            lerp(u, grad(p[AB    ], x    , y - 1, z    ),
                                    grad(p[BB    ], x - 1, y - 1, z    ))),
                    lerp(v, lerp(u, grad(p[AA + 1], x    , y    , z - 1),
                                    grad(p[BA + 1], x - 1, y    , z - 1)),
                            lerp(u, grad(p[AB + 1], x    , y - 1, z - 1),
                                    grad(p[BB + 1], x - 1, y - 1, z - 1)))));
}

Float Noiser::FractalBrownianMotion(Vectorf localPoint, Float H, Float lacunarity, Float octave)
{
	Float fbm = 0.0f;

	Integer32 i;
	for (i = 0; i < octave; ++ i)
	{
		fbm += Noise(localPoint.x, localPoint.y, localPoint.z) * powf(lacunarity, - H * i);
		localPoint.x *= lacunarity;
		localPoint.y *= lacunarity;
		localPoint.z *= lacunarity;
	}
	Float reminder = octave - static_cast<Integer32>(octave);
	if (reminder)
	{
		fbm += reminder * Noise(localPoint.x, localPoint.y, localPoint.z) * powf(lacunarity, - H * i);
	}

	return fbm;
}

Float Noiser::Turbulence(Vectorf localPoint, Float frequency)
{
	Float f = frequency;
	Float t;
	Vectorf v;

	for (t = 0; f >= 1.0f; f *= 0.5f)
	{
		v.x = f * localPoint.x;
		v.y = f * localPoint.y;
		v.z = f * localPoint.z;
		t += fabs(Noise(v.x, v.y, v.z)) / f;
	}

	return t;
}

LEAVE_NAMESPACE_STOKES
