#ifndef MAIN_H
#define MAIN_H

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#   pragma hdrstop
#endif

#ifndef WX_PRECOMP
	// Include your minimal set of headers here, or wx.h
#   include <wx/wx.h>
#endif

#include "MainFrame.h"

class MedeaApp : public wxApp
{
public:
	bool OnInit();
};

#endif

