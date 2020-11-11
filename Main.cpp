#include "Main.h"

IMPLEMENT_APP(MedeaApp);

bool MedeaApp::OnInit()
{
	MainFrame *main = new MainFrame(wxSize(800, 600));
	main->Show(true);
	SetTopWindow(main);
	return true;
}
