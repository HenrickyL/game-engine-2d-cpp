#ifndef UT_GL_VERTEXBUFFER_ID_H
#define UT_GL_VERTEXBUFFER_ID_H

#include "VertexBufferID.h"
#include "types.h"
#include "UT_Utils.h"
class GLVertexBufferID : public VertexBufferID {
private:
    uint _vao = 0;           // Vertex Array Object
    uint _vboPosition = 0;   // Vertex Buffer Object for positions
    uint _vboColor = 0;      // Vertex Buffer Object for colors
    uint _ebo = 0;           // Element Buffer Object

public:
    uint vao() const;
    uint vboPosition() const;
    uint vboColor() const;
    uint ebo() const;

    void SetVao(uint value);
    void SetVboPosition(uint value);
    void SetVboColor(uint value);
    void SetEbo(uint value);

    void SetId(VertexBufferID* value) override;
};

inline uint GLVertexBufferID::vao() const { return _vao; }
inline uint GLVertexBufferID::vboPosition() const { return _vboPosition; }
inline uint GLVertexBufferID::vboColor() const { return _vboColor; }
inline uint GLVertexBufferID::ebo() const { return _ebo; }

inline void GLVertexBufferID::SetVao(uint value) { _vao = value; }
inline void GLVertexBufferID::SetVboPosition(uint value) { _vboPosition = value; }
inline void GLVertexBufferID::SetVboColor(uint value) { _vboColor = value; }
inline void GLVertexBufferID::SetEbo(uint value) { _ebo = value; }

inline void GLVertexBufferID::SetId(VertexBufferID* value) {
    GLVertexBufferID* id = dynamic_cast<GLVertexBufferID*>(value);
    if (id != nullptr) {
        this->SetVao(id->vao());
        this->SetVboPosition(id->vboPosition());
        this->SetVboColor(id->vboColor());
        this->SetEbo(id->ebo());
    }
}


#endif