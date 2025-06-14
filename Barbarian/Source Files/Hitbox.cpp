#include "../Header Files/Hitbox.h"
#include "../Header Files/IFighter.h"   //workaround
#include <iostream>

Hitbox::Hitbox(sf::Vector2f position, sf::Vector2f size, sf::Vector2f velocity, float damage, Entity* owner, float lifetime)
{
    expired = false;
    bounds = sf::FloatRect(position, size);
    this->velocity = velocity;
    this->lifetime = lifetime;
    this->damage = damage;
    this->owner = owner;
}

void Hitbox::update(float time) 
{
    if (expired)
    {
        //workaround
        IFighter* o = dynamic_cast<IFighter*>(owner);
        if (o)
        {
            o->endAttack();
            return;
        } 
    }
    bounds.position.x += velocity.x * time;
    bounds.position.y += velocity.y * time;


    if (lifetime != 0)
    {
        elapsed += time;
        if (elapsed >= lifetime)
            expired = true;
    }
   
}

void Hitbox::setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }

void Hitbox::setExpired(bool expired) 
{ 
    this->expired = expired; 
    //workaround
    IFighter* o = dynamic_cast<IFighter*>(owner);
    if (o)
    {
        o->endAttack();
        return;
    }
}

bool Hitbox::isExpired() const { return expired;}

sf::FloatRect Hitbox::getBounds() const { return bounds;}

float Hitbox::getDamage() const { return damage;}

Entity* Hitbox::getOwner() const { return owner;}