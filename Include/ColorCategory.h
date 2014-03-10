#ifndef COLORCATEGORY_H_INCLUDED
#define COLORCATEGORY_H_INCLUDED

namespace ColorCategory
{
    enum Type
    {
        None = 0,
        Blue = 1 << 1,
        Red = 1 << 0,
        Violet = Blue | Red,
    };
}


#endif // COLORCATEGORY_H_INCLUDED
