#ifndef SCORE_H
#define SCORE_H

#include <wx/dialog.h>
#include <wx/wx.h>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include "player.h"

class Score : public wxDialog
{
  wxButton* m_ok;
  wxButton* save_score;
  Player<int> m_p1;
  Player<int> m_p2;
public :
  Score(wxWindow* parent, Player<int> p1, Player<int> p2);

  void OnOk(wxCommandEvent& event);
  void OnSave(wxCommandEvent& event);
};

#endif
