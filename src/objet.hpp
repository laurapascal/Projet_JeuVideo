#ifndef OBJET_HPP
#define OBJET_HPP
#include <irrlicht.h>
#include <vector>
#include <iostream>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;



class objet
{
public:

    enum type{armor1,
             armor2,
             chest,
             box,
             wood};

    objet(ic::vector3df position, ic::vector3df rotation, ic::vector3df scale, type Type, scene::ISceneManager *smgr);

    ic::vector3df const& get_position() const;

    ic::vector3df const& get_rotation() const;

    ic::vector3df  const& get_scale() const;

    type const& get_type() const;

//    is::IAnimatedMeshSceneNode* const& get_mesh() const;

//    is::IMeshSceneNode* const& get_objet() const;


private:
    /** position **/
    ic::vector3df objectPostion;
    /** rotation **/
    ic::vector3df objectRotation;
    /** scale **/
    ic::vector3df objectScale;
    /** type of decoration **/
    type objectType;
    /** mesh **/
    is::IAnimatedMesh *meshObject;
    /** object **/
    is::IAnimatedMeshSceneNode *nodeObject;

};

#endif // OBJET_HPP

