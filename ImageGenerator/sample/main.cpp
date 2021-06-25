
#include<stdio.h>
#include<math.h>
#include<random>
#include"image.h"

namespace{
int nextint(int s, int t) {
	static std::mt19937 rnd;
	return (int)(rnd() % (t - s + 1)) + s;
}

const std::string sampleImagesDir = "sampleImages/";
const std::string resourcesDir = "resources/";

} // namespace


void generate_sample1() {
	printf("Sample 1 : Red gradient\n");

	std::string filename = sampleImagesDir + "sample1.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int color = (i + j) % 100;
			img.set_pixel(i, j, color / 99.0, 0.0, 0.0);
		}
	}

	img.Save(filename);
}
void generate_sample2() {
	printf("Sample 2 : Rectangles + Diamond + Circle\n");

	std::string filename = sampleImagesDir + "sample2.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	img.clean(0.5, 0.5, 0.5);

	// red rectangle
	img.draw_rectangle(width * 0.2, height * 0.2, width * 0.8, height * 0.3, 1.0, 0.0, 0.0);
	// green diamond
	img.draw_diamond(width * 0.3, height * 0.8, std::min(width, height) * 0.4, 0.0, 1.0, 0.0);
	// blue circle
	img.draw_circle(width * 0.8, height * 0.7, std::min(width, height) * 0.3, 0.0, 0.0, 1.0);

	img.Save(filename);
}
void generate_sample3() {
	printf("Sample 3 : Rectangles + Diamond + Circle only border\n");

	std::string filename = sampleImagesDir + "sample3.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	img.clean(0.5, 0.5, 0.5);

	// red rectangle border
	img.draw_rectangle_border(width * 0.2, height * 0.2, width * 0.8, height * 0.3, std::min(width, height) * 0.01, 1.0, 0.0, 0.0);
	img.draw_rectangle_border(width * 0.25, height * 0.25, width * 0.85, height * 0.35, std::min(width, height) * 0.01, 1.0, 0.0, 0.0);
	// green diamond border
	img.draw_diamond_border(width * 0.3, height * 0.8, std::min(width, height) * 0.4, std::min(width, height) * 0.01, 0.0, 1.0, 0.0);
	img.draw_diamond_border(width * 0.3, height * 0.8, std::min(width, height) * 0.2, std::min(width, height) * 0.04, 0.0, 1.0, 0.0);
	// blue circle border
	img.draw_circle_border(width * 0.8, height * 0.7, std::min(width, height) * 0.3, std::min(width, height) * 0.02, 0.0, 0.0, 1.0);
	img.draw_circle_border(width * 0.8, height * 0.7, std::min(width, height) * 0.1, std::min(width, height) * 0.02, 0.0, 0.0, 1.0);

	img.Save(filename);
}

