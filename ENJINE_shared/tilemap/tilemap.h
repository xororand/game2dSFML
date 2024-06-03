#ifndef H_TILEMAP_TILEMAP
#define H_TILEMAP_TILEMAP

#include "tile.h"

class tilemap : public Drawable, public Transformable {
public:
    tilemap(Texture* tileset, v2u tileSize);
    void update(vector<tile>& tiles);
    void clean();
private:
    virtual void draw(RenderTarget& target, RenderStates states) const;
    v2u m_tileSize;

    VertexArray m_vertices;
    Texture* m_tileset;
};

#endif