#ifndef PLANE_H_
#define PLANE_H_
#include "bscode.h"
LTexture gPLANETexture;

LTexture gBGTexture;

class plane
{
    public:
		static const int PLANE_WIDTH = 60;
		static const int PLANE_HEIGHT = 30;

		static const int PLANE_VEL = 8;

		plane();

		void handleEvent( SDL_Event& e );

		void move();

		void render();

    private:

		int mPosX, mPosY;

		int mVelX, mVelY;
		
};
#endif