#include "app.h"

IMPLEMENT_APP(app)

bool app::OnInit()
{
  Cases* s = new Cases(wxT("cases"));
  s->Show(true);
  return true;
}
