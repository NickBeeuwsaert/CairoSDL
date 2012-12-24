#ifndef __CAIRO_SDL__
#include <SDL/SDL.h>
#include <cairo.h>
class CairoSDL {
	cairo_t *context;
	cairo_surface_t *surface;
	SDL_Surface *target_surface;
	public:
		CairoSDL(SDL_Surface*);
		
		void moveTo(double, double, bool=false);
		void lineTo(double, double, bool=false);
		void beginPath(bool=false);
		void closePath();
		void arc(double, double, double, double, double, bool=false);
		void bezierCurveTo(double, double, double, double, double, double, bool=false);
		void quadraticCurveTo(double, double, double, double, bool=false);
		void stroke(bool=false);
		void lineWidth(double);
		void fill(bool=false);
		void setRGB(double, double, double);
		
		
		~CairoSDL();
};
typedef CairoSDL Context;

#endif //__CAIRO_SDL__
