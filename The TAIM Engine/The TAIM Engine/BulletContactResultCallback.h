#pragma once
#include <assert.h>
#include <Bullet3-3.0.6/btBulletDynamicsCommon.h>
struct BulletContactResultCallback : public btCollisionWorld::ContactResultCallback {
    //! Constructor, pass whatever context you want to have available when processing contacts
     /*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
      *  (supplied by the superclass) for needsCollision() */

    bool bCollision;

    BulletContactResultCallback()
        : btCollisionWorld::ContactResultCallback(), bCollision(false) { }


    //! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
    virtual btScalar addSingleResult(btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0, int partId0, int index0,
        const btCollisionObjectWrapper* colObj1, int partId1, int index1) 
    {
        btVector3 pt;
        bCollision = true;
        // will be set to point of collision relative to body
        //if (colObj0->m_collisionObject == &body) {
        //    pt = cp.m_localPointA;
        //}
        //else {
        //    assert(colObj1->m_collisionObject == &body && "body does not match either collision object");
        //    pt = cp.m_localPointB;
        return 0;
       }
 
};