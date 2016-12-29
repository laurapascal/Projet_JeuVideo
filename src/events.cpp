// events.cpp

#include <iostream>
#include <irrlicht.h>
#include "events.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

/**************************************************************************\
 * EventReceiver::EventReceiver                                           *
\**************************************************************************/
EventReceiver::EventReceiver()
    : gui(nullptr)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::keyboard_handler                                        *
\*------------------------------------------------------------------------*/
bool EventReceiver::keyboard_handler(const SEvent &event)
{
    if (event.KeyInput.PressedDown)
    {
        switch (event.KeyInput.Key)
        {
        case KEY_ESCAPE:
            exit(0);
        case KEY_KEY_E:
          secouer_objet = true;
          break;
        case KEY_RETURN:
          close_widget = true;
          break;
        default:;
        }
    }

    return false;
}

bool EventReceiver::mouse_handler(const SEvent &event)
{

    switch (event.MouseInput.Event)
    {

    case EMIE_LMOUSE_PRESSED_DOWN:
        display_fire = true;
        break;
    case EMIE_LMOUSE_LEFT_UP:
        display_fire = false;
        break;
    case EMIE_MOUSE_WHEEL:
        display_arme1 = !display_arme1;
        display_arme2 = !display_arme2;
        break;
    default:;
    }


    return false;
}

/**************************************************************************\
 * EventReceiver::OnEvent                                                 *
\**************************************************************************/
bool EventReceiver::OnEvent(const SEvent &event)
{
    switch (event.EventType)
    {
    case EET_KEY_INPUT_EVENT:
        return keyboard_handler(event);
    case EET_MOUSE_INPUT_EVENT:
        return mouse_handler(event);
    default:;
    }

    return false;
}

/**************************************************************************\
 * EventReceiver::set_gui                                                 *
\**************************************************************************/
void EventReceiver::set_gui(irr::gui::IGUIEnvironment *g)
{
    gui = g;
}
