
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

const int NUI_WIDTH = 3840;
const int NUI_HEIGHT = 2160;
const lf NUI_SCALE = 860;
} // namespace

void generate_sample10()
{
	printf("Sample 10 : NUI Infographic\n");

	std::string filename = sampleImagesDir + "sample10.png";

	int i, j, k;
	int width = NUI_WIDTH;
	int height = NUI_HEIGHT;
	lf scale = NUI_SCALE;
	IMAGE::Image img(width, height);
	img.mSamplingMode = IMAGE::SamplingModeType::SAMPLING_3x3;
	img.mAlphaBehavior = IMAGE::AlphaBehaviorType::ONE;

	// convert corrdinate [0~6],[0~4] to [width], [height] without scale
	auto convertitox = [width, height, scale](vec2 p) {
		lf diff = scale;
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

	lf radius_scale = scale;
	lf radius_max = 35.0 / 160.0 * radius_scale;
	lf radius_min = 24.0 / 160.0 * radius_scale;
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

	//magic number!
	lf n_scale = 2.0;
	lf u_scale = sqrt(2.0);
	lf i_scale = sqrt(0.5);
	std::vector<std::vector<lf>> vdo = {
		// n
		{0, n_scale},
		{0, 0},
		{n_scale, 0},
		// u
		{0, 1},
		{u_scale, u_scale},
		{1, 0},
		// i
		{0, i_scale},
		{1, 0},
		{0, 1},
		{i_scale, 0},
		{i_scale, i_scale},
	};

	img.clean(1.0, 1.0, 1.0);
	img.set_transparency_color(255, 255, 255);

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
			if (img.data[id * 4 + 3] > 0) {
				img.data[id * 4 + 0] = 255;
				img.data[id * 4 + 1] = 255;
				img.data[id * 4 + 2] = 255;
				int z = base_alpha * img.data[id * 4 + 3];
				if (z < 0)z = 0;
				if (z > 255)z = 255;
				img.data[id * 4 + 3] = z;
			}
		}
	}

	img.mAlphaBehavior = IMAGE::AlphaBehaviorType::ONE_MINUS_ALPHA;
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

		img.draw_polygon(4, px, py, rr, gg, bb, 1);
	}

	if (sample_image_changed(img, filename)) {
		img.Save(filename);
	}
}

void generate_sample11()
{
	printf("Sample 11 : NUI Infographic without white blur\n");

	std::string filename = sampleImagesDir + "sample11.png";

	int i, j, k;
	int width = NUI_WIDTH;
	int height = NUI_HEIGHT;
	lf scale = NUI_SCALE;
	IMAGE::Image img(width, height);
	img.mSamplingMode = IMAGE::SamplingModeType::SAMPLING_3x3;

	// convert corrdinate [0~6],[0~4] to [width], [height] without scale
	auto convertitox = [width, height, scale](vec2 p) {
		lf diff = scale;
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

	lf radius_scale = scale;
	lf radius_max = 35.0 / 160.0 * radius_scale;
	lf radius_min = 24.0 / 160.0 * radius_scale;
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

	//magic number!
	lf n_scale = 2.0;
	lf u_scale = sqrt(2.0);
	lf i_scale = sqrt(0.5);
	std::vector<std::vector<lf>> vdo = {
		// n
		{0, n_scale},
		{0, 0},
		{n_scale, 0},
		// u
		{0, 1},
		{u_scale, u_scale},
		{1, 0},
		// i
		{0, i_scale},
		{1, 0},
		{0, 1},
		{i_scale, 0},
		{i_scale, i_scale},
	};

	int vl = vn.size();
	lf rr = 0.37;
	lf gg = 0.67;
	lf bb = 0.92;


	img.clean(rr, gg, bb);
	//img.set_transparency_color(255, 255, 255);
	for (int i = 0; i < img.h; i++) {
		for (int j = 0; j < img.w; j++) {
			int id = i * img.w + j;
			img.data[id * 4 + 3] = 0;
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

		img.draw_polygon(4, px, py, rr, gg, bb, 1);
	}

	if (sample_image_changed(img, filename)) {
		img.Save(filename);
	}
}

void generate_sample12()
{
	printf("Sample 12 : NUI Infographic\n");

	std::string filename = sampleImagesDir + "sample12.png";

	int i, j, k;
	int width = NUI_WIDTH;
	int height = NUI_HEIGHT;
	lf scale = NUI_SCALE;
	IMAGE::Image img(width, height);
	img.mSamplingMode = IMAGE::SamplingModeType::SAMPLING_3x3;
	img.mAlphaBehavior = IMAGE::AlphaBehaviorType::ONE;

	// convert corrdinate [0~6],[0~4] to [width], [height] without scale
	auto convertitox = [width, height, scale](vec2 p) {
		lf diff = scale;
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

	lf radius_scale = scale;
	lf radius_max = 35.0 / 160.0 * radius_scale;
	lf radius_min = 24.0 / 160.0 * radius_scale;
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

	//magic number!
	lf n_scale = 2.0;
	lf u_scale = sqrt(2.0);
	lf i_scale = sqrt(0.5);
	std::vector<std::vector<lf>> vdo = {
		// n
		{0, n_scale},
		{0, 0},
		{n_scale, 0},
		// u
		{0, 1},
		{u_scale, u_scale},
		{1, 0},
		// i
		{0, i_scale},
		{1, 0},
		{0, 1},
		{i_scale, 0},
		{i_scale, i_scale},
	};

	img.clean(1.0, 1.0, 1.0);
	img.set_transparency_color(255, 255, 255);

	int vl = vn.size();
	lf base_alpha = 1.0;
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
			if (img.data[id * 4 + 3] > 0) {
				img.data[id * 4 + 0] = 255;
				img.data[id * 4 + 1] = 255;
				img.data[id * 4 + 2] = 255;
				int z = base_alpha * img.data[id * 4 + 3];
				if (z < 0)z = 0;
				if (z > 255)z = 255;
				img.data[id * 4 + 3] = z;
			}
		}
	}

	img.mAlphaBehavior = IMAGE::AlphaBehaviorType::ONE_MINUS_ALPHA;
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

		img.draw_polygon(4, px, py, rr, gg, bb, 1);
	}

	if (sample_image_changed(img, filename)) {
		img.Save(filename);
	}
}
int main() {
	//generate_sample1();
	//generate_sample2();
	//generate_sample3();
	//generate_sample4();
	//generate_sample5();
	//generate_sample6();
	//generate_sample7();
	//generate_sample8();
	//generate_sample9();
	generate_sample10();
	generate_sample11();
	generate_sample12();
	return 0;
}