

#include "coins.hpp"
#include <iostream>
#include <cmath>

coins::coins(int Nb_coins_param, ic::vector3df pos_begin_param, ic::vector3df pos_end_param)
    :Nb_coins(Nb_coins_param),pos_begin(pos_begin_param),pos_end(pos_end_param)
{

}

int const& coins::get_Nb_coins() const
{
    return Nb_coins;
}
void coins::set_Nb_coins(int new_nb_coins)
{
    Nb_coins = new_nb_coins;
}
ic::vector3df const& coins::get_pos_begin() const
{
    return pos_begin;
}
ic::vector3df const& coins::get_pos_end() const
{
    return pos_end;
}
std::vector<scene::IAnimatedMeshSceneNode *> coins::get_vectorNodeCoins()
{
    return vectorNodeCoins;
}

void coins::set_vectorNodeCoins(std::vector<is::IAnimatedMeshSceneNode*> vectorNodeCoins_param)
{
    vectorNodeCoins = vectorNodeCoins_param;
}


std::vector<scene::IAnimatedMeshSceneNode *> coins::creation_vectorNodeCoins(is::ISceneManager *smgr)
{
    for( int i = 0; i < Nb_coins; i++)
    {
        is::IAnimatedMesh *mesh = smgr->getMesh("data/coin/coin.obj");
        is::IAnimatedMeshSceneNode *nodeCoin = smgr->addAnimatedMeshSceneNode(mesh); // chargement de notre piece
        nodeCoin->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        nodeCoin->setPosition(pos_begin);
        nodeCoin->setScale(ic::vector3df(7,7,7));
        ic::vector3df rotationCoin = nodeCoin->getRotation();
        rotationCoin.X += 90;
        nodeCoin->setRotation(rotationCoin);
        ic::vector3df positionCoin = nodeCoin->getPosition();
        int step = 0;
        if ( pos_begin.X - pos_end.X != 0 )
        {
            step = std::fabs(pos_begin.X - pos_end.X)/(Nb_coins-1);
            positionCoin.X -= step*i;
        }
        else if ( pos_begin.Z - pos_end.Z != 0 )
        {
            step = std::fabs(pos_begin.Z - pos_end.Z)/(Nb_coins-1);
            positionCoin.Z -= step*i;
        }
        nodeCoin->setPosition(positionCoin);
        vectorNodeCoins.push_back(nodeCoin);
    }

    return vectorNodeCoins;
}
