#include "atUserInterface.h"

atRenderEngine::atUserInterface::atUserInterface(int width, int height)
{
	TwDefine(" GLOBAL fontscaling=5 "); // double the size of all fonts
	// Initialize AntTweakBar
	if (!TwInit(TW_OPENGL_CORE, NULL))
	{
		std::cout << "Ant Tweak Bar init failed" << std::endl;
		return;
	}
	
	// Tell the window size to AntTweakBar
	TwWindowSize(width, height);

	// Create a tweak bar
	bar = TwNewBar("TweakBar");
	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with SDL and OpenGL.\nPress [Space] to toggle fullscreen.' "); // Message added to the help bar.
	TwDefine("TweakBar position= '0 0'");
	TwDefine("TweakBar size= '300 1080'");
	TwDefine("TweakBar resizable=true ");

	TwDefine("TweakBar movable=true ");
	// Add 'width' and 'height' to 'bar': they are read-only (RO) variables of type TW_TYPE_INT32.
	TwAddVarRO(bar, "Width", TW_TYPE_INT32, &width,
		" label='Wnd width' help='Width of the graphics window (in pixels)' ");

	TwAddVarRO(bar, "Height", TW_TYPE_INT32, &height,
		" label='Wnd height' help='Height of the graphics window (in pixels)' ");

	// Add 'numCurves' to 'bar': this is a modifiable variable of type TW_TYPE_INT32. Its shortcuts are [c] and [C].
	TwAddVarRW(bar, "NumCubes", TW_TYPE_INT32, &numCubes,
		" label='Number of cubes' min=1 max=100 keyIncr=c keyDecr=C help='Defines the number of cubes in the scene.' ");

	// Add 'ka', 'kb and 'kc' to 'bar': they are modifiable variables of type TW_TYPE_DOUBLE
	TwAddVarRW(bar, "ka", TW_TYPE_DOUBLE, &ka,
		" label='X path coeff' keyIncr=1 keyDecr=CTRL+1 min=-10 max=10 step=0.01 ");
	TwAddVarRW(bar, "kb", TW_TYPE_DOUBLE, &kb,
		" label='Y path coeff' keyIncr=2 keyDecr=CTRL+2 min=-10 max=10 step=0.01 ");
	TwAddVarRW(bar, "kc", TW_TYPE_DOUBLE, &kc,
		" label='Z path coeff' keyIncr=3 keyDecr=CTRL+3 min=-10 max=10 step=0.01 ");

	// Add 'color0' and 'color1' to 'bar': they are modifable variables of type TW_TYPE_COLOR3F (3 floats color)
	TwAddVarRW(bar, "color0", TW_TYPE_COLOR3F, &color0,
		" label='Start color' help='Color of the first cube.' ");
	TwAddVarRW(bar, "color1", TW_TYPE_COLOR3F, &color1,
		" label='End color' help='Color of the last cube. Cube colors are interpolated between the Start and End colors.' ");

	// Add 'quit' to 'bar': this is a modifiable (RW) variable of type TW_TYPE_BOOL32 
	// (a boolean stored in a 32 bits integer). Its shortcut is [ESC].
	TwAddVarRW(bar, "Quit", TW_TYPE_BOOL32, &quit,
		" label='Quit?' true='+' false='-' key='ESC' help='Quit program.' ");

}

atRenderEngine::atUserInterface::~atUserInterface()
{
	TwTerminate();
}

void atRenderEngine::atUserInterface::Draw()
{
	TwDraw();
}
