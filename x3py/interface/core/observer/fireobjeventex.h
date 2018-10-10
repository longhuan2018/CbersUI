// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_FIRE_OBJECT_EVENTEX_H
#define X3_CORE_FIRE_OBJECT_EVENTEX_H

#include <observer/fireobjevent.h>

#define X3DEFINE_OBJEVENT_4(TypeName, Param1, Param2, Param3, Param4, Namespace)   \
	X3DEFINE_OBJEVENT(TypeName, void, (Param1, Param2, Param3, Param4), Namespace);  \
	typedef x3::FireObjectEvent4<TypeName, Param1, Param2, Param3, Param4> Fire ## TypeName

#define X3DEFINE_OBJEVENT_4Break(TypeName, Param1, Param2, Param3, Param4, Namespace)   \
	X3DEFINE_OBJEVENT(TypeName, bool, (Param1, Param2, Param3, Param4), Namespace);  \
	typedef x3::FireObjectEvent4<TypeName, Param1, Param2, Param3, Param4, \
	x3::FireObjectEvent4Break> Fire ## TypeName

#define X3DEFINE_OBJEVENT_5(TypeName, Param1, Param2, Param3, Param4, Param5, Namespace)   \
	X3DEFINE_OBJEVENT(TypeName, void, (Param1, Param2, Param3, Param4, Param5), Namespace);  \
	typedef x3::FireObjectEvent5<TypeName, Param1, Param2, Param3, Param4, Param5> Fire ## TypeName

#define X3DEFINE_OBJEVENT_5Break(TypeName, Param1, Param2, Param3, Param4, Param5, Namespace)   \
	X3DEFINE_OBJEVENT(TypeName, bool, (Param1, Param2, Param3, Param4, Param5), Namespace);  \
	typedef x3::FireObjectEvent5<TypeName, Param1, Param2, Param3, Param4, Param5, \
	x3::FireObjectEvent5Break> Fire ## TypeName

// ----------------------------------------

namespace x3 {

// -------------- FireObjectEvent4 --------------

struct FireObjectEvent4NotBreak {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4>
	static bool call(ObserverObject* obj, Handler hd, Param1* p1, Param2* p2, Param3* p3, Param4* p4) {
		(obj->*hd)(*p1, *p2, *p3, *p4); return true;
	}
};

struct FireObjectEvent4Break {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4>
	static bool call(ObserverObject* obj, Handler hd, Param1* p1, Param2* p2, Param3* p3, Param4* p4) {
		return !!(obj->*hd)(*p1, *p2, *p3, *p4);
	}
};

template <class EventType, typename Param1, typename Param2 = Param1, typename Param3 = Param1, typename Param4 = Param1, 
class Break = FireObjectEvent4NotBreak >
class FireObjectEvent4 : public FireObjEventBase<EventType>
{
public:
	typedef FireObjEventBase<EventType> Base;
	typedef FireObjectEvent4<EventType, Param1, Param2, Param3, Param4, Break> This;
	Param1  param1;
	Param2  param2;
	Param3  param3;
	Param4  param4;

	FireObjectEvent4(Param1 p1, Param2 p2, Param3 p3, Param4 p4) : param1(p1), param2(p2), param3(p3), param4(p4) {}
	This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
	FireObjectEvent4(const This&);
	This& operator=(const This&);
	FireObjectEvent4();

	static bool dispatcher(ObserverObject* obj, ON_EVENT hd, void* data)
	{
		This* p = (This*)data;
		typename EventType::Handler handler;

		Base::cast(handler, hd);
		return Break::call(obj, handler, &p->param1, &p->param2, &p->param3, &p->param4);
	}
};

// -------------- FireObjectEvent5 --------------

struct FireObjectEvent5NotBreak {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	static bool call(ObserverObject* obj, Handler hd, Param1* p1, Param2* p2, Param3* p3, Param4* p4, Param5* p5) {
		(obj->*hd)(*p1, *p2, *p3, *p4, *p5); return true;
	}
};

struct FireObjectEvent5Break {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	static bool call(ObserverObject* obj, Handler hd, Param1* p1, Param2* p2, Param3* p3, Param4* p4, Param5* p5) {
		return !!(obj->*hd)(*p1, *p2, *p3, *p4, *p5);
	}
};

template <class EventType, typename Param1, typename Param2 = Param1, typename Param3 = Param1, typename Param4 = Param1, typename Param5 = Param1, 
class Break = FireObjectEvent5NotBreak >
class FireObjectEvent5 : public FireObjEventBase<EventType>
{
public:
	typedef FireObjEventBase<EventType> Base;
	typedef FireObjectEvent5<EventType, Param1, Param2, Param3, Param4, Param5, Break> This;
	Param1  param1;
	Param2  param2;
	Param3  param3;
	Param4  param4;
	Param5  param5;

	FireObjectEvent5(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) : param1(p1), param2(p2), param3(p3), param4(p4), param5(p5) {}
	This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
	FireObjectEvent5(const This&);
	This& operator=(const This&);
	FireObjectEvent5();

	static bool dispatcher(ObserverObject* obj, ON_EVENT hd, void* data)
	{
		This* p = (This*)data;
		typename EventType::Handler handler;

		Base::cast(handler, hd);
		return Break::call(obj, handler, &p->param1, &p->param2, &p->param3, &p->param4, &p->param5);
	}
};

} // x3
#endif
