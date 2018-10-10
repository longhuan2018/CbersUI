// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_FIRE_EVENTEX_H
#define X3_CORE_FIRE_EVENTEX_H

#include <observer/fireevent.h>

#define X3DEFINE_EVENT_3(TypeName, Param1, Param2, Param3, Namespace)   \
	X3DEFINE_EVENT(TypeName, void, (Param1, Param2, Param3), Namespace);  \
	typedef x3::FireEvent3<TypeName, Param1, Param2, Param3> Fire ## TypeName

#define X3DEFINE_EVENT_3Break(TypeName, Param1, Param2, Param3, Namespace)   \
	X3DEFINE_EVENT(TypeName, bool, (Param1, Param2, Param3), Namespace);  \
	typedef x3::FireEvent3<TypeName, Param1, Param2, Param3, \
	x3::FireEvent3Break> Fire ## TypeName

#define X3DEFINE_EVENT_4(TypeName, Param1, Param2, Param3, Param4, Namespace)   \
	X3DEFINE_EVENT(TypeName, void, (Param1, Param2, Param3, Param4), Namespace);  \
	typedef x3::FireEvent4<TypeName, Param1, Param2, Param3, Param4> Fire ## TypeName

#define X3DEFINE_EVENT_4Break(TypeName, Param1, Param2, Param3, Param4, Namespace)   \
	X3DEFINE_EVENT(TypeName, bool, (Param1, Param2, Param3, Param4), Namespace);  \
	typedef x3::FireEvent4<TypeName, Param1, Param2, Param3, Param4, \
	x3::FireEvent4Break> Fire ## TypeName

#define X3DEFINE_EVENT_5(TypeName, Param1, Param2, Param3, Param4, Param5, Namespace)   \
	X3DEFINE_EVENT(TypeName, void, (Param1, Param2, Param3, Param4, Param5), Namespace);  \
	typedef x3::FireEvent5<TypeName, Param1, Param2, Param3, Param4, Param5> Fire ## TypeName

#define X3DEFINE_EVENT_5Break(TypeName, Param1, Param2, Param3, Param4, Param5, Namespace)   \
	X3DEFINE_EVENT(TypeName, bool, (Param1, Param2, Param3, Param4, Param5), Namespace);  \
	typedef x3::FireEvent5<TypeName, Param1, Param2, Param3, Param4, Param5, \
	x3::FireEvent5Break> Fire ## TypeName

// ----------------------------------------

namespace x3 {

// -------------- FireEvent3 --------------

struct FireEvent3NotBreak {
	template <typename Handler, typename Param1, typename Param2, typename Param3>
	static bool call(Handler handler, Param1* param1, Param2* param2, Param3* param3) {
		handler(*param1, *param2, *param3); return true;
	}
};

struct FireEvent3Break {
	template <typename Handler, typename Param1, typename Param2, typename Param3>
	static bool call(Handler handler, Param1* param1, Param2* param2, Param3* param3) {
		return !!handler(*param1, *param2, *param3);
	}
};

template <class EventType, typename Param1, 
	typename Param2 = Param1, typename Param3 = Param1, class Break = FireEvent3NotBreak >
class FireEvent3 : public FireEventBase<EventType>
{
public:
	typedef FireEventBase<EventType> Base;
	typedef FireEvent3<EventType, Param1, Param2, Param3, Break> This;
	Param1  param1;
	Param2  param2;
	Param3  param3;

	FireEvent3(Param1 p1, Param2 p2, Param3 p3) : param1(p1), param2(p2), param3(p3) {}
	This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
	FireEvent3(const This&);
	This& operator=(const This&);
	FireEvent3();

	static bool dispatcher(PROC handler, void* data) {
		This* p = (This*)data;
		return Break::call((typename EventType::Handler)handler, &p->param1, &p->param2, &p->param3);
	}
};

// -------------- FireEvent4 --------------

struct FireEvent4NotBreak {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4>
	static bool call(Handler handler, Param1* param1, Param2* param2, Param3* param3, Param4* param4) {
		handler(*param1, *param2, *param3, *param4); return true;
	}
};

struct FireEvent4Break {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4>
	static bool call(Handler handler, Param1* param1, Param2* param2, Param3* param3, Param4* param4) {
		return !!handler(*param1, *param2, *param3, *param4);
	}
};

template <class EventType, typename Param1, 
	typename Param2 = Param1, typename Param3 = Param1, typename Param4 = Param1, class Break = FireEvent4NotBreak >
class FireEvent4 : public FireEventBase<EventType>
{
public:
	typedef FireEventBase<EventType> Base;
	typedef FireEvent4<EventType, Param1, Param2, Param3, Param4, Break> This;
	Param1  param1;
	Param2  param2;
	Param3  param3;
	Param4  param4;

	FireEvent4(Param1 p1, Param2 p2, Param3 p3, Param4 p4) : param1(p1), param2(p2), param3(p3), param4(p4) {}
	This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
	FireEvent4(const This&);
	This& operator=(const This&);
	FireEvent4();

	static bool dispatcher(PROC handler, void* data) {
		This* p = (This*)data;
		return Break::call((typename EventType::Handler)handler, &p->param1, &p->param2, &p->param3, &p->param4);
	}
};

// -------------- FireEvent5 --------------

struct FireEvent5NotBreak {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	static bool call(Handler handler, Param1* param1, Param2* param2, Param3* param3, Param4* param4, Param5* param5) {
		handler(*param1, *param2, *param3, *param4, *param5); return true;
	}
};

struct FireEvent5Break {
	template <typename Handler, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	static bool call(Handler handler, Param1* param1, Param2* param2, Param3* param3, Param4* param4, Param5* param5) {
		return !!handler(*param1, *param2, *param3, *param4, *param5);
	}
};

template <class EventType, typename Param1, 
	typename Param2 = Param1, typename Param3 = Param1, typename Param4 = Param1, typename Param5 = Param1, class Break = FireEvent4NotBreak >
class FireEvent5 : public FireEventBase<EventType>
{
public:
	typedef FireEventBase<EventType> Base;
	typedef FireEvent5<EventType, Param1, Param2, Param3, Param4, Param5, Break> This;
	Param1  param1;
	Param2  param2;
	Param3  param3;
	Param4  param4;
	Param5  param5;

	FireEvent5(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) : param1(p1), param2(p2), param3(p3), param4(p4), param5(p5) {}
	This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
	FireEvent5(const This&);
	This& operator=(const This&);
	FireEvent5();

	static bool dispatcher(PROC handler, void* data) {
		This* p = (This*)data;
		return Break::call((typename EventType::Handler)handler, &p->param1, &p->param2, &p->param3, &p->param4, &p->param5);
	}
};

} // x3
#endif