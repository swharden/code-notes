/*------------------------------------------------------------------------------*
 * File Name: ThrowTryAndCatchEx.c												*
 * Creation: GJL, 3/4/2004														*
 * Purpose: OriginC Source C file for Throw, Try, and Catch examples.			*
 * Copyright (c) OriginLab Corp.	2004, 2005, 2006, 2007, 2008, 2009			*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include <origin.h>

void CallingExternalDLL()
{
	try // Protected code...
	{
		LPSTR lpdest = NULL;
		strcpy(lpdest, "Test");
	}
	catch(int nErr) // Error handler...
	{
		out_int("Error Calling External DLL = ", nErr);
	}
}

void COMErrorTrappingEx()
{
	string SQLString = "select * table";
	Object ocrs;
	ocrs = CreateObject("ADODB.Recordset");
	try // Protected code...
	{
		ocrs.open(SQLString, "Provider=msdaora; Data Source=Source; User ID=UserID; Password=Password;"); 
	}
	catch(int nErr) // Error handler...
	{
		out_int("COM Error = ", nErr);
	}
}

void ThrowTryCatchEx(double dY)
{
	try // Protected code...
	{
		FuncA(dY);
		FuncB(dY);
	}
	catch(int iErr) // Error handler...
	{
		printf("Computational Error code = %d\n", iErr);
	}
}		

void FuncA(double dY)
{
	int iErr;
	if( dY < 0 )
		throw 100; // Force error...
	else if(is_equal(0, dY))
		throw 101; // Force error...
	else if(is_equal(1, dY))
		throw 102; // Force error...

	double dX = sqrt(dY) / log(dY);
	printf("No error generated, dX = sqrt(dY) / log(dY) = %g\n", dX); 
}

void FuncB(double dY)
{
	int iErr;
	if(is_equal(2, dY))
		throw 103; // Force error...

	double dZ = 1 / (2 - dY);
	printf("No error generated, dZ = 1 / (2 - dY) = %g\n", dZ); 
}