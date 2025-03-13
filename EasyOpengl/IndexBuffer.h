#pragma once

class IndexBuffer {
	unsigned int ibo, size;
public:
	IndexBuffer(int size, void* data = nullptr);
	~IndexBuffer();
	void bind() const;
	void unBind() const;
	void subData(unsigned int begin, unsigned int size, void* data);
	inline unsigned int getSize() { return size; }
};