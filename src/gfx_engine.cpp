#include "gfx_engine.h"

#include "exception.h"
#include "fmt/format.h"

GfxEngine::GfxEngine()
{

}

void GfxEngine::addActor(std::shared_ptr<Actor> actor, const std::string& name)
{
    if (m_actors.count(name) > 0)
    {
        throw Exception(fmt::format("Actor with name \"{}\" already exists.",  name));
    }
    m_actors[name] = actor;
}

std::shared_ptr<Actor> GfxEngine::getActorByName(const std::string& name)
{
    if (m_actors.count(name) > 0)
    {
        return m_actors.at(name);
    }
    else
    {
        return std::shared_ptr<Actor>();
    }
}

std::map<std::string, std::shared_ptr<Actor>> GfxEngine::getAllActors()
{
    return m_actors;
}

void GfxEngine::draw(PaintSurface& surface)
{
    // first let actors act
    for (auto& actor: m_actors)
    {
        actor.second->act(*this);
    }

    // second draw the actors
    for (auto& actor: m_actors)
    {
        auto pos = actor.second->getPos();
        surface.drawImage(*actor.second->getImage(), pos[0], pos[1], true); // @todo not all actors need transparency...
    }
}
