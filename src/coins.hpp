#pragma once

#ifndef COINS_HPP
#define COINS_HPP
#include <irrlicht.h>
#include <vector>
#include <iostream>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


class coins
{
public:

    coins(int Nb_coins, ic::vector3df pos_begin_param, ic::vector3df pos_end_param);


    int const& get_Nb_coins() const;
    void set_Nb_coins(int new_nb_coins);
    ic::vector3df const& get_pos_begin() const;
    ic::vector3df const& get_pos_end() const;
    std::vector<is::IAnimatedMeshSceneNode*> get_vectorNodeCoins();
    void set_vectorNodeCoins(std::vector<is::IAnimatedMeshSceneNode*> vectorNodeCoins_param);

    /** Creation of a vector containing Nb_coins coins nodes**/
    std::vector<scene::IAnimatedMeshSceneNode *> creation_vectorNodeCoins(is::ISceneManager *smgr);

private:
    /** Number of coins in the vector vectorNodeCoins **/
    int Nb_coins;
    /** Position of the first coin  **/
    ic::vector3df pos_begin;
    /** Number of the last coin **/
    ic::vector3df pos_end;
    /** Vector containing the coins nodes **/
    std::vector<is::IAnimatedMeshSceneNode*> vectorNodeCoins;

};



#endif
