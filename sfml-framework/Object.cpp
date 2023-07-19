#include "stdafx.h"
#include "Object.h"
#include "ObjectTable.h"

void Object::SetPosition(float x, float y)
{
    SpriteGo::SetPosition(x, y);
}

void Object::SetPosition(const sf::Vector2f& p)
{
    SpriteGo::SetPosition(p);
}

void Object::Init()
{
    SpriteGo::Init();
    SetOrigin(Origins::MC);
}

void Object::Reset()
{
    SpriteGo::Reset();
    sortLayer = 8;
}

void Object::Update(float dt)
{
    SpriteGo::Update(dt);
}

void Object::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}

bool Object::Load(const std::string& filePath)
{
    return true;
}

void Object::SetType(Types t)
{
    objectType = t;

    const ObjectInfo& info = DATATABLE_MGR.Get<ObjectTable>(DataTable::Ids::Object)->Get(t);

    int index = (int)objectType;
    textureId = info.textureId;
}

Object::Types Object::GetType() const
{
    return objectType;
}
