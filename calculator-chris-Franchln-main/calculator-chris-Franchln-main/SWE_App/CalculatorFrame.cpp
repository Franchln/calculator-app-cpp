#include "CalculatorFrame.h"
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/bmpbuttn.h>
#include <cmath>

#include "Icon_0.xpm"
#include "Icon_1.xpm"
#include "Icon_2.xpm"
#include "Icon_3.xpm"
#include "Icon_4.xpm"
#include "Icon_5.xpm"
#include "Icon_6.xpm"
#include "Icon_7.xpm"
#include "Icon_8.xpm"
#include "Icon_9.xpm"
#include "Icon_Add.xpm"
#include "Icon_Subtract.xpm"
#include "Icon_Multiply.xpm"
#include "Icon_Divide.xpm"
#include "Icon_Mod.xpm"
#include "Icon_Equals.xpm"
#include "Icon_Clear.xpm"
#include "Icon_Delete.xpm"
#include "Icon_Decimal.xpm"
#include "Icon_Negative.xpm"
#include "Icon_sin.xpm"
#include "Icon_cos.xpm"
#include "Icon_tan.xpm"

wxBEGIN_EVENT_TABLE(CalculatorFrame, wxFrame)
EVT_BUTTON(wxID_ANY, CalculatorFrame::OnButtonClicked)
wxEND_EVENT_TABLE()

