#include "GameObject.h"

GameObject::GameObject(char* luaFile, char* filename, char* luaID, int objectID)
{
	lua_State* F = luaL_newstate();
	luaL_dofile(F, luaFile);
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef r = getGlobal(F, "directories");
	std::string textureDir = r["textures"].cast<std::string>();
	LuaRef t = getGlobal(F, luaID);

	LuaRef position = t["position"];
	LuaRef scale = t["scale"];
	LuaRef rotateVec = t["rotateVec"];

	this->objectToFollow = objectToFollow;
	this->objectID = objectID;
	this->filename = filename;
	this->position = glm::vec3(position["X"].cast<float>(), position["Y"].cast<float>(), position["Z"].cast<float>());
	this->scale = glm::vec3(scale["X"].cast<float>(), scale["Y"].cast<float>(), scale["Z"].cast<float>());
	this->textureLoc = textureDir + t["texture"].cast<std::string>();
	this->rotate = t["rotate"].cast<float>();
	this->rotateVec = glm::vec3(rotateVec["X"].cast<float>(), rotateVec["Y"].cast<float>(), rotateVec["Z"].cast<float>());
	this->objectToFollow = t["objectToFollow"].cast<bool>();
	cout << "object: " << luaID << " loaded" << endl;
	//if (objectID == 3) { this->objectToFollow = false; }
	setupObject();
}

GameObject::~GameObject()
{
}

void GameObject::setupObject()
{
	texture = new Texture(textureLoc, 1);
	mesh = new Mesh(this->filename, texture->texture, this->position, this->rotate, this->scale);
}

void GameObject::drawObject()
{
	modelMat = mat4(1.0);
	//modelMat = glm::rotate(modelMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = glm::translate(modelMat, this->position);
	modelMat = glm::rotate(modelMat, this->rotate, this->rotateVec);
	modelMat = glm::scale(modelMat, this->scale);
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));
	glBindVertexArray(mesh->VAO);
	glUniform1ui(glGetUniformLocation(GraphicsEngine::programId, "tex"), mesh->meshID);
	//glBindTexture(GL_TEXTURE_2D, texture->texture);
	mesh->drawMesh();
}