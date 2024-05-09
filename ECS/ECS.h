#ifndef ECS_H
#define ECS_H

//Sistema manage'int entities ir komponents ((E)ntity (C)omponent (S)ystem)
//Kaip dabar suprantu: entities - objektai zaidimo pasaulyje, components "laukai" kuriuos entities turi (gali buti Ftion, speed, etc.).

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID=std::size_t;


//Kiekvienas komponento tipas tures sava id.
inline ComponentID getComponentTypeID()
{
    static ComponentID lastID=0;
    return lastID++;
}

//Grazina komponento tipo id.
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID=getComponentTypeID();
    return typeID;
}

//Maksimalus komponentus skaicius.
constexpr std::size_t maxComponents=32;

//maxComponents dydzio bitset'as.
using ComponentBitSet=std::bitset<maxComponents>;

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
    bool active=true;
    std::vector<std::unique_ptr<Component>> components; //Vektorius komponentu kurie priklauso siam entity.

    ComponentArray  componentArray;
    ComponentBitSet componentBitSet; //Bitsetas tam, kad butu galima greit patikrint ar entity turi tam tikra komponenta.

public:
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

    //Tikrina ar entity turi tam tikro tipo komponenta.
    template<typename T> bool hasComponent() const
    {
        return componentBitSet [getComponentTypeID<T>];
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
        entities.erase(std::remove_if(std::begin(entities),std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity->isActive();
        }),
        std::end(entities));
    }

    //Prideda naujas entities.
    Entity& addEntity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr)); //Prideda naujai sukurta entity i vektoriu
        return *e;
    }
};

#endif
