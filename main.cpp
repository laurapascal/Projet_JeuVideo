#include <irrlicht.h>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

// Un gestionnaire d'événement ne gérant que la touche escape permettant de sortir du programme
struct MyEventReceiver : IEventReceiver
{
  bool OnEvent(const SEvent &event)
  {
    // Si l'événement est de type clavier (KEY_INPUT)
    // et du genre pressage de touche
    // et que la touche est escape, on sort du programme
    if (event.EventType == EET_KEY_INPUT_EVENT &&
        event.KeyInput.PressedDown)
    {
      switch (event.KeyInput.Key)
      {
        case KEY_ESCAPE:
          exit(0);
        default:;
      }
    }
    return false;
  }
};

int main()
{
  // Le gestionnaire d'événements
  MyEventReceiver receiver;
  // Création de la fenêtre et du système de rendu.
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                        ic::dimension2d<u32>(640, 480),
                                        16, false, false, false, &receiver);

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();

  // Ajout de l'archive qui contient entre autres un niveau complet
  device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");

  // On charge un bsp (un niveau) en particulier :
  is::IAnimatedMesh *mesh = smgr->getMesh("20kdm2.bsp");
  is::IMeshSceneNode *node = smgr->addOctreeSceneNode(mesh->getMesh(0));
  node->setPosition(core::vector3df(-1350, -130, -1400));

  // Création du triangle selector
  scene::ITriangleSelector *selector;
  selector = smgr->createOctreeTriangleSelector(node->getMesh(), node);
  node->setTriangleSelector(selector);

  // Création de la caméra
  scene::ICameraSceneNode* camera =
    smgr->addCameraSceneNodeFPS(nullptr,
                                100,         // Vitesse de rotation
                                .3,          // Vitesse de déplacement
                                -1,          // Identifiant
                                nullptr, 0,  // Table de changement de touches
                                true,        // Pas de possibilité de voler
                                3);          // Vitesse saut
  camera->setPosition(ic::vector3df(50, 50, -60));
  camera->setTarget(ic::vector3df(-70, 30, -60));

  // Et l'animateur/collisionneur
  scene::ISceneNodeAnimator *anim;
  anim = smgr->createCollisionResponseAnimator(selector,
                                               camera,  // Le noeud que l'on veut gérer
                                               ic::vector3df(30, 50, 30), // "rayons" de la caméra
                                               ic::vector3df(0, -10, 0),  // gravité
                                               ic::vector3df(0, 30, 0));  // décalage du centre
  camera->addAnimator(anim);

  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(100,150,200,255));

    // Dessin de la scène :
    smgr->drawAll();
    //
    driver->endScene();
  }
  device->drop();

  return 0;
}
