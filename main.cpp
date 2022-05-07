
#include "bscode.h"
#include "plane.h"

bool init();

bool loadMedia();

void close();

bool init()
{

	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Plane Control", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{

			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
			
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if( !gPLANETexture.loadFromFile( "plane.bmp" ) )
	{
		printf( "Failed to load plane texture!\n" );
		success = false;
	}

	if( !gBGTexture.loadFromFile( "bg600.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void close()
{

	gPLANETexture.free();
	gBGTexture.free();

	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	int mVelS = 0;

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			bool quit = false;

			SDL_Event e;

			plane plane;


			int scrollingOffset = 0;


			while( !quit )
			{

				while( SDL_PollEvent( &e ) != 0 )
				{

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					

					plane.handleEvent( e );
				if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    				{
        				switch( e.key.keysym.sym )
        				{
						//case SDLK_LEFT: mVelS -=10 ; break;
            			case SDLK_RIGHT: mVelS +=10; break;
        				}
    				}
				else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    				{
        				switch( e.key.keysym.sym ) {
        				//case SDLK_LEFT: mVelS += 10; break;
            			case SDLK_RIGHT: mVelS -= 10; break;
        			}
    				}
				}

				plane.move();
				
					
					
				scrollingOffset --;	
				scrollingOffset-=mVelS;
				if( scrollingOffset > 0 )
				{
					scrollingOffset = -gBGTexture.getWidth();
				}
				if( scrollingOffset < -gBGTexture.getWidth() )
				{
					scrollingOffset = 0;
				}


				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				
				gBGTexture.render( scrollingOffset, 0 );
				gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

				
				plane.render();

				
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}