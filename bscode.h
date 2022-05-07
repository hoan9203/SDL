#ifndef BSCODE_H_
#define BSCODE_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>




const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

class LTexture
{
	public:

		LTexture();
	
		~LTexture();


		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif


		void free();

		void setColor( Uint8 red, Uint8 green, Uint8 blue );


		void setBlendMode( SDL_BlendMode blending );


		void setAlpha( Uint8 alpha );
		

		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );


		int getWidth();
		int getHeight();

	private:

		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};

#endif
