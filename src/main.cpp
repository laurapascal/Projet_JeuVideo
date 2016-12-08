#include <irrlicht.h>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


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
  ig::IGUIEnvironment *gui  = device->getGUIEnvironment();


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


  // Chargement des textures pour le score
  iv::ITexture *digits[10];
  digits[0] = driver->getTexture("data/0.png");
  digits[1] = driver->getTexture("data/1.png");
  digits[2] = driver->getTexture("data/2.png");
  digits[3] = driver->getTexture("data/3.png");
  digits[4] = driver->getTexture("data/4.png");
  digits[5] = driver->getTexture("data/5.png");
  digits[6] = driver->getTexture("data/6.png");
  digits[7] = driver->getTexture("data/7.png");
  digits[8] = driver->getTexture("data/8.png");
  digits[9] = driver->getTexture("data/9.png");

  // Création des places pour les chiffres
  ig::IGUIImage *score_10000 = gui->addImage(ic::rect<s32>(10,10,  50,50)); score_10000->setScaleImage(true);
  ig::IGUIImage *score_1000  = gui->addImage(ic::rect<s32>(50,10,  90,50)); score_1000->setScaleImage(true);
  ig::IGUIImage *score_100   = gui->addImage(ic::rect<s32>(90,10,  130,50)); score_100->setScaleImage(true);
  ig::IGUIImage *score_10    = gui->addImage(ic::rect<s32>(130,10, 170,50)); score_10->setScaleImage(true);
  ig::IGUIImage *score_1     = gui->addImage(ic::rect<s32>(170,10, 210,50)); score_1->setScaleImage(true);


  int score = 0;
  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(100,150,200,255));

    // Calcul du score :
    // TODO: incrémenter le score en fonction du game
    // Mise à jour du score :
    score_10000->setImage(digits[(score / 10000) % 10]);
    score_1000->setImage(digits[(score / 1000) % 10]);
    score_100->setImage(digits[(score / 100) % 10]);
    score_10->setImage(digits[(score / 10) % 10]);
    score_1->setImage(digits[(score / 1) % 10]);


    // Dessin de la scène :
    smgr->drawAll();
    gui->drawAll();
    driver->endScene();
  }
  device->drop();

  return 0;
}
