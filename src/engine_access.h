#ifndef ENGINE_ACCESS_H
#define ENGINE_ACCESS_H

#include "actor.h"

#include <memory>
#include <map>

class EngineAccess
{
public:
    virtual ~EngineAccess() {}
    virtual std::shared_ptr<Actor> getActorByName(const std::string& name) = 0;
    virtual std::map<std::string, std::shared_ptr<Actor>> getAllActors() = 0;
};

#endif // ENGINE_ACCESS_H
