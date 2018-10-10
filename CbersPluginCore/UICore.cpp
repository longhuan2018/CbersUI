#include "UICore.h"

BEGIN_NAMESPACE_CBERSPLUGINS

CUICore::CUICore()
{

}

CUICore::~CUICore()
{
	clear();
}

long CUICore::size()
{
	x3::LockRW locker(m_mapData.locker);
	return locker.canRead() ? m_mapData.size() : 0;
}

x3::IObject* CUICore::Find(const char* key)
{
	x3::LockRW locker(m_mapData.locker);
	IObject* ret = NULL;
	if (locker.canRead())
	{
		hash_map<std::string, x3::AnyObject>::const_iterator it = m_mapData.find(key);
		ret = (it != m_mapData.end()) ? it->second.p() : NULL;
	}

	return ret;
}

bool CUICore::Add(const char* key, x3::IObject* obj)
{
	if( key==NULL || strlen(key)<=0 || obj==NULL )
		return false;

	x3::LockRW locker(m_mapData.locker, true);
	bool ret = false;
	if (locker.canWrite())
	{		
		m_mapData[key] = obj;
		ret = true;
	}

	return ret;
}

bool CUICore::Remove(const char* key)
{
	x3::LockRW locker(m_mapData.locker, true);
	bool ret = false;
	if (locker.canWrite())
	{
		hash_map<std::string, x3::AnyObject>::iterator it = m_mapData.find(key);
		if( it!=m_mapData.end() )
		{
            if( it->second.valid() )
				it->second.release();
			m_mapData.erase(it);
			ret = true;
		}
	}

	return ret;
}

bool CUICore::Remove(x3::IObject* obj)
{
    if( obj==nullptr )
		return false;

	x3::LockRW lockcls(m_mapData.locker, true);
	bool ret = false;
	if (lockcls.canWrite())
	{
		hash_map<std::string, x3::AnyObject>::iterator it = m_mapData.begin();
		while (it != m_mapData.end())
		{
			if (it->second == obj)
			{				
                if( it->second.valid() )
					it->second.release();
				m_mapData.erase(it);
				it = m_mapData.begin();
				ret = true;
			}
			else
			{
				++it;
			}
		}
	}

	return ret;
}

void CUICore::clear()
{
	x3::LockRW lockcls(m_mapData.locker, true);	
	if (lockcls.canWrite())	
	{
		hash_map<std::string, x3::AnyObject>::iterator it = m_mapData.begin();
		for( ; it!=m_mapData.end(); it++ )
		{
            if( it->second.valid() )
				it->second.release();
		}
		m_mapData.clear();
	}
}

END_NAMESPACE_CBERSPLUGINS
