#include "objet.hpp"
#include <iostream>
#include <cmath>

objet::objet(ic::vector3df position, ic::vector3df rotation, ic::vector3df scale, type Type, is::ISceneManager *smgr, is::IMetaTriangleSelector *meta_selector)
:objectPostion(position),objectRotation(rotation),objectScale(scale),objectType(Type)
{
    switch(objectType)
    {
    case armor1: meshObject = smgr->getMesh("data/decoration/armor/armor1.obj"); break;
    case armor2: meshObject = smgr->getMesh("data/decoration/armor/armor2.obj"); break;
    case chest: meshObject = smgr->getMesh("data/decoration/chest/chest.obj"); break;
    case box: meshObject = smgr->getMesh("data/decoration/box/box.obj"); break;
    case wood: meshObject = smgr->getMesh("data/decoration/wood/wood.obj"); break;
    }
    nodeObject = smgr->addAnimatedMeshSceneNode(meshObject);
    nodeObject->setMD2Animation(is::EMAT_CROUCH_STAND );
    nodeObject->setPosition(objectPostion);
    nodeObject->setRotation(objectRotation);
    nodeObject->setScale(objectScale);
    nodeObject->setMaterialFlag(iv::EMF_LIGHTING, false);
    // Création du triangle selector
    scene::ITriangleSelector *object_selector;
    object_selector = smgr->createTriangleSelector(nodeObject->getMesh(), nodeObject);
    nodeObject->setTriangleSelector(object_selector);
    meta_selector->addTriangleSelector(object_selector);
}

ic::vector3df const& objet::get_position() const
{
    return objectPostion;
}

ic::vector3df const& objet::get_rotation() const
{
    return objectRotation;
}

ic::vector3df const& objet::get_scale() const
{
    return objectScale;
}

objet::type const& objet::get_type() const
{
    return objectType;
}

scene::IAnimatedMesh * const &objet::get_mesh() const
{
    return meshObject;
}

is::IAnimatedMeshSceneNode* const& objet::get_objet() const
{
    return nodeObject;
}
