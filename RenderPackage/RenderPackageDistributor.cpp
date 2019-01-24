#include "RenderPackageDistributor.h"

RenderPackageDistributor::RenderPackageDistributor(int maxInstances) :
    m_ReadReady(),
    m_WriteReady(),
    m_CheckedOut(),
	m_MaxInstanceCount(maxInstances)
{
    const int numPackages = 2;
    m_ReadReady.reserve(numPackages);
    m_WriteReady.reserve(numPackages);
    m_CheckedOut.reserve(numPackages);

    for (int i = 0; i < numPackages; ++i)
    {
        m_WriteReady.emplace_back(std::make_unique<RenderPackage>(m_MaxInstanceCount));
    }
}

RenderPackageDistributor::~RenderPackageDistributor()
{}

RenderPackage* RenderPackageDistributor::Checkout_ForWrite()
{
    RenderPackage* rPackage = nullptr;

    if (!m_WriteReady.empty())
    {
        std::unique_ptr<RenderPackage> pack = std::move(m_WriteReady.back());
        m_WriteReady.pop_back();

        m_CheckedOut.emplace_back(std::move(pack));
        rPackage = m_CheckedOut[m_CheckedOut.size() - 1].get();
        rPackage->Clean();
    }

    return rPackage;
}

RenderPackage* RenderPackageDistributor::Checkout_ForRead()
{
    RenderPackage* rPackage = nullptr;

    if (!m_ReadReady.empty())
    {
        std::unique_ptr<RenderPackage> pack = std::move(m_ReadReady.back());
        m_ReadReady.pop_back();

        m_CheckedOut.emplace_back(std::move(pack));
        rPackage = m_CheckedOut[m_CheckedOut.size() - 1].get();
    }

    return rPackage;
}

void RenderPackageDistributor::Checkin_FromWrite(RenderPackage& renderPackage)
{
    std::unique_ptr<RenderPackage> package = CheckInPackage(renderPackage);
    if (package != nullptr)
    {
        m_ReadReady.emplace_back(std::move(package));
    }
}

void RenderPackageDistributor::Checkin_FromRead(RenderPackage& renderPackage)
{
    std::unique_ptr<RenderPackage> package = CheckInPackage(renderPackage);
    if (package != nullptr)
    {
        m_WriteReady.emplace_back(std::move(package));
    }
}

std::unique_ptr<RenderPackage> RenderPackageDistributor::CheckInPackage(RenderPackage& renderPackage)
{
    std::unique_ptr<RenderPackage> package = nullptr;
    for (PackageContainer::iterator iter = m_CheckedOut.begin(); iter != m_CheckedOut.end(); ++iter)
    {
        if ((iter->get()) == &renderPackage)
        {
            package = std::move(*iter);
            m_CheckedOut.erase(iter);
            break;
        }
    }

    if (package == nullptr)
    {
        printf("Warning: Check-in failed - Package not checked-out!");
    }

    return package;
}