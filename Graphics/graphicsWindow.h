
#ifndef CSE167_graphicsWindow_h
#define CSE167_graphicsWindow_h

class graphicsWindow	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void processNormalKeys(unsigned char key, int x, int y);
};

#endif

