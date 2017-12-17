#ifndef GPOINTLIGHT_H
#define GPOINTLIGHT_H
#include "gmodel.h"

enum GLightType
{
    kDirectionLight,
    kPointLight,
    kSpotLight
};

enum GLightPropType
{
    kLightPropType_Enable,
    kLightPropType_Type,
    kLightPropType_Color,
    kLightPropType_Dir,
    kLightPropType_Pos,
    kLightPropType_Ambient,
    kLightPropType_Shininess,
    kLightPropType_Strengthen,
    kLightPropType_Attenuation,
    kLightPropType_Linear_attenuation,
    kLightPropType_Quadratic_attenuation,
    kLightPropType_Spot_inner_cutoff,
    kLightPropType_Spot_outer_cutoff,
    kLightPropType_TypeNumbs
};

struct GLightProp
{
    bool        enable;
    GLightType  type;
    glm::vec3   color;
    glm::vec3   dir;
    glm::vec3   pos;
    glm::vec3   ambient;
    float       shininess;
    float       strengthen;
    float       attenuation;
    float       linear_attenuation;
    float       quadratic_attenuation;
    float       spot_inner_cutoff;
    float       spot_outer_cutoff;
};

class GLightBase : public GModel
{
public:
    GLightBase();

    static const std::string GetLightTypeName(GLightType type);
    static const std::string GetLightPropName(GLightPropType type);
    static const char** GetLightPropNameArr();

    virtual void Init(const char *v_shader, const char *f_shader,
                      GUniformType* uniform_types, int count=0) = 0;

    GLightProp property;
    void SetPropertyLocal(GLightPropType type,GLint local);
    GLint GetPropertyLocal(GLightPropType type);
    void UploadProperty(GLightPropType type,GCamera* camera);
protected:
    GLint      _property_local[GLightPropType::kLightPropType_TypeNumbs];
};

class GCubeLight : public GLightBase
{
public:
    void Init(const char *v_shader, const char *f_shader, GUniformType* uniform_types, int count=0);
    void GetVertexData(GLfloat *&vertex_data, GLuint *&vertex_index_data, GLfloat *&vertex_color_data,
                       int &vertex_data_size, int &index_data_size, int &color_data_size,
                       int &vertex_pos_comp_count, int &vertex_color_comp_count);
    void Draw();
private:
    GLuint _vertex_buffer;
    GLuint _vertex_arr_obj;
    GLuint _vertex_index_buffer;
    GLuint _program;
};

#endif // GPOINTLIGHT_H
