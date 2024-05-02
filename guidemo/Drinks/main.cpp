#include <CtrlLib/CtrlLib.h>
#include <AutoScroller/AutoScroller.h>
#define LAYOUTFILE <Drinks/drinks.lay>
#include <CtrlCore/lay.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "drinks.h"


using namespace Upp;

class MyAppWindow : public WithMainAppWindow<TopWindow> //with layout name from layout file
{
	public:
		MyAppWindow();
		//~MyAppWindow();
		AutoScroller scroller;
		WithDrinks<ParentCtrl> scroller_view;
		//WithFlavors<ParentCtrl> flav_view;
		Option flavor[10];
};

MyAppWindow::MyAppWindow()
{
	CtrlLayout(*this, "Drink Order Form");
	Sizeable().Zoomable();
	scroller.EnableScroll();
	Add(scroller.SizePos());
	CtrlLayout(scroller_view);
	scroller.AddPane(scroller_view);
	scroller_view.base = -1;
	scroller_view.size = -1;
	scroller_view.temp = -1;
	for(int i = 0 ; i< 6; i++)
	{
		scroller_view.dairy.Add(dairyStr[i]);
	}
	//scroller_view.Add(flav_view.SizePos());
	
	for(int i = 0; i < 10; i++)
	{
		flavor[i].SetLabel(flavStr[i].c_str());
	}
	int l = 0;
	int optionSize = 100;
	int checkDist = 20;
	int checkCount = 0;
	for(int i = 0; i < 10; i++)
	{
		scroller_view.options.Add(flavor[i].LeftPosZ(l + optionSize*(i%2),optionSize).TopPosZ(0 + checkDist * checkCount));
		if(i % 2 == 1)
		{
			checkCount++;
		}
	}
	scroller_view.price.Disable();
}


GUI_APP_MAIN
{
	MyAppWindow app;
	app.Run();
}
