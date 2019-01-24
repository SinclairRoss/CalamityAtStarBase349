// name: RenderPackageDistributor
// date: 05/01/2017
// Note: Owns Render packages, other objects can "Check-In/Out" Render Packages somewhat like a librarian. (RenderPackages contain all the information needed to render one complete frame).
//       The logic thread checks out a render package and fills it with data.
//       The rendering thread can check out a filled package and use its data to draw a frame. 
//       This helps minimise the size of critical sections in multi-threading.
//       After use it is important to check-in the renderpacakge. Failure to do this will completely lock up the game.

// WARNING! This class is currently not thread safe. to make it so, lock the check-in/out functions with a mutex.

#pragma once

#include <memory>
#include <vector>

#include "RenderPackage.h"

using PackageContainer = std::vector<std::unique_ptr<RenderPackage>>;

class RenderPackageDistributor
{
	public:
        RenderPackageDistributor(int maxInstances);
        ~RenderPackageDistributor();

        RenderPackageDistributor(const RenderPackageDistributor&) = delete;
        RenderPackageDistributor& operator=(const RenderPackageDistributor&) = delete;

        RenderPackageDistributor(RenderPackageDistributor&& other) = delete;
        RenderPackageDistributor& operator=(RenderPackageDistributor&& other) = delete;

        RenderPackage* Checkout_ForWrite();
        RenderPackage* Checkout_ForRead();
        
        void Checkin_FromWrite(RenderPackage& renderPackage);
        void Checkin_FromRead(RenderPackage& renderPackage);

	private:
        std::unique_ptr<RenderPackage> CheckInPackage(RenderPackage& renderPackage);

        PackageContainer m_ReadReady;
        PackageContainer m_WriteReady;
        PackageContainer m_CheckedOut;

		const size_t m_MaxInstanceCount;
};