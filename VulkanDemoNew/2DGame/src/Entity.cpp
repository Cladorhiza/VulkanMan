#include "Entity.h"

Entity::Entity() 
	:id(666666), hasComponentBits(0x00000000), tag("")
{

}

Entity::Entity(uint32_t id)
	:id(id), hasComponentBits(0x00000000), tag("")
{



}

Entity::Entity(uint32_t id, std::string tag)
	:id(id), hasComponentBits(0x00000000), tag(tag)
{



}