void generate_sample4() {
	printf("Sample 4 : Lines\n");

	std::string filename = sampleImagesDir + "sample4.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	int sx, sy;
	int ex, ey;
	// red line
	sx = nextint(0, width); sy = nextint(0, height);
	ex = nextint(0, width); ey = nextint(0, height);
	img.draw_line(sx, sy, ex, ey, std::min(width, height) * 0.01, 1.0, 0.0, 0.0);

	// green line
	sx = nextint(0, width); sy = nextint(0, height);
	ex = nextint(0, width); ey = nextint(0, height);
	img.draw_line(sx, sy, ex, ey, std::min(width, height) * 0.02, 0.0, 1.0, 0.0);

	// blue line
	sx = nextint(0, width); sy = nextint(0, height);
	ex = nextint(0, width); ey = nextint(0, height);
	img.draw_line(sx, sy, ex, ey, std::min(width, height) * 0.03, 0.0, 0.0, 1.0);

	// red-green gradient line
	sx = nextint(0, width); sy = nextint(0, height);
	ex = nextint(0, width); ey = nextint(0, height);
	img.draw_line_gradient(sx, sy, ex, ey, std::min(width, height) * 0.02, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	img.Save(filename);
}
void generate_sample5() {
	printf("Sample 5 : Alpha blending and Alpha Behavior\n");

	std::string filename = sampleImagesDir + "sample5.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	img.clean(0.0, 0.0, 0.0);

	int sx, sy;
	int ex, ey;
	//random blue rectangle
	for (int i = 0; i < 10; i++) {
		sx = nextint(0, width); sy = nextint(0, height);
		ex = nextint(0, width); ey = nextint(0, height);
		img.draw_rectangle(sx, sy, ex, ey, 0.0, 0.0, nextint(128, 255) / 255.0);
	}

	// red alpha 0.7
	img.draw_circle(width * 0.1, height * 0.2, std::min(width, height) * 0.7, 1.0, 0.0, 0.0, 0.7);
	// green alpha 0.5
	img.draw_circle(width * 0.8, height * 0.9, std::min(width, height) * 0.7, 0.0, 1.0, 0.0, 0.5);
	// change alpha behavior and summation it.
	img.mAlphaBehavior = IMAGE::AlphaBehaviorType::ONE;
	int n = 100;
	for (int i = 0; i < n; i++) {
		// alpha overwhelming
		img.draw_circle(width * 0.1, height * 0.9, std::min(width, height) * 0.7 * (n - i) / n, pow(0.7, (n - i) * 1.2 / n), pow(0.5, (n - i) * 1.5 / n), 1.0, 1.5 / n);
	}

	img.mAlphaBehavior = IMAGE::AlphaBehaviorType::ONE_MINUS_ALPHA;

	img.Save(filename);
}
void generate_sample6() {
	printf("Sample 6 : Load Image\n");

	std::string filename = sampleImagesDir + "sample6.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	IMAGE::Image number[10];
	for (i = 0; i < 10; i++) {
		char xxx[99];
		sprintf(xxx, (resourcesDir + "numbers/%d.png").c_str(), i);
		number[i].Load(xxx);
		number[i].set_transparency_color(255, 255, 255, 0);
	}

	int n, m;
	n = 7;
	m = 10;

	double cell_size = std::min((double)width * 0.95 / m, (double)height * 0.95 / n) ;
	double cell_margin = cell_size * 0.05;
	double sx = width * 0.5 - cell_size * m / 2.0;
	double sy = height * 0.5 - cell_size * n / 2.0;

	int** a = new int* [n];
	for (i = 0; i < n; i++) {
		a[i] = new int[m];
		for (j = 0; j < m; j++) {
			a[i][j] = nextint(0, 9);
		}
	}

	//draw background (for border line)
	img.draw_rectangle(sx, sy, sx + m * cell_size, sy + n * cell_size, 0.0, 0.0, 0.0);

	//draw number
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			double x = sx + j * cell_size;
			double y = sy + i * cell_size;


			img.draw_rectangle(x + cell_margin, y + cell_margin, x + cell_size - cell_margin, y + cell_size - cell_margin, 0.8, 1.0, 0.8);
			img.draw_image(x, y, x + cell_size, y + cell_size, number[a[i][j]]);
		}
	}

	//draw border line
	// NOTE : this class only use overdrawing. So border line must draw "after" drawing background is done
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			double x = sx + j * cell_size;
			double y = sy + i * cell_size;

			if (a[i][j] == 0) {
				img.draw_rectangle_border(x, y, x + cell_size, y + cell_size, cell_margin * 2.0, 1.0, 0.0, 0.0);
			}
		}
	}

	img.Save(filename);

	for (i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
}

void generate_sample7() {
	printf("Sample 7 : Whatever you want\n");

	std::string filename = sampleImagesDir + "sample7.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	img.clean(0.02, 0.05, 0.1);

	struct STAR {
		double x, y;
		double r, g, b, a;
		double offset;
		double radius;

		void draw(IMAGE::Image& img) {
			int i, j, k;
			for (i = 0; i < img.h; i++) {
				for (j = 0; j < img.w; j++) {
					double dx = j - x;
					double dy = i - y;
					double ang = atan2(dy, dx);
					ang /= 2.0;
					ang *= 5.0;
					double magic = abs(tan(ang + offset)) + 1;
					double local_radius = radius / std::max(0.01, magic);
					double dd = sqrt(dx * dx + dy * dy);
					if (dd <= local_radius) {
						img.set_pixel(i, j, r, g, b, a * (1.0 - dd / local_radius));
					}
				}
			}
		}
	};
	int n = 50;
	STAR* a = new STAR[n];

	for (i = 0; i < n; i++) {
		a[i].x = nextint(0, width);
		a[i].y = nextint(0, height);
		a[i].r = nextint(128, 255) / 255.0;
		a[i].g = nextint(128, 255) / 255.0;
		a[i].b = nextint(128, 255) / 255.0;
		a[i].a = nextint(100, 150) / 255.0;
		a[i].radius = std::min(width, height) * nextint(5, 10) / 50.0;
		a[i].offset = nextint(0, 3141592) / 1000000.0;

		a[i].draw(img);
	}

	img.Save(filename);

	delete[] a;
}
void generate_sample8() {
	printf("Sample 8 : Resize Image\n");

	std::string filename = sampleImagesDir + "sample8.png";

	int i, j, k;
	int width = 1280;
	int height = 480;
	IMAGE::Image img(width, height);

	IMAGE::Image base(sampleImagesDir + "sample6.png");

	// same scale image
	img.draw_image(0, 0, 160, 120, base);
	img.draw_image(160, 0, 480, 240, base);
	img.draw_image(480, 0, 1120, 480, base);
	img.draw_image(0, 120, 80, 180, base);
	img.draw_image(80, 150, 120, 180, base);
	img.draw_image(120, 165, 140, 180, base);

	// extream scale image
	img.draw_image(20, 300, 480, 320, base);
	img.draw_image(0, 180, 20, 480, base);

	img.Save(filename);
}
int main() {
	generate_sample1();
	generate_sample2();
	generate_sample3();
	generate_sample4();
	generate_sample5();
	generate_sample6();
	generate_sample7();
	generate_sample8();
	return 0;
}