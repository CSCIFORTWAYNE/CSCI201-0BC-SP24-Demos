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
		void SaveOrder();
	private:
		//~MyAppWindow();
		AutoScroller scroller;
		WithDrinks<ParentCtrl> scroller_view;
		//WithFlavors<ParentCtrl> flav_view;
		Option flavor[10];
		drink d;
		std::vector<drink> order;
		Button writeBtn;
		
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
	writeBtn.SetLabel("Complete Order");
	//writeBtn.
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
		
		flavor[i] << [&,this,i]
		{
			if(flavor[i].Get())
			{
				d.addFlavor(flavs[i]);
			}
			else
			{
				d.removeFlavor(flavs[i]);
			}
			if((int)scroller_view.base != -1 &&(int)scroller_view.size != -1 &&(int)scroller_view.temp != -1)
			{
				std::ostringstream priceStr;
				priceStr << std::setprecision(2) << std::fixed << std::showpoint;
				priceStr << "$" << d.getPrice();
				scroller_view.price.SetData(priceStr.str());
			}
		};
	}
	scroller_view.price.Disable();
	
	scroller_view.base << [&,this] // = in [] means local variables by value class members by reference or maybe value
								   // [&, this] everything by reference
	{
		baseType b = static_cast<baseType>((int)scroller_view.base);
		d.setBase(b);
		if((int)scroller_view.temp != -1 &&(int)scroller_view.size != -1)
		{
			std::ostringstream priceStr;
			priceStr << std::setprecision(2) << std::fixed << std::showpoint;
			priceStr << "$" << d.getPrice();
			scroller_view.price.SetData(priceStr.str());
		}
	};
	scroller_view.size << [&,this] // = in [] means local variables by value class members by reference or maybe value
								   // [&, this] everything by reference
	{
		sizeType s = static_cast<sizeType>((int)scroller_view.size);
		d.setSize(s);
		if((int)scroller_view.temp != -1 &&(int)scroller_view.base != -1)
		{
			std::ostringstream priceStr;
			priceStr << std::setprecision(2) << std::fixed << std::showpoint;
			priceStr << "$" << d.getPrice();
			scroller_view.price.SetData(priceStr.str());
		}
	};
	scroller_view.temp << [&,this] // = in [] means local variables by value class members by reference or maybe value
								   // [&, this] everything by reference
	{
		tempType t = static_cast<tempType>((int)scroller_view.temp);
		d.setTemperature(t);
		if((int)scroller_view.base != -1 &&(int)scroller_view.size != -1)
		{
			std::ostringstream priceStr;
			priceStr << std::setprecision(2) << std::fixed << std::showpoint;
			priceStr << "$" << d.getPrice();
			scroller_view.price.SetData(priceStr.str());
		}
	};
	scroller_view.dairy << [&, this]
	{
		d.setDairy(scroller_view.dairy.GetData().ToStd());
		if((int)scroller_view.base != -1 &&(int)scroller_view.size != -1 &&(int)scroller_view.temp != -1)
		{
			std::ostringstream priceStr;
			priceStr << std::setprecision(2) << std::fixed << std::showpoint;
			priceStr << "$" << d.getPrice();
			scroller_view.price.SetData(priceStr.str());
		}	
	};
	scroller_view.createDrink << [&, this]
	{
			
		if((int)scroller_view.base == -1 || (int)scroller_view.size == -1 ||(int)scroller_view.temp == -1)
		{
			ErrorOK("Please choose the base, size and temperature");
			return;
		}
		std::string dairyStr = scroller_view.dairy.GetData().ToStd();
		if(dairyStr.empty())
		{
			ErrorOK("Please make a dairy choice");
			return;
		}
		order.push_back(d);
		std::ostringstream drinkStr;
		drinkStr << d << std::endl;
		scroller_view.drinkList.Append(drinkStr.str());
		scroller_view.base = -1;
		d.setBase(CREAM);
		scroller_view.temp = -1;
		d.setTemperature(HOT);
		scroller_view.size = -1;
		d.setSize(SMALL);
		scroller_view.dairy <<= "";
		d.setDairy("");
		d.removeAllFlavor();
		for(int i = 0; i < 10; i++)
		{
			flavor[i] = 0;	
		}
		scroller_view.price.SetData("");
		scroller_view.writeBtnParent.Add(writeBtn.HSizePosZ().VSizePosZ());
	};
	writeBtn << [=]{SaveOrder();};
	
	
}

void MyAppWindow::SaveOrder()
{
	std::ofstream out("order.txt");
	out << std::setprecision(2) << std::fixed << std::showpoint;
	double total = 0;
	for(int i = 0; i < order.size(); i++)
	{
		out << order[i] << std::endl;
		total += order[i].getPrice();
	}
	out << "Total: $" << total;
	out.close();
	Close();
}


GUI_APP_MAIN
{
	MyAppWindow app;
	app.Run();
}
