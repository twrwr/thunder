#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "pipelinepass.h"

class CommandBuffer;
class RenderTarget;
class MaterialInstance;
class AtlasNode;

class Camera;

class AreaLight;
class DirectLight;
class SpotLight;
class PointLight;
class Renderable;

class ShadowMap : public PipelinePass {
public:
    ShadowMap();

private:
    Texture *draw(Texture *source, PipelineContext *context) override;

    uint32_t layer() const override;

    void areaLightUpdate(PipelineContext *context, AreaLight *light, list<Renderable *> &components);
    void directLightUpdate(PipelineContext *context, DirectLight *light, list<Renderable *> &components, Camera &camera);
    void pointLightUpdate(PipelineContext *context, PointLight *light, list<Renderable *> &components);
    void spotLightUpdate(PipelineContext *context, SpotLight *light, list<Renderable *> &components);

    void cleanShadowCache();

    RenderTarget *requestShadowTiles(uint32_t id, uint32_t lod, int32_t *x, int32_t *y, int32_t *w, int32_t *h, uint32_t count);

private:
    unordered_map<uint32_t, pair<RenderTarget *, vector<AtlasNode *>>> m_tiles;
    unordered_map<RenderTarget *, AtlasNode *> m_shadowPages;

    Matrix4 m_scale;

    vector<Quaternion> m_directions;

};

#endif // SHADOWMAP_H
