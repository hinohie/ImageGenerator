#pragma once

#include<string>
#include<vector>
#include"image_property.h"

namespace IMAGE {
	using uchar = unsigned char;
#define E 1e-9
	class Image {
	public:
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
		int h, w;
		uchar* data;
		Image();
		Image(int _w, int _h);
		Image(const Image& other);
		Image(Image&& other);
		Image(const std::string& filename);
		~Image();

		Image& operator = (const Image& other);
		Image& operator = (Image&& other);

		void setsize(int _w, int _h);
		uchar dtoc(double x);
		void clean(double rr = 1.0, double gg = 1.0, double bb = 1.0);
		void set_pixel(int i, int j, double rr, double gg, double bb, double aa = 1.0);

		void draw_circle(double cx, double cy, double radius, double rr, double gg, double bb, double aa = 1.0);
		void draw_circle_border(double cx, double cy, double radius, double border_width, double rr, double gg, double bb, double aa = 1.0);
		void draw_diamond(double cx, double cy, double radius, double rr, double gg, double bb, double aa = 1.0);
		void draw_diamond_border(double cx, double cy, double radius, double border_width, double rr, double gg, double bb, double aa = 1.0);
		void draw_rectangle(double cx, double cy, double px, double py, double rr, double gg, double bb, double aa = 1.0);
		void draw_rectangle_border(double cx, double cy, double px, double py, double border_width, double rr, double gg, double bb, double aa = 1.0);
		void draw_line(double cx, double cy, double px, double py, double radius, double rr, double gg, double bb, double aa = 1.0);
		void draw_line_gradient(double cx, double cy, double px, double py, double radius, double rr, double gg, double bb, double rrr, double ggg, double bbb);
		void draw_triangle(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double rr, double gg, double bb, double aa = 1.0);
		void draw_polygon(int n, const double *px, const double *py, double rr, double gg, double bb, double aa = 1.0);
		void draw_polygon(int n, const std::vector<double> &px, const std::vector<double> &py, double rr, double gg, double bb, double aa = 1.0);
		void draw_polygon(int n, const double *pxy, double rr, double gg, double bb, double aa = 1.0);
		void draw_polygon(int n, const std::vector<double> &pxy, double rr, double gg, double bb, double aa = 1.0);
		void draw_image(double cx, double cy, double px, double py, const Image& img);

		AlphaBehaviorType mAlphaBehavior;
		SamplingModeType  mSamplingMode;

		void flip_x();
		void flip_y();

		void Save(const std::string& filename);
		void Load(const std::string& filename);

		// double have error rate. so we use uchar value at here
		void set_transparency_color(uchar tr, uchar tg, uchar tb, uchar ta = 0, uchar nr = 0, uchar ng = 0, uchar nb = 0);
	};
} /* namespace IMAGE */