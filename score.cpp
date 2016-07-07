#include "score.h"

Score::Score(wxWindow* parent, Player<int> p1, Player<int> p2)
    : wxDialog(parent, wxID_ANY, wxT("Score"), wxDefaultPosition, wxSize(400, 200)),
      m_p1(p1), m_p2(p2)
{
  wxPanel* panel = new wxPanel(this, wxID_ANY);
  wxStaticText* for_winner = new wxStaticText(panel, wxID_ANY, wxT(""));
  wxStaticText* for_looser = new wxStaticText(panel, wxID_ANY, wxT(""));
  if (m_p1.data() < m_p2.data()) {
    for_winner->SetLabel(m_p2.to_string());
    for_looser->SetLabel(m_p1.to_string());
  }
  else if (m_p2.data() < m_p1.data()) {
    for_winner->SetLabel(m_p1.to_string());
    for_looser->SetLabel(m_p2.to_string());
  }
  else {
    wxMessageBox(wxT("[ NUL ] have same score"), wxT("NUL SCORE"));
    return;
  }
  wxBoxSizer* hbox_win = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* hbox_loose = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
  wxStaticText* winner = new wxStaticText(panel, wxID_ANY, wxT("WIN"));
  winner->SetForegroundColour(*wxBLUE);
  wxStaticText* looser = new wxStaticText(panel, wxID_ANY, wxT("LOOSE"));
  looser->SetForegroundColour(*wxRED);
  wxFont font(20, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL, false);
  winner->SetFont(font);
  looser->SetFont(font);
  for_winner->SetFont(font);
  for_looser->SetFont(font);

  m_ok = new wxButton(panel, wxID_OK, wxT("Ok"));
  save_score = new wxButton(panel, wxID_SAVE, wxT("Save score"));

  hbox->Add(save_score, 1, wxALL | wxEXPAND, 10);
  hbox->Add(m_ok, 1, wxALL | wxEXPAND, 10);
  
  hbox_win->Add(winner, 0, wxALL, 10);
  hbox_win->Add(for_winner, 0, wxLEFT, 65);
  hbox_loose->Add(looser, 0, wxALL, 10);
  hbox_loose->Add(for_looser, 0, wxLEFT, 50);
  vbox->Add(hbox_win);
  vbox->Add(hbox_loose);
  vbox->Add(hbox, 0, wxALIGN_CENTRE);

  Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(Score::OnOk));
  Connect(wxID_SAVE, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(Score::OnSave));
      
  panel->SetSizer(vbox);
  Centre();
  ShowModal();
}

void Score::OnOk(wxCommandEvent& WXUNUSED(event))
{
  EndModal(wxEVT_WINDOW_MODAL_DIALOG_CLOSED);
}

void Score::OnSave(wxCommandEvent& WXUNUSED(event))
{
  ofstream ofs("historique.txt", ios_base::app);
  if (!ofs) throw runtime_error("Can't open file name historique.txt !");
  ofs << m_p1 << '\n';
  ofs << m_p2 << '\n';
  wxMessageBox(wxT("Your score is saved"), wxT("Save"));
}
