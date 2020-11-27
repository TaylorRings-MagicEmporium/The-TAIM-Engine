#pragma once
#include <vector>
#include "MeshRenderer.h"
#include "ShaderRegistry.h"
#include "Model_Registry.h"
#include "SubSystem.h"
// the graphics system is responsible for the handling and executing of components that give a display onto the screen
class Graphics_System : public SubSystem {
private:
	// holds the vector of MeshRenderer components
	std::vector<MeshRenderer> ListOfMeshRenderers;

	unsigned int DebugVAO;
	unsigned int DebugVBO;
	Shader* s;


	void UpdateTransformEv(Event* e);
	//void GunShotFeedback(Event* e);
	void HideAnimatedComponent(Event* e);
public:
	ShaderRegistry* SR;
	Model_Registry MR = Model_Registry();
	// the initialisation of the Graphics system which needs to maximum number of components allowed.

	Graphics_System();

	// destroys the system
	~Graphics_System();

	// Update will cause the graphics system to do its generic procedure and poll the events related to it.
	void Update();
	void Startup();
	void ShutDown();
	void SetComponentSize(int size);
	void ResetSystem();
	// creates a mesh renderer that is capable of displaying something on the screen.
	// it returns the pointer of it the the entity that required it.
	MeshRenderer* CreateMeshRenderer(std::string path, Shader* shader, bool flip);

	// draws everything on to the screen.
	void Draw();

	// draws speicifc debug visuals from multiple systems
	void DebugDraw();

	// toggles the appearence of the mesh being displayed.
	void ToggleHidingComponent(ComponentType c, Entity* e);
	void SyncComponentsToSystem();
};