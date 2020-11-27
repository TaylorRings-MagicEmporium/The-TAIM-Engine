#pragma once
#include "bullet3-3.0.6/LinearMath/btIDebugDraw.h"
#include "bullet3-3.0.6/btBulletDynamicsCommon.h"
#include "Communication_Layer.h"

#include <glm/glm.hpp>


// used to generate debugging lines for the Physics_System
class Bullet_Debug_Drawer : public btIDebugDraw
{
private:
	int m_debugMode;
	DefaultColors m_ourColors;
public:
	Communication_Layer* CL;
	Bullet_Debug_Drawer();
	virtual ~Bullet_Debug_Drawer();

	virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) {};
	virtual void   drawSphere(const btVector3& p, btScalar radius, const btVector3& color) {};

	virtual void   drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha) {};

	virtual void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {};

	virtual void   reportErrorWarning(const char* warningString) {};

	virtual void   draw3dText(const btVector3& location, const char* textString) {};

	virtual void    drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	virtual DefaultColors getDefaultColors() const {
		return m_ourColors;
	}

	virtual void    setDebugMode(int debugMode) { m_debugMode = debugMode; };

	virtual int     getDebugMode() const { return m_debugMode; };

	virtual void	flushLines() {};

	virtual void	drawContactPoint() {};
};

