#include "FileLoader_System.h"

extern "C" {
#include <Lua/lua.h>
#include <Lua/lauxlib.h>
#include <Lua/lualib.h>
}

#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

FileLoader_System::FileLoader_System()
{
	LevelFiles.push_back("Lua files/player.lua");
	LevelFiles.push_back("Lua files/level.lua");
}

void FileLoader_System::LoadShaders()
{

}

void FileLoader_System::LoadEntities()
{

	std::vector<std::string> elementList;
	std::string FileString = LevelFiles[fileCount];

	lua_State* F = luaL_newstate();
	luaL_dofile(F, FileString.c_str());
	int indx1 = FileString.find_last_of("/") + 1;
	std::string FTag = FileString.substr(indx1, FileString.find_last_of(".") - indx1);
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	std::string source =
		"function getElements(tab) "
		"s = \"\""
		"for k,v in pairs(_G[tab]) do "
		"	s = s..k..\"|\" "
		"	end "
		"return s "
		"end";

	luaL_loadstring(F, source.c_str());
	lua_pcall(F, 0, 0, 0);
	lua_getglobal(F, "getElements");
	lua_pushstring(F, "EntityList");
	lua_pcall(F, 1, 1, 0);

	std::string ans = lua_tostring(F, -1);
	std::vector<std::string> entityStrings;
	bool IsEntity = false;
	std::string temp = "";
	for (int i = 0; i < ans.size(); i++) {
		if (ans.at(i) == '|') {
			entityStrings.push_back(temp);
			temp = "";
		}
		else {
			temp += ans.at(i);
		}

	}

	int n = lua_gettop(F);
	lua_pop(F, 1);
	LuaRef EntityRef = getGlobal(F, "EntityList");
	for (int a = 0; a < entityStrings.size(); a++) {
		LuaRef ComponentView = EntityRef[entityStrings.at(a)];
		//Entity object;

		//TRANSFORM
		TempTransData TTD;
		TTD.FileTag = FTag;
		LuaRef transform = ComponentView["Transform"];
		if (!transform.isNil()) {
			LuaRef Position = transform["Position"];
			LuaRef Rotation = transform["Rotation"];
			LuaRef Scale = transform["Scale"];
			LuaRef tag = transform["Tag"];
			if (!Position.isNil()) {
				TTD.position.x = Position["x"].cast<float>();
				TTD.position.y = Position["y"].cast<float>();
				TTD.position.z = Position["z"].cast<float>();
			}
			else {
				//std::cout << "NO POSITION" << std::endl;
			}
			if (!Rotation.isNil()) {
				TTD.degrees = Rotation["degrees"].cast<float>();
				TTD.rotateAxis.x = Rotation["axisX"].cast<float>();
				TTD.rotateAxis.y = Rotation["axisY"].cast<float>();
				TTD.rotateAxis.z = Rotation["axisZ"].cast<float>();
			}
			else {
				//std::cout << "NO ROTATION" << std::endl;
			}
			if (!Scale.isNil()) {
				TTD.scale.x = Scale["x"].cast<float>();
				TTD.scale.y = Scale["y"].cast<float>();
				TTD.scale.z = Scale["z"].cast<float>();
			}
			else {
				//std::cout << "NO SCALE" << std::endl;
			}
			
			if (!tag.isNil()) {
				TTD.tag = tag.cast<std::string>();
			}
		}
		else {
			//std::cout << "NO TRANSFORM" << std::endl;
		}

		Entity* object = ES->CreateEntity(TTD.position, glm::angleAxis(glm::radians(TTD.degrees), glm::normalize(TTD.rotateAxis)),TTD.scale,TTD.tag, TTD.FileTag);

		//MESH RENDEREER
		LuaRef meshRend = ComponentView["MeshRenderer"];
		if (!meshRend.isNil()) {
			Component* temp = GS->CreateMeshRenderer(meshRend["MeshPath"].cast<std::string>(), SR->GetShader(meshRend["ShaderName"].cast<std::string>()), meshRend["flipImage"].cast<bool>());
			object->SetComponent(temp);
			//std::cout << meshRend["MeshPath"].cast<std::string>() << ", " << meshRend["ShaderName"].cast<std::string>() << ", " << meshRend["flipImage"].cast<bool>() << std::endl;
			
			if (meshRend["ShaderName"].cast<std::string>() == "basic") {
				glm::vec4 col;
				LuaRef colour = meshRend["Colour"];
				if (!colour.isNil()) {
					col = glm::vec4(colour["r"].cast<float>(), colour["g"].cast<float>(), colour["b"].cast<float>(), colour["a"].cast<float>());
				}
				else {
					col = glm::vec4(1.0, 0, 1.0, 1.0);
				}
				static_cast<MeshRenderer*>(temp)->SetCol(col);
			}


		}

		//RIGIDBODY
		LuaRef Rigid = ComponentView["Rigidbody"];

		if (!Rigid.isNil()) {
			LuaRef offset = Rigid["offset"];
			if (!offset.isNil()) {

			}
			
			std::cout << Rigid["mass"].cast<float>() << std::endl;
			Component* temp = PS->CreateRigidbody(glm::vec3(offset["x"].cast<float>(), offset["y"].cast<float>(), offset["z"].cast<float>()), Rigid["mass"].cast<float>());
			object->SetComponent(temp);
		
			bool locks[3] = { false,false,false };
			LuaRef lockX = Rigid["LockX"];
			LuaRef lockY = Rigid["LockY"];
			LuaRef lockZ = Rigid["LockZ"];
			std::cout << Rigid["LockX"].cast<bool>() << std::endl;
			if (!lockX.isNil()) {
				locks[0] = lockX.cast<bool>();
			}
			if (!lockY.isNil()) {
				locks[1] = lockY.cast<bool>();
			}
			if (!lockZ.isNil()) {
				locks[2] = lockZ.cast<bool>();
			}

			static_cast<Rigidbody*>(temp)->ConstrictRotation(locks[0], locks[1], locks[2]);
		}

		//CUBECOLLIDER
		LuaRef CuColl = ComponentView["CubeCollider"];
		if (!CuColl.isNil()) {
			object->SetComponent(PS->CreateCubeCollider(glm::vec3(CuColl["sizeX"].cast<float>(), CuColl["sizeY"].cast<float>(), CuColl["sizeZ"].cast<float>())));
		}
		std::cout << std::endl;

		//SPHERECOLLIDER
		LuaRef SphColl = ComponentView["SphereCollider"];
		if (!SphColl.isNil()) {
			object->SetComponent(PS->CreateSphereCollider(SphColl["radius"].cast<float>()));
		}
		std::cout << std::endl;

		//AUDIOPLAYER
		LuaRef AudPla = ComponentView["AudioPlayer"];
		if (!AudPla.isNil()) {
			object->SetComponent(AS->CreateAudioPlayer(AudPla["AudioPath"].cast<std::string>().c_str()));
		}

		//CAMERA
		LuaRef Cam = ComponentView["Camera"];
		if (!Cam.isNil()) {
			LuaRef type = Cam["Type"];
			if (type.cast<std::string>() == "FIRST") {
				LuaRef Off = Cam["Offset"];
				object->SetComponent(CS->CreateFirstCamera(glm::vec3(Off["x"].cast<float>(), Off["y"].cast<float>(), Off["z"].cast<float>())));
			} else if (type.cast<std::string>() == "STATIC") {
				LuaRef targ = Cam["Target"];
				object->SetComponent(CS->CreateStaticCamera(glm::vec3(targ["x"].cast<float>(), targ["y"].cast<float>(), targ["z"].cast<float>())));
			}
			else {
				std::cout << "WARNING: no camera type was stated for tag " << TTD.tag << std::endl;
			}

		}

		//ANIMATOR
		LuaRef ani = ComponentView["Animator"];
		if (!ani.isNil()) {
			bool temp = ani["start"].cast<bool>();
			object->SetComponent(AnS->CreateAnimator(ani["Type"].cast<std::string>(), ani["loop"].cast<bool>(), ani["start"].cast<bool>()));
		}
	}
	std::cout << "objects loaded correctly!" << std::endl;
}

ConfigData FileLoader_System::LoadConfig()
{
	ConfigData CD = ConfigData();

	lua_State* F = luaL_newstate();
	luaL_dofile(F, "LUA files/config.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);
	
	LuaRef t = getGlobal(F, "config");
	if (t.isNil()) {
		std::cout << "CONFIG FILE MISSING OR BROKEN. reverting to default values" << std::endl;
		return CD;
	}

	LuaRef title = t["title"];
	LuaRef w = t["width"];
	LuaRef h = t["height"];
	LuaRef RePath = t["resourcePATH"];

	CD.FileLoaded = true;

	CD.ScreenSize = glm::vec2(w.cast<int>(), h.cast<int>());
	CD.WindowName = title.cast<std::string>();

	ResourcePATH = RePath.cast<std::string>();
	
	return CD;
}

void FileLoader_System::SwapFile() {
	fileCount++;
	if (fileCount > LevelFiles.size() - 1) {
		fileCount = 0;
	}
}
