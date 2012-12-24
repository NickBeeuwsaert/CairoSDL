#include "CairoSDL.hpp"
#include <SDL/SDL.h>
#include <cairo.h>
#define LERP(s,e,t) (s+(e-s)*(double)t)
CairoSDL::CairoSDL(SDL_Surface *surf){
	this->target_surface = surf;
	if(SDL_MUSTLOCK(this->target_surface)){
		SDL_LockSurface(this->target_surface);
	}
	this->surface = cairo_image_surface_create_for_data (
	    (uint8_t*)surf->pixels,
	    CAIRO_FORMAT_RGB24,
	    surf->w,
	    surf->h,
	    surf->pitch);
    this->context = cairo_create(this->surface);
}

void CairoSDL::moveTo(double x, double y, bool rel){
	if(rel)
		cairo_rel_move_to(this->context, x, y);
	else
		cairo_move_to(this->context, x, y);
}
void CairoSDL::lineTo(double x, double y, bool rel){
	if(rel)
		cairo_rel_line_to(this->context, x, y);
	else
		cairo_line_to(this->context, x, y);
}
void CairoSDL::beginPath(bool subpath){
	if(subpath)
		cairo_new_sub_path(this->context);
	else
		cairo_new_path(this->context);
	
}
void CairoSDL::closePath(){
	cairo_close_path(this->context);
}
void CairoSDL::arc(double x, double y, double radius, double start, double end, bool negative){
	if(negative)
		cairo_arc_negative(this->context, x, y, radius, start, end);
	else
		cairo_arc(this->context, x, y, radius, start, end);
}
void CairoSDL::bezierCurveTo(double x1, double y1, double x2, double y2, double x3, double y3, bool rel){
	if(rel)
		cairo_rel_curve_to(this->context, x1, y1, x2, y2, x3, y3);
	else
		cairo_curve_to(this->context, x1, y1, x2, y2, x3, y3);
}
void CairoSDL::quadraticCurveTo(double x1, double y1, double x2, double y2, bool rel){
	//TODO: implement
	//I think it is 2/3 from AB and the same for CB
	// Where A is the start point
	//		 B is the control point
	//		 C is the endpoint
	double x, y;
	cairo_get_current_point(this->context, &x, &y);
	if(rel){
		x1 += x;
		y1 += y;
		
		x2 += x;
		y2 += y;
	}
	double cp1x = LERP(x, x1, 2/3.);
	double cp1y = LERP(y, y1, 2/3.);
	double cp2x = LERP(x1, x2, 1.0 - (2/3.0));
	double cp2y = LERP(y1, y2, 1.0 - (2/3.0));
	
	cairo_curve_to(this->context, cp1x, cp1y, cp2x, cp2y, x2, y2);
	
}
void CairoSDL::fill(bool preserve){
	if(preserve)
		cairo_fill_preserve(this->context);
	else
		cairo_fill(this->context);
}
void CairoSDL::stroke(bool preserve){
	if(preserve)
		cairo_stroke_preserve(this->context);
	else
		cairo_stroke(this->context);
}
void CairoSDL::lineWidth(double w){
	cairo_set_line_width(this->context, w);
}
void CairoSDL::setRGB(double r, double g, double b){
	cairo_set_source_rgb(this->context, r,g,b);
}
CairoSDL::~CairoSDL(){
	//printf("Be free!\n");
	cairo_destroy(this->context);
	cairo_surface_destroy(this->surface);
	if(SDL_MUSTLOCK(this->target_surface)){
		SDL_UnlockSurface(this->target_surface);
	}
}