CalculatorFrame::CalculatorFrame()
    : wxFrame(nullptr, wxID_ANY, "Calculator", wxDefaultPosition, wxSize(350, 450)) //window size
{
    displayTextBox = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 50), wxTE_RIGHT | wxTE_READONLY);
    wxFont font(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    displayTextBox->SetFont(font);
    displayTextBox->SetBackgroundColour(wxColour(30, 30, 30));   
    displayTextBox->SetForegroundColour(wxColour(0, 255, 0)); 
    displayTextBox->Refresh();
    this->SetBackgroundColour(wxColour(20, 20, 20));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(displayTextBox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxGridSizer* mainGrid = new wxGridSizer(4, 4, 5, 5);
    mainGrid->Add(CreateIconButton("7", wxBitmap(icon7_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("8", wxBitmap(icon8_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("9", wxBitmap(icon9_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("/", wxBitmap(icondivide_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("4", wxBitmap(icon4_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("5", wxBitmap(icon5_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("6", wxBitmap(icon6_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("*", wxBitmap(iconmultiply_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("1", wxBitmap(icon1_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("2", wxBitmap(icon2_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("3", wxBitmap(icon3_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("-", wxBitmap(iconsubtract_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("+/-", wxBitmap(iconnegative_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("0", wxBitmap(icon0_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton(".", wxBitmap(icondecimal_xpm), wxID_ANY));
    mainGrid->Add(CreateIconButton("+", wxBitmap(iconadd_xpm), wxID_ANY));
    mainSizer->Add(mainGrid, 0, wxALL | wxALIGN_CENTER, 10);

    wxGridSizer* functionGrid = new wxGridSizer(2, 4, 5, 5);
    functionGrid->Add(CreateIconButton("%", wxBitmap(iconmod_xpm), wxID_ANY));
    functionGrid->Add(CreateIconButton("sin", wxBitmap(iconsin_xpm), wxID_ANY));
    functionGrid->Add(CreateIconButton("cos", wxBitmap(iconcos_xpm), wxID_ANY));
    functionGrid->Add(CreateIconButton("tan", wxBitmap(icontan_xpm), wxID_ANY));
    functionGrid->Add(CreateIconButton("Del", wxBitmap(icondelete_xpm), wxID_ANY));
    functionGrid->Add(CreateIconButton("C", wxBitmap(iconclear_xpm), wxID_ANY));
    functionGrid->Add(CreateIconButton("=", wxBitmap(iconequals_xpm), wxID_ANY));
    functionGrid->AddSpacer(1);
    mainSizer->Add(functionGrid, 0, wxALL | wxALIGN_CENTER, 10);

    this->SetSizer(mainSizer);
}

wxBitmapButton* CalculatorFrame::CreateIconButton(const wxString& label, const wxBitmap& icon, wxWindowID id)
{
    wxBitmapButton* button = new wxBitmapButton(this, id, icon, wxDefaultPosition, wxSize(48, 48));
    button->SetToolTip(label);
    return button;
}

//  error check
bool errorDisplayed = false;

void CalculatorFrame::OnButtonClicked(wxCommandEvent& event)
{
    wxBitmapButton* button = dynamic_cast<wxBitmapButton*>(FindWindowById(event.GetId()));
    if (!button) return;

    wxString label = button->GetToolTipText();

    if (errorDisplayed && label != "C" && label != "Del" && label != "=")
    {
        displayTextBox->Clear();
        errorDisplayed = false;
    }

    if (label == "C")
    {
        displayTextBox->Clear();
        errorDisplayed = false;
        return;
    }

    if (label == "Del")
    {
        wxString current = displayTextBox->GetValue();

        if (errorDisplayed || current.StartsWith("Error:"))
        {
            displayTextBox->Clear();
            errorDisplayed = false;
            return;
        }

        if (current.EndsWith("sin") || current.EndsWith("cos") || current.EndsWith("tan"))
        {
            current = current.RemoveLast().RemoveLast().RemoveLast();
        }
        else if (!current.IsEmpty())
        {
            current.RemoveLast();
        }

        displayTextBox->SetValue(current);
        return;
    }

    if (label == "+/-")
    {
        wxString current = displayTextBox->GetValue();
        if (current.IsEmpty()) 
        {
            displayTextBox->AppendText("-");
            return;
        }

        int lastOpIndex = -1;
        wxString operators = "+-*/%";
        for (int i = current.length() - 1; i >= 0; --i) 
        {
            if (operators.Find(current[i]) != wxNOT_FOUND) 
            {
                lastOpIndex = i;
                break;
            }
        }

        int numStart = lastOpIndex + 1;
        wxString numberPart = current.Mid(numStart);

        if (numberPart.StartsWith("-")) 
        {
            current.Remove(numStart, 1); 
        }
        else 
        {
            current = current.Mid(0, numStart) + "-" + current.Mid(numStart); 
        }

        displayTextBox->SetValue(current);
        return;
    }

    if (label == "=")
    {
        wxString input = displayTextBox->GetValue().Trim(true).Trim(false);
        input.MakeLower();

        if (input.Contains("++") || input.Contains("--") || input.Contains("**") ||
            input.Contains("//") || input.Contains("%%") || input.Contains("==") ||
            input.Contains(".."))
        {
            displayTextBox->SetValue("Error: invalid expression");
            errorDisplayed = true;
            return;
        }

        if (input.StartsWith("sin") || input.StartsWith("cos") || input.StartsWith("tan")) {
            wxString function;
            wxString valueStr;

            if (input.StartsWith("sin"))
            {
                function = "sin";
                valueStr = input.Mid(3);
            }
            else if (input.StartsWith("cos")) 
            {
                function = "cos";
                valueStr = input.Mid(3);
            }
            else if (input.StartsWith("tan")) 
            {
                function = "tan";
                valueStr = input.Mid(3);
            }

            valueStr = valueStr.Trim(true).Trim(false);
            double angleDeg;
            if (!valueStr.ToDouble(&angleDeg))
            {
                displayTextBox->SetValue("Error: invalid trig input");
                errorDisplayed = true;
                return;
            }

            double angleRad = angleDeg * (M_PI / 180.0);
            double result = 0;

            if (function == "sin") result = std::sin(angleRad);
            else if (function == "cos") result = std::cos(angleRad);
            else if (function == "tan") result = std::tan(angleRad);

            displayTextBox->SetValue(wxString::Format("%g", result));
            errorDisplayed = false;
            return;
        }

        wxString operators = "+-*/%";
        int opPos = -1;

        for (int i = 1; i < input.length(); ++i)
        {
            if (operators.Find(input[i]) != wxNOT_FOUND)
            {
                opPos = i;
                break;
            }
        }

        if (opPos == -1)
        {
            displayTextBox->SetValue("Error: no operator");
            errorDisplayed = true;
            return;
        }

        wxString leftStr = input.Mid(0, opPos);
        wxString rightStr = input.Mid(opPos + 1);
        wxChar op = input[opPos];

        double left, right;

        if (!leftStr.ToDouble(&left) || !rightStr.ToDouble(&right))
        {
            displayTextBox->SetValue("Error: invalid number");
            errorDisplayed = true;
            return;
        }

        double result = 0;
        bool error = false;

        switch (op)
        {
        case '+': result = left + right;
            break;
        case '-': result = left - right;
            break;
        case '*': result = left * right;
            break;
        case '/':
            if (right == 0)
            {
                displayTextBox->SetValue("Error: divide by 0");
                error = true;
            }
            else
            {
                result = left / right;
            }
            break;
        case '%':
            result = static_cast<int>(left) % static_cast<int>(right);
            break;
        default:
            displayTextBox->SetValue("Error: unknown op");
            error = true;
        }

        if (!error)
        {
            displayTextBox->SetValue(wxString::Format("%g", result));
            errorDisplayed = false;
        }
        else
        {
            errorDisplayed = true;
        }

        return;
    }

    displayTextBox->AppendText(label);
}