#pragma once

#include <functional>
#include <vector>

template<typename T>
class GenericRegister
{
    public:
        GenericRegister()
        {}

        void RegisterObject(T& obj)
        {
            if (!IsRegistered(obj))
            {
                m_Register.emplace_back(&obj);
            } 
            else
            {
                printf("Attempting to re-register object\n");
            }
        }

        void DeregisterObject(T& obj)
        {
            for (std::vector<T*>::iterator iter = m_Register.begin(); iter != m_Register.end(); ++iter)
            {
                if (*iter == &obj)
                {
                    m_Register.erase(iter);
                    break;
                }
            }
        }

        bool IsRegistered(const T& obj) const
        {
            bool isRegistered = std::find(m_Register.begin(), m_Register.end(), &obj) != m_Register.end();
            return isRegistered;
        }

        void Replace(T& oldObj, T& newObj)
        {
            for (std::vector<T*>::iterator iter = m_Register.begin(); iter != m_Register.end(); ++iter)
            {
                if (*iter == &oldObj)
                {
                    *iter = &newObj;
                }
            }
        }
        
        void Foreach(const std::function<void(T* obj)>& func)
        {
            for (T* ptr : m_Register)
            {
                func(ptr);
            }
        }

    private:
        std::vector<T*> m_Register;
};