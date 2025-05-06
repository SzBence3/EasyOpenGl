#include<glm/glm.hpp>


namespace eogl{
    template <int posDCount = 3, int texDCount = 0, int normDCount = 0,int extraiDCount1 = 0, int extrafDCount1 = 0, int extrafDCount2 = 0>
    struct Vertex{
        #if posDCount > 0
        glm::vec<posDCount, float> pos;
        #endif
        #if texDCount > 0
        glm::vec<texDCount, float> tex;
        #endif
        #if normDCount > 0
        glm::vec<normDCount, float> norm;
        #endif
        #if extraiDCount1 > 0
        glm::vec<extraiDCount1, int> extra1;
        #endif
        #if extrafDCount1 > 0
        glm::vec<extraDCount1, float> extra1;
        #endif
        #if extrafDCount2 > 0
        glm::vec<extraDCount2, float> extra2;
        #endif
        Vertex(){
            #if posDCount > 0
            pos = glm::vec<posDCount, float>(0);
            #endif
            #if texDCount > 0
            tex = glm::vec<texDCount, float>(0);
            #endif
            #if normDCount > 0
            norm = glm::vec<normDCount, float>(0);
            #endif
            #if extraiDCount1 > 0
            extra1 = glm::vec<extraiDCount1, int>(0);
            #endif
            #if extraDCount1 > 0
            extra1 = glm::vec<extraDCount1, float>(0);
            #endif
            #if extraDCount2 > 0
            extra2 = glm::vec<extraDCount2, float>(0);
            #endif
        }
    };  
}