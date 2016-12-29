#include "zombie.hpp"
#include <iostream>
#include <cmath>

zombie::zombie( ic::vector3df pos_begin_param, ic::vector3df pos_end_param)
    :pos_begin(pos_begin_param),pos_end(pos_end_param)
{

}

ic::vector3df const& zombie::get_pos_begin() const
{
    return pos_begin;
}
ic::vector3df const& zombie::get_pos_end() const
{
    return pos_end;
}
scene::IAnimatedMeshSceneNode * zombie::get_nodeZombie()
{
    return nodeZombie;
}

void zombie::set_nodeZombie(is::IAnimatedMeshSceneNode* nodeZombie_param)
{
    nodeZombie = nodeZombie_param;
}


void zombie::creation_nodeZombie(is::ISceneManager *smgr, iv::IVideoDriver  *driver)
{

    is::IAnimatedMesh *zombie = smgr->getMesh("data/ennemis_zombie/tris.md2");
      // Attachement de notre personnage dans la scène
    nodeZombie = smgr->addAnimatedMeshSceneNode(zombie);
    nodeZombie->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    nodeZombie->setMD2Animation(irr::scene::EMAT_STAND);
    nodeZombie->setPosition(pos_begin);
    iv::ITexture* texture_zombie = driver->getTexture("data/ennemis_zombie/base.pcx");
    nodeZombie->setMaterialTexture(0, texture_zombie);
    nodeZombie->setMD2Animation(irr::scene::EMAT_RUN);
}
