#ifndef GUI_H
#define GUI_H

#include "/usr/include/irrlicht/irrlicht.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


//Crée un GUI pour le choix du personnage
ig::IGUIWindow * creation_message_objet(ig::IGUIEnvironment *gui);
ig::IGUIWindow * creation_message_fantome(ig::IGUIEnvironment *gui);
ig::IGUIWindow * creation_message_finjeu(ig::IGUIEnvironment *gui);
void remove_message(ig::IGUIWindow *window);

#endif // GUI_H
