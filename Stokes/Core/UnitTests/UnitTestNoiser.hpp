#include <cxxtest/TestSuite.h>

#include <Stokes/Core/Noiser.hpp>
#include <Stokes/Core/SimpleField.hpp>

class UnitTestNoiser : public CxxTest::TestSuite
{
public:

	UnitTestNoiser() :
	  width(512),
	  height(512),

	  x(512.0f),
	  y(512.0f)
	{
		cellWidth = x / width;
		cellHeight = y / height;
	}
	~UnitTestNoiser()
	{
	}

	void testNoise()
	{
		float* pixels = new float[width * height];
		float minValue = 1e6f, maxValue = - 1e6f;

		for (int y = 0; y < height; ++ y)
		{
			for (int x = 0; x < width; ++ x)
			{
				//float z = (float)rand() / (float)RAND_MAX * y;
				Stokes::Vectorf np(cellWidth * (x + 0.5f), cellHeight * (y + 0.5f), 0);
				float r = Stokes::Noiser::Noise(np.x, np.y, np.z);
				minValue = std::min(minValue, r);
				maxValue = std::max(maxValue, r);
				pixels[y * height + x] = r;
			}
		}

		TS_ASSERT(SaveAsPGM("testNoise.pgm", width, height, pixels, minValue, maxValue));
		delete [] pixels;
	}

	void testFBM()
	{
		float* pixels = new float[width * height];
		float minValue = 1e6f, maxValue = - 1e6f;

		for (int y = 0; y < height; ++ y)
		{
			for (int x = 0; x < width; ++ x)
			{
				//float z = (float)rand() / (float)RAND_MAX * y;
				Stokes::Vectorf np(cellWidth * (x + 0.5f), 0.0f, cellHeight * (y + 0.5f));
				float r = Stokes::Noiser::FractalBrownianMotion(np, 0.225f, 0.725f, 10.5f);
				minValue = std::min(minValue, r);
				maxValue = std::max(maxValue, r);
				pixels[y * height + x] = r;
			}
		}

		TS_ASSERT(SaveAsPGM("testFBM.pgm", width, height, pixels, minValue, maxValue));
		delete [] pixels;
	}
	
	void testTurbulence()
	{
		float* pixels = new float[width * height];
		float minValue = 1e6f, maxValue = - 1e6f;

		for (int y = 0; y < height; ++ y)
		{
			for (int x = 0; x < width; ++ x)
			{
				//float z = (float)rand() / (float)RAND_MAX * y;
				Stokes::Vectorf np(cellWidth * (x + 0.5f), cellHeight * (y + 0.5f), 0);
				float r = Stokes::Noiser::Turbulence(np, 4.0f);
				minValue = std::min(minValue, r);
				maxValue = std::max(maxValue, r);
				pixels[y * height + x] = r;
			}
		}

		TS_ASSERT(SaveAsPGM("testTurbulence.pgm", width, height, pixels, minValue, maxValue));
		delete [] pixels;
	}

private:

	int width, height;
	float x, y;
	float cellWidth, cellHeight;

	bool SaveAsPGM(const char* path, const int width, const int height, const float* pixels, const float minValue, const float maxValue)
	{
		FILE* fp = fopen(path, "w");
		if (!fp)
		{
			return false;
		}
		fprintf(fp, "P2\n%d %d\n255\n", width, height);

		const float valueRange = maxValue - minValue;

		for (int y = 0; y < height; ++ y)
		{
			for (int x = 0; x < width; ++ x)
			{
				float p = pixels[y * height + x];
				p = (p - minValue) / valueRange;
				fprintf(fp, "%d ", (int)floorf(p * 255.0f));
			}
			fprintf(fp, "\n");
		}
		fclose(fp);

		return true;
	}
};
