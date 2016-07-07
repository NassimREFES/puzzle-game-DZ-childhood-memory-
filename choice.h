#ifndef CHOICE_H
#define CHOICE_H

#include <wx/wx.h>
#include <wx/dcclient.h>
#include <wx/dialog.h>
#include <wx/bmpbuttn.h>

enum { ID_3X3 = 100, ID_5X5, ID_12X12 };

class Choice : public wxDialog
{
  wxBitmapButton* sz_3x3;
  wxBitmapButton* sz_5x5;
  wxBitmapButton* sz_12x12;

  int grid_size; // par defaut = 3
  int sd;
public :
  Choice(wxWindow* parent);
  ~Choice()
  {
    delete sz_3x3;
    delete sz_5x5;
    delete sz_12x12;
  }

  void OnClickButton3x3(wxCommandEvent& event);
  void OnClickButton5x5(wxCommandEvent& event);
  void OnClickButton12x12(wxCommandEvent& event);

  int get_grid_size() const { return grid_size; }
private :
  DECLARE_EVENT_TABLE()
};

#endif
