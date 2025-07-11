#include "fenetre.h"

std::string 	*pCHRacine;
int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("application.dgdemlog");
  return app->make_window_and_run<Fenetre>(argc, argv);
}
