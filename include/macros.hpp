#ifndef MACROS_HPP
#define MACROS_HPP

#include <memory>

#define PTR_CONSTRUCTOR(CLASSNAME)\
    typedef typename std::shared_ptr<CLASSNAME > Ptr;\
    template <typename... Args> static Ptr create(Args&&... args) {\
        return Ptr(new CLASSNAME(args...));\
    }\

#endif
