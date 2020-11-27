#pragma once
#include <assert.h>
#include <Bullet3-3.0.6/btBulletDynamicsCommon.h>

// used to get contactResultCallback for detecting raycast hits 
struct BulletContactResultCallback : public btCollisionWorld::ContactResultCallback {

    bool bCollision;

    BulletContactResultCallback()
        : btCollisionWorld::ContactResultCallback(), bCollision(false) { }

    virtual btScalar addSingleResult(btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0, int partId0, int index0,
        const btCollisionObjectWrapper* colObj1, int partId1, int index1) 
    {
        btVector3 pt;
        bCollision = true;
        return 0;
       }
 
};