#include "InteractionBoundsRegister.h"

#include "Core\Physics\CollisionSolver.h"

namespace InteractionBoundsRegister
{
    namespace Internal
    {
        ColliderRegisterSet<Interactable> Register_Interactable;

        template<>
        ColliderRegisterSet<Interactable>& GetRegister<Interactable>() { return Register_Interactable; }
    }
}