#ifndef UT_GL_VERTEXBUFFER_ID_H
#define UT_GL_VERTEXBUFFER_ID_H

#include "VertexBufferID.h"
#include "types.h"
#include "UT_Utils.h"
class GLVertexBufferID : public VertexBufferID {
private:
    uint _vao = 0; // Vertex Array Object
    uint _vbo = 0; // Vertex Buffer Object
    uint _ebo = 0; // Element Buffer Object
public:
    uint vao()const;
    uint vbo()const;
    uint ebo()const;

    void SetVao(uint value);
    void SetVbo(uint value);
    void SetEbo(uint value);

    void SetId(VertexBufferID* value) override;

};


inline uint GLVertexBufferID::vao()const { return _vao; }
inline uint GLVertexBufferID::vbo()const { return _vbo; }
inline uint GLVertexBufferID::ebo()const { return _ebo; }


inline void GLVertexBufferID::SetVao(uint value) { _vao = value; }
inline void GLVertexBufferID::SetVbo(uint value) { _vbo = value; }
inline void GLVertexBufferID::SetEbo(uint value) { _ebo = value; }

inline void GLVertexBufferID::SetId(VertexBufferID* value) {
    GLVertexBufferID* id = dynamic_cast<GLVertexBufferID*>(value);;
    if (id != nullptr) {
        this->SetVao(id->vao());
        this->SetVbo(id->vbo());
        this->SetEbo(id->ebo());
    }
}


#endif