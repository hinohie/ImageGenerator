#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

#include <stdio.h>
#include <vector>

using namespace IMAGE;

/**********************************
*                                 *
*        --> j                    *
*        --> x                    *
*   | | 0,0              w-1,0    *
*   | |                           *
*   v v                           *
*   i y                           *
*                                 *
*                                 *
*       0,h-1             w-1,h-1 *
*                                 *
*  data[(i*w+j) * 4 + 0 ~ 3]      *
*      = color at (j,i)           *
*   0 : red, 1 : green, 2 : blue  *
*   3 : alpha. normally 255       *
*                                 *
**********************************/


Image::Image()
	: h(0)
	, w(0)
	, data(NULL)
	, mAlphaBehavior(AlphaBehaviorType::ONE_MINUS_ALPHA)
	, mSamplingMode(SamplingModeType::SAMPLING_CENTER)
{
}

Image::Image(int _w, int _h)
	: h(_h)
	, w(_w)
	, data(new uchar[h * w * 4])
	, mAlphaBehavior(AlphaBehaviorType::ONE_MINUS_ALPHA)
	, mSamplingMode(SamplingModeType::SAMPLING_CENTER)
{
	clean();
}

Image::Image(const Image& other)
	: h(other.h)
	, w(other.w)
	, data(new uchar[h * w * 4])
	, mAlphaBehavior(other.mAlphaBehavior)
	, mSamplingMode(other.mSamplingMode)
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int id = i * w + j;
			data[id * 4 + 0] = other.data[id * 4 + 0];
			data[id * 4 + 1] = other.data[id * 4 + 1];
			data[id * 4 + 2] = other.data[id * 4 + 2];
			data[id * 4 + 3] = other.data[id * 4 + 3];
		}
	}
}

Image::Image(Image&& other)
	: h(other.h)
	, w(other.w)
	, data(other.data)
	, mAlphaBehavior(other.mAlphaBehavior)
	, mSamplingMode(other.mSamplingMode)
{
	other.h = 0;
	other.w = 0;
	other.data = NULL;
}

Image::Image(const std::string& filename)
	: h(0)
	, w(0)
	, data(NULL)
	, mAlphaBehavior(AlphaBehaviorType::ONE_MINUS_ALPHA)
	, mSamplingMode(SamplingModeType::SAMPLING_CENTER)
{
	Load(filename);
}

Image::~Image() { if (data) delete[] data; }


Image& Image::operator = (const Image& other)
{
	Image copy(other);
	std::swap(*this, copy);
	return *this;
}

Image& Image::operator = (Image&& other)
{
	if (&other == this) { return *this; }

	std::swap(h, other.h);
	std::swap(w, other.w);
	std::swap(data, other.data);
	std::swap(mAlphaBehavior, other.mAlphaBehavior);
	std::swap(mSamplingMode, other.mSamplingMode);

	return *this;
}

void Image::setsize(int _w, int _h) {
	h = _h; w = _w;
	if (data)delete[] data;
	data = new uchar[h * w * 4];
	clean();
}

uchar Image::dtoc(double x) {
	int xx = x * 255;
	if (xx < 0)xx = 0;
	if (xx > 255)xx = 255;
	return xx;
}

void Image::clean(double rr, double gg, double bb) {
	uchar r = dtoc(rr);
	uchar g = dtoc(gg);
	uchar b = dtoc(bb);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int id = i * w + j;
			data[id * 4 + 0] = r;
			data[id * 4 + 1] = g;
			data[id * 4 + 2] = b;
			data[id * 4 + 3] = 255;
		}
	}
}

