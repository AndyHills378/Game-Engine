#include "CubeMap.h"

CubeMap::CubeMap(char* filename)
{
	lua_State* F = luaL_newstate();
	luaL_dofile(F, filename);
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	/*LuaRef r = getGlobal(F, "directories");
	std::string textureDir = r["textures"].cast<std::string>();*/
	LuaRef t = getGlobal(F, "position");

	LuaRef coord1 = t["coords1"];
	LuaRef coord2 = t["coords2"];
	LuaRef coord3 = t["coords3"];
	LuaRef coord4 = t["coords4"];

	this->coords1 = glm::vec3(coord1["X"].cast<float>(), coord1["Y"].cast<float>(), coord1["Z"].cast<float>());
	this->coords2 = glm::vec3(coord2["X"].cast<float>(), coord2["Y"].cast<float>(), coord2["Z"].cast<float>());
	this->coords3 = glm::vec3(coord3["X"].cast<float>(), coord3["Y"].cast<float>(), coord3["Z"].cast<float>());
	this->coords4 = glm::vec3(coord4["X"].cast<float>(), coord4["Y"].cast<float>(), coord4["Z"].cast<float>());

	cout << "object: " << filename << " loaded" << endl;
}

CubeMap::~CubeMap()
{
}
