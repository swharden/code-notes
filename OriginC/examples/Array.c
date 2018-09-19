/*------------------------------------------------------------------------------*
 * File Name:				 													*
 * Creation: 																	*
 * Purpose: OriginC Source C file												*
 * Copyright (c) ABCD Corp.	2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010		*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/
 
////////////////////////////////////////////////////////////////////////////////////
// Including the system header file Origin.h should be sufficient for most Origin
// applications and is recommended. Origin.h includes many of the most common system
// header files and is automatically pre-compiled when Origin runs the first time.
// Programs including Origin.h subsequently compile much more quickly as long as
// the size and number of other included header files is minimized. All NAG header
// files are now included in Origin.h and no longer need be separately included.
//
// Right-click on the line below and select 'Open "Origin.h"' to open the Origin.h
// system header file.
#include <Origin.h>
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Include your own header files here.
#include <Array.h>  // need to include this header


////////////////////////////////////////////////////////////////////////////////////
// Start your functions here.
class POINTEX
{
public:
	POINTEX(int n)
	{
		m_n = n;
		printf("Constructor\n");
	}
	
	~POINTEX()
	{
		printf("Destructor, n = %d\n", m_n);
	}
	
	int m_n;
};

static void _perpare_array(Array<POINTEX&> &myArray)
{	
	// Add elements to the array.
	int		ii;
	int		nSize = 3;
	for(ii = 0; ii < nSize; ii++)
	{		
		POINTEX		*pp = new POINTEX(ii+1);
		myArray.Add(*pp);
	}	
}

//////////////// Modify anyone(value only) object of this list ////////////////
//Method 1:
// get object reference by Array::GetAt(int nIndex) and then modify this reference
void	Array_modify_one_item_1(int nToModify = 0)
{
	Array<POINTEX&> myArray;
	myArray.SetAsOwner(true);
	_perpare_array(myArray);
	
	POINTEX&	obj = myArray.GetAt(nToModify);
	if( obj )
		obj.m_n = 100;
}

//Method 2:
// create a new object and set it to Array to replace old item, Array::SetAt will destruct old object firstly whatever Set Owner TRUE or FALSE
void	Array_modify_one_item_2(int nToModify = 0)
{
	Array<POINTEX&> myArray;
	myArray.SetAsOwner(true);
	_perpare_array(myArray);
	
	POINTEX		*pNew = new POINTEX(100);	
	myArray.SetAt(nToModify, *pNew);
}

//////////////// Remove(clear) anyone object of this list ////////////////
// remove an object by calling RemoveAt
void	Array_remove_one_item(int nToRemove = 0 )
{
	Array<POINTEX&> myArray;
	myArray.SetAsOwner(true);
	_perpare_array(myArray);
	
	ASSERT( myArray.RemoveAt( nToRemove ) );
	return;
}

//////////////// Add a new object or Replace the anyone object of this list ////////////////
void	Array_set_or_add_one_item( int nToSet = 0 )
{
	Array<POINTEX&> myArray;
	myArray.SetAsOwner(true);
	_perpare_array(myArray);
	
	POINTEX		*pObj = new POINTEX( 200 );
	myArray.SetAtGrow( nToSet, *pObj );
}

//////////////// Get the size of this list ////////////////
void	Array_get_size_of_the_array()
{
	Array<POINTEX&> myArray;
	myArray.SetAsOwner(true);
	_perpare_array(myArray);

	int nSize = myArray.GetSize();
	ASSERT( 3 == nSize );
	
	POINTEX		*pObj = new POINTEX(20);
	myArray.Add( *pObj );
	nSize = myArray.GetSize();
	ASSERT( 4 == nSize );
	
	POINTEX		*pObjTwo = new POINTEX(22);
	myArray.SetAtGrow( 8, *pObjTwo );
	nSize = myArray.GetSize();
	ASSERT( 9 == nSize );
}

//////////////// Set the size of this list ////////////////
void	Array_set_size_of_the_array()
{
	Array<POINTEX&> myArray;
	myArray.SetAsOwner(true);
	_perpare_array(myArray);

	myArray.SetSize(8);
	ASSERT( 8 == myArray.GetSize() );
	
	myArray.SetSize(2);
	ASSERT( 2 == myArray.GetSize() );
	
}

//////////////// Set the list as the owner of objects' memory ////////////////
void	Array_set_as_owner()
{
	Array<POINTEX&> myArray;
	myArray.SetAsOwner(true);
	_perpare_array(myArray);

	BOOL bOwner = TRUE;
	ASSERT( myArray.SetAsOwner( bOwner ) );
	ASSERT( myArray.IsOwner() );
	
	bOwner = FALSE;
	ASSERT( myArray.SetAsOwner( bOwner ) );
	ASSERT( !myArray.IsOwner() );
}
