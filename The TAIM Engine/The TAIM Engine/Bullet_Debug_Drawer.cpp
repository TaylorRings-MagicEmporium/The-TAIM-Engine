#include "Bullet_Debug_Drawer.h"

Bullet_Debug_Drawer::Bullet_Debug_Drawer() {

}

Bullet_Debug_Drawer::~Bullet_Debug_Drawer() {

}

void Bullet_Debug_Drawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
	//if (m_currentLineColor != color) {
	//	flushLines();
	//	m_currentLineColor = color;
	//}

	CL->Debug_Line_Vertices[CL->Debug_Line_Vertices_Counter] = glm::vec3(from.x(), from.y(), from.z());
	CL->Debug_Line_Vertices[CL->Debug_Line_Vertices_Counter +1] = glm::vec3(to.x(), to.y(), to.z());

	CL->Debug_Line_Vertices_Counter += 2;

	//MyDebugVec3 from1(from);
	//MyDebugVec3 to1(to);

	//m_linePoints.push_back(from);
	//m_linePoints.push_back(to);

	//m_lineIndices.push_back(m_lineIndices.size());
	//m_lineIndices.push_back(m_lineIndices.size());
}

//void GLDebugDrawer::setDebugMode(int debugMode) {
//	m_debugMode = debugMode;
//}

//void GLDebugDrawer::flushLines() {
//
//	if (counter > 0) {
//
//		//std::cout << counter << std::endl;
//		////std::cout << "FROM: " << vertices[0].x << ", " << vertices[0].y << ", " << vertices[0].z << std::endl;
//		////std::cout << "TO: " << vertices[1].x << ", " << vertices[1].y << ", " << vertices[1].z << std::endl;
//		////std::cout << std::endl;
//		//std::cout << "FROM: " << vertices[0].x << ", " << vertices[0].y << ", " << vertices[0].z << std::endl;
//		//std::cout << "TO: " << vertices[1].x << ", " << vertices[1].y << ", " << vertices[1].z << std::endl;
//		//std::cout << std::endl;
//		//std::cout << "FROM: " << vertices[14].x << ", " << vertices[14].y << ", " << vertices[14].z << std::endl;
//		//std::cout << "TO: " << vertices[15].x << ", " << vertices[15].y << ", " << vertices[15].z << std::endl;
//		//std::cout << std::endl;
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, counter * sizeof(glm::vec3), vertices);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		//float debugColor[4];
//		//debugColor[0] = m_currentLineColor.x();
//		//debugColor[1] = m_currentLineColor.y();
//		//debugColor[2] = m_currentLineColor.z();
//		//debugColor[3] = 1.f;
//
//		s->Use();
//		glBindVertexArray(VAO);
//
//		unsigned int transformLoc = glGetUniformLocation(s->ID, "proj");
//
//		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EM->CC->GetViewCamProj()));
//		transformLoc = glGetUniformLocation(s->ID, "view");
//		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EM->CC->GetViewCamView()));
//
//		glDrawArrays(GL_LINES, 0, counter);
//
//		std::fill_n(vertices, counter, glm::vec3(0.0));
//		counter = 0;
//	}
//
//}