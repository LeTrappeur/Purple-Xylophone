#ifndef COLORCATEGORY_H_INCLUDED
#define COLORCATEGORY_H_INCLUDED

namespace ColorCategory
{
    enum Type
    {
        None = 0,
        Blue = 1 << 0,
        Red = 1 << 1,
        Green = 1 << 2,
    };
}


#endif // COLORCATEGORY_H_INCLUDED
