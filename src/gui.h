#ifndef GUI_H
#define GUI_H

#include "/usr/include/irrlicht/irrlicht.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


//Crée un GUI pour le choix du personnage
ig::IGUIWindow * gui_creation(ig::IGUIEnvironment *gui);
void remove_message(ig::IGUIWindow *window);

#endif // GUI_H
