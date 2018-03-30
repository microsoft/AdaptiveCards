#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include <windows.foundation.collections.h>
#include <wrl.h>

using namespace ABI::Windows::Foundation::Collections;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

AdaptiveNamespaceStart
    template <typename T>
    struct Wrap
    {
        typename typedef T type;
        static const T& MakeWrap(const T& t)
        {
            return t;
        }
        static const T& Unwrap(const T& t)
        {
            return t;
        }
    };

    template <>
    struct Wrap<HSTRING>
    {
        typedef std::string type;
        static std::string MakeWrap(const HSTRING& t)
        {
            std::string wrappedValue;
            HStringToUTF8(t, wrappedValue);
            return wrappedValue;
        }
        static HSTRING Unwrap(const std::string& t)
        {
            HSTRING retvalue;
            UTF8ToHString(t, &retvalue);
            return retvalue;
        }
    };


    template <typename T>
    struct Wrap<T*>
    {
        typename typedef ComPtr<T> type;
        static ComPtr<T> MakeWrap(T* t)
        {
            ComPtr<T> ptr(t);
            return ptr;
        }
        static T* Unwrap(ComPtr<T> t)
        {
            ComPtr<T> ptr(t);
            return t.Detach();
        }
    };

    template <class T>
    class Iterator : public RuntimeClass<IIterator<T>>
    {
        AdaptiveRuntimeStringClass(Iterator)

    private:
        typedef typename std::vector<typename Wrap<T>::type> WrappedVector;
        typedef typename std::vector<typename Wrap<T>::type>::iterator WrappedVectorIterator;

    public:
        Iterator() {} 

        HRESULT Init(const std::shared_ptr<WrappedVector>& vec) try
        {
            m_wrappedVector = vec;

            m_iterator = m_wrappedVector->begin();
            if (m_iterator != m_wrappedVector->end())
            {
                m_currentElement = Wrap<T>::Unwrap(*m_iterator);
                m_hasCurrentElement = true;
            }
            else
            {
                m_hasCurrentElement = false;
            }
            return S_OK;
        }CATCH_RETURN;

    public:
        STDMETHODIMP get_Current(T *current) try
        {
            if (m_iterator != m_wrappedVector->end())
            {
                m_hasCurrentElement = true;
                m_currentElement = Wrap<T>::Unwrap(*m_iterator);
                *current = m_currentElement;
            }
            else
            {
                m_hasCurrentElement = false;
            }
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP get_HasCurrent(boolean *hasCurrent)
        {
            *hasCurrent = m_hasCurrentElement;
            return S_OK;
        }

        STDMETHODIMP MoveNext(boolean *hasCurrent) try
        {
            if (m_iterator != m_wrappedVector->end())
            {
                ++m_iterator;
                if (m_iterator == m_wrappedVector->end())
                {
                    *hasCurrent = false;
                    m_hasCurrentElement = false;
                }
                else
                {
                    *hasCurrent = true;
                    m_hasCurrentElement = true;
                }
            }
            else
            {
                *hasCurrent = false;
                m_hasCurrentElement = false;
            }
            return S_OK;
        } CATCH_RETURN;


    private:
        std::shared_ptr<WrappedVector> m_wrappedVector;
        WrappedVectorIterator m_iterator;
        T m_currentElement;
        boolean m_hasCurrentElement = false;
    };

    template <typename T>
    class Vector : public RuntimeClass<IVector<T>,
        IIterable<T>,
        Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntimeStringClass(Vector)

    private:
        typedef typename std::vector<typename Wrap<T>::type> WrappedVector;
        typedef typename VectorChangedEventHandler<T> WFC_Handler;

    public:
        Vector() 
        {
            m_wrappedVector = std::make_shared<WrappedVector>();
        }

    public:
        STDMETHODIMP GetAt(unsigned int index, T* item) try
        {
            if (index >= m_wrappedVector->size())
            {
                return E_INVALIDARG;
            }
            *item = Wrap<T>::Unwrap((*m_wrappedVector)[index]);
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP get_Size(unsigned int* size) try
        {
            *size = static_cast<unsigned int>(m_wrappedVector->size());
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP GetView(IVectorView<T>** view)
        {
            *view = nullptr;
            return E_NOTIMPL;
        }

        STDMETHODIMP IndexOf(T value, unsigned int* index, boolean* found) try
        {
            *index = 0;
            *found = false;

            unsigned foundIndex = 0;
            for (auto& entry : *m_wrappedVector)
            {
                const T& unwrappedEntry = Wrap<T>::Unwrap(entry);
                if (unwrappedEntry == value)
                {
                    *found = true;
                    *index = foundIndex;
                    break;
                }
                foundIndex++;
            }

            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP SetAt(unsigned int index, T item) try
        {
            if (index >= m_wrappedVector->size())
            {
                return E_INVALIDARG;
            }
            (*m_wrappedVector)[index] = Wrap<T>::MakeWrap(item);
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP InsertAt(unsigned int index, T item) try
        {
            m_wrappedVector->insert(m_wrappedVector->begin() + index, Wrap<T>::MakeWrap(item));
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP RemoveAt(unsigned int index) try
        {
            if (index >= m_wrappedVector->size())
            {
                return E_INVALIDARG;
            }
            m_wrappedVector->erase(m_wrappedVector->begin() + index);
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP Append(T item) try
        {
            m_wrappedVector->push_back(Wrap<T>::MakeWrap(item));
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP RemoveAtEnd() try
        {
            if (!m_wrappedVector->empty())
            {
                m_wrappedVector->pop_back();
            }
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP Clear() try
        {
            m_wrappedVector->clear();
            return S_OK;
        } CATCH_RETURN;

        STDMETHODIMP First(IIterator<T> **first) try
        {
            ComPtr<Iterator<T>> p = Make<Iterator<T>>();
            p->Init(m_wrappedVector);
            *first = p.Detach();
            return S_OK;
        } CATCH_RETURN;

    private:
        std::shared_ptr<WrappedVector> m_wrappedVector;
    };
AdaptiveNamespaceEnd
