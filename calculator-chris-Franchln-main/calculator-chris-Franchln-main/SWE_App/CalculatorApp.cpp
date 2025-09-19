#include <wx/wx.h>
#include "CalculatorFrame.h"

class CalculatorApp : public wxApp
{
public:
    virtual bool OnInit() override;
};

wxIMPLEMENT_APP(CalculatorApp);

bool CalculatorApp::OnInit()
{
    CalculatorFrame* calculatorWindow = new CalculatorFrame();
    calculatorWindow->Show(true);
    return true;
}