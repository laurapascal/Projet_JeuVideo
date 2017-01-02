#include "zombie.hpp"
#include <iostream>
#include <cmath>

zombie::zombie( ic::vector3df pos_begin_param, ic::vector3df pos_end_param, bool ghost_param)
    :pos_begin(pos_begin_param),pos_end(pos_end_param), ghost(ghost_param)
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
bool const& zombie::is_ghost() const
{
    return ghost;
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
    nodeZombie->setScale(ic::vector3df(1.5, 1.5, 1.5));
    if(pos_begin.Z != pos_end.Z) nodeZombie->setRotation(ic::vector3df(0.0, 270.0, 0.0));
    if(ghost) nodeZombie->setDebugDataVisible(is::EDS_HALF_TRANSPARENCY);
    iv::ITexture* texture_zombie = driver->getTexture("data/ennemis_zombie/base.pcx");
    nodeZombie->setMaterialTexture(0, texture_zombie);
    is::ITriangleSelector *selector = smgr->createTriangleSelector(nodeZombie);
    nodeZombie->setTriangleSelector(selector);
    nodeZombie->setMD2Animation(irr::scene::EMAT_RUN);
}

bool const& zombie::isAlive() const
{
    return alive;
}

void zombie::zombieDied()
{
    alive = false;
}

