#include "tilemap.h"

tilemap::tilemap(Texture* tileset, v2u tileSize) {
    m_tileset = tileset;
    m_tileSize = tileSize;
}
void tilemap::update(vector<tile>& tiles) {
    m_vertices.setPrimitiveType(Triangles);
    m_vertices.resize(tiles.size() * 6);

    for (tile& tile : tiles) {
        int index = &tile - &tiles[0];

        int tu = tile.get_texture_id() % (m_tileset->getSize().x / m_tileSize.x);
        int tv = tile.get_texture_id() / (m_tileset->getSize().x / m_tileSize.x);

        Vertex* triangles = &m_vertices[(index) * 6];

        triangles[0].position = v2f(tile.get_pos().x, tile.get_pos().y);
        triangles[1].position = v2f(tile.get_pos().x + m_tileSize.x, tile.get_pos().y);
        triangles[2].position = v2f(tile.get_pos().x, tile.get_pos().y + m_tileSize.y);
        triangles[3].position = v2f(tile.get_pos().x, tile.get_pos().y + m_tileSize.y);
        triangles[4].position = v2f(tile.get_pos().x + m_tileSize.x, tile.get_pos().y);
        triangles[5].position = v2f(tile.get_pos().x + m_tileSize.x, tile.get_pos().y + m_tileSize.y);

        triangles[0].texCoords = v2f(tu * m_tileSize.x, tv * m_tileSize.y);
        triangles[1].texCoords = v2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
        triangles[2].texCoords = v2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
        triangles[3].texCoords = v2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
        triangles[4].texCoords = v2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
        triangles[5].texCoords = v2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
    }
}
void tilemap::clean() {
    m_vertices.clear();
}

void tilemap::draw(RenderTarget& target, RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}