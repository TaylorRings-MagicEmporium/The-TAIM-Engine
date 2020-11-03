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
}

void FileLoader_System::LoadShaders()
{

}

void FileLoader_System::LoadEntities()
{

	std::vector<std::string> elementList;
	//std::vector<std::string> entitiyList;

	lua_State* F = luaL_newstate();
	luaL_dofile(F, "LUA files/player.lua");
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
		LuaRef transform = ComponentView["Transform"];
		if (!transform.isNil()) {
			LuaRef Position = transform["Position"];
			LuaRef Rotation = transform["Rotation"];
			LuaRef tag = transform["Tag"];
			if (!Position.isNil()) {
				TTD.position.x = Position["x"].cast<float>();
				TTD.position.y = Position["y"].cast<float>();
				TTD.position.z = Position["z"].cast<float>();
				
				//std::cout << Position["x"].cast<float>() << ", " << Position["y"].cast<float>() << ", " << Position["z"].cast<float>() << std::endl;

			}
			else {
				std::cout << "NO POSITION" << std::endl;
			}
			if (!Rotation.isNil()) {
				TTD.degrees = Rotation["degrees"].cast<float>();
				TTD.rotateAxis.x = Rotation["axisX"].cast<float>();
				TTD.rotateAxis.y = Rotation["axisY"].cast<float>();
				TTD.rotateAxis.z = Rotation["axisZ"].cast<float>();
				//std::cout << Rotation["degrees"].cast<float>() << ", " << Rotation["axisX"].cast<float>() << ", " << Rotation["axisY"].cast<float>() << ", " << Rotation["axisZ"].cast<float>() << std::endl;
			}
			else {
				std::cout << "NO ROTATION" << std::endl;
			}
			if (!tag.isNil()) {
				TTD.tag = tag.cast<std::string>();
			}
		}
		else {
			std::cout << "NO TRANSFORM" << std::endl;
		}

		Entity* object = ES->CreateEntity(TTD.position, glm::angleAxis(glm::radians(TTD.degrees), glm::normalize(TTD.rotateAxis)),TTD.tag);
		//EntityList.push_back();

		//MESH RENDEREER
		LuaRef meshRend = ComponentView["MeshRenderer"];
		if (!meshRend.isNil()) {
			object->SetComponent(GS->CreateMeshRenderer(meshRend["MeshPath"].cast<std::string>(), SR->GetShader(meshRend["ShaderName"].cast<std::string>()), meshRend["flipImage"].cast<bool>()));
			//std::cout << meshRend["MeshPath"].cast<std::string>() << ", " << meshRend["ShaderName"].cast<std::string>() << ", " << meshRend["flipImage"].cast<bool>() << std::endl;
		}

		//RIGIDBODY
		LuaRef Rigid = ComponentView["Rigidbody"];

		if (!Rigid.isNil()) {
			LuaRef offset = Rigid["offset"];
			if (!offset.isNil()) {
				std::cout << offset["x"].cast<float>() << ", " << offset["y"].cast<float>() << ", " << offset["z"].cast<float>() << std::endl;
			}
			
			std::cout << Rigid["mass"].cast<float>() << std::endl;
			object->SetComponent(PS->CreateRigidbody(glm::vec3(offset["x"].cast<float>(), offset["y"].cast<float>(), offset["z"].cast<float>()), Rigid["mass"].cast<float>()));
		}

		//COLLIDER
		LuaRef Coll = ComponentView["Collider"];
		if (!Coll.isNil()) {
			std::cout << Coll["sizeX"].cast<float>() << ", " << Coll["sizeY"].cast<float>() << ", " << Coll["sizeZ"].cast<float>() << std::endl;
			object->SetComponent(PS->CreateCollider(glm::vec3(Coll["sizeX"].cast<float>(), Coll["sizeY"].cast<float>(), Coll["sizeZ"].cast<float>())));
		}
		std::cout << std::endl;
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