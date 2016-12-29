#include "gui.h"
#include <iostream>

//Crée un GUI pour le choix du personnage
ig::IGUIWindow* gui_creation(ig::IGUIEnvironment *gui)
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(200,220, 430,300), false, L"Message");
    gui->addStaticText(L"Pour secouer l'objet appuyer sur E", ic::rect<s32>(40,40, 200,200), false, false, window);
    return window;
}

void remove_message(ig::IGUIWindow *window)
{
    window->remove();
}
