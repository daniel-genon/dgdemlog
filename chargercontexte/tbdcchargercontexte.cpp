#include "creercontexte.h"

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.ethop.boitedialog.contexte");
  return app->make_window_and_run<CreerContexte>(argc, argv);
}