void Image::set_pixel(int i, int j, double rr, double gg, double bb, double aa) {
	if (i < 0) { return; }
	if (j < 0) { return; }
	if (i >= h) { return; }
	if (j >= w) { return; }
	int id = i * w + j;
	double pr = data[id * 4 + 0] / 255.0;
	double pg = data[id * 4 + 1] / 255.0;
	double pb = data[id * 4 + 2] / 255.0;
	double pa = 1.0 - aa;
	if (mAlphaBehavior == AlphaBehaviorType::ONE) {
		pa = 1.0;
	}

	uchar r = dtoc(rr * aa + pr * pa);
	uchar g = dtoc(gg * aa + pg * pa);
	uchar b = dtoc(bb * aa + pb * pa);
	data[id * 4 + 0] = r;
	data[id * 4 + 1] = g;
	data[id * 4 + 2] = b;
	data[id * 4 + 3] = 255;
}
void Image::draw_circle(double cx, double cy, double radius, double rr, double gg, double bb, double aa) {
	for (int ci = cy - radius - 1; ci <= cy + radius + 1; ci++) {
		for (int cj = cx - radius - 1; cj <= cx + radius + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (di * di + dj * dj <= radius * radius) {
				set_pixel(ci, cj, rr, gg, bb, aa);
			}
		}
	}
}
void Image::draw_circle_border(double cx, double cy, double radius, double border_width, double rr, double gg, double bb, double aa) {
	for (int ci = cy - radius - border_width / 2.0 - 1; ci <= cy + radius + border_width / 2.0 + 1; ci++) {
		for (int cj = cx - radius - border_width / 2.0 - 1; cj <= cx + radius + border_width / 2.0 + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (di * di + dj * dj <= (radius+ border_width / 2.0) * (radius+ border_width / 2.0) && di * di + dj * dj >= (radius - border_width / 2.0) * (radius - border_width / 2.0)) {
				set_pixel(ci, cj, rr, gg, bb, aa);
			}
		}
	}
}
void Image::draw_diamond(double cx, double cy, double radius, double rr, double gg, double bb, double aa) {
	for (int ci = cy - radius - 1; ci <= cy + radius + 1; ci++) {
		for (int cj = cx - radius - 1; cj <= cx + radius + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (abs(di) + abs(dj) <= radius) {
				set_pixel(ci, cj, rr, gg, bb, aa);
			}
		}
	}
}
void Image::draw_diamond_border(double cx, double cy, double radius, double border_width, double rr, double gg, double bb, double aa) {
	for (int ci = cy - radius - border_width / 2.0 - 1; ci <= cy + radius + border_width / 2.0 + 1; ci++) {
		for (int cj = cx - radius - border_width / 2.0 - 1; cj <= cx + radius + border_width / 2.0 + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (abs(di) + abs(dj) <= radius + border_width / 2.0 && abs(di) + abs(dj) >= radius - border_width / 2.0) {
				set_pixel(ci, cj, rr, gg, bb, aa);
			}
		}
	}
}
void Image::draw_rectangle(double cx, double cy, double px, double py, double rr, double gg, double bb, double aa) {
	if (cx > px)std::swap(cx, px);
	if (cy > py)std::swap(cy, py);
	for (int ci = cy - 1; ci <= py + 1; ci++) {
		for (int cj = cx - 1; cj <= px + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (di >= -E && dj >= -E && di <= py - cy + E && dj <= px - cx + E) {
				set_pixel(ci, cj, rr, gg, bb, aa);
			}
		}
	}
}
void Image::draw_rectangle_border(double cx, double cy, double px, double py, double border_width, double rr, double gg, double bb, double aa) {
	if (cx > px)std::swap(cx, px);
	if (cy > py)std::swap(cy, py);
	for (int ci = cy - border_width / 2.0 - 1; ci <= py + border_width / 2.0 + 1; ci++) {
		for (int cj = cx - border_width / 2.0 - 1; cj <= px + border_width / 2.0 + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			double ei = ci - py;
			double ej = cj - px;
			if (di >= -border_width / 2.0 -E && dj >= -border_width / 2.0 -E && di <= border_width / 2.0 + py - cy + E && dj <= border_width / 2.0 + px - cx + E) {
				if (abs(di) <= border_width / 2.0 || abs(dj) <= border_width / 2.0 || abs(ei) <= border_width / 2.0 || abs(ej) <= border_width / 2.0) {
					set_pixel(ci, cj, rr, gg, bb, aa);
				}
			}
		}
	}
}
void Image::draw_line(double cx, double cy, double px, double py, double radius, double rr, double gg, double bb, double aa) {
	std::vector<std::vector<bool>> vb(h, std::vector<bool>(w, false));
	for (int ci = cy - radius - 1; ci <= cy + radius + 1; ci++) {
		for (int cj = cx - radius - 1; cj <= cx + radius + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (di * di + dj * dj <= radius * radius) {
				/*
				if (di * di + dj * dj <= radius * radius * 0.9) {
					set_pixel(ci, cj, rr, gg, bb);
				}
				else {
					set_pixel(ci, cj, rr * 0.1, gg * 0.1, bb * 0.1);
				}
				*/
				if (ci >= 0 && ci < h && cj >= 0 && cj < w && !vb[ci][cj]) {
					vb[ci][cj] = true;
					set_pixel(ci, cj, rr, gg, bb, aa);
				}
			}
		}
	}
	for (int ci = py - radius - 1; ci <= py + radius + 1; ci++) {
		for (int cj = px - radius - 1; cj <= px + radius + 1; cj++) {
			double di = ci - py;
			double dj = cj - px;
			if (di * di + dj * dj <= radius * radius) {
				/*
				if (di * di + dj * dj <= radius * radius * 0.81) {
					set_pixel(ci, cj, rr, gg, bb);
				}
				else {
					set_pixel(ci, cj, rr * 0.1, gg * 0.1, bb * 0.1);
				}
				*/
				if (ci>=0 && ci<h && cj>=0 && cj<w && !vb[ci][cj]) {
					vb[ci][cj] = true;
					set_pixel(ci, cj, rr, gg, bb, aa);
				}
			}
		}
	}
	double vx = px - cx;
	double vy = py - cy;
	double nx = vy;
	double ny = -vx;
	double vv = sqrt(vx * vx + vy * vy);
	if (vv < E)return;
	nx /= vv;
	ny /= vv;
	double det = vx * ny - vy * nx;
	for (int ci = 0; ci < h; ci++) {
		for (int cj = 0; cj < w; cj++) {
			double di = ci - cy;
			double dj = cj - cx;

			double s = ny * dj - nx * di;
			double t = -vy * dj + vx * di;
			s /= det;
			t /= det;
			if (s < 0 || s > 1)continue;
			if (t * t <= radius * radius) {
				/*/
				if (t * t <= radius * radius * 0.81) {
					set_pixel(ci, cj, rr, gg, bb);
				}
				else {
					set_pixel(ci, cj, rr * 0.1, gg * 0.1, bb * 0.1);
				}
				*/
				if (!vb[ci][cj]) {
					vb[ci][cj] = true;
					set_pixel(ci, cj, rr, gg, bb, aa);
				}
			}
		}
	}
}

