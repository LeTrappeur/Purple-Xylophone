#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

namespace Category
{
    enum Type
    {
        None = 0,
        LowerScene = 1 << 1,
        UpperScene = 1 << 0,
        PlayerActor = 1 << 2,

        Turret = 1 << 3,
        SoundEffect = 1 << 6,
    };
}

#endif // CATEGORY_H_INCLUDED
