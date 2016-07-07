#ifndef PLAYER_H
#define PLAYER_H

#include <wx/string.h>
#include <iostream>
#include <stdexcept>

using namespace std;

template<class Data>
class Player
{
  Data d;
  wxString n;
public :
  Player() : n(wxT("")), d(Data()) { }
  Player(wxString name, Data data) : n(name), d(data) { }

  void name(const wxString& name) { n = name; }
  void data(const Data& dd) { d = dd; }
  wxString name() const { return n; }
  Data data() const { return d; }
  wxString to_string() const { wxString x; x << n.SubString(0, 20).ToStdString() << " = " << d; return x; }
};

template< class d >
istream& operator>>(istream& is, Player<d>& p)
{
  d data;
  string n;
  char ch;
  is >> n >> ch >> data;
  //cout << n << " -- " << ch << " -- " << data << '\n';
  //if (!is || ch != '=') throw runtime_error("Invalid player!");
  p.data(data);
  p.name(wxString(n.c_str()));
  return is;
}

template< class d >
ostream& operator<<(ostream& os, const Player<d>& p)
{
  return os << p.to_string().ToStdString();
}

template< class d>
bool great_score(const Player<d>& p1, const Player<d>& p2)
{
  return p1.data() > p2.data();
}

#endif 
