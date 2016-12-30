#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <irrlicht.h>
#include"iostream"
#include"vector"
#include"math.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;


class callback: public is::IAnimationEndCallBack
{
public:

    callback(scene::ISceneManager *data_smgr);
    virtual void OnAnimationEnd(is::IAnimatedMeshSceneNode* node);

private:
    scene::ISceneManager *smgr;

};


#endif // CALLBACK_HPP

