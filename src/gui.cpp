#include "gui.h"

//Crée un GUI pour le choix du personnage
void gui_creation(ig::IGUIEnvironment *gui)
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25, 620,460), false, L"Settings");
}

