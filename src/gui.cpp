#include "gui.h"

//Crée un GUI pour le choix du personnage
void gui_creation(ig::IGUIEnvironment *gui)
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(200,220, 430,300), false, L"Message");
}

