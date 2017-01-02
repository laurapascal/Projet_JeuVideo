#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "events.h"
#include "zombie.hpp"
#include "coins.hpp"
#include "objet.hpp"
#include "callback.hpp"
#include "gui.h"

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
    is::IMetaTriangleSelector *meta_selector = smgr->createMetaTriangleSelector();


    // Ajout de l'archive qui contient entre autres un niveau complet
    device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");

    // On charge un bsp (un niveau) en particulier :
    is::IAnimatedMesh *mesh = smgr->getMesh("20kdm2.bsp");
    is::IMeshSceneNode *node = smgr->addOctreeSceneNode(mesh->getMesh(0));
    node->setPosition(core::vector3df(-1350, -130, -1400));

    // Création du triangle selector
    scene::ITriangleSelector *castle_selector;
    castle_selector = smgr->createOctreeTriangleSelector(node->getMesh(), node);
    node->setTriangleSelector(castle_selector);
    meta_selector->addTriangleSelector(castle_selector);
    SKeyMap keyMap[5];
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_KEY_Z;
    keyMap[1].Action = EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = KEY_KEY_S;
    keyMap[2].Action = EKA_STRAFE_LEFT ;
    keyMap[2].KeyCode = KEY_KEY_Q;
    keyMap[3].Action = EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = KEY_KEY_D;
    keyMap[4].Action = EKA_JUMP_UP;
    keyMap[4].KeyCode = KEY_SPACE;

    // Création de la caméra
    scene::ICameraSceneNode* camera =
            smgr->addCameraSceneNodeFPS(nullptr,
                                        10,         // Vitesse de rotation
                                        .3,          // Vitesse de déplacement
                                        -1,          // Identifiant
                                        keyMap, 5,  // Table de changement de touches
                                        true,        // Pas de possibilité de voler
                                        3);
    camera->setPosition(ic::vector3df(50, 50, -60));
    camera->setTarget(ic::vector3df(-70, 30, -60));

    //Création du décor
    std::vector<objet> decoration;
    decoration.push_back(objet(ic::vector3df(256.0 ,-16.0 ,45.0),ic::vector3df(-90.0 ,-135.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor1, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(55.0 ,179.0 ,-1050.0),ic::vector3df(-90.0 ,0.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor1, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(680.0 ,243.0 ,1025.0),ic::vector3df(-90.0 ,225.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor1, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-580.0 ,115.0 ,-555.0),ic::vector3df(-90.0 ,45.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor1, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-150.0 ,-16.0 ,-160.0),ic::vector3df(-90.0 ,45.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor2, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(250.0 ,115.0 ,-340.0),ic::vector3df(-90.0 ,-135.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor2, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-570.0 ,275.0 ,-1010.0),ic::vector3df(-90.0 ,45.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor2, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(63.0 ,339.0 ,505.0),ic::vector3df(-90.0 ,180.0 ,0.0),ic::vector3df(2.0 ,2.0 ,2.0), objet::armor2, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-120.0 ,90.0 ,450.0),ic::vector3df(180.0 ,0.0 ,0.0),ic::vector3df(20.0 ,20.0 ,20.0), objet::box, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(210.0 ,280.0 ,-60.0),ic::vector3df(180.0 ,0.0 ,0.0),ic::vector3df(20.0 ,20.0 ,20.0), objet::box, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(442.0 ,-45.0 ,-65.0),ic::vector3df(180.0 ,0.0 ,0.0),ic::vector3df(20.0 ,20.0 ,20.0), objet::box, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-470.0 ,310.0 ,344.0),ic::vector3df(180.0 ,0.0 ,0.0),ic::vector3df(20.0 ,20.0 ,20.0), objet::box, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-325.0 ,-60.0 ,-45.0),ic::vector3df(0.0 ,-90.0 ,0.0),ic::vector3df(13.0 ,13.0 ,13.0), objet::chest, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-460.0 ,280.0 ,-240.0),ic::vector3df(0.0 ,180.0 ,0.0),ic::vector3df(13.0 ,13.0 ,13.0), objet::chest, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-450.0 ,60.0 ,450.0),ic::vector3df(0.0 ,0.0 ,0.0),ic::vector3df(13.0 ,13.0 ,13.0), objet::chest, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(570.0 ,60.0 ,-540.0),ic::vector3df(0.0 ,180.0 ,0.0),ic::vector3df(13.0 ,13.0 ,13.0), objet::chest, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-160.0 ,-60.0 ,90.0),ic::vector3df(0.0 ,0.0 ,0.0),ic::vector3df(8.0 ,8.0 ,8.0), objet::wood, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(560.0 ,70.0 ,450.0),ic::vector3df(0.0 ,0.0 ,0.0),ic::vector3df(8.0 ,8.0 ,8.0), objet::wood, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(683.0 ,230.0 ,-1000.0),ic::vector3df(0.0 ,-45.0 ,0.0),ic::vector3df(8.0 ,8.0 ,8.0), objet::wood, smgr, meta_selector));
    decoration.push_back(objet(ic::vector3df(-95.0 ,260.0 ,-40.0),ic::vector3df(0.0 ,90.0 ,0.0),ic::vector3df(8.0 ,8.0 ,8.0), objet::wood, smgr, meta_selector));

    // Variable pour gerer notre message lorsque le joueur rentre en collision avec un objet
    bool ouverture_message[decoration.size()];
    bool collision_objet[decoration.size()];
    for (unsigned int i = 0; i < decoration.size(); ++i)
    {
        ouverture_message[i] = false;
        collision_objet[i] = false;
    }
    // Tableau pour définir les 3 index des objets où se cachent nos 3 fantômes
    std::vector<unsigned int>  index_objet_fantome;
    bool index_different = false;
    while(!index_different)
    {
        int j = rand() % decoration.size();
        int k = rand() % decoration.size();
        int l = rand() % decoration.size();
        if (j != k && k != l && l != j)
        {
            index_objet_fantome.push_back(j);
            index_objet_fantome.push_back(k);
            index_objet_fantome.push_back(l);
            index_different = true;
        }

    }

    // Et l'animateur/collisionneur
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(meta_selector,
                                                 camera,  // Le noeud que l'on veut gérer
                                                 ic::vector3df(30, 50, 30), // "rayons" de la caméra
                                                 ic::vector3df(0, -10, 0),  // gravité
                                                 ic::vector3df(0, 30, 0));  // décalage du centre
    camera->addAnimator(anim);

    // Chargement de nos ennemis zombie
    std::vector<zombie> vector_zombies;
    int Nb_zombies = 2;
    ic::vector3df pos_begin_zombie[Nb_zombies] = {ic::vector3df(-200.0,-30.0,-60.0), ic::vector3df(49.0,-30.0,-180.0)};
    ic::vector3df pos_end_zombie[Nb_zombies] = {ic::vector3df(0.0,-30.0,-60.0), ic::vector3df(49.0,-30.0,70.0)};
    for( int i = 0; i < Nb_zombies; i++)
    {
        zombie Zombie(pos_begin_zombie[i], pos_end_zombie[i], false);
        Zombie.creation_nodeZombie(smgr, driver);
        vector_zombies.push_back(Zombie);
    }

    //Chargement de la cible
    ig::IGUIImage *target;
    iv::ITexture *target_texture;
    target_texture=driver->getTexture("data/Weapons/target.png");
    target = gui->addImage(ic::rect<s32>(300,220,  340,260));
    target->setScaleImage(true);
    target->setImage(target_texture);

    // Chargement de l'arme initiale
    ///Weapon 1
    is::IAnimatedMesh *weapon = smgr->getMesh("data/Weapons/weapon1/weapon1.obj");
    is::IAnimatedMeshSceneNode *node_weapon = smgr->addAnimatedMeshSceneNode(weapon,camera);
    node_weapon->setMD2Animation(is::EMAT_CROUCH_STAND );
    node_weapon->setPosition(ic::vector3df(1.0, -0.5, 1.5));
    node_weapon->setScale(ic::vector3df(0.5,0.5,0.5));
    node_weapon->setRotation(ic::vector3df(0, 90, 0));
    node_weapon->setMaterialFlag(iv::EMF_LIGHTING, false);

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


    // Vecteur des nodes de nos pièces
    std::vector<coins> vectorCoins;

    // Création of N set of coins:
    // Initialisation des set de coins : position de départ, position de fin, et nombre de pièces
    int Nb_coinsSet = 13;
    ic::vector3df pos_begin[Nb_coinsSet] = {ic::vector3df(-200.0,10.0,-60.0),
                                            ic::vector3df(60.0,10.0,23.0),
                                            ic::vector3df(210.0,10.0,-134.0),
                                            ic::vector3df(282.0,10.0,0.0),
                                            ic::vector3df(280.0,140.0,320.0),
                                            ic::vector3df(760.0,270.0,840.0),
                                            ic::vector3df(570.0,364.0,235.0),
                                            ic::vector3df(225.0,364.0,325.0),
                                            ic::vector3df(-450.0,364.0,210.0),
                                            ic::vector3df(185.0,206.0,-970.0),
                                            ic::vector3df(-97.0,142.0,-450.0),
                                            ic::vector3df(-450.0,142.0,-217.0),
                                            ic::vector3df(570.0,142.0,174.0)
                                           };
    ic::vector3df pos_end[Nb_coinsSet] = {ic::vector3df(-280.0,10.0,-60.0),
                                          ic::vector3df(-120.0,10.0,23.0),
                                          ic::vector3df(-65.0,10.0,-134.0),
                                          ic::vector3df(282.0,10.0,-153.0),
                                          ic::vector3df(720.0,140.0,320.0),
                                          ic::vector3df(420.0,270.0,840.0),
                                          ic::vector3df(570.0,364.0,-500.0),
                                          ic::vector3df(-310.0,364.0,325.0),
                                          ic::vector3df(-450.0,364.0,-130.0),
                                          ic::vector3df(-147.0,206.0,-970.0),
                                          ic::vector3df(-524.0,142.0,-450.0),
                                          ic::vector3df(-450.0,142.0,310.0),
                                          ic::vector3df(570.0,142.0,-450.0),
                                         };
    int nb_coins[Nb_coinsSet] = {3, 4, 3, 6, 5, 4, 7, 6, 3, 3, 4, 3, 5};
    std::vector<int> set_selection;
    for( int i = 0; i < Nb_coinsSet; i++)
    {
        set_selection.push_back(i);
    }
    std::vector<int> selected_set;
    // Affichage des set de pièces sélectionnées
    int Nb_coinsSet_display = 6;
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
    int fire_display = false;
    ig::IGUIImage *fire;
    iv::ITexture *fire_texture;
    ig::IGUIWindow *window;
    callback* CallBack=new callback(smgr);

    while(device->run())
    {
        driver->beginScene(true, true, iv::SColor(100,150,200,255));

        // Gestion de nos objets
        for (unsigned int i = 0; i  <decoration.size(); ++i)
        {
            ic::vector3df positionObjet = decoration[i].get_position();
            float diffX = camera->getPosition().X - positionObjet.X;
            float diffY = camera->getPosition().Y - positionObjet.Y;
            float diffZ = camera->getPosition().Z - positionObjet.Z;
            float dist_perso_coins= sqrt(diffX*diffX + diffY*diffY + diffZ*diffZ);
            if (dist_perso_coins <= 100)
            {
                // Ouverture du message si il n'est pas déjà ouvert
                if(!collision_objet[i] && !ouverture_message[i])
                {
                    // Le joueur ne peux appuyer sur entree pour fermer un message
                    // ou sur F pour fouiller un objet
                    // seulement si il est proximité de cet objet
                    if(receiver.close_widget) receiver.close_widget = false;
                    if(receiver.fouiller_objet) receiver.fouiller_objet = false;
                    // Creation d'un message indiquant que:
                    // si le joueur appuye sur la touche F, le joueur peut fouiller cet objet
                    window = creation_message_objet(gui);
                    ouverture_message[i] = true;
                }
                collision_objet[i] = true;
                // Si le joueur a appuyé sur F
                if(receiver.fouiller_objet)
                {
                    receiver.fouiller_objet = false;
                    remove_message(window);
                    ouverture_message[i] = false;
                    // Si le joueur a trouvé le bon objet:
                    // - message indiquant que l'on a trouvé un fantome
                    // - apparition d'un fantome
                    for(unsigned k = 0; k < index_objet_fantome.size(); k++)
                    {
                        if(index_objet_fantome[k] == i)
                        {
                            ouverture_message[i] = true;
                            window = creation_message_fantome(gui);
                            zombie Zombie(ic::vector3df(-200.0,40.0,-60.0),ic::vector3df(0.0,80.0,-60.0), true);
                            Zombie.creation_nodeZombie(smgr, driver);
                            vector_zombies.push_back(Zombie);
                            index_objet_fantome.erase(index_objet_fantome.begin() + k);
                        }
                    }
                }
                // Si le joueur a appuyé sur entré
                if(receiver.close_widget)
                {
                    receiver.close_widget = false;
                    remove_message(window);
                    ouverture_message[i] = false;
                }
            }
            else
            {
                // Fermeture du message si le joueur n'est plus a proximité de l'objet
                collision_objet[i] = false;
                if(ouverture_message[i])
                {
                    remove_message(window);
                    ouverture_message[i] = false;
                }
            }
        }

        // Gestion de nos ennemis zombie
        for (unsigned int i = 0 ; i<vector_zombies.size(); ++i)
        {
            // Cent pas du zombie
            zombie Zombie = vector_zombies[i];
            if (Zombie.isAlive())
            {
                is::IAnimatedMeshSceneNode* nodeZombie = Zombie.get_nodeZombie();
                ic::vector3df position_zombie = nodeZombie->getPosition();
                ic::vector3df rotation_zombie = nodeZombie->getRotation();
                if(Zombie.get_pos_begin().X != Zombie.get_pos_end().X)
                {
                    if( (int)rotation_zombie.Y % 360 == 0)
                        position_zombie.X += 2;
                    else if ((int)rotation_zombie.Y % 360 == 180)
                        position_zombie.X -= 2;
                    if(position_zombie.X == Zombie.get_pos_end().X || position_zombie.X == Zombie.get_pos_begin().X)
                        rotation_zombie.Y += 180;
                }
                if(Zombie.get_pos_begin().Z != Zombie.get_pos_end().Z)
                {
                    if( (int)rotation_zombie.Y % 360 == 90)
                        position_zombie.Z -= 2;
                    else if ((int)rotation_zombie.Y % 360 == 270)
                        position_zombie.Z += 2;
                    if(position_zombie.Z == Zombie.get_pos_end().Z || position_zombie.Z == Zombie.get_pos_begin().Z)
                        rotation_zombie.Y += 180;
                }
                nodeZombie->setRotation(rotation_zombie);
                nodeZombie->setPosition(position_zombie);
            }
        }


        // Gestion de nos armes
        if(receiver.display_arme1)
        {
            // Suppression de l'arme 2
            smgr->addToDeletionQueue(node_weapon);

            //Affichage de l'arme 1
            weapon = smgr->getMesh("data/Weapons/weapon1/weapon1.obj");
            node_weapon = smgr->addAnimatedMeshSceneNode(weapon,camera);
            node_weapon->setMD2Animation(is::EMAT_CROUCH_STAND );
            node_weapon->setPosition(ic::vector3df(1.0, -0.5, 1.5));
            node_weapon->setScale(ic::vector3df(0.5,0.5,0.5));
            node_weapon->setRotation(ic::vector3df(0, 90, 0));
            node_weapon->setMaterialFlag(iv::EMF_LIGHTING, false);
        }

        if(receiver.display_arme2)
        {
            // Suppression de l'arme 1
            smgr->addToDeletionQueue(node_weapon);

            //Affichage de l'arme 2
            weapon = smgr->getMesh("data/Weapons/weapon2/weapon2.obj");
            node_weapon = smgr->addAnimatedMeshSceneNode(weapon,camera);
            node_weapon->setMD2Animation(is::EMAT_CROUCH_STAND );
            node_weapon->setPosition(ic::vector3df(2, -0.5, 2.0));
            node_weapon->setRotation(ic::vector3df(0, 0, 0));
            node_weapon->setScale(ic::vector3df(0.05,0.05,0.05));
            node_weapon->setMaterialFlag(iv::EMF_LIGHTING, false);
        }


        // Gestion de nos pièces
        for (unsigned int ii = 0 ; ii<vectorCoins.size(); ++ii)
        {

            std::vector<is::IAnimatedMeshSceneNode*> vectorNodeCoins = vectorCoins[ii].get_vectorNodeCoins();

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

        // Gestion de la flame du canon
        if(receiver.display_fire && !fire_display)
        {
            //Chargement de la flame au canon

            if(receiver.display_arme1)
            {
                fire_texture=driver->getTexture("data/Weapons/fire.png");
                fire = gui->addImage(ic::rect<s32>(450,260,  490,300));
            }
            if(receiver.display_arme2)
            {
                fire_texture=driver->getTexture("data/Weapons/blast.png");
                fire = gui->addImage(ic::rect<s32>(440,220,  480,260));
            }
            fire->setScaleImage(true);
            fire->setImage(fire_texture);
            fire_display = true;
        }
        else if(!receiver.display_fire && fire_display)
        {
            fire->remove();
            fire_display = false;
        }

        //Detection de tir
        if(receiver.display_fire)
        {
            is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();
            ic::line3d<f32> ray;
            ray = collision_manager->getRayFromScreenCoordinates(ic::position2d<s32>(320, 240));
            ic::vector3df intersection;
            ic::triangle3df hit_triangle;
            is::ISceneNode *selected_scene_node =
                    collision_manager->getSceneNodeAndCollisionPointFromRay(
                        ray,
                        intersection, // On récupère ici les coordonnées 3D de l'intersection
                        hit_triangle); // et le triangle intersecté
            if (selected_scene_node)
            {
                for(unsigned int i=0;i<vector_zombies.size();i++)
                {

                    if(vector_zombies[i].get_nodeZombie()==selected_scene_node)
                    {
                        is::IAnimatedMeshSceneNode* node = vector_zombies[i].get_nodeZombie();
                        node->setMD2Animation(is::EMAT_DEATH_FALLBACK);
                        node->setLoopMode(false);
                        node->setAnimationEndCallback(CallBack);
                        vector_zombies[i].zombieDied();
                    }
                }
            }

        }

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
