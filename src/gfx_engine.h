#ifndef GFX_ENGINE_H
#define GFX_ENGINE_H

#include "engine_access.h"
#include "paint_surface.h"

#include <map>
#include <memory>



class GfxEngine : public EngineAccess, public std::enable_shared_from_this<EngineAccess>
{
public:
    GfxEngine();

    /**
     * Adds a new actor to the engine.
     *
     * @param actor The actor to be added.
     * @param name The name of the actor. The name must be unique.
     *             If name is not unique an exception is thrown.
     */
    void addActor(std::shared_ptr<Actor> actor, const std::string& name);

    /**
     * This method should be called after all actors have been added to the engine.
     * It causes the init() method of all the actors to be called.
     */
    void start();

    /**
     * This method draws all currently visible actors to the given PaintSurface.
     *
     * The method also clls the act() method of all actors.
     *
     * @param surface The PaintSurface to draw on.
     */
    void draw(PaintSurface& surface);

    // EngineAccess interface
public:
    std::shared_ptr<Actor> getActorByName(const std::string &name) override;
    std::map<std::string, std::shared_ptr<Actor>> getAllActors() override;

private:
    std::map<std::string, std::shared_ptr<Actor>> m_actors;
};

#endif // GFX_ENGINE_H
