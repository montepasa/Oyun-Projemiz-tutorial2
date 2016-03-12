#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

class CException : public std::exception
{
	//Hata mekanizmalar� i�in fonksiyon
public:
	const char* what() const  { return m_strMessage.c_str(); }

	CException(const std::string& strMessage="") : m_strMessage(strMessage)  { }
	virtual ~CException()  { }

	std::string m_strMessage;
};

#endif  // _EXCEPTION_H_