#pragma once

#include "Object/GameObject.h"
#include <rapidjson/document.h>
#include "SmartPointer/SmartPointer.h"

class ObjectGenerator
{
public:
	ObjectGenerator();
	~ObjectGenerator();
	SharedPointer<GameObject> CreateGameObjectFromJSONDocument(const rapidjson::Document InJSONDocument);

};

