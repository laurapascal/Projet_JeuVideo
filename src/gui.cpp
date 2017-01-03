#include "gui.h"
#include <iostream>

//Crée un GUI pour le choix du personnage
ig::IGUIWindow* creation_message_objet(ig::IGUIEnvironment *gui)
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(200,220, 430,300), false, L"Message");
    gui->addStaticText(L"Pour fouiller l'objet appuyer sur F", ic::rect<s32>(40,40, 200,200), false, false, window);
    return window;
}
ig::IGUIWindow* creation_message_fantome(ig::IGUIEnvironment *gui)
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(200,220, 430,300), false, L"Message");
    gui->addStaticText(L"Vous avez trouvé un fantôme zombie!", ic::rect<s32>(40,40, 200,50), false, false, window);
    gui->addStaticText(L"Tuez le avant qu'il ne vous tueee!", ic::rect<s32>(42,50, 200,200), false, false, window);
    return window;
}

ig::IGUIWindow* creation_message_finjeu(ig::IGUIEnvironment *gui)
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(200,220, 530,300), false, L"Message");
    gui->addStaticText(L"Vous avez tué tous les zombies et tous les fantômes!", ic::rect<s32>(40,40, 300,50), false, false, window);
    gui->addStaticText(L"FELICITATION! Votre mission est pleinement accomplie!", ic::rect<s32>(42,50, 300,200), false, false, window);
    return window;
}

void remove_message(ig::IGUIWindow *window)
{
    window->remove();
}
