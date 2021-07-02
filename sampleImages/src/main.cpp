
#include<stdio.h>
#include<math.h>
#include<random>
#include"image.h"

using lf = double;

namespace{
int nextint(int s, int t) {
	static std::mt19937 rnd;
	return (int)(rnd() % (t - s + 1)) + s;
}
bool sample_image_changed(const IMAGE::Image &img, const std::string filename){
	IMAGE::Image prev(filename);
	if(img.w != prev.w)return true;
	if(img.h != prev.h)return true;
	for(int i = 0; i < img.h * img.w * 4; i++) {
		if(img.data[i] != prev.data[i]){
			return true;
		}
	}
	return false;
}

const std::string sampleImagesDir = "sampleImages/";
const std::string resourcesDir = "resources/";

struct vec2 {
	lf x, y;
	vec2() {
		x = y = 0;
	}
	vec2(lf x, lf y) :x(x), y(y) {}

	vec2 operator +(const vec2& z) {
		return vec2(x + z.x, y + z.y);
	}
	vec2 operator -(const vec2& z) {
		return vec2(x - z.x, y - z.y);
	}
	vec2 operator *(const lf& z) {
		return vec2(x * z, y * z);
	}
	lf operator *(const vec2& z) {
		return x * z.x + y * z.y;
	}
	void normalize() {
		lf dd = sqrt(x * x + y * y);
		x /= dd;
		y /= dd;
	}
};
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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}
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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}
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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}
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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}
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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}
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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}

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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}

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

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}
}
void generate_sample9() {
	printf("Sample 9 : Triangle and Polygon\n");

	std::string filename = sampleImagesDir + "sample9.png";

	int i, j, k;
	int width = 320;
	int height = 240;
	IMAGE::Image img(width, height);

	const double vertex[5][2] = {
		{10, 10},
		{10, 230},
		{310, 230},
		{310, 10},
		{160, 20},
	};

	img.draw_polygon(5, &vertex[0][0], 0.1, 0.1, 0.1, 1.0);

	img.draw_triangle(20, 20, 200, 300, 240, 60, 1.0, 0.0, 0.0);
	img.draw_triangle(40, 20, 400, 30, 200, 400, 0.0, 1.0, 1.0, 0.5);

	int n = 5;
	std::vector<double> px(2*n);
	std::vector<double> py(2*n);

	for(k = 0; k < n; k++) {
		double cx = width * 0.2 + (k&1 ? width * 0.6 : 0.0);
		double cy = height * 0.2 + height * 0.6 * k/n;
		px[k] = cx - width * 0.05;
		py[k] = cy;
		if(k == 0){
			px[n] = width * 0.2 + (n&1 ? width * 0.6 : 0.0);
			py[n] = height * 0.2 + height * 0.6;
		}
		else{
			px[2*n - k] = cx + width * 0.05;
			py[2*n - k] = cy;
		}
	}

	img.draw_polygon(2*n, px, py, 0.9, 0.8, 0.5);

	if(sample_image_changed(img, filename)){
		img.Save(filename);
	}
}

