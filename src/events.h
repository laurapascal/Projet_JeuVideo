// events.h

#ifndef EVENTS_H
#define EVENTS_H

#include <irrlicht.h>

class EventReceiver : public irr::IEventReceiver
{
  irr::gui::IGUIEnvironment *gui;
  bool keyboard_handler(const irr::SEvent &event);
  bool mouse_handler(const irr::SEvent &event);
  bool OnEvent(const irr::SEvent &event);

public:
  EventReceiver();
  bool display_fire = false;
  void set_gui(irr::gui::IGUIEnvironment *gui);

};

#endif
