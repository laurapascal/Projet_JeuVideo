

#include "coins.hpp"
#include <iostream>
#include <cmath>

coins::coins(int Nb_coins_param, ic::vector3df pos_begin_param, ic::vector3df pos_end_param)
    :Nb_coins(Nb_coins_param),pos_begin(pos_begin_param),pos_end(pos_end_param)
{

}

int& coins::get_Nb_coins()
{
    return Nb_coins;
}
ic::vector3df const& coins::get_pos_begin() const
{
    return pos_begin;
}
ic::vector3df const& coins::get_pos_end() const
{
    return pos_end;
}
std::vector<scene::IMeshSceneNode *> coins::get_vectorNodeCoins()
{
    return vectorNodeCoins;
}

void coins::set_vectorNodeCoins(std::vector<is::IMeshSceneNode*> vectorNodeCoins_param)
{
    vectorNodeCoins = vectorNodeCoins_param;
}


std::vector<scene::IMeshSceneNode *> coins::creation_vectorNodeCoins(is::ISceneManager *smgr)
{
    for( int i = 0; i < Nb_coins; i++)
    {
        is::IAnimatedMeshSceneNode *meshCoin = smgr->addAnimatedMeshSceneNode(smgr->getMesh("data/coin/coin.obj")); // chargement de notre piece
        is::IMeshSceneNode *nodeCoin = smgr->addOctreeSceneNode(meshCoin->getMesh());
        nodeCoin->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        nodeCoin->setPosition(pos_begin);
        nodeCoin->setScale(ic::vector3df(7,7,7));
        ic::vector3df rotationCoin = nodeCoin->getRotation();
        rotationCoin.X += 90;
        nodeCoin->setRotation(rotationCoin);
        ic::vector3df positionCoin = nodeCoin->getPosition();
        int step = (pos_begin.X - pos_end.X)/Nb_coins;
        positionCoin.X += step*i;
        nodeCoin->setPosition(positionCoin);
        vectorNodeCoins.push_back(nodeCoin);
    }

    return vectorNodeCoins;
}
