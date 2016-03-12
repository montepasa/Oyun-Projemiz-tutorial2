#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

template <class T>
class CRectangle
{
public:
	// Default constructor
	CRectangle () : m_Top(0), m_Bottom(0), m_Left(0), m_Right(0)   { }
	// Constructor which takes the rectangle coordinates as argument
	CRectangle (T top, T bottom, T left, T right) 
		: m_Top(top), m_Bottom(bottom), m_Left(left), m_Right(right)   { }
	~CRectangle()  { }

	// Rectangle 'ýn yüksekliðini döndür
	T GetWidth()  const  { return m_Right - m_Left;  }
	// Rectangle 'ýn yüksekliðini döndür
	T GetHeight() const  { return m_Bottom - m_Top;  }

	//
	bool Intersect(const CRectangle& rect) const
	{
		return ((m_Left < rect.m_Right) && (m_Right > rect.m_Left ) &&
			    (m_Bottom > rect.m_Top) && (m_Top < rect.m_Bottom) );
	}

	//
	bool IsValid() const
	{
		if ( (m_Top > m_Bottom) || (m_Left > m_Right) )
			return false;
		return true;
	}


	T  m_Top;
	
	T  m_Bottom;
	
	T  m_Left;
	
	T  m_Right;	
};


typedef CRectangle<int>    TRectanglei;
typedef CRectangle<float>  TRectanglef;
typedef CRectangle<double> TRectangled;

#endif  // _RECTANGLE_H_