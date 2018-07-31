#pragma once

/*
Grow an array - has to be a basic C-type array of pointers, where the values can just be copied.
Example usage:
	if ( (m_iFontCount+1) > m_iArraySize )
		m_pArrayFonts = GrowArray( m_pArrayFonts, m_iArraySize, 10 );
This is used by the framework code where basic arrays are being used rather than classes.
*/
template <class T> 
T* GrowArray( T* pOldArray, int& iSize, int iGrowBy )
{
	T* pNewArray = new T[iSize+iGrowBy];
	if ( pOldArray != nullptr )
	{
		for ( int i = 0 ; i < iSize ; i++ )
		{
			pNewArray[i] = pOldArray[i];
		}
		delete[] pOldArray;
	}
	iSize += iGrowBy;
	return pNewArray;
}





