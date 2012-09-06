#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"

#define MAX_TILE_COUNT_X 100
#define MAX_TILE_COUNT_Y 10

using namespace ci;
using namespace ci::app;
using namespace std;

class InterpolationPaletteApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
    
    int mTileCountX;
    int mTileCountY;

    float mTileSizeX;
    float mTileSizeY;
    Vec2f leftColors[MAX_TILE_COUNT_Y];
    Vec2f rightColors[MAX_TILE_COUNT_Y];
    
    float currentH;
    float currentS;
    float currentB;
    
    Perlin mPerlin;
};

void InterpolationPaletteApp::setup()
{
    mTileCountX = MAX_TILE_COUNT_X;
    mTileCountY = MAX_TILE_COUNT_Y;
    
    gl::enableAlphaBlending();
    
    for (int i = 0; i < MAX_TILE_COUNT_Y; i++) {
        
        leftColors[i] = Vec2f(Rand::randFloat(),Rand::randFloat());
        
    }
    for (int i = 0; i < MAX_TILE_COUNT_Y; i++) {
        
        rightColors[i] = Vec2f(Rand::randFloat(),Rand::randFloat());
    }
    
    
}

void InterpolationPaletteApp::mouseDown( MouseEvent event )
{
}

void InterpolationPaletteApp::mouseMove( MouseEvent event )
{
    mTileCountX = lmap((float)event.getX(), (float)0, (float)getWindowWidth(), (float)0, (float)MAX_TILE_COUNT_X);
    mTileCountX = constrain(mTileCountX, 1, MAX_TILE_COUNT_X);
    
    mTileCountY = lmap((float)event.getY(), (float)0, (float)getWindowHeight(), (float)0, (float)MAX_TILE_COUNT_Y);
    mTileCountY = constrain(mTileCountY, 1, MAX_TILE_COUNT_Y);
    
    mTileSizeX = (float) getWindowWidth() / mTileCountX;
    mTileSizeY = (float) getWindowHeight() / mTileCountY;
    
}

void InterpolationPaletteApp::update()
{
    //printf("%f", mPerlin.fBm(1.0f));
//    printf("windowWidth: %i, mTileCountX: %i, mTileSizeX: %f\n",getWindowWidth(), mTileCountX, mTileSizeX);
}

void InterpolationPaletteApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    for (int gridY = 0; gridY < mTileCountY; gridY++) {
        // hue 설정 (버렸음)
        //float hue = lerp(0.0f, 1.0f, (float)gridY/mTileCountY);
        Vec2f leftColorVector = leftColors[gridY];
        Vec2f rightColorVector = rightColors[gridY];
        
        // 세로축의 첫컬러.
        for (int gridX = 0; gridX < mTileCountX; gridX++) {
            // 현재 칸의 위치 설정(버렸음)
            //float sat = lerp(1.0f, 0.0f, (float)gridX/mTileCountX);
            //gl::color( ColorA(CM_HSV, hue, sat,1.0f) );
            currentH = lerp(leftColorVector.x, rightColorVector.x, (float)gridX/mTileCountX); //각 컬러 벡터의 h 값을 가지고 선형 인터폴레이션
            currentS = lerp(leftColorVector.y, rightColorVector.y, (float)gridX/mTileCountX);
            
            gl::color(ColorA(CM_HSV,currentH,currentS,1.0f));
            
            float posX1 = mTileSizeX * gridX;
            float posY1 = mTileSizeY * gridY;
            float posX2 = posX1 + mTileSizeX;
            float posY2 = posY1 + mTileSizeY;
            
            gl::drawSolidRect(Rectf(posX1, posY1, posX2, posY2));
            
            
        }
    }
    
}

CINDER_APP_BASIC( InterpolationPaletteApp, RendererGl )
