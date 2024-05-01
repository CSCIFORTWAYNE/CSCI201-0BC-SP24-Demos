#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyAppWindow : TopWindow
{
	Label baseLbl;
	
	MyAppWindow()
	{
		baseLbl.SetLabel("Drink Base:");
		Add(baseLbl);
		baseLbl.LeftPosZ(10, 104).TopPosZ(10);
	};
};

GUI_APP_MAIN
{
	MyAppWindow app;
	app.Run();
}
