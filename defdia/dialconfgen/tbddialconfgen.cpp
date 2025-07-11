#include "dialogconfiggenerale.h"

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.ethop.boitedialogue.configgenerale");
  return app->make_window_and_run<DialogConfigGenerale>(argc, argv);
}
