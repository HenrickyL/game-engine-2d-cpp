#ifndef UT_VERTEXBUFFER_ID_H
#define UT_VERTEXBUFFER_ID_H

class VertexBufferID {
public:
	virtual ~VertexBufferID() = default;
	virtual void SetId(VertexBufferID* value) = 0;
};
#endif