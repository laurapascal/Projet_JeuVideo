#pragma once
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <irrlicht.h>
#include <vector>
#include <iostream>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


class zombie
{
public:

    zombie(ic::vector3df pos_begin_param, ic::vector3df pos_end_param);

    ic::vector3df const& get_pos_begin() const;
    ic::vector3df const& get_pos_end() const;
    is::IAnimatedMeshSceneNode* get_nodeZombie();
    void set_nodeZombie(is::IAnimatedMeshSceneNode* nodeZombie_param);

    /** Creation of a vector containing Nb_zombie zombie nodes**/
    void creation_nodeZombie(is::ISceneManager *smgr, video::IVideoDriver *driver);

private:
    /** Position of the first coin  **/
    ic::vector3df pos_begin;
    /** Number of the last coin **/
    ic::vector3df pos_end;
    /** Node de notre zombie **/
    is::IAnimatedMeshSceneNode *nodeZombie;

};



#endif