void Image::draw_line_gradient(double cx, double cy, double px, double py, double radius, double rr, double gg, double bb, double rrr, double ggg, double bbb) {
	for (int ci = cy - radius - 1; ci <= cy + radius + 1; ci++) {
		for (int cj = cx - radius - 1; cj <= cx + radius + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (di * di + dj * dj <= radius * radius) {
				/*
				if (di * di + dj * dj <= radius * radius * 0.9) {
					set_pixel(ci, cj, rr, gg, bb);
				}
				else {
					set_pixel(ci, cj, rr * 0.1, gg * 0.1, bb * 0.1);
				}
				*/
				set_pixel(ci, cj, rr, gg, bb);
			}
		}
	}
	for (int ci = py - radius - 1; ci <= py + radius + 1; ci++) {
		for (int cj = px - radius - 1; cj <= px + radius + 1; cj++) {
			double di = ci - py;
			double dj = cj - px;
			if (di * di + dj * dj <= radius * radius) {
				/*
				if (di * di + dj * dj <= radius * radius * 0.81) {
					set_pixel(ci, cj, rr, gg, bb);
				}
				else {
					set_pixel(ci, cj, rr * 0.1, gg * 0.1, bb * 0.1);
				}
				*/
				set_pixel(ci, cj, rrr, ggg, bbb);
			}
		}
	}
	double vx = px - cx;
	double vy = py - cy;
	double nx = vy;
	double ny = -vx;
	double vv = sqrt(vx * vx + vy * vy);
	if (vv < E)return;
	nx /= vv;
	ny /= vv;
	double det = vx * ny - vy * nx;
	for (int ci = 0; ci < h; ci++) {
		for (int cj = 0; cj < w; cj++) {
			double di = ci - cy;
			double dj = cj - cx;

			double s = ny * dj - nx * di;
			double t = -vy * dj + vx * di;
			s /= det;
			t /= det;
			if (s < 0 || s > 1)continue;
			if (t * t <= radius * radius) {
				/*/
				if (t * t <= radius * radius * 0.81) {
					set_pixel(ci, cj, rr, gg, bb);
				}
				else {
					set_pixel(ci, cj, rr * 0.1, gg * 0.1, bb * 0.1);
				}
				*/
				double zrr = rr * (1.0 - s) + rrr * s;
				double zgg = gg * (1.0 - s) + ggg * s;
				double zbb = bb * (1.0 - s) + bbb * s;
				set_pixel(ci, cj, zrr, zgg, zbb);
			}
		}
	}
}
void Image::draw_image(double cx, double cy, double px, double py, const Image& img) {
	if (cx > px)std::swap(cx, px);
	if (cy > py)std::swap(cy, py);
	// integral_f(x, y) = a[i][j] * (s-s^2/2)*(t-t^2/2) + a[i+1][j] * s^2/2*(t-t^2/2) + a[i][j+1] * (s-s^2/2)*t^2/2 + a[i+1][j+1]s^2/2*t^2/2

	auto f = [&img](int offset, int i, int j, double di, double dj) -> double {
		int ti = i + 1;
		int tj = j + 1;
		if (i < 0)i = 0; if (i >= img.h)i = img.h - 1;
		if (j < 0)j = 0; if (j >= img.w)j = img.w - 1;
		if (ti < 0)ti = 0; if (ti >= img.h)ti = img.h - 1;
		if (tj < 0)tj = 0; if (tj >= img.w)tj = img.w - 1;
		double s = di - i;
		double t = dj - j;
		double ss2 = s * s / 2.0;
		double tt2 = t * t / 2.0;
		if (s < 0)s = 0; if (s > 1.0)s = 1.0;
		if (t < 0)t = 0; if (t > 1.0)t = 1.0;
		double pp = img.data[(i * img.w + j) * 4 + offset];
		double pq = img.data[(i * img.w + tj) * 4 + offset];
		double qp = img.data[(ti * img.w + j) * 4 + offset];
		double qq = img.data[(ti * img.w + tj) * 4 + offset];

		return (pp * (s - ss2) + qp * ss2) * (t - tt2) + (pq * (s - ss2) + qq * ss2) * tt2;
	};

	auto ff = [&f, &img](int offset, int i, int j, double di, double dj, double zi, double zj) -> double {
		return f(offset, i, j, zi, zj) - f(offset, i, j, zi, dj) - f(offset, i, j, di, zj) + f(offset, i, j, di, dj);
	};

	for (int ci = cy - 1; ci <= py + 1; ci++) {
		for (int cj = cx - 1; cj <= px + 1; cj++) {
			double di = ci - cy;
			double dj = cj - cx;
			if (di >= -E && dj >= -E && di <= py - cy + E && dj <= px - cx + E) {
				double rr = 0;
				double gg = 0;
				double bb = 0;
				double aa = 0;

				double ndi = di / (py - cy + 1) * img.h;
				double ndj = dj / (px - cx + 1) * img.w;
				double zdi = (di + 1) / (py - cy + 1) * img.h;
				double zdj = (dj + 1) / (px - cx + 1) * img.w;

				int indi = floor(ndi);
				int indj = floor(ndj);
				int izdi = floor(zdi);
				int izdj = floor(zdj);

				//printf("%d %d  %lf %lf  %lf %lf  %lf %lf  %d %d %d %d\n", ci, cj, di, dj, ndi, ndj, zdi, zdj, indi, indj, izdi, izdj);
				if (indi == izdi) {
					if (indj == izdj) {
						rr = ff(0, indi, indj, ndi, ndj, zdi, zdj);
						gg = ff(1, indi, indj, ndi, ndj, zdi, zdj);
						bb = ff(2, indi, indj, ndi, ndj, zdi, zdj);
						aa = ff(3, indi, indj, ndi, ndj, zdi, zdj);
					}
					else {
						rr += ff(0, indi, indj, ndi, ndj, zdi, indj + 1.0);
						gg += ff(1, indi, indj, ndi, ndj, zdi, indj + 1.0);
						bb += ff(2, indi, indj, ndi, ndj, zdi, indj + 1.0);
						aa += ff(3, indi, indj, ndi, ndj, zdi, indj + 1.0);
						for (int tj = indj + 1; tj < izdj; tj++) {
							rr += ff(0, indi, tj, ndi, tj, zdi, tj + 1.0);
							gg += ff(1, indi, tj, ndi, tj, zdi, tj + 1.0);
							bb += ff(2, indi, tj, ndi, tj, zdi, tj + 1.0);
							aa += ff(3, indi, tj, ndi, tj, zdi, tj + 1.0);
						}
						rr += ff(0, indi, izdj, ndi, izdj, zdi, zdj);
						gg += ff(1, indi, izdj, ndi, izdj, zdi, zdj);
						bb += ff(2, indi, izdj, ndi, izdj, zdi, zdj);
						aa += ff(3, indi, izdj, ndi, izdj, zdi, zdj);
					}
				}
				else {
					if (indj == izdj) {
						rr += ff(0, indi, indj, ndi, ndj, indi + 1.0, zdj);
						gg += ff(1, indi, indj, ndi, ndj, indi + 1.0, zdj);
						bb += ff(2, indi, indj, ndi, ndj, indi + 1.0, zdj);
						aa += ff(3, indi, indj, ndi, ndj, indi + 1.0, zdj);
						for (int ti = indi + 1; ti < izdi; ti++) {
							rr += ff(0, ti, indj, ti, ndj, ti + 1.0, zdj);
							gg += ff(1, ti, indj, ti, ndj, ti + 1.0, zdj);
							bb += ff(2, ti, indj, ti, ndj, ti + 1.0, zdj);
							aa += ff(3, ti, indj, ti, ndj, ti + 1.0, zdj);
						}
						rr += ff(0, izdi, indj, izdi, ndj, zdi, zdj);
						gg += ff(1, izdi, indj, izdi, ndj, zdi, zdj);
						bb += ff(2, izdi, indj, izdi, ndj, zdi, zdj);
						aa += ff(3, izdi, indj, izdi, ndj, zdi, zdj);
					}
					else {
						rr += ff(0, indi, indj, ndi, ndj, indi + 1.0, indj + 1.0);
						gg += ff(1, indi, indj, ndi, ndj, indi + 1.0, indj + 1.0);
						bb += ff(2, indi, indj, ndi, ndj, indi + 1.0, indj + 1.0);
						aa += ff(3, indi, indj, ndi, ndj, indi + 1.0, indj + 1.0);
						for (int tj = indj + 1; tj < izdj; tj++) {
							rr += ff(0, indi, tj, ndi, tj, indi + 1.0, tj + 1.0);
							gg += ff(1, indi, tj, ndi, tj, indi + 1.0, tj + 1.0);
							bb += ff(2, indi, tj, ndi, tj, indi + 1.0, tj + 1.0);
							aa += ff(3, indi, tj, ndi, tj, indi + 1.0, tj + 1.0);
						}
						rr += ff(0, indi, izdj, ndi, izdj, indi + 1.0, zdj);
						gg += ff(1, indi, izdj, ndi, izdj, indi + 1.0, zdj);
						bb += ff(2, indi, izdj, ndi, izdj, indi + 1.0, zdj);
						aa += ff(3, indi, izdj, ndi, izdj, indi + 1.0, zdj);
						for (int ti = indi + 1; ti < izdi; ti++) {
							rr += ff(0, ti, indj, ti, ndj, ti + 1.0, indj + 1.0);
							gg += ff(1, ti, indj, ti, ndj, ti + 1.0, indj + 1.0);
							bb += ff(2, ti, indj, ti, ndj, ti + 1.0, indj + 1.0);
							aa += ff(3, ti, indj, ti, ndj, ti + 1.0, indj + 1.0);
							for (int tj = indj + 1; tj < izdj; tj++) {

								rr += ff(0, ti, tj, ti, tj, ti + 1.0, tj + 1.0);
								gg += ff(1, ti, tj, ti, tj, ti + 1.0, tj + 1.0);
								bb += ff(2, ti, tj, ti, tj, ti + 1.0, tj + 1.0);
								aa += ff(3, ti, tj, ti, tj, ti + 1.0, tj + 1.0);
							}
							rr += ff(0, ti, izdj, ti, izdj, ti + 1.0, zdj);
							gg += ff(1, ti, izdj, ti, izdj, ti + 1.0, zdj);
							bb += ff(2, ti, izdj, ti, izdj, ti + 1.0, zdj);
							aa += ff(3, ti, izdj, ti, izdj, ti + 1.0, zdj);
						}
						rr += ff(0, izdi, indj, izdi, ndj, zdi, indj + 1.0);
						gg += ff(1, izdi, indj, izdi, ndj, zdi, indj + 1.0);
						bb += ff(2, izdi, indj, izdi, ndj, zdi, indj + 1.0);
						aa += ff(3, izdi, indj, izdi, ndj, zdi, indj + 1.0);
						for (int tj = indj + 1; tj < izdj; tj++) {
							rr += ff(0, izdi, tj, izdi, tj, zdi, tj + 1.0);
							gg += ff(1, izdi, tj, izdi, tj, zdi, tj + 1.0);
							bb += ff(2, izdi, tj, izdi, tj, zdi, tj + 1.0);
							aa += ff(3, izdi, tj, izdi, tj, zdi, tj + 1.0);
						}
						rr += ff(0, izdi, izdj, izdi, izdj, zdi, zdj);
						gg += ff(1, izdi, izdj, izdi, izdj, zdi, zdj);
						bb += ff(2, izdi, izdj, izdi, izdj, zdi, zdj);
						aa += ff(3, izdi, izdj, izdi, izdj, zdi, zdj);
					}
				}

				rr /= (zdi - ndi) * (zdj - ndj);
				gg /= (zdi - ndi) * (zdj - ndj);
				bb /= (zdi - ndi) * (zdj - ndj);
				aa /= (zdi - ndi) * (zdj - ndj);

				rr /= 255;
				gg /= 255;
				bb /= 255;
				aa /= 255;

				set_pixel(ci, cj, rr, gg, bb, aa);
			}
		}
	}
}


