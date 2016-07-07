#include "choice.h"

BEGIN_EVENT_TABLE(Choice, wxDialog)
  EVT_BUTTON(ID_3X3, Choice::OnClickButton3x3)
  EVT_BUTTON(ID_5X5, Choice::OnClickButton5x5)
  EVT_BUTTON(ID_12X12, Choice::OnClickButton12x12)
END_EVENT_TABLE()

Choice::Choice(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxT("Grid Choice"),
               wxDefaultPosition, wxSize(500, 400)), grid_size(3)
{
  wxGridSizer* gs = new wxGridSizer(3, 2, 5, 5);
  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
  
  wxBitmap bmp_3x3(wxT("3x3x3.png"), wxBITMAP_TYPE_PNG);
  wxBitmap bmp_5x5(wxT("5x5x5.png"), wxBITMAP_TYPE_PNG);
  wxBitmap bmp_12x12(wxT("12x12x12.png"), wxBITMAP_TYPE_PNG);
  sz_3x3 = new wxBitmapButton(this, ID_3X3, bmp_3x3);
  sz_5x5 = new wxBitmapButton(this, ID_5X5, bmp_5x5);
  sz_12x12 = new wxBitmapButton(this, ID_12X12, bmp_12x12);

  wxStaticText* st_3x3 = new wxStaticText(this, wxID_ANY, wxT("#   3x3   #"));
  st_3x3->SetFont(wxFont(17, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL, false));
  wxStaticText* st_5x5 = new wxStaticText(this, wxID_ANY, wxT("#   5x5   #"));
  st_5x5->SetFont(wxFont(17, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL, false));
  wxStaticText* st_12x12 = new wxStaticText(this, wxID_ANY, wxT("#   12x12   #"));
  st_12x12->SetFont(wxFont(17, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL, false));
  gs->Add(st_3x3, 0, wxALIGN_CENTRE);
  gs->Add(sz_3x3, 1, wxEXPAND | wxALL, 5);
  gs->Add(st_5x5, 0, wxALIGN_CENTRE);
  gs->Add(sz_5x5, 1, wxEXPAND | wxALL, 5);
  gs->Add(st_12x12, 0, wxALIGN_CENTRE);
  gs->Add(sz_12x12, 1, wxEXPAND | wxALL, 5);

  wxStaticText* prs = new wxStaticText(this, wxID_ANY, wxT("{    New party    }"));
  prs->SetFont(wxFont(22, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL, false));
  prs->SetForegroundColour(*wxBLUE);

  vbox->Add(prs, 0, wxALIGN_CENTRE, 10);
  vbox->Add(gs, 1, wxALL | wxEXPAND, 10);
  SetSizer(vbox);
  
  sd = ShowModal();
  Centre();
}

void Choice::OnClickButton3x3(wxCommandEvent& event)
{
  grid_size = 3;
  EndModal(sd);
}

void Choice::OnClickButton5x5(wxCommandEvent& event)
{
  grid_size = 5;
  EndModal(sd);
}

void Choice::OnClickButton12x12(wxCommandEvent& event)
{
  grid_size = 12;
  EndModal(sd);
}
