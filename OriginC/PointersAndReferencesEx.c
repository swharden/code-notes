/*------------------------------------------------------------------------------*
 * File Name: PointersAndReferences.c											*
 * Creation: GJL 2/16/05														*
 * Purpose: OriginC Source C file containing pointer and reference examples.	*
 * Copyright (c) OriginLab Corp.	2005, 2006, 2007, 2008, 2009				*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/
 
#include <Origin.h>

void PointersEx1()
{
	double dVar1;    // Declare a variable dVar1 of type double
	double *pdVar1;  // Declare a variable pdVar1 of type pointer to double
	dVar1 = 3.14159; // Assign the value 3.14159 to dVar1
	pdVar1 = &dVar1; // Assign the address of the variable dVar1 to pdVar1
	printf("The value of dVar1 is %g and the address of dVar1 (or pdVar1) is 0x%p\n", dVar1, pdVar1); 
}
	
void PointersEx2()
{
	double dVar1, dVar2;      // Declare dVar1 and dVar2 as doubles
	double *pdVar1, *p2dVar1; // Declare pdVar1 and p2dVar1 as pointers to doubles 
	dVar1 = 3.14159;          // Assign the value 3.14159 to dVar1 
	pdVar1 = &dVar1;          // Assign the address of dVar1 to pdVar1
	p2dVar1 = pdVar1;         // Assign pdVar1 (the address of dVar1) to p2dVar1
	dVar2 = *p2dVar1;         // Assign the value of dVar1 (3.14159) to dVar2
	printf("The value of dVar1 is %g and the address of dVar1 (or pdVar1)  is 0x%p\n", dVar1, pdVar1);
	printf("The value of dVar2 is %g and the address of dVar1 (or p2dVar1) is 0x%p\n", dVar2, p2dVar1);
}

void ReferencesEx()
{
	int iVal = 5;     // Declare a variable iVal of type int and initialize to 5
	int &iRef = iVal; // Declare a variable iRef as a reference to iVal
	// Here after iRef refers to iVal (and vice-versa)
	int iNotARef = iVal; // Declare iNotARef and initialize to iVal but not as a reference
	iRef += 2;        // Add 2 to iRef which also adds 2 to iVal since they are synonyms for same variable
	printf("The value of iRef was changed to %d and the value iVal was changed to %d\n", iRef, iVal);
	printf("..but the value of iNotARef is unchanged and is still %d", iNotARef);
}

void PassByValueEx()
{
	double dVal = 5;
	double dValx2;
	printf("dVal is %g before function call\n", dVal);
	dValx2 = TimesTwoEx(dVal); // Since we passed dVal by value it is not changed by called function
	printf("dVal is %g after function call\n", dVal);
	printf("dValx2 is %g\n", dValx2);
}

double TimesTwoEx(double dIn) // To pass by value do not use pointer * or reference &
{
	double dOut = dIn *2.0;
	dIn = -1.0; // Changing dIn here does not effect dVal in PassByValueEx
	return dOut;
}

void PassByPointerEx(int iCol = 0)
{
	Worksheet wks = Project.ActiveLayer();
	if( wks ) // If wks is valid...
		ColProcessByPointerEx(iCol, &wks); // Pass wks with address of operator
}
                                                              // Declare reference argument 
void ColProcessByPointerEx(int iIndex, Worksheet *sht = NULL) // Pointer allows default of NULL
{
	if( NULL != sht ) // Use inequality
	{
		printf("Active Worksheet is %s\n", sht->GetName()); // Use member selecter operator -> for pointer
		Dataset ds;
		ds.Attach(*sht, iIndex); // Use the value of or dereference operator *
		ds /= 10.;
	}
}

void PassByReferenceEx1(int iCol = 0)
{
	Worksheet wks = Project.ActiveLayer();
	if( wks ) // If wks is valid...
		ColProcessByReferenceEx(iCol, wks); // Pass wks with no address of operator
}

void ColProcessByReferenceEx(int iIndex, Worksheet &sht) // Declare reference argument sht 
{
	if( sht.IsValid() ) // Use IsValid method
	{
		printf("Active Worksheet is %s\n", sht.GetName()); // Use member selecter operator . for object
		Dataset ds;
		ds.Attach(sht, iIndex); // Do not need to use the value of or dereference operator *
		ds /= 10.;
	}
}

void PassByReferenceEx2()
{
	int iVal1 = 5, iVal2 = 10;
	printf("Before function call: iVal1 = %3d and iVal2 = %3d\n", iVal1, iVal2);
	ChangeValsEx(iVal1, iVal2); // Pass iVal1 by value and iVal2 by reference 
	printf("After function call:  iVal1 = %3d and iVal2 = %3d\n", iVal1, iVal2);
	// Note iVal1 does not change but iVal2 does change
}

void ChangeValsEx(int in1, int& in2) // Pass in1 by value and in2 by reference
{
	in1 = in1 + 100;
	in2 = in2 + 100;
	printf("in1 = %3d and in2 = %3d\n", in1, in2);
}