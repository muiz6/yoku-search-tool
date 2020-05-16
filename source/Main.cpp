#include "Main.hpp"
#include "MyGui.hpp"

// mandatory wxWidgets boiler plate code
IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    // for enabling png files for wxwidgets
    // wxImage::AddHandler(new wxPNGHandler);
    // wxSystemOptions::SetOption("msw.remap", 2);

    // creating gui object
    MyGui *gui = new MyGui("Yoku", 800, 600);
    gui->Show(true);

    return true;
}