void Image::flip_x() {
	int i, j, k;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w / 2; j++) {
			int id = i * w + j;
			int tid = i * w + (w - j - 1);
			std::swap(data[id * 4 + 0], data[tid * 4 + 0]);
			std::swap(data[id * 4 + 1], data[tid * 4 + 1]);
			std::swap(data[id * 4 + 2], data[tid * 4 + 2]);
			std::swap(data[id * 4 + 3], data[tid * 4 + 3]);
		}
	}
}
void Image::flip_y() {
	int i, j, k;
	for (int i = 0; i < h / 2; i++) {
		for (int j = 0; j < w; j++) {
			int id = i * w + j;
			int tid = (h - i - 1) * w + j;
			std::swap(data[id * 4 + 0], data[tid * 4 + 0]);
			std::swap(data[id * 4 + 1], data[tid * 4 + 1]);
			std::swap(data[id * 4 + 2], data[tid * 4 + 2]);
			std::swap(data[id * 4 + 3], data[tid * 4 + 3]);
		}
	}
}

void Image::Save(const std::string& filename) {
	if (data == NULL) {
		printf("ERROR : Image data is null!\n");
		return;
	}
	stbi_write_png(filename.c_str(), w, h, 4, data, 4 * w);
}
void Image::Load(const std::string& filename) {
	FILE* fp = fopen(filename.c_str(), "rb");
	if (fp == NULL) {
		printf("load fail : %s file not exist\n", filename.c_str());
		return;
	}
	int tmp_width;
	int tmp_height;
	int tmp_c;
	uchar* tmp = stbi_load_from_file(fp, &tmp_width, &tmp_height, &tmp_c, 4);
	if (tmp == NULL) {
		printf("load fail : %s is not image file\n", filename.c_str());

		fclose(fp);
		return;
	}
	if (data != NULL) { delete[] data; data = NULL; }
	data = tmp;
	w = tmp_width;
	h = tmp_height;
	fclose(fp);
}

// double have error rate. so we use uchar value at here
void Image::set_transparency_color(uchar tr, uchar tg, uchar tb, uchar ta, uchar nr, uchar ng, uchar nb) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int id = i * w + j;
			if (data[id * 4 + 0] == tr && data[id * 4 + 1] == tg && data[id * 4 + 2] == tb) {
				data[id * 4 + 0] = nr;
				data[id * 4 + 1] = ng;
				data[id * 4 + 2] = nb;
				data[id * 4 + 3] = ta;
			}
		}
	}
}