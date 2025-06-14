#pragma once
class IDamageable 
{
public:
    virtual void takeDamage(int amount) = 0;
};