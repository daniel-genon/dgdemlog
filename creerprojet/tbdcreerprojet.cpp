#include "creerprojet.h"

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.dgdemlog.boitedialog.projet");
  return app->make_window_and_run<CreerProjet>(argc, argv);
}