void generate_sample10()
{
	printf("Sample 10 : NUI Infographic\n");

	std::string filename = sampleImagesDir + "sample10.png";

	int i, j, k;
	int width = 960;
	int height = 640;
	IMAGE::Image img(width, height);

	// convert corrdinate [0~6],[0~4] to [width], [height] without scale
	auto convertitox = [width, height](vec2 p) {
		lf diff = std::min(width / 6.0, height / 4.0);
		lf x = (p.x - 3.0) * diff + width * 0.5;
		lf y = (2.0 - p.y) * diff + height * 0.5;
		return vec2(x, y);
	};

	std::vector<std::vector<vec2>> vn =
	{
		// n
		{convertitox(vec2(1, 1)), convertitox(vec2(1, 3))},
		{convertitox(vec2(1, 3)), convertitox(vec2(2, 1))},
		{convertitox(vec2(2, 1)), convertitox(vec2(2, 3))},
		// u
		{convertitox(vec2(2.5, 3)), convertitox(vec2(2.5, 1))},
		{convertitox(vec2(2.5, 1)), convertitox(vec2(3.5, 1))},
		{convertitox(vec2(3.5, 1)), convertitox(vec2(3.5, 3))},
		//i
		{convertitox(vec2(4, 3)), convertitox(vec2(4.5, 3))},
		{convertitox(vec2(4.5, 3)), convertitox(vec2(5, 3))},
		{convertitox(vec2(4, 1)), convertitox(vec2(4.5, 1))},
		{convertitox(vec2(4.5, 1)), convertitox(vec2(5, 1))},
		{convertitox(vec2(4.5, 1)), convertitox(vec2(4.5, 3))},
	};

	lf radius_scale = std::min(width, height);
	lf radius_max = 30.0 / 960.0 * radius_scale;
	lf radius_min = 20.0 / 960.0 * radius_scale;
	lf dx[10] = { 0,1,1,1,0,-1,-1,-1,0,0 };
	lf dy[10] = { -1,-1,0,1,1,1,0,-1,0,0 };

	{
		vec2 dif = vn[1][1] - vn[1][0];
		dif.y += 2 * radius_max;
		lf xx = dif.x;
		lf yy = dif.y / dif.x * 2 * radius_max - radius_max;
		dif.x = 1.0;
		dif.y = yy / radius_max;
		dx[8] = dif.x;
		dy[8] = dif.y;
		dx[9] = -dif.x;
		dy[9] = -dif.y;
	}

	std::vector<std::vector<std::vector<int>>> vdn = {
		// n
		{{5,3}, {8, 7}},
		{{1,7}, {5, 3}},
		{{9,3}, {1, 7}},
		// u
		{{1,7}, {7, 1}},
		{{7,3}, {5, 1}},
		{{7,1}, {1, 7}},
		// i
		{{7,5}, {5, 1}},
		{{1,3}, {3, 1}},
		{{7,5}, {5, 7}},
		{{1,5}, {3, 1}},
		{{5,1}, {1, 5}},
	};

	lf global_scale = 1.0;
	lf n_scale = 2.0;
	lf u_scale = 1.5;
	lf i_scale = 0.75;
	std::vector<std::vector<lf>> vdo = {
		// n
		{0, n_scale},
		{0, 0},
		{n_scale, 0},
		// u
		{0, global_scale},
		{u_scale, u_scale},
		{global_scale, 0},
		// i
		{0, i_scale},
		{global_scale, 0},
		{0, global_scale},
		{i_scale, 0},
		{i_scale, i_scale},
	};

	img.clean(0.0, 0.0, 0.0);
	img.set_transparency_color(0, 0, 0);

	int vl = vn.size();
	lf base_alpha = 0.8;
	lf rr = 0.37;
	lf gg = 0.67;
	lf bb = 0.92;
	// draw white
	for (int k = 0; k < vl; k++) {
		lf radius = radius_max;
		std::vector<lf> px(4);
		std::vector<lf> py(4);
		std::vector<vec2> s(2);
		s[0] = vn[k][0];
		s[1] = vn[k][1];

		for (int i = 0; i < 4; i++) {
			px[i] = s[i / 2].x + dx[vdn[k][i / 2][i % 2]] * radius;
			py[i] = s[i / 2].y + dy[vdn[k][i / 2][i % 2]] * radius;
		}

		img.draw_polygon(4, px, py, 1, 1, 1, 1);
	}

	// bluring
	for (int i = 0; i < img.h; i++) {
		for (int j = 0; j < img.w; j++) {
			int id = i * img.w + j;
			if (img.data[id * 4 + 3] == 255) {
				img.data[id * 4 + 3] = (base_alpha * 255);
			}
		}
	}

	for (int k = 0; k < vl; k++) {
		lf radius = radius_min;
		std::vector<lf> px(4);
		std::vector<lf> py(4);
		std::vector<vec2> s(2);
		s[0] = vn[k][0];
		s[1] = vn[k][1];
		vec2 diff = (s[1] - s[0]) * 0.5;
		diff.normalize();
		s[0] = s[0] + diff * vdo[k][0] * (radius_max - radius_min);
		s[1] = s[1] - diff * vdo[k][1] * (radius_max - radius_min);

		for (int i = 0; i < 4; i++) {
			px[i] = s[i / 2].x + dx[vdn[k][i / 2][i % 2]] * radius;
			py[i] = s[i / 2].y + dy[vdn[k][i / 2][i % 2]] * radius;
		}

		img.draw_polygon(4, px, py, 1, 1, 1, 1);
	}
	// coloring
	for (int i = 0; i < img.h; i++) {
		for (int j = 0; j < img.w; j++) {
			int id = i * img.w + j;
			if (img.data[id * 4 + 3] == 255) {
				img.data[id * 4 + 0] = (rr * 255);
				img.data[id * 4 + 1] = (gg * 255);
				img.data[id * 4 + 2] = (bb * 255);
			}
		}
	}

	if (sample_image_changed(img, filename)) {
		img.Save(filename);
	}
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
	generate_sample9();
	generate_sample10();
	return 0;
}