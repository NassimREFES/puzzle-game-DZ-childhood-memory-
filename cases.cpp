
#include "cases.h"

BEGIN_EVENT_TABLE(Cases, wxFrame)
  EVT_MENU(wxID_NEW, Cases::OnNew)
  EVT_MENU(ID_SCORE, Cases::OnScore)
  EVT_MENU(wxID_HELP, Cases::OnHelp)
  EVT_MENU(wxID_ABOUT, Cases::OnAbout)
  EVT_MENU(wxID_EXIT, Cases::OnQuit)
END_EVENT_TABLE()

Cases::Cases(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
              wxSize(300, 300)), MARGIN_OFFSET(4), player(true)
{
  m_cases = new wxMenu;
  m_cases->Append(wxID_NEW, wxT("New party"));
  m_cases->AppendSeparator();
  m_cases->Append(ID_SCORE, wxT("Score"));
  m_cases->AppendSeparator();
  m_cases->Append(wxID_HELP, wxT("Help"));
  m_cases->Append(wxID_ABOUT, wxT("About"));
  m_cases->AppendSeparator();
  m_cases->Append(wxID_EXIT, wxT("Exit"));

  m_menubar = new wxMenuBar;
  m_menubar->Append(m_cases, wxT("Cases"));
  SetMenuBar(m_menubar);

  m_choice = new Choice(this);

  SetClientSize(wxSize(100 + m_choice->get_grid_size()*50,
                       100 + m_choice->get_grid_size()*50 + 70));
  wxString label;
  label << title << " - Grid = " << m_choice->get_grid_size();
  SetLabel(label);

  DefineText();
  
  Connect(wxEVT_PAINT, wxPaintEventHandler(Cases::OnPaint));
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Cases::OnClick));
  Centre();

  SetMaxSize(GetClientSize());
  SetMinSize(GetClientSize());

  CreateStatusBar(1);

  table.resize(m_choice->get_grid_size());
  valid_full_square.resize(m_choice->get_grid_size());
  for (int i = 0; i <table.size(); ++i) {
    table[i].resize(m_choice->get_grid_size());
    valid_full_square[i].resize(m_choice->get_grid_size());
    for (int j = 0; j < valid_full_square[i].size(); ++j)
      valid_full_square[i][j] = false;
  }

  count_round = (m_choice->get_grid_size()+1)
                *m_choice->get_grid_size()*2;                    
}

Cases::~Cases()
{
  m_choice->Destroy();
  //  m_cases->Destroy(); // menubar le detruit !
  // m_menubar->Destroy(); // frame le detruit !
  m_first_player->Destroy();
  m_second_player->Destroy();
}

void Cases::OnPaint(wxPaintEvent& WXUNUSED(event))
    // dessiné la table de jeu
{
  wxPaintDC dc(this);
  wxString x;
  if (m_choice->get_grid_size() == 3)
    x << "hd1.png";
  else if (m_choice->get_grid_size() == 5)
    x << "hd2.png";
  else
    x << "hd3.png";
  
  wxBitmap bmp(x, wxBITMAP_TYPE_PNG);
  dc.DrawBitmap(bmp, wxPoint(0, 0), true);
  wxPen pen(*wxLIGHT_GREY, 8);
  dc.SetPen(pen);
  wxSize sz = GetClientSize();
  wxString s;
  DrawTable(dc, m_choice->get_grid_size());
}

void Cases::OnClick(wxMouseEvent& event)
{
  if (event.LeftDown()) {
    wxClientDC dc(this);
    player_turn(dc);
  
    wxPoint pos = event.GetPosition();
    wxPoint dl_begin, dl_end;

    if (is_into_table(pos)) {
      if ( round(pos.y/50.0)*50-MARGIN_OFFSET <= pos.y
           && pos.y <= round(pos.y/50.0)*50+MARGIN_OFFSET )
        // gere la position de la sourie selon la taille
        // de la ligne ( 8 pixels )
      {
        dl_begin.y = dl_end.y = ((pos.y+MARGIN_OFFSET)/50)*50;
        dl_begin.x = pos.x<60 ? ((pos.x+MARGIN_OFFSET)/50)*50
                           : ((pos.x-MARGIN_OFFSET-1)/50)*50;
        dl_end.x   = dl_begin.x+50;
        if (set_square(dl_begin, Cases::horizontal)) {
          player = !player; // prochaine joueur
          --count_round;
          dc.DrawLine(dl_begin, dl_end);
        }
      }
      else if (round(pos.x/50.0)*50-MARGIN_OFFSET <= pos.x
               && pos.x <= round(pos.x/50.0)*50+MARGIN_OFFSET )
      {
        dl_begin.x = dl_end.x = ((pos.x+MARGIN_OFFSET)/50)*50;
        dl_begin.y = (pos.y/50)*50;
        dl_end.y   = dl_begin.y+50;
        if (set_square(dl_begin, Cases::vertical)) {
          player = !player; // prochaine joueur
          --count_round;
          dc.DrawLine(dl_begin, dl_end);
        }
      }
    }
  }
  // fin de la partie
  if (count_round == 0)
    final_score();
}

void Cases::final_score()
    // affiché le score final
{
  Score* s = new Score(this, m_p1, m_p2);
}

bool Cases::set_square(wxPoint beg, Orientation o)
{
  wxPoint p;
  p.x = beg.y/50 - 1;
  p.y = beg.x/50 - 1;
  cout << beg.x << " -- " << beg.y << '\n';
  if ( o == Cases::horizontal ) {
    if (table.size() == p.x) {
      if (!table[p.x-1][p.y].bottom) {
        table[p.x-1][p.y].bottom = true;
        is_closed_square(wxPoint(p.x-1, p.y), o);
        return true;
      }
    }
    else if (!table[p.x][p.y].top) {
        table[p.x][p.y].top = true;
        if (0<p.x) table[p.x-1][p.y].bottom = true;
        is_closed_square(p, o);
        return true;
    }
    else
      return false;
  
  }
  else if ( o == Cases::vertical ) {
    if (table.size() == p.x) {
      if (!table[p.x][p.y-1].right) {
        table[p.x][p.y-1].right = true;
        is_closed_square(wxPoint(p.x, p.y-1), o);
        return true;
      }
    }
    else if (!table[p.x][p.y].left) {
        table[p.x][p.y].left = true;
        if (0<p.y) table[p.x][p.y-1].right = true;
        is_closed_square(p, o);
        return true;
    }
    else
      return false;
  }
  return false;
}

bool Cases::is_closed_square(wxPoint pos, Orientation o)
    // determin un carrée complet
    // calcule le score d'un joueur
{
  int add = 0;

  if ((table[pos.x][pos.y].full_square()) && !valid_full_square[pos.x][pos.y]) {
    valid_full_square[pos.x][pos.y] = true;
    ++add;
  }
  switch (o) {
      case Cases::horizontal :
        if (0<pos.x && table[pos.x-1][pos.y].full_square()
            && !valid_full_square[pos.x-1][pos.y]) {
          ++add;
          valid_full_square[pos.x-1][pos.y] = true;
        }
        break;
      case Cases::vertical :
        if (0<pos.y && table[pos.x][pos.y-1].full_square()
            && !valid_full_square[pos.x][pos.y-1]) {
          ++add;
          valid_full_square[pos.x][pos.y-1] = true;
        }
         break;
  }
  if (player) {
        m_p1.data(m_p1.data()+add);
        m_first_player->SetLabel(m_p1.to_string());
  }
  else {
        m_p2.data(m_p2.data()+add);
        m_second_player->SetLabel(m_p2.to_string());
  }
}

void Cases::player_turn(wxDC& dc)
    // determin la couleur du trait pour un joueur
{
  SetStatusText( player ? m_p1.name() : m_p2.name() );
  if (player) {
    wxPen pen(*wxRED, 8);
    dc.SetPen(pen);
  }
  else {
    wxPen pen(*wxBLUE, 8);
    dc.SetPen(pen);
  }
}

bool Cases::is_into_table(wxPoint pos) const
    // si le point donnée est inclut dans la table de jeu
{
  return 50-MARGIN_OFFSET <= pos.x
       && pos.x <= (m_choice->get_grid_size()+1)*50 + MARGIN_OFFSET
       && 50-MARGIN_OFFSET <= pos.y
       && pos.y <= (m_choice->get_grid_size()+1)*50 + MARGIN_OFFSET;
}

void Cases::DrawTable(wxDC& dc, int sz)
    // dessin de la table
{
  for (int i = 1; i <= sz+1; ++i) {
    dc.DrawLine(wxPoint(i*50, 50), wxPoint(i*50, (sz+1)*50));
    dc.DrawLine(wxPoint(50, i*50), wxPoint((sz+1)*50, i*50));
  }
}

void Cases::OnNew(wxCommandEvent& WXUNUSED(event))
    // nouvelle partie
{
  Close(true);
  Cases* s = new Cases(wxT("cases"));
  s->Show(true);
}

void Cases::OnScore(wxCommandEvent& event)
    // avoir la table des scores ( historique )
{
  ifstream ifs("historique.txt");
  if (!ifs) throw runtime_error("historique.txt file name not exist !");
  istream_iterator< Player<int> > ii(ifs);
  istream_iterator< Player<int> > eos;
  vector< Player<int> > v(ii, eos);
  sort(v.begin(), v.end(), great_score<int>);
  //-------------------------------------------------
  wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("Score"),
                               wxDefaultPosition, wxSize(300, 300));
  wxPanel* panel = new wxPanel(frame, wxID_ANY);
  wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
  
  wxListView* listview = new wxListView(panel, wxID_ANY, wxDefaultPosition,
                                        wxDefaultSize, wxLC_REPORT);
  wxListItem name_item;
  name_item.SetId(0);
  name_item.SetText(wxT("Name"));
  name_item.SetWidth(150);
  listview->InsertColumn(0, name_item);

  wxListItem score_item;
  score_item.SetId(1);
  score_item.SetText(wxT("Score"));
  score_item.SetWidth(150);
  listview->InsertColumn(1, score_item);

  for (int i = 0; i<v.size(); ++i) {
    listview->InsertItem(i, wxT(""));
    listview->SetItem(i, 0, v[i].name());
    wxString x; x << v[i].data();
    listview->SetItem(i, 1, x);
  }
  hbox->Add(listview, 1, wxEXPAND | wxALL, 15);
  panel->SetSizer(hbox);

  frame->SetMaxSize(frame->GetClientSize());
  frame->SetMinSize(frame->GetClientSize());
  frame->Centre();
  frame->Show(true);
}

void Cases::OnHelp(wxCommandEvent& WXUNUSED(event))
{

}

void Cases::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  
}

void Cases::OnQuit(wxCommandEvent& WXUNUSED(event))
    // quitter
{
  Close(true);
}

void Cases::DefineText()
    // definir le text 
{
  m_first_player = new wxStaticText(this, wxID_ANY, wxT(""), wxPoint(20, 5));
  m_first_player->SetForegroundColour(*wxLIGHT_GREY);
  m_first_player->SetFont(wxFont(18, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL, false));
  wxSize cs = GetClientSize();
  m_second_player = new wxStaticText(this, wxID_ANY, wxT(""), wxPoint(20, m_choice->get_grid_size()*50+60));
  m_second_player->SetForegroundColour(*wxLIGHT_GREY);
  m_second_player->SetFont(wxFont(18, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL, false));

  AboutNamePlayer();
}

void set_name(wxString& name)
{
  for (int i = 0; i < name.size(); ++i)
    if (name[i] == ' ')
      name[i] = '_';
}

void Cases::AboutNamePlayer()
    // information sur le joueur ( nom )
{
  wxString n;
  // first player !
  wxTextEntryDialog* d1 = new wxTextEntryDialog(NULL, wxT("First player name ?"),
                                                wxT("Name"), wxT(""), wxOK |
                                                wxCENTRE | wxWS_EX_VALIDATE_RECURSIVELY);
  while (d1->ShowModal() == wxID_OK
         && (d1->GetValue().Cmp(wxT("")) == 0)) {
      wxMessageBox(wxT("No Empty name !!"), wxT("Name Player Error"));
  }
  n = d1->GetValue();
  set_name(n);
  m_p1.name(n);
  m_first_player->SetLabel(m_p1.to_string());

  // second player !
  wxTextEntryDialog* d2 = new wxTextEntryDialog(NULL, wxT("Second player name ?"),
                                                wxT("Name"), wxT(""), wxOK |
                                                wxCENTRE | wxWS_EX_VALIDATE_RECURSIVELY);
  while (d2->ShowModal() == wxID_OK
         && (d2->GetValue().Cmp(m_p1.name()) == 0
             || d2->GetValue().Cmp(wxT("")) == 0)) {
    if (d2->GetValue().Cmp(wxT("")) == 0)
      wxMessageBox(wxT("No Empty name !!"), wxT("Name Player Error"));
    else
      wxMessageBox(wxT("Enter another name pls."), wxT("Name Player Error"), wxOK | wxCENTRE);
  }
  
  n = d2->GetValue();
  set_name(n);
  m_p2.name(n);
  m_second_player->SetLabel(m_p2.to_string());

  d1->Destroy();
  d2->Destroy();
}
