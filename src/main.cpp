#include <irrlicht.h>
#include <iostream>
#include <vector>
#include "coins.hpp"
#include <cstdlib>
#include "gui.h"
#include "events.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

int main()
{

  // Le gestionnaire d'événements
  EventReceiver receiver;

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
  digits[0] = driver->getTexture("data/score/0.png");
  digits[1] = driver->getTexture("data/score/1.png");
  digits[2] = driver->getTexture("data/score/2.png");
  digits[3] = driver->getTexture("data/score/3.png");
  digits[4] = driver->getTexture("data/score/4.png");
  digits[5] = driver->getTexture("data/score/5.png");
  digits[6] = driver->getTexture("data/score/6.png");
  digits[7] = driver->getTexture("data/score/7.png");
  digits[8] = driver->getTexture("data/score/8.png");
  digits[9] = driver->getTexture("data/score/9.png");

  // Création des places pour les chiffres
  ig::IGUIImage *score_10000 = gui->addImage(ic::rect<s32>(10,10,  50,50)); score_10000->setScaleImage(true);
  ig::IGUIImage *score_1000  = gui->addImage(ic::rect<s32>(50,10,  90,50)); score_1000->setScaleImage(true);
  ig::IGUIImage *score_100   = gui->addImage(ic::rect<s32>(90,10,  130,50)); score_100->setScaleImage(true);
  ig::IGUIImage *score_10    = gui->addImage(ic::rect<s32>(130,10, 170,50)); score_10->setScaleImage(true);
  ig::IGUIImage *score_1     = gui->addImage(ic::rect<s32>(170,10, 210,50)); score_1->setScaleImage(true);


  // Création de notre Gui
  // Choix de la police de caractères
  ig::IGUISkin* skin = gui->getSkin();
  ig::IGUIFont* font = gui->getFont("data/fontlucida.png");
  skin->setFont(font);


  // Une fenêtre pour différents réglages lorsque l'utilisateur appuie sur la touche "m"
//  create_window(gui);

  // Vecteur des nodes de nos pièces
  std::vector<coins> vectorCoins;

  // Création of N set of coins:
    // Initialisation des set de coins : position de départ, position de fin, et nombre de pièces
  int Nb_coinsSet = 4;
  ic::vector3df pos_begin[Nb_coinsSet] = {ic::vector3df(-200.0,10.0,-60.0),
                                          ic::vector3df(60.0,10.0,23.0),
                                          ic::vector3df(210.0,10.0,-134.0),
                                          ic::vector3df(282.0,10.0,70.0)};
  ic::vector3df pos_end[Nb_coinsSet] = {ic::vector3df(-350.0,10.0,-60.0),
                                        ic::vector3df(-120.0,10.0,23.0),
                                        ic::vector3df(-65.0,10.0,-134.0),
                                        ic::vector3df(282.0,10.0,-153.0)};
  int nb_coins[Nb_coinsSet] = {3, 4, 3, 6};
  std::vector<int> set_selection;
  for( int i = 0; i < Nb_coinsSet; i++)
  {
      set_selection.push_back(i);
  }
  std::vector<int> selected_set;
    // Affichage des set de pièces sélectionnées
  int Nb_coinsSet_display = 2;
  for( int i = 0; i < Nb_coinsSet_display; i++)
  {
      int j = rand() % set_selection.size();
      selected_set.push_back(set_selection[j]);
      coins coinsSet(nb_coins[set_selection[j]],pos_begin[set_selection[j]],pos_end[set_selection[j]]);
      coinsSet.creation_vectorNodeCoins(smgr);
      vectorCoins.push_back(coinsSet);
      set_selection.erase(set_selection.begin() + j);
  }

  int score = 0;
  while(device->run())
  {
    // Lorsque l'utilisateur appuie sur la touche "m" un menu s'affiche pour pouvoir changer d'arme
    if(receiver.display_menu)
        gui_creation(gui);

    driver->beginScene(true, true, iv::SColor(100,150,200,255));

    // Gestion de nos pièces
    for (unsigned int ii = 0 ; ii<vectorCoins.size(); ++ii)
    {

        std::vector<is::IMeshSceneNode*> vectorNodeCoins = vectorCoins[ii].get_vectorNodeCoins();

        for (unsigned int i = 0 ; i<vectorNodeCoins.size(); ++i)
        {
            // Rotation des pièces
            ic::vector3df rotationCoins = vectorNodeCoins[i]->getRotation();
            rotationCoins.Y += 5;
            vectorNodeCoins[i]->setRotation(rotationCoins);

            // Collision de notre personnage avec nos pièces
            ic::vector3df positionPiece = vectorNodeCoins[i]->getPosition();
            float diffX = camera->getPosition().X - positionPiece.X;
            float diffY = camera->getPosition().Y - positionPiece.Y;
            float diffZ = camera->getPosition().Z - positionPiece.Z;
            float dist_perso_coins= sqrt(diffX*diffX + diffY*diffY + diffZ*diffZ);
            if (dist_perso_coins <= 10) // Collisions dans ce cas
            {
                score += 1;
                // Suppression de la pièce de la scéne
                if(vectorNodeCoins[i])
                {
                    // Suppression de la pièce de la scéne
                    smgr->addToDeletionQueue(vectorNodeCoins[i]);
                    // Suppression de la pièce du vector
                    vectorCoins[ii].set_Nb_coins(vectorCoins[ii].get_Nb_coins() - 1);
                        // Si il reste encore des pièces dans le set de pièces
                    if(vectorCoins[ii].get_Nb_coins() != 0)
                    {
                        vectorNodeCoins.erase(vectorNodeCoins.begin() + i);
                        vectorCoins[ii].set_vectorNodeCoins(vectorNodeCoins);
                    }
                        // Si il ne reste plus de pièce dans le set
                    else
                    {
                        // Affichage d'un autre set de pièces
                        vectorCoins.erase(vectorCoins.begin() + ii);
                        set_selection.push_back(selected_set[ii]);
                        int j = rand() % set_selection.size();
                        coins coinsSet(nb_coins[set_selection[j]],pos_begin[set_selection[j]],pos_end[set_selection[j]]);
                        coinsSet.creation_vectorNodeCoins(smgr);
                        vectorCoins.push_back(coinsSet);
                        set_selection.erase(set_selection.begin() + j);
                    }
                }
            }
        }
    }

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
    // Dessin de l'interface utilisateur :
    gui->drawAll();

    driver->endScene();
  }
  device->drop();

  return 0;
}
