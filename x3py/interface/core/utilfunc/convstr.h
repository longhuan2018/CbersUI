// x3c - C++ PluginFramework
//! \file convstr.h
//! \brief Define functions to convert between UNICODE string and ANSI string.

#ifndef UTILFUNC_CONVSTR_H_
#define UTILFUNC_CONVSTR_H_

#include <string>
#include <algorithm>

#ifndef CP_UTF8
#define CP_UTF8 65001
#endif

namespace x3 {

//! Convert from UNICODE string to ANSI string, x3::w2a.
/*!
    \ingroup _GROUP_UTILFUNC
    \param s The source UNICODE string to be converted.
    \param codepage Code page of the target ANSI string. For example CP_UTF8 is UTF-8 code.
    \return The target ANSI string.
*/
inline std::string w2a(const wchar_t* s, int codepage = 0)
{
    std::string str;
    int wlen = (NULL == s) ? 0 : (int)wcslen(s);

    if (wlen > 0)
    {
        int len = WideCharToMultiByte(codepage, 0, s, wlen, NULL, 0, NULL, NULL);
        str.resize(len);
        WideCharToMultiByte(codepage, 0, s, wlen,
            const_cast<char*>(str.data()), len, NULL, NULL);
    }

    return str;
}

//! Convert from UNICODE string to ANSI string, x3::w2a.
/*!
    \ingroup _GROUP_UTILFUNC
    \param s The source UNICODE string to be converted.
    \param codepage Code page of the target ANSI string. For example CP_UTF8 is UTF-8 code.
    \return The target ANSI string.
*/
inline std::string w2a(const std::wstring& s, int codepage = 0)
{
    return w2a(s.c_str(), codepage);
}

//! Convert from ANSI string to UNICODE string, x3::a2w.
/*!
    \ingroup _GROUP_UTILFUNC
    \param s The source ANSI string to be converted.
    \param codepage Code page of the source ANSI string. For example CP_UTF8 is UTF-8 code.
    \return UNICODE string
*/
inline std::wstring a2w(const char* s, int codepage = 0)
{
    std::wstring wstr;
    int len = (NULL == s) ? 0 : (int)strlen(s);

    if (len > 0)
    {
        int wlen = MultiByteToWideChar(codepage, 0, s, len, NULL, 0);
        wstr.resize(wlen);
        MultiByteToWideChar(codepage, 0, s, len,
            const_cast<wchar_t*>(wstr.data()), wlen);
    }

    return wstr;
}

//! Convert from ANSI string to UNICODE string, x3::a2w.
/*!
    \ingroup _GROUP_UTILFUNC
    \param s The source ANSI string to be converted.
    \param codepage Code page of the source ANSI string. For example CP_UTF8 is UTF-8 code.
    \return UNICODE string
*/
inline std::wstring a2w(const std::string& s, int codepage = 0)
{
    return a2w(s.c_str(), codepage);
}

inline int compare(const std::string& str1, const std::string& str2, bool bCaseSensitive = true)
{
    if (bCaseSensitive)
        return str1.compare(str2);
    else
    {
        std::string lowStr1 = str1;
        std::transform(lowStr1.begin(), lowStr1.end(), lowStr1.begin(), tolower);
        std::string lowStr2 = str2;
        std::transform(lowStr2.begin(), lowStr2.end(), lowStr2.begin(), tolower);
        return lowStr1.compare(lowStr2);
    }
}

inline int compare(const std::wstring& str1, const std::wstring& str2, bool bCaseSensitive = true)
{
    if (bCaseSensitive)
        return str1.compare(str2);
    else
    {
        std::wstring lowStr1 = str1;
        std::transform(lowStr1.begin(), lowStr1.end(), lowStr1.begin(), tolower);
        std::wstring lowStr2 = str2;
        std::transform(lowStr2.begin(), lowStr2.end(), lowStr2.begin(), tolower);
        return lowStr1.compare(lowStr2);
    }
}

#ifdef _UNICODE
inline std::wstring w2t(const wchar_t* s) { return s; }
inline std::wstring w2t(const std::wstring& s) { return s; }
inline std::wstring t2w(const wchar_t* s) { return s; }
inline std::wstring a2t(const char* s) { return w2t(a2w(s)); }
inline std::wstring a2t(const std::string& s) { return w2t(a2w(s)); }
inline std::string  t2a(const wchar_t* s) { return w2a(t2w(s)); }
#else
inline std::string w2t(const wchar_t* s) { return w2a(s); }
inline std::string w2t(const std::wstring& s) { return w2a(s); }
inline std::wstring t2w(const char* s) { return a2w(s); }
inline std::string a2t(const char* s) { return std::string(s); }
inline std::string a2t(const std::string& s) { return s; }
inline std::string  t2a(const char* s) { return std::string(s); }
#endif

}
#endif // UTILFUNC_CONVSTR_H_
