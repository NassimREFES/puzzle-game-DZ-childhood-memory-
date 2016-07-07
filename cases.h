#ifndef CASES_H
#define CASES_H

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/textdlg.h>
#include <wx/event.h>
#include <wx/headerctrl.h>
#include <wx/listctrl.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include "choice.h"
#include "player.h"
#include "square.h"
#include "score.h"

const int ID_SCORE = 1000;

class Cases : public wxFrame
{
public :
  enum Orientation { vertical, horizontal };
  Cases(const wxString& title);
  ~Cases();
  void OnPaint(wxPaintEvent& event);
  void OnClick(wxMouseEvent& event);

  void OnNew(wxCommandEvent& event);
  void OnScore(wxCommandEvent& event);
  void OnHelp(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnQuit(wxCommandEvent& event);
  
private :
  DECLARE_EVENT_TABLE()
  void DrawTable(wxDC& dc, int sz);
  void AboutNamePlayer();
  void DefineText();
  bool is_into_table(wxPoint p) const;
  void player_turn(wxDC&);
  bool set_square(wxPoint beg, Orientation o);
  bool is_closed_square(wxPoint pos, Orientation o);
  void final_score();
  
private :
  int MARGIN_OFFSET;
  Choice* m_choice;
  wxMenu* m_cases;
  wxMenuBar* m_menubar;
  wxStaticText* m_first_player;
  wxStaticText* m_second_player;
  Player<int> m_p1;
  Player<int> m_p2;
  bool player;
  vector< vector<Square> > table;
  vector< vector<bool> > valid_full_square;
  long count_round;
};

#endif
