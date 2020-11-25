#include "Bullet_Debug_Drawer.h"

Bullet_Debug_Drawer::Bullet_Debug_Drawer() {

}

Bullet_Debug_Drawer::~Bullet_Debug_Drawer() {

}

void Bullet_Debug_Drawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
	CL->Debug_Line_Vertices[CL->Debug_Line_Vertices_Counter] = glm::vec3(from.x(), from.y(), from.z());
	CL->Debug_Line_Vertices[CL->Debug_Line_Vertices_Counter +1] = glm::vec3(to.x(), to.y(), to.z());

	CL->Debug_Line_Vertices_Counter += 2;

}
