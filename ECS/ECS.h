#ifndef ECS_H
#define ECS_H

//Sistema manage'int entities ir komponents ((E)ntity (C)omponent (S)ystem)
//Kaip dabar suprantu: entities - objektai zaidimo pasaulyje, components "laukai" kuriuos entities turi (gali buti position, speed, etc.).

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID=std::size_t;
using Group = std::size_t;


//Kiekvienas komponento tipas tures sava id.
inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID=0u;
    return lastID++;
}

//Grazina komponento tipo id.
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID=getNewComponentTypeID();
    return typeID;
}

//Maksimalus komponentus skaicius.
constexpr std::size_t maxComponents=32;
constexpr std::size_t maxGroups=32;

//maxComponents dydzio bitset'as.
using ComponentBitSet=std::bitset<maxComponents>;
using GroupBitSet=std::bitset<maxGroups>;

//maxComponents dydzio masyvas, laikantis Component* tipo objektus.
using ComponentArray=std::array<Component*, maxComponents>;

class Component
{
public:
    Entity* entity; //Kiekvienas komponentas turi pointer'i i entity kuriam jis priklauso.

    virtual void init(){}
    virtual void update(){}
    virtual void draw(){}

    virtual ~Component(){}
};

class Entity //Entity - objektas zaidime.
{
private:
    Manager& manager;
    bool active=true;
    std::vector<std::unique_ptr<Component>> components; //Vektorius komponentu kurie priklauso siam entity.

    ComponentArray  componentArray;
    ComponentBitSet componentBitSet; //Bitsetas tam, kad butu galima greit patikrint ar entity turi tam tikra komponenta.
    GroupBitSet groupBitset;

public:
    Entity(Manager& mManager) : manager(mManager){}

    void update()
    {
        for(auto&c: components) c->update();

    }

    void draw()
    {
        for(auto& c:components) c->draw();
    }
    bool isActive() const{return active;} //Returnina ar entity aktyvi ar ne.
    void destroy(){active=false;} //Pazymi entity kaip neaktyvia.

    bool hasGroup(Group mGroup)
    {
        return groupBitset[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup)
    {
        groupBitset[mGroup] = false;
    }

    //Tikrina ar entity turi tam tikro tipo komponenta.
    template<typename T> bool hasComponent() const
    {
        return componentBitSet [getComponentTypeID<T>()];
    }

    //Prideda nauja komponenta
    template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...)); //Sukuria ir inicializuoja nauja komponenta su argumentais mArgs.
        c->entity=this; //Komponentas priklauso sitai entity.
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));//Prideda komponenta i komponentu vektoriu.

        componentArray[getComponentTypeID<T>()]=c; //Prideda komponenta i masyva.
        componentBitSet[getComponentTypeID<T>()]=true; //Update'ina BitSeta, kad jis sakytu kad komponentas yra.

        c->init();
        return *c;
    }

    //Returnina T tipo komponenta
    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager //Klase skirta visu entity valdymui
{
private:
    std::vector<std::unique_ptr<Entity>> entities; //Vektorius pointeriu i entities
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
    void update()
    {
        for(auto& e: entities) e->update(); //Update'ina visas entities
    }
    void draw()
    {
        for(auto& e:entities)e->draw(); //Draw'ina visas entities
    }

    //Panaikina neaktyvias entities.
    void refresh()
    {   
        for (auto i(0u); i < maxGroups; i++)
        {
            auto& v(groupedEntities[i]);
            v.erase(
                std::remove_if(std::begin(v), std::end(v),
                [i](Entity* mEntity)
            {
                return !mEntity->isActive() || !mEntity->hasGroup(i);
            }),
                std::end(v));
        }

        entities.erase(std::remove_if(std::begin(entities),std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity->isActive();
        }),
        std::end(entities));
    }

    void AddToGroup(Entity* mEntity, Group mGroup) 
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }

    //Prideda naujas entities.
    Entity& addEntity()
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr)); //Prideda naujai sukurta entity i vektoriu
        return *e;
    }
};

#endif
