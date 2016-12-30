#include "callback.hpp"
#include <iostream>

callback::callback(is::ISceneManager *data_smgr)
{
    smgr = data_smgr;
}

void callback::OnAnimationEnd(is::IAnimatedMeshSceneNode* node)
{
    smgr->addToDeletionQueue(node);
}



