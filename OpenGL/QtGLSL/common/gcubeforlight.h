#ifndef GCUBEFORLIGHT_H
#define GCUBEFORLIGHT_H
#include "gmodel.h"
#include <string>
#include <array>
#include <vector>

enum GUniformType
{
};

struct GUniformInfo
{
    GUniformType    type;
    int             local;
    std::string     name;
};

enum GAttribType
{
    kPos = 0,
    kColor,
    kNormal,
    kAttribNums
};

class GCubeForLight : public GModel
{
public:
    GCubeForLight();
    void Init(const char* v_shader, const char* f_shader, GUniformInfo* uniform_infos, int count=0);

    void GetVertexData(GLfloat *&vertex_data, int &data_size, int& pos_comp_count, int& color_comp_count, int& normal_comp_count);
    void Draw();

private:
    std::vector<GUniformInfo> _uniform_infos;

    GLuint _vertex_buffer;
    GLuint _vertex_arr_obj;
    GLuint _program;
};

#endif // GCUBEFORLIGHT_H
