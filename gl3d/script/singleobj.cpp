#include "general.hpp"
#include "objs.hpp"

SingleObj::SingleObj() {

}

ColorCuboid3::ColorCuboid3(shared_ptr<Vec3> pos, shared_ptr<Vec3> size, shared_ptr<Vec3> rot, std::array<float, 4> color) {
    this->pos = pos;
    this->size = size;
    this->rot = rot;
    this->color = color;
}

void ColorCuboid3::render(Game *game, shared_ptr<Camera3> camera, shared_ptr<Vec3> lightD) {
    glUniform1i(game->luModeV, 1);
    glUniform3f(game->luMPos, this->pos->x, this->pos->y, this->pos->z);
    glUniform3f(game->luMSize, this->size->x, this->size->y, this->size->z);
    glUniform3f(game->luMRot, this->rot->x, this->rot->y, this->rot->z);
    glUniform4f(game->luCProj, camera->asp, camera->fov, camera->near, camera->far);
    glUniform3f(game->luCPos, camera->pos->x, camera->pos->y, camera->pos->z);
    glUniform3f(game->luCRot, camera->rot->x, camera->rot->y, camera->rot->z);
    glUniform1i(game->luModeF, 3);
    glUniform3f(game->luColor, color[0], color[1], color[2]);
    glUniform3f(game->luLightD, lightD->x, lightD->y, lightD->z);

    glBindBuffer(GL_ARRAY_BUFFER, game->bCuboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game->bCuboidIndex);
    glVertexAttribPointer(game->laPosition, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)(0));
    glVertexAttribPointer(game->laTexcoord, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glVertexAttribPointer(game->laNormal, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 5));
    glEnableVertexAttribArray(game->laPosition);
    glEnableVertexAttribArray(game->laTexcoord);
    glEnableVertexAttribArray(game->laNormal);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)(0));
}