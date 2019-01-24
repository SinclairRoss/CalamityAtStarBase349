#include "ColourLibrary.h"

namespace ColourLibrary
{
    const Colour White(1.0f, 1.0f, 1.0f, 1.0f);
    const Colour Black(0.0f, 0.0f, 0.0f, 1.0f);

    const Colour Red(1.0f, 0.0f, 0.0f, 1.0f);
    const Colour Green(0.0f, 1.0f, 0.0f, 1.0f);
    const Colour Blue(0.0f, 0.0f, 1.0f, 1.0f);

    const Colour Cyan(0.0f, 1.0f, 1.0f, 1.0f);
    const Colour Magenta(1.0f, 0.0f, 1.0f, 1.0f);
    const Colour Yellow(1.0f, 1.0f, 0.0f, 0.0f);

    const Colour SexyOrange(0.839215f, 0.43529f, 0.0f, 1.0f);
    const Colour SexyOrange_Low(0.839215f, 0.43529f, 0.0f, 0.1f);
    const Colour SuperBlue(0.024f, 0.388f, 0.525f, 1.0f);

    const Colour Highlight_RigidBody_Static(Blue);
    const Colour Highlight_RigidBody_Dynamic(Blue);
    const Colour Highlight_InteractionBounds(SexyOrange);
}