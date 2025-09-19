#pragma once
#include <wx/wx.h>
#include <wx/bmpbuttn.h>

class CalculatorFrame : public wxFrame
{
public:
    CalculatorFrame();

private:
    wxTextCtrl* displayTextBox;

    void OnButtonClicked(wxCommandEvent& event);

    wxBitmapButton* CreateIconButton(const wxString& label, const wxBitmap& icon, wxWindowID id);

    wxDECLARE_EVENT_TABLE(); 
};