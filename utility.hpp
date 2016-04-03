//
// Created by chnvideo on 2016/4/2.
//

#ifndef RTMP_SERVER_UTILITY_HPP
#define RTMP_SERVER_UTILITY_HPP

#include <stddef.h>

extern void srs_random_generate(char* bytes, int size);

extern bool srs_is_little_endian();


#define AutoFree(classname, instance) \
imple__AutoFree<classname> _auto_free_##instance(&instance, false)

#define AutoFreeA(classname, instance) \
imple__AutoFree<classname> _auto_free_array_##instance(&instance, true)

template <class T>
class imple__AutoFree
{
private:
    T** ptr;
    bool is_array;
public:
    imple__AutoFree(T** p, bool array){
        ptr = p;
        is_array = array;
    }

    virtual ~imple__AutoFree(){
        if (ptr == NULL || *ptr == NULL) {
            return ;
        }

        if (is_array) {
            delete[] *ptr;
        } else {
            delete *ptr;
        }

        *ptr = NULL;
    }
};

#endif //RTMP_SERVER_UTILITY_HPP
