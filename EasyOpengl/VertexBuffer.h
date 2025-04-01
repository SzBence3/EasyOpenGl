
#pragma once
#include<vector>
#include"glTypeConversion.h"

namespace eogl {
    class VertexBuffer {
    public:
        class Layout{
            friend class VertexArray;
            class Layer{
                friend class VertexArray;
                friend class Layout;
                unsigned char count;
                unsigned short size;
                bool normalized;
                unsigned int type;
                unsigned int index;
            };
            std::vector<Layer> layers;
        public:
            Layout() = default;
            Layout(std::initializer_list<Layer> layers) : layers(layers) {}
            template<typename T>  void pushLayer(const int count , const unsigned int index, const bool normalized = false)
            {
                layers.push_back(newLayer<T>(count, index, normalized));
            }
            template<typename T>  static Layer newLayer(const int count , const unsigned int index, const bool normalized = false)
            {
                Layer layer{};
                layer.count = count;
                layer.normalized = normalized;
                layer.size = sizeof(T);
                layer.type = getGlType<T>();
                layer.index = index;
                return layer;
            }
            void bind(unsigned int divisor) const;
            void unBind() const;
        };
    private:
        unsigned int id, size, divisor;
        Layout layout;
    public:
        VertexBuffer();
        //size is in bytes
        VertexBuffer(unsigned int size,Layout layout, const void* data = nullptr, unsigned int divisor = 0);
        ~VertexBuffer();
        //size is in bytes
        void reassign(unsigned int size, const void* data);
        void setDivisor(const unsigned int divisor) { this->divisor = divisor; }
        void setLayout(const Layout &layout) { this->layout = layout; };
        [[nodiscard]] const Layout& getLayout() const { return layout; };
        [[nodiscard]] unsigned int getDivisor() const { return divisor; }
        [[nodiscard]] unsigned int getSize() const { return size; }
        void subData(unsigned int offset, unsigned int size, const void* data);
        void bind() const;
        void VertexBuffer::unBind() const
        {
            layout.unBind();
        }
    };
}