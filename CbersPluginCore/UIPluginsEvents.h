#pragma once
#include <QVariant>
#include "iobject.h"
#include "module/plugininc.h"
#include "observer/fireeventex.h"
#include "observer/fireobjeventex.h"
#include <string>
#include <map>
#include "cbersplugincore_global.h"

BEGIN_NAMESPACE_CBERSPLUGINS

#ifndef EVENT_NAMESPACE
#define EVENT_NAMESPACE "CbersEvent"
#endif

X3DEFINE_OBJEVENT_4Break(EventMouseDown, long, long, long, long, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_4Break(EventMouseMove, long, long, long, long, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_4Break(EventMouseUp, long, long, long, long, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_4Break(EventButtonDblClk, long, long, long, long, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_5Break(EventMouseWheel, long, long, short, long, long, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_4Break(EventMouseHover, long, long, long, long, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_0Break(EventMouseLeave, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_3Break(EventContextMenu, long, long, long, EVENT_NAMESPACE);

class IUIMouseResponse : x3::ObserverObject
{	
public:
    IUIMouseResponse()
    {
        X3_REGISTER_OBSERVER_OBJECT(EventMouseDown, &IUIMouseResponse::OnMouseDown);
        X3_REGISTER_OBSERVER_OBJECT(EventMouseMove, &IUIMouseResponse::OnMouseMove);
        X3_REGISTER_OBSERVER_OBJECT(EventMouseUp, &IUIMouseResponse::OnMouseUp);
        X3_REGISTER_OBSERVER_OBJECT(EventButtonDblClk, &IUIMouseResponse::OnButtonDblClk);
        X3_REGISTER_OBSERVER_OBJECT(EventMouseWheel, &IUIMouseResponse::OnMouseWheel);
        X3_REGISTER_OBSERVER_OBJECT(EventMouseHover, &IUIMouseResponse::OnMouseHover);
        X3_REGISTER_OBSERVER_OBJECT(EventMouseLeave, &IUIMouseResponse::OnMouseLeave);
        X3_REGISTER_OBSERVER_OBJECT(EventContextMenu, &IUIMouseResponse::OnContextMenu);
    }

    virtual ~IUIMouseResponse()
    {
        x3::unregisterObserver(this);
    }

public:
	virtual bool OnMouseDown(long button, long shift, long x, long y) { return true; }
	virtual bool OnMouseMove(long button, long shift, long x, long y) { return true; }
	virtual bool OnMouseUp(long button, long shift, long x, long y)   { return true; }
	virtual bool OnButtonDblClk(long button, long shift, long x, long y) { return true; }
	virtual bool OnMouseWheel(long button, long shift, short zDelta, long x, long y) { return true; }
	virtual bool OnMouseHover(long button, long shift, long x, long y) { return true; }
	virtual bool OnMouseLeave() { return true; }
    virtual bool OnContextMenu(long hWnd,long x, long y) { return true; }
};

X3DEFINE_OBJEVENT_2Break(EventKeyDown, long, long, EVENT_NAMESPACE);
X3DEFINE_OBJEVENT_2Break(EventKeyUp, long, long, EVENT_NAMESPACE);

class IUIKeyResponse : public x3::ObserverObject
{
public:
    IUIKeyResponse()
    {
        X3_REGISTER_OBSERVER_OBJECT(EventKeyDown, &IUIKeyResponse::OnKeyDown);
        X3_REGISTER_OBSERVER_OBJECT(EventKeyUp, &IUIKeyResponse::OnKeyUp);
    }

    virtual ~IUIKeyResponse()
    {
        x3::unregisterObserver(this);
    }

public:
	virtual bool OnKeyDown(long keyCode, long shift) { return false; }
	virtual bool OnKeyUp(long keyCode, long shift) { return false; }
};

X3DEFINE_OBJEVENT_4Break(EventAnything, x3::IObject*, const std::string&, const QVariant&, const QVariant&, EVENT_NAMESPACE);

class IAnythingEventObserver : public x3::ObserverObject
{
public:
	IAnythingEventObserver() 
	{
		m_bRegister = false;
	}

	virtual ~IAnythingEventObserver()
	{
		unregisterHandlers();
	}

public:
	// Event
	virtual void registerHandlers()
	{
		if( m_bRegister )
			return;

        X3_REGISTER_OBSERVER_OBJECT(EventAnything, &IAnythingEventObserver::_OnAnything);
		m_bRegister = true;
	}

	virtual void unregisterHandlers()
	{
		if( !m_bRegister )
			return;

		x3::unregisterObserver(this);
        m_bRegister = false;
	}

	virtual void supportsEvent(const std::string& eventKey)
	{
		if( !eventKey.empty() )
		{
			std::string lowerKey = eventKey;
			std::transform(eventKey.begin(), eventKey.end(), lowerKey.begin(), tolower);
			m_supportedEvents.insert(std::map<std::string, std::string>::value_type(lowerKey, lowerKey));
		}
	}

	virtual bool acceptsEvent(const std::string& eventKey)
	{
		if( eventKey.empty() )
			return false;

		if( m_supportedEvents.size()<=0 )
			return true;

		std::string lowerKey = eventKey;
		std::transform(eventKey.begin(), eventKey.end(), lowerKey.begin(), tolower);
		return m_supportedEvents.find(lowerKey)!=m_supportedEvents.end();		
	}

	// Node Event
    virtual bool OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam) { return true; }

protected:	
    bool _OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam)
    {
        if( acceptsEvent(eventKey) )
            OnAnything(sender, eventKey, wParam, lParam);

        return true;
    }

protected:
	bool m_bRegister;
	std::map<std::string, std::string> m_supportedEvents;
};

END_NAMESPACE_CBERSPLUGINS

