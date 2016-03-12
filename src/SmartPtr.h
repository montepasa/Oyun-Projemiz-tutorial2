#ifndef _SMARTPTR_H_
#define _SMARTPTR_H_

#include <cassert>

#ifndef NULL
#define NULL	0
#endif


template <class T>
class CSmartPtr
{
public:
	
	CSmartPtr()
	{
		m_pPtrInfo = NULL;
	}

	CSmartPtr(T* pPointee)
	{
		m_pPtrInfo = new TSharedData;
		m_pPtrInfo->m_pPointee = pPointee;
		m_pPtrInfo->m_iRefCount = 1;
	}

	CSmartPtr(const CSmartPtr& other)
	{
		m_pPtrInfo = other.m_pPtrInfo;
		if (m_pPtrInfo)
			m_pPtrInfo->m_iRefCount++;
	}

	CSmartPtr& operator=(const CSmartPtr& other)
	{
		if (this != &other)
		{
			if (m_pPtrInfo)
			{
				m_pPtrInfo->m_iRefCount--;
				if (m_pPtrInfo->m_iRefCount == NULL)
				{
					delete m_pPtrInfo->m_pPointee;
					delete m_pPtrInfo;
				}
			}
			m_pPtrInfo = other.m_pPtrInfo;
			if (m_pPtrInfo)
				m_pPtrInfo->m_iRefCount++;
		}
		return *this;
	}

	~CSmartPtr()  
	{ 
		if (m_pPtrInfo)
		{
			m_pPtrInfo->m_iRefCount--;
			if (m_pPtrInfo->m_iRefCount == 0)
			{
				delete m_pPtrInfo->m_pPointee;
				delete m_pPtrInfo;
			}
		}
	}



	T& operator* () const  
	{ 
		assert(m_pPtrInfo != NULL);
		return *(m_pPtrInfo->m_pPointee); 
	}
	
	T* operator->() const  
	{ 
		assert(m_pPtrInfo != NULL);
		return m_pPtrInfo->m_pPointee; 
	}

	
	bool isNull() const  
	{ 
		if (m_pPtrInfo && m_pPtrInfo->m_pPointee)
			return false;
		return true;
	}

private:

	struct TSharedData
	{
		T*	m_pPointee;
		int m_iRefCount;
	};
	TSharedData* m_pPtrInfo;
};

#endif  // _SMARTPTR_H_