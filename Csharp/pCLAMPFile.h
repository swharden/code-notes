/*------------------------------------------------------------------------------*
 * File Name: pclampfile.h														*
 * Copyright (c) OriginLab Corp. 2004											*
 *																				*
 * Modification Log:															*
 * EJP 12-08-2004 v8.0173 QA70-7210 PCLAMP_IMPORT_DIALOG						*
 * SY 02/15/2005 QA70-7210 v8.0193 MORE_WORK_PCLAMP_IMPORT_DIALOG				*
 * AW 11/07/06 MORE_WORK_ON_SHOW_TIME_COL										*
 * Hong 11/9/06 TEMP_OPEN_SUPPORT_GAPFREE_MODE									*
 * Hong 11/10/06 MORE_ADD_TAG_TO_PLOT											*
 * AW 12/01/06 CHECK_FILE_DATA_TYPE												*
 * Hong 12/08/06 UPDATE_TO_VERSION_2											*
 * Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH									*
 * Hong 12/09/06 READ_MATH_CHANNEL												*
 * Hong 12/11/06 FIX_TIME_ERROR_OFFSET											*
 * Hong 12/21/06 ERROR_GENERATE_DATA_BY_RAW_DATA								*
 * AW 03/12/07 8.0579 FIX_PLCAMP_CRASH_AT_FILENODE_CLEANUP						*
 *	Hong 05/05/07 FIX_FAIL_GET_CORRECT_NUMBER_WHEN_GAPFREE						*
 *	Hong 05/14/07 v8.0617 ADD_STIMULUS_SELECT_OPTION							*
 * AW 01/06/09 QA80-12413 ADD_HOLDING_DURATION_TIME_IN_PCLAMP					*
 *	Hong 01/15/09 FIX_PCLAMP_PLOT_FAIL_HANDLE_TIME_OFFSET_OF_HOLDING_DURATION	*
 *	Hong 03/06/09 QA80-13222 TIME_COL_SHOULD_TRIM_TO_MAX_SWEEP_LENGTH_FOR_VARIABLE_LENGTH_MODE_FIILE
 *	Hong 04/20/09 USER_ASK_FOR_PUBLIC_ACCESS_OF_HEADER_INFO						*
 *	Hong 04/20/09 FIX_VERSION_2_SAMPLE_INTERVAL_NOT_CONSISTENT_WITH_VERSION_1	*
 *	Hong 04/23/09 QA80-13222-P7 FIX_TAG_TIME_IS_WRONG_WHEN_CHECK_HOLDING_DURATION
 *	Sophy 11/26/2013 ORG-9402-S1 PROPER_CLOSE_PCLAMP_FILE_WITH_CHECK			*
 *------------------------------------------------------------------------------*/

#ifndef	PCLAMPFILE_H
#define	PCLAMPFILE_H
/// Hong 12/08/06 UPDATE_TO_VERSION_2
//#include "pClamp9.h"
///Sophy 5/15/2014 ORG-9424 CLEAN_PCLAMP_HEADER_FOR_EASY_UPDATE
//#include "abffiles.h"
#include "oabffiles.h"
///end CLEAN_PCLAMP_HEADER_FOR_EASY_UPDATE
/// end UPDATE_TO_VERSION_2
#include <string.h> /// EJP 12-08-2004 v8.0173 QA70-7210 PCLAMP_IMPORT_DIALOG

#define ADC_UNIT_SIZE		8
//#define DIGIT_WAVEFORM_NUM 	4 // Hong 11/8/06 MORE_ADD_STIMULUR_OUTPUT_DATA
#define DIGIT_WAVEFORM_NUM 	8 // Hong 01/05/06 UPDATE_TO_VERSION_2
#define MATH_CHANNEL 		-1	// Hong 12/09/06 READ_MATH_CHANNEL

enum
{ 	
	INFO_TERSE=0,
	INFO_LONG,
	INFO_VERBOSE
};

#define SWEEP_OFFSET		1


/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
void	_init_string_from_mbcs(string& str, LPCSTR lpcsz)
{
/// Hong 07/19/2017 ORG-15873-P4 FIX_SOME_IMPORT_FAIL_WITH_UNICODE_PATH
//#ifdef __OC_UNICODE__
//	int			nLength = lstrlen(lpcsz);
//	LPSTR		lpstr = str.GetBuffer(nLength * FCT_SIZE_MBCS_TO_UTF8);
//	int			nLen = LABUTIL_UNICODE_MBCS_to_UTF8(lpcsz, -1, lpstr, nLength * FCT_SIZE_MBCS_TO_UTF8, -1);
//	str.ReleaseBuffer(nLen);
//#else // __OC_UNICODE__
//	str = lpcsz;
//#endif // __OC_UNICODE__
	str = lpcsz;
	mbcs_text_to_str(str);
/// End FIX_SOME_IMPORT_FAIL_WITH_UNICODE_PATH
}
/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN



/// Hong 04/23/09 QA80-13222-P7 FIX_TAG_TIME_IS_WRONG_WHEN_CHECK_HOLDING_DURATION
class CBoolResetAndRestoreHelper
{
public:
	CBoolResetAndRestoreHelper(BOOL* pbVal)
	{
		m_pbVal = NULL;
		if ( NULL != pbVal )
		{
			m_pbVal = pbVal;
			m_bOldVal = *m_pbVal;
			*m_pbVal = FALSE;
		}
	}
	~CBoolResetAndRestoreHelper()
	{
		if ( m_pbVal )
		{
			*m_pbVal = m_bOldVal;
		}
	}
	
private:
	BOOL*		m_pbVal;
	BOOL		m_bOldVal;
};
/// end FIX_TAG_TIME_IS_WRONG_WHEN_CHECK_HOLDING_DURATION

class pCLAMPFile
{
public:
	
	pCLAMPFile(LPCSTR strFileName)
	{
		m_strFileName = strFileName;
/// Hong 07/19/2017 ORG-15873-P4 FIX_SOME_IMPORT_FAIL_WITH_UNICODE_PATH
///// Hong 01/06/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
//#ifdef __OC_UNICODE__
//		int			nLength = LABUTIL_UNICODE_UTF8_to_MBCS(strFileName, -1, NULL, 0, -1);
//		if (nLength > 0)
//		{
//			LPSTR		lpBuf = m_strFileNameMBCS.GetBuffer(nLength);
//			LABUTIL_UNICODE_UTF8_to_MBCS(strFileName, -1, lpBuf, nLength, -1);
//			m_strFileNameMBCS.ReleaseBuffer();
//		}
//#else // __OC_UNICODE__
//		m_strFileNameMBCS = m_strFileName;
//#endif // __OC_UNICODE__
///// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		m_strFileNameMBCS = m_strFileName;
		str_to_mbcs_text(m_strFileNameMBCS);
/// End FIX_SOME_IMPORT_FAIL_WITH_UNICODE_PATH

		m_bValidPClamp = FALSE;
		/// Hong 12/08/06 UPDATE_TO_VERSION_2
		/*
		m_header.lFileSignature       = ABF_NATIVESIGNATURE;
   		m_header.fFileVersionNumber   = ABF_CURRENTVERSION;
   		m_header.fHeaderVersionNumber = ABF_CURRENTVERSION;
   		m_header.lHeaderSize          = ABF_HEADERSIZE;
   		*/
   	  	m_header.fFileVersionNumber   = ABF_CURRENTVERSION;
	   	m_header.fHeaderVersionNumber = ABF_CURRENTVERSION;
	   	m_header.lHeaderSize          = sizeof(ABFFileHeader);
   		/// end UPDATE_TO_VERSION_2

		m_bUseHoldingDuration = false;		/// Fisher 01/07/09 QA80-12413 ADD_HOLDING_DURATION_TIME_IN_PCLAMP
		///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING should be inited with -1 inside Open()
   		//m_nFileHandle = 0;	///Sophy 11/26/2013 ORG-9402-S1 PROPER_CLOSE_PCLAMP_FILE_WITH_CHECK
   		///end PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
   		m_strErrMsg.Empty();	///Sophy 8/19/2014 ORG-11755-S1 IMPROVE_ERRMSG_WITH_FILE_VERSION_CHECKING
		if( m_strFileName.IsFile() && Open() )
		{
			m_bValidPClamp = TRUE;
			m_nChannelNum = GetChannelNum();
   			m_nSweepNum = GetSweepNumPerChannel();
		}
   		
	}
	
	~pCLAMPFile()
	{
		Close();
	}
	
public:	
	/// Fisher 01/07/09 QA80-12413 ADD_HOLDING_DURATION_TIME_IN_PCLAMP
	void UseHoldingDuration(BOOL bUseHoldingDuration = true)
	{
		m_bUseHoldingDuration = bUseHoldingDuration;
	}
	/// End ADD_HOLDING_DURATION_TIME_IN_PCLAMP

	string GetHeaderInfo(UINT nHeaderDisplayMode = INFO_TERSE)
	{
		/// SY 02/15/2005 QA70-7210 v8.0193 MORE_WORK_PCLAMP_IMPORT_DIALOG
		if( !m_strFileName.IsFile() )
			return "";
		/// end MORE_WORK_PCLAMP_IMPORT_DIALOG
		///Sophy 3/13/2012 ORG-5261-P1 PROPER_CHECK_INVALID_PCLAMP_FILE
		if ( !IsValid() )
			return "";
		///end PROPER_CHECK_INVALID_PCLAMP_FILE
		
		UINT uBufSize = 0;
		
		try
		{
			uBufSize = INFO_GetBufferSize(&m_header, (LPCSTR)m_strFileNameMBCS, nHeaderDisplayMode);
		}
		catch(int nErr)
		{
			return "";
		}
		
		char* HeadBuf;
		HeadBuf = (char*)malloc(uBufSize);
		
		INFO_GetInfo(&m_header, m_strFileNameMBCS, nHeaderDisplayMode, HeadBuf, uBufSize);
		
		string strHeaderInfo;
		/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		//strHeaderInfo = HeadBuf;
		_init_string_from_mbcs(strHeaderInfo, HeadBuf);
		/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		return strHeaderInfo;
	}
	
	/// SY 02/21/2005 QA70-7210 v8.0193 MORE_WORK_PCLAMP_IMPORT_DIALOG
	// Get information about the tags in the file
	bool IsValid() { return m_bValidPClamp; }
	
	///Sophy 8/19/2014 ORG-11755-S1 IMPROVE_ERRMSG_WITH_FILE_VERSION_CHECKING
	string	GetLastErrMsg(){ return m_strErrMsg; }
	///end IMPROVE_ERRMSG_WITH_FILE_VERSION_CHECKING
	
	//// AW 11/07/06 MORE_WORK_ON_SHOW_TIME_COL
	float GetSecondSamepleInterval()
	{
		/// Hong 12/08/06 UPDATE_TO_VERSION_2
		//return m_header.fADCSecondSampleInterval;
		return m_header.uFileCompressionRatio;
		/// end UPDATE_TO_VERSION_2
	}
	/// END MORE_WORK_ON_SHOW_TIME_COL
	
	
	//// AW 10/10/06 MORE_ON_XF_PCLAMP_HEADER_INFO
	//string GetTags()
	//{
	string GetTags(BOOL* pbHasData = NULL)
	{
		if ( pbHasData )
			*pbHasData = false;
	//// END MORE_ON_XF_PCLAMP_HEADER_INFO
		if( !m_bValidPClamp )
			return "";
		
		if( (m_header.lTagSectionPtr <= 4) || (m_header.lNumTagEntries < 1) )
			return "Data file does not contain any tags.\r\n";
		
		//// AW 10/10/06 MORE_ON_XF_PCLAMP_HEADER_INFO
		if ( pbHasData )
			*pbHasData = true;
		//// END MORE_ON_XF_PCLAMP_HEADER_INFO
		
		int nErrorNum = 0;
		string strTags(" Tag#	Offset	Type	Text\r\n");
		ABFTag Tag;
		string strTemp;
		int nTagTime;
		
		for( DWORD i = 0; i < (DWORD)m_header.lNumTagEntries; i++ )
		{
		  	if( ABF_ReadTags(m_nFileHandle, &m_header, i, &Tag, 1, &nErrorNum) )
		  	{
		  		/// Hong 10/17/06 FIX_NOT_GET_RIGHT_TIME
		  		//nTagTime = (Tag.lTagTime * m_header.fADCSampleInterval) / 1000;
		  		if(!m_header.fSynchTimeUnit)
		  			/// Hong 12/08/06 UPDATE_TO_VERSION_2 
		  			//nTagTime = (Tag.lTagTime * m_header.fADCSampleInterval) / 1000000;//make Units to ms
		  			/// Hong 04/20/09 FIX_VERSION_2_SAMPLE_INTERVAL_NOT_CONSISTENT_WITH_VERSION_1
		  			//nTagTime = (Tag.lTagTime * m_header.fADCSequenceInterval) / 1000000;//make Units to ms
		  			nTagTime = Tag.lTagTime * GetADCSequenceInterval();
		  			/// end FIX_VERSION_2_SAMPLE_INTERVAL_NOT_CONSISTENT_WITH_VERSION_1
		  			/// end UPDATE_TO_VERSION_2
		  		else
		  			nTagTime = Tag.lTagTime * m_header.fSynchTimeUnit / 1000;//make Units to ms
		  		/// end FIX_NOT_GET_RIGHT_TIME
			  	/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
			  	//strTemp.Format("%5lu	%-8ld	  %d	%55.55s\r\n", i+1, nTagTime, Tag.nTagType, Tag.sComment);
				string	strCmt;
				_init_string_from_mbcs(strCmt, Tag.sComment);
				strTemp.Format("%5lu	%-8ld	  %d	%55.55s\r\n", i + 1, nTagTime, Tag.nTagType, strCmt);
			  	/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
				strTags += strTemp;
		  	}
		}
		
		return strTags;
	}
	
    int GetMaxSamples() { return m_nMaxSamples;}

    /// Hong 01/15/09 FIX_PCLAMP_PLOT_FAIL_HANDLE_TIME_OFFSET_OF_HOLDING_DURATION
    double GetHoldingDuration()
    {
    	UINT nHoldingDuration = ABFH_GetHoldingDuration(&m_header);
    	return -(double)nHoldingDuration / m_header.nADCNumChannels * m_header.fADCSequenceInterval / 1000.0;   // AW: in new version, there is no fADCSampleInterval, need divide nADCNumChannels here
    }
    /// end FIX_PCLAMP_PLOT_FAIL_HANDLE_TIME_OFFSET_OF_HOLDING_DURATION    
    BOOL GetStartTime(double *pdStartTime, int nChannel = -1 , DWORD dwEpisode = -1)
    {
    	int nError;
    	
    	if( dwEpisode < 0 )
    		dwEpisode = SWEEP_OFFSET;
    	
    	int nPhysicalChannelNum;
    	if( nChannel < 0 )
	    	nChannel = m_header.nADCSamplingSeq[0];
    	
      	nPhysicalChannelNum = m_header.nADCPtoLChannelMap[nChannel];
    	
		/// Fisher 01/07/09 QA80-12413 ADD_HOLDING_DURATION_TIME_IN_PCLAMP
		//return ABF_GetStartTime(m_nFileHandle, &m_header, nPhysicalChannelNum, dwEpisode, pdStartTime, &nError);
		BOOL bRet = ABF_GetStartTime(m_nFileHandle, &m_header, nPhysicalChannelNum, dwEpisode, pdStartTime, &nError);
		if(pdStartTime && m_bUseHoldingDuration)
		{
			/// Hong 01/15/09 FIX_PCLAMP_PLOT_FAIL_HANDLE_TIME_OFFSET_OF_HOLDING_DURATION
			//UINT nHoldingDuration = ABFH_GetHoldingDuration(&m_header);
			//double dTimeOffset = -(double)nHoldingDuration / m_header.nADCNumChannels * m_header.fADCSequenceInterval / 1000.0;   // AW: in new version, there is no fADCSampleInterval, need divide nADCNumChannels here
			double dTimeOffset = GetHoldingDuration();
			/// end FIX_PCLAMP_PLOT_FAIL_HANDLE_TIME_OFFSET_OF_HOLDING_DURATION
			*pdStartTime = *pdStartTime + dTimeOffset ;
		}
		return bRet;
		/// Fisher 01/07/09 QA80-12413 ADD_HOLDING_DURATION_TIME_IN_PCLAMP

    }
    
    BOOL GetEpisodeDuration(double *pdDuration, int iEpisode, bool bConvertIndexToNo = false)
    {
    	int nError;
    	
		if( SWEEP_OFFSET && bConvertIndexToNo )
			iEpisode = convertSweepIndexToSweepNo(iEpisode);
		
		if( iEpisode < 0 )
			iEpisode = SWEEP_OFFSET;
    	
    	return ABF_GetEpisodeDuration(m_nFileHandle, &m_header, iEpisode, pdDuration, &nError);
    }
    
	void GetEpisodeTimeDataSize(const vector<int>& vnEpisodes, int nNumEpisodes, bool bAllEpisodes, vector<float> &vTimeData)
	{
		// Match the time column with the Episode's samples
		UINT uMaxNumSamples = 0;
		UINT uNumSamples = 0;
		int nEpisode;
		
		// Get the max episode sample
		for( int nEpIndex = 0; nEpIndex < nNumEpisodes; nEpIndex++ )
		{
			if( bAllEpisodes )
				nEpisode = nEpIndex;
			else
				nEpisode = vnEpisodes[nEpIndex];
			
			uNumSamples = GetSweepSize(nEpisode, true);
	
			if( uNumSamples > uMaxNumSamples )
				uMaxNumSamples = uNumSamples;
		}
		
		// Set the time data vector size
		vTimeData.SetSize(uMaxNumSamples);
	}
	
	int GetOperationMode()
	{
		return m_header.nOperationMode;
	}
	/// Hong 01/25/07 ADD_MORE_COLUMN_INFO
	void GetUserInfoTree(TreeNode& trUserInfo, int nChannelNo, int nSweepNo)
	{
		///---Sim 01-29-2007 ADD_FULL_FILE_NAME_INTO_COLUMN_INFO
		TreeNode trFileName = trUserInfo.AddTextNode(m_strFileName, "ImportFile");
		trFileName.Enable = ENABLE_READ_ONLY;
		///---END ADD_FULL_FILE_NAME_INTO_COLUMN_INFO
		
		string strVal = "";
		GetChannelName(nChannelNo, strVal);
		trUserInfo.AddTextNode(strVal, "ADCChannelName");
		
		trUserInfo.AddNumericNode(m_header.nADCPtoLChannelMap[nChannelNo], "ADCPtoLChannelMap");
		trUserInfo.AddNumericNode(m_header.nADCSamplingSeq[nChannelNo], "ADCSamplingSeq");
		trUserInfo.AddNumericNode(m_header.fADCProgrammableGain[nChannelNo], "ADCProgrammableGain");
		trUserInfo.AddNumericNode(m_header.fInstrumentScaleFactor[nChannelNo], "InstrumentScaleFactor");
		trUserInfo.AddNumericNode(m_header.fInstrumentOffset[nChannelNo], "InstrumentOffset");
		trUserInfo.AddNumericNode(m_header.fSignalGain[nChannelNo], "SignalGain");
		trUserInfo.AddNumericNode(m_header.fSignalOffset[nChannelNo], "SignalOffset");
		trUserInfo.AddNumericNode(m_header.fSignalLowpassFilter[nChannelNo], "SignalLowpassFilter");
		trUserInfo.AddNumericNode(m_header.fSignalHighpassFilter[nChannelNo], "SignalHighpassFilter");
		trUserInfo.AddNumericNode(m_header.nLowpassFilterType[nChannelNo], "LowpassFilterType");
		trUserInfo.AddNumericNode(m_header.nHighpassFilterType[nChannelNo], "HighpassFilterType");
		
		trUserInfo.AddNumericNode(m_header.nTelegraphEnable[nChannelNo], "TelegraphEnable");
		trUserInfo.AddNumericNode(m_header.nTelegraphInstrument[nChannelNo], "TelegraphInstrument");
		trUserInfo.AddNumericNode(m_header.fTelegraphAdditGain[nChannelNo], "TelegraphAdditGain");
		trUserInfo.AddNumericNode(m_header.fTelegraphFilter[nChannelNo], "TelegraphFilter");
		trUserInfo.AddNumericNode(m_header.fTelegraphMembraneCap[nChannelNo], "TelegraphMembraneCap");
		trUserInfo.AddNumericNode(m_header.nTelegraphMode[nChannelNo], "TelegraphMode");
		
		trUserInfo.AddNumericNode(m_header.fPostProcessLowpassFilter[nChannelNo], "PostProcessLowpassFilter");
		trUserInfo.AddNumericNode(m_header.nPostProcessLowpassFilterType[nChannelNo], "PostProcessLowpassFilterType");
	}
	/// end ADD_MORE_COLUMN_INFO
	// PURPOSE:  Calculate the trial duration in ms.
	//           This is the duration between the start of the file and the last sample in the file.
	BOOL GetTrialDuration(double *pdDuration)
	{
		if( !pdDuration )
			return FALSE;
		
    	int nError;
		*pdDuration = 0.0;
		
		// Get the start time of the last sweep.
		double dLastSweepStart = 0.0;
		if( !ABF_GetStartTime(m_nFileHandle, &m_header, m_header.nADCSamplingSeq[0], m_header.lActualEpisodes, &dLastSweepStart, &nError) )
		  return FALSE;
		
		// Now the duration of the last sweep.
		double dLastSweepDuration = 0;
		if( !ABF_GetEpisodeDuration(m_nFileHandle, &m_header, m_header.lActualEpisodes, &dLastSweepDuration, &nError) )
		  return FALSE;
		
		double dTotalDuration = dLastSweepStart + dLastSweepDuration;
		ASSERT( dTotalDuration > 0 );
		*pdDuration = dTotalDuration;
		
		return TRUE;   
	}
	/// end MORE_WORK_PCLAMP_IMPORT_DIALOG
	
	//Get ADCUnits name
	string GetUnit(int nChannelNo)
	{	
		if( !checkChannelNo(nChannelNo) )
			return "";
		
		int 	nPhysChannel = m_header.nADCSamplingSeq[nChannelNo];
		char 	chUnit[ADC_UNIT_SIZE];
		
		for( int ii =0; ii < ADC_UNIT_SIZE; ii++)
		{
			chUnit[ii] = m_header.sADCUnits[nPhysChannel*ADC_UNIT_SIZE+ii];
		}
		/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		//string strUnit = strtok(chUnit," ");
		string strUnit;
		_init_string_from_mbcs(strUnit, strtok(chUnit, " "));
		/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN

		return strUnit;
	}

	/// EJP 12-08-2004 v8.0173 QA70-7210 PCLAMP_IMPORT_DIALOG
	BOOL GetChannelName(int nChannel, string& strName)
	{
		if( checkChannelNo(nChannel) )
		{
			LPCSTR lpcstrName = m_header.sADCChannelName;
			
			int nPhysChannel = m_header.nADCSamplingSeq[nChannel];
			lpcstrName += (nPhysChannel * ABF_ADCNAMELEN);
			
			char cName[ABF_ADCNAMELEN + 1];
			memcpy(cName, (LPSTR)lpcstrName, ABF_ADCNAMELEN);
			cName[ABF_ADCNAMELEN] = 0;

			/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
			//strName = cName;
			_init_string_from_mbcs(strName, cName);
			/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
			strName.TrimRight();
			return TRUE;
		}
		return FALSE;
	}
	/// end PCLAMP_IMPORT_DIALOG
	
 	//Read No.nSweep Sweep in the No.nChannel channel.
	bool	ReadOneSweep(int nChannelNo, int nSweepNo, vector<float>& vData)
	{
		if( !checkChannelNo(nChannelNo) || !checkSweepNo(nSweepNo) )
			return false;
		
		if(SWEEP_OFFSET)
		{
			nSweepNo = convertSweepIndexToSweepNo(nSweepNo);
		}
		/// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH
		// The data buffer must be the max size return by ABF_ReadOpen
		//int	nSweepMaxSize = GetSweepSize(SWEEP_OFFSET); //The size of the last sweep may be small than other sweeps, but the data buffer must has the size same as other Sweep, otherwise will result in crash.
		/// end FIX_SWEEP_BUFFER_LENGTH_CRASH
		int nSweepCurrentSize;
			
		//// AW 12/01/06 CHECK_FILE_DATA_TYPE
		int nError;
		/// Hong 12/21/06 ERROR_GENERATE_DATA_BY_RAW_DATA
		// temp comment it before we have know enough to fix it
		/*
		if ( ABF_INTEGERDATA == m_nDataFormat )
		{	
			int 	nPhysChannel = m_header.nADCSamplingSeq[nChannelNo];
			float fGain, fOffset;
			
			/// Hong 12/08/06 UPDATE_TO_VERSION_2			
			//float _fAutosampleAdditGain = m_header._fAutosampleAdditGain;
			float _fAutosampleAdditGain = m_header.fTelegraphAdditGain[nChannelNo];
			/// end UPDATE_TO_VERSION_2
			if ( _fAutosampleAdditGain < 0 )    /// Justin, please check this case
				_fAutosampleAdditGain = 1;      /// Justin, please check this case
			
			fGain = m_header.fADCRange / m_header.lADCResolution / (_fAutosampleAdditGain * m_header.fInstrumentScaleFactor[nChannelNo] * m_header.fADCProgrammableGain[nChannelNo] * m_header.fSignalGain[nChannelNo]);
			fOffset = m_header.fSignalOffset[nChannelNo];

			vector<short> 	vstTemp;
			/// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH
			// The data buffer must be the max size return by ABF_ReadOpen, otherwise will result crash for variable-length data, document not expain why
			//vstTemp.SetSize(nSweepMaxSize);
			vstTemp.SetSize(m_nMaxSamples);
			/// end FIX_SWEEP_BUFFER_LENGTH_CRASH
			if( !ABF_ReadRawChannel( m_nFileHandle, &m_header, nPhysChannel, nSweepNo, vstTemp, &nSweepCurrentSize, &nError) ) 
			{
				return false;
			}
			vData = fGain*vstTemp + fOffset;
			vData.SetSize(nSweepCurrentSize);// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH
			return true;
		}
		*/
		/// end ERROR_GENERATE_DATA_BY_RAW_DATA
		/// SY 03/18/2005 QA70-7210 v8.0207 MORE_WORK_PCLAMP_IMPORT_DIALO
		///	vData.RemoveAll();
		/// end MORE_WORK_PCLAMP_IMPORT_DIALOG
		/// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH
		// The data buffer must be the max size return by ABF_ReadOpen, otherwise will result crash for variable-length data, document not expain why
		//vData.SetSize(nSweepMaxSize);
		vData.SetSize(m_nMaxSamples);
		/// end FIX_SWEEP_BUFFER_LENGTH_CRASH
		
		int 	nPhysChannel = m_header.nADCSamplingSeq[nChannelNo];
		if( !ABF_ReadChannel( m_nFileHandle, &m_header, nPhysChannel, nSweepNo, vData, &nSweepCurrentSize, &nError) ) 
		{
			return false;
		}
		
		vData.SetSize(nSweepCurrentSize);// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH
		/// SY 03/11/2005 QA70-7210 v8.0200 MORE_WORK_PCLAMP_IMPORT_DIALOG
		///	if( nSweepMaxSize != nSweepCurrentSize)
		///		vData.RemoveAt(nSweepCurrentSize, nSweepMaxSize-nSweepCurrentSize);
		/// end MORE_WORK_PCLAMP_IMPORT_DIALOG
		return true;
	}
	
 	//Read all in the No.nChannel channel.
	bool ReadOneChannel(int nChannelNo, vector<float> &vfData)//
	{		
		if( !checkChannelNo(nChannelNo) )
			return false;

		/// SY 04/21/2005 QA70-7210 v8.0225 MORE_WORK_PCLAMP_IMPORT_DIALOG
		int ii, nC1 = 0, uNumSamples = 0;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			uNumSamples += GetSweepSize(ii, true);
		}
		vfData.SetSize(uNumSamples);
		/// end MORE_WORK_PCLAMP_IMPORT_DIALOG
		
		vector<float> vfTemp;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			/// SY 04/21/2005 QA70-7210 v8.0225 MORE_WORK_PCLAMP_IMPORT_DIALOG
			///	ReadOneSweep(nChannelNo, ii, vfTemp);
			///	
			///	vfData.Append(vfTemp);
			///	vfTemp.RemoveAll();
			if( ReadOneSweep(nChannelNo, ii, vfTemp) )
			{
				vfData.SetSubVector(vfTemp, nC1);
				nC1 += vfTemp.GetSize();
			}
			else
				return false;
			/// end MORE_WORK_PCLAMP_IMPORT_DIALOG 
		}

		return true;
	}
	
	//Make the time data for the use of time column (X axis)
	bool	GetTimeData(vector<float> &vfData,	double fTimeOffset = 0.0, long nSize = 0)
	{
		/// Hong 12/11/06 FIX_TIME_ERROR_OFFSET
		/* as we make our time column start at 0, so no need to caculate offset
		// this part is taken from the AbfReadRaw code
		int nHoldingDuration;
		/// Hong 12/08/06 UPDATE_TO_VERSION_2 
		//if( m_header._nWaveformSource == 0 )
		if( m_header.nWaveformSource[0] == 0 )
		///end UPDATE_TO_VERSION_2
			nHoldingDuration = 0;
		else if( m_header.nFileType == ABF_CLAMPEX )
			nHoldingDuration = 6 * (WORD)(m_header.lNumSamplesPerEpisode >> 9);
		else 
			nHoldingDuration = (WORD)(m_header.lNumSamplesPerEpisode >> 6);
		
		/// Hong 12/08/06 UPDATE_TO_VERSION_2 
		//float fTimeOffset = -(float)nHoldingDuration * m_header.fADCSampleInterval / 1000;
		float fTimeOffset = -(float)nHoldingDuration * m_header.fADCSequenceInterval / 1000;
		/// end UPDATE_TO_VERSION_2
		*/
		///float fTimeOffset = 0.0;
		/// end FIX_TIME_ERROR_OFFSET
		
		/// AW 01/06/09 QA80-12413 ADD_HOLDING_DURATION_TIME_IN_PCLAMP
		if ( fTimeOffset < 0 )
		{
			/// Hong 01/15/09 FIX_PCLAMP_PLOT_FAIL_HANDLE_TIME_OFFSET_OF_HOLDING_DURATION
			//UINT nHoldingDuration = ABFH_GetHoldingDuration(&m_header);
			//fTimeOffset = -(double)nHoldingDuration / m_header.nADCNumChannels * m_header.fADCSequenceInterval / 1000.0;   // AW: in new version, there is no fADCSampleInterval, need divide nADCNumChannels here
			fTimeOffset = GetHoldingDuration();
			/// end FIX_PCLAMP_PLOT_FAIL_HANDLE_TIME_OFFSET_OF_HOLDING_DURATION
		}
		/// END ADD_HOLDING_DURATION_TIME_IN_PCLAMP

		
		if ( 0 == nSize )
			nSize = m_nMaxSamples;
		/// Hong 03/06/09 QA80-13222 TIME_COL_SHOULD_TRIM_TO_MAX_SWEEP_LENGTH_FOR_VARIABLE_LENGTH_MODE_FIILE
		// Hong, code below still fail to file bc3h1f01.abf, i think this maybe a bug of pclamp DLL,
		// if we want to make a work around, then need to fisrt import all data, keep the max size, and then use it to generate time column.
		if ( ABF_VARLENEVENTS == GetOperationMode() ) // Hong, this variable length mode, m_nMaxSamples is NOT the actual maximum sweep length
		{
			int			nMax = 0;
			for ( int ii = 0; ii < GetSweepNumPerChannel(); ii++ )
			{
				nMax = max(nMax, GetSweepSize(ii, true));
			}
			if ( nMax > 0 )
				nSize = min(nSize, nMax);
		}
		/// end TIME_COL_SHOULD_TRIM_TO_MAX_SWEEP_LENGTH_FOR_VARIABLE_LENGTH_MODE_FIILE
		
		vfData.SetSize(nSize);		
		/// Hong 12/08/06 UPDATE_TO_VERSION_2 
		//ABFH_GetTimebase(&m_header, fTimeOffset, vfData, m_nMaxSamples);
		vector vdData;
		/// Hong 03/06/09 QA80-13222 TIME_COL_SHOULD_TRIM_TO_MAX_SWEEP_LENGTH_FOR_VARIABLE_LENGTH_MODE_FIILE
		//vdData.SetSize(m_nMaxSamples);
		vdData.SetSize(nSize);
		/// end TIME_COL_SHOULD_TRIM_TO_MAX_SWEEP_LENGTH_FOR_VARIABLE_LENGTH_MODE_FIILE
		ABFH_GetTimebase(&m_header, fTimeOffset, vdData, nSize);
		vfData = vdData;
		// end UPDATE_TO_VERSION_2
	
		return true;
	}
	
	//when nSweep < 0  return the quantity of samples if it is the same in all sweeps else returns -1;
	//and when nSweep >0 return the the quantity of samples in No.nSweep sweep.
	/// SY 03/18/2005 QA70-7210 v8.0207 MORE_WORK_PCLAMP_IMPORT_DIALO 
	///	int GetSweepSize(int nSweepNo = -1)
	int GetSweepSize(int nSweepNo = -1, bool bConvertIndexToNo = false)
	/// end MORE_WORK_PCLAMP_IMPORT_DIALO
	{
		int 	nError;
		UINT 	uNumSamples = -1;
		
		/// SY 03/18/2005 QA70-7210 v8.0207 MORE_WORK_PCLAMP_IMPORT_DIALO
		if( SWEEP_OFFSET && bConvertIndexToNo )
			nSweepNo = convertSweepIndexToSweepNo(nSweepNo);
		/// end MORE_WORK_PCLAMP_IMPORT_DIALO
		
		if( nSweepNo < 0 )
		{
			if( !ABF_GetNumSamples(m_nFileHandle, &m_header, SWEEP_OFFSET, &uNumSamples, &nError) )
				return -1;				
		}
		else if( !ABF_GetNumSamples(m_nFileHandle, &m_header, nSweepNo, &uNumSamples, &nError) )
			 return -1;
		
		return uNumSamples;
	}
	
	int GetChannelNum()
	{
		return m_header.nADCNumChannels;
	}
	
	//////// AW 05/04/07
	long GetTotalSamplingNumber()
	{
		/// Hong 05/05/07 FIX_FAIL_GET_CORRECT_NUMBER_WHEN_GAPFREE
		// this will return the actual valid data which can be imported
		//return m_header.lActualAcqLength
		int nSweepNum = GetSweepNumPerChannel();
		long lSampleingNum = 0;
		for(int ii=0; ii < nSweepNum; ii++)
		{
			int nIndex = convertSweepIndexToSweepNo(ii);
			int nErr;
			UINT unTempNum;
			ABF_GetNumSamples(m_nFileHandle, &m_header, nIndex, &unTempNum, &nErr);
			lSampleingNum += unTempNum;
		}
		
		return lSampleingNum;
		/// END FIX_FAIL_GET_CORRECT_NUMBER_WHEN_GAPFREE
	}
	/////// END
	
	int GetSweepNumPerChannel()
	{
		/// Hong 11/9/06 TEMP_OPEN_SUPPORT_GAPFREE_MODE
		///// Hong 10/18/06 FIX_ERROR_SWEEP_NUMBER_OF_GAPFREE_MODE
		////return m_header.lActualEpisodes;
		//if(m_header.nOperationMode == 3)//Gap-free mode, only one sweep
			//return 1;
		return m_header.lActualEpisodes;
		/// end FIX_ERROR_SWEEP_NUMBER_OF_GAPFREE_MODE
		/// end TEMP_OPEN_SUPPORT_GAPFREE_MODE
	}
	
 	//Get SampleInterval which is not the ADCSampleInterval.Used for Time Column.
	//float GetSampleInterval()
	double GetSampleInterval() // Hong 02/08/07 MORE_PRECISE
	{
		/// Hong 12/08/06 UPDATE_TO_VERSION_2 
		//return m_header.fADCSampleInterval*m_header.nADCNumChannels/1000;
		//return m_header.fADCSequenceInterval/1000;
		return (double)m_header.fADCSequenceInterval/1000; // Hong 02/08/07 MORE_PRECISE
		/// end UPDATE_TO_VERSION_2
	}
	
	/// Hong 04/20/09 FIX_VERSION_2_SAMPLE_INTERVAL_NOT_CONSISTENT_WITH_VERSION_1
	double GetADCSequenceInterval()
	{
		/* Hong, commnt below is copied from pclamp document
		Note that in ABF version 2.0, irrespective of whether the acquisition program specifies
		the sampling interval on a perchannel
		or a multiplexed basis, the value stored in the ABF file is the perchannel
		value.
		In the three channel example used previously, if each channel were sampled at 21 µs, the value stored in the file is 21
		µs, even though multiplexed sampling interval used by the digitizer is 7 µs. This is different to earlier versions (1.x) of
		ABF.
		*/
		return GetSampleInterval()/m_header.nADCNumChannels;
	}
	/// end FIX_VERSION_2_SAMPLE_INTERVAL_NOT_CONSISTENT_WITH_VERSION_1
	
	///// AW 09/22/06 ADD_PCLAMP_IMPORT_XF
	string GetFileName()
	{
		return m_strFileName;
	}
	///// END ADD_PCLAMP_IMPORT_XF
	
	//// AW 03/12/07 8.0579 FIX_PLCAMP_CRASH_AT_FILENODE_CLEANUP
	// the better way is fix it in VC level, but too many exiting codes there, so need wait TD check
	/*
	ABFFileHeader GetHeaderStruct()
	{
		return  m_header;	
	}
	*/
	void GetHeaderStruct(ABFFileHeader& abdHeader)
	{
		abdHeader =  m_header;	
	}
	/// END FIX_PLCAMP_CRASH_AT_FILENODE_CLEANUP
	//// END MORE_ON_XF_PCLAMP_HEADER_INFO
	
	/// Hong 11/6/06 CHECK_IF_SUPPORT_DATA_MODE
	bool IsSupportData()
	{
		/// Hong 11/9/06 TEMP_OPEN_SUPPORT_GAPFREE_MODE
		/*
		// we now not support Event-driven(variable length), and gap-free mode
		if( 1 == m_header.nOperationMode || 3 == m_header.nOperationMode )
		*/
		/// end TEMP_OPEN_SUPPORT_GAPFREE_MODE
		if( 1 == m_header.nOperationMode )
			return false;
		return true;
	}
	/// end CHECK_IF_SUPPORT_DATA_MODE
	/// Hong 11/8/06 MORE_ADD_STIMULUR_OUTPUT_DATA
	/*
	/// Hong 11/6/06 ADD_STIMULUR_OUTPUT_DATA
	bool AddOneSweepStimulur(int nChannelNo, int nSweepNo, vector<float>& vData)
	{
		if( nChannelNo < 0 || nChannelNo > ABF_WAVEFORMCOUNT ||!checkSweepNo(nSweepNo) )
			return false;
		
		if(SWEEP_OFFSET)
		{
			nSweepNo = convertSweepIndexToSweepNo(nSweepNo);
		}
		if( !m_header.nWaveformEnable[nChannelNo] || !m_header.nWaveformSource[nChannelNo])
			return false;
		
		int	nSweepMaxSize = GetSweepSize(SWEEP_OFFSET);
		vData.SetSize(nSweepMaxSize);
		
		if( !ABF_GetWaveform( m_nFileHandle, &m_header, nChannelNo, nSweepNo, vData, NULL) ) 
			return false;
		return true;
	}
	bool ReadOneChannelStimulur(int nChannelNo, vector<float> &vfData)//
	{		
		if( nChannelNo < 0 || nChannelNo > ABF_WAVEFORMCOUNT )
			return false;

		if( !m_header.nWaveformEnable[nChannelNo] || !m_header.nWaveformSource[nChannelNo])
			return false;
		
		/// SY 04/21/2005 QA70-7210 v8.0225 MORE_WORK_PCLAMP_IMPORT_DIALOG
		int ii, nC1 = 0, uNumSamples = 0;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			uNumSamples += GetSweepSize(ii, true);
		}
		vfData.SetSize(uNumSamples);
		/// end MORE_WORK_PCLAMP_IMPORT_DIALOG
		
		vector<float> vfTemp;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			if( !AddOneSweepStimulur(nChannelNo, ii, vfTemp) )
				return false;		
			vfData.SetSubVector(vfTemp, nC1);
			nC1 += vfTemp.GetSize();
		}

		return true;
	}
	/// end ADD_STIMULUR_OUTPUT_DATA
	*/
	
	///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
	int	GetAbfDacCount()
	{
		return (ABFVERSION_V1 == m_header.nABFVersion) ? OABF_DACCOUNT_V1 : OABF_DACCOUNT_V2;
	}
	///end PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
	
	/// Hong 05/14/07 v8.0617 ADD_STIMULUS_SELECT_OPTION
	bool IsHaveStimulus()
	{
		if( ABF_WAVEFORMFILE != GetOperationMode() )
			return false;
		///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		//for(int ii=0; ii < ABF_DACCOUNT; ii++)
		int nABFCount = GetAbfDacCount();
		for ( int ii=0; ii < nABFCount; ii++ )
		///end PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		{
			if( 1 == m_header.nWaveformEnable[ii] )
				return true;
		}
			
		if ( 1 == m_header.nDigitalEnable )
			return true;
						
		return false;
	}
	/// END ADD_STIMULUS_SELECT_OPTION
	
	/// Hong 01/05/06 FIX_MULTI_CHANNEL_WAVEFORM
	//bool ReadOneSweepWaveform(int nSweepNo, vector<float>& vData)
	bool ReadOneSweepWaveform(int nSweepNo, vector<float>& vData, int nChannel)
	/// end FIX_MULTI_CHANNEL_WAVEFORM
	{
		if( !checkSweepNo(nSweepNo) )
			return false;
		
		if( 1 != m_header.nWaveformEnable[nChannel] )
			return false;
		
		if(SWEEP_OFFSET)
		{
			nSweepNo = convertSweepIndexToSweepNo(nSweepNo);
		}
		/// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH 	
		//int	nSweepMaxSize = GetSweepSize(SWEEP_OFFSET);
		//vData.SetSize(nSweepMaxSize);
		int	nCurrentSweepSize = GetSweepSize(nSweepNo);
		// The data buffer must be the max size return by ABF_ReadOpen, otherwise will result crash for variable-length data, document not expain why
		vData.SetSize(m_nMaxSamples);
		/// end FIX_SWEEP_BUFFER_LENGTH_CRASH
		// Note: we now ignore the nADCChannel parameter.
		//if( !ABF_GetWaveform( m_nFileHandle, &m_header, 0, nSweepNo, vData, NULL) ) 
		if( !ABF_GetWaveform( m_nFileHandle, &m_header, nChannel, nSweepNo, vData, NULL) ) // Hong 01/05/06 FIX_MULTI_CHANNEL_WAVEFORM
			return false;
		
		vData.SetSize(nCurrentSweepSize);// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH 
		
		return true;
	}
	
	bool ReadOneSweepDigitWaveform(int nSweepNo, vector<DWORD>& vData)
	{
		// this code may need to change
		if( !checkSweepNo(nSweepNo) )
			return false;
		
		if(SWEEP_OFFSET)
		{
			nSweepNo = convertSweepIndexToSweepNo(nSweepNo);
		}
		/// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH	
		//int	nSweepMaxSize = GetSweepSize(SWEEP_OFFSET);
		//vData.SetSize(nSweepMaxSize);
		int	nCurrentSweepSize = GetSweepSize(nSweepNo);
		// The data buffer must be the max size return by ABF_ReadOpen, otherwise will result crash for variable-length data, document not expain why
		vData.SetSize(m_nMaxSamples);
		/// end FIX_SWEEP_BUFFER_LENGTH_CRASH

	//	if( !ABFH_GetDigitalWaveform( &m_header, 0, nSweepNo, vData, NULL) ) 
	//		return false;
		if( !ABFH_GetDigitalWaveform( &m_header, m_header.nActiveDACChannel, nSweepNo, vData, NULL) ) 
			return false;
		
		vData.SetSize(nCurrentSweepSize);// Hong 12/09/06 FIX_SWEEP_BUFFER_LENGTH_CRASH 
		
		return true;
	}
	/// Hong 01/05/06 FIX_MULTI_CHANNEL_WAVEFORM
	//bool ReadWaveform(vector<float>& vData)
	bool ReadWaveform(vector<float>& vData, int nChannel)
	/// end FIX_MULTI_CHANNEL_WAVEFORM
	{
		int ii, nC1 = 0, uNumSamples = 0;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			uNumSamples += GetSweepSize(ii, true);
		}
		vData.SetSize(uNumSamples);
		
		vector<float> vfTemp;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			//if( !ReadOneSweepWaveform(ii, vfTemp) )
			if( !ReadOneSweepWaveform(ii, vfTemp, nChannel) )
				return false;		
			vData.SetSubVector(vfTemp, nC1);
			nC1 += vfTemp.GetSize();
		}

		return true;
	}
	
	bool ReadDigitWaveform(vector<DWORD>& vData)
	{
		// this code may need to change
	//	if( nChannelNo < 0 || nChannelNo > DIGIT_WAVEFORM_NUM )
	//		return false;
		
		int ii, nC1 = 0, uNumSamples = 0;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			uNumSamples += GetSweepSize(ii, true);
		}
		vData.SetSize(uNumSamples);
		
		vector<DWORD> vdwTemp;
		for( ii = 0; ii < m_nSweepNum; ii++ )
		{
			if( !ReadOneSweepDigitWaveform(ii, vdwTemp) )
				return false;		
			vData.SetSubVector(vdwTemp, nC1);
			nC1 += vdwTemp.GetSize();
		}

		return true;
	}
	/// Hong 01/05/06 FIX_MULTI_CHANNEL_WAVEFORM
	// not only one channel of waveform output is available
	/*
	//Get DACUnits for waveform output
	string GetActiveDACUnit()
	{		
		LPCSTR lpcstrUnit = m_header.sDACChannelUnits;
		lpcstrUnit += (m_header.nActiveDACChannel * ABF_DACUNITLEN);
		
		char 	chUnit[ABF_DACUNITLEN + 1];
		memcpy(chUnit, (LPSTR)lpcstrUnit, ABF_DACUNITLEN);
		chUnit[ABF_DACUNITLEN] = 0;
		
		string strUnit = strtok(chUnit," "); 
		
		return strUnit;
	}
	//Get DACChannelName for waveform output
	string GetActiveDACChannelName()
	{
		string strName;
		LPCSTR lpcstrName = m_header.sDACChannelName;
		lpcstrName += (m_header.nActiveDACChannel * ABF_DACNAMELEN);
		
		char cName[ABF_DACNAMELEN + 1];
		memcpy(cName, (LPSTR)lpcstrName, ABF_DACNAMELEN);
		cName[ABF_DACNAMELEN] = 0;

		strName = cName;
		strName.TrimRight();
		return strName;
	}
	*/
	string GetDACUnit(int nChannelNo)
	{		
		LPCSTR lpcstrUnit = m_header.sDACChannelUnits;
		lpcstrUnit += (nChannelNo * ABF_DACUNITLEN);
		
		char 	chUnit[ABF_DACUNITLEN + 1];
		memcpy(chUnit, (LPSTR)lpcstrUnit, ABF_DACUNITLEN);
		chUnit[ABF_DACUNITLEN] = 0;
		
		/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		//string strUnit = strtok(chUnit," ");
		string strUnit;
		_init_string_from_mbcs(strUnit, strtok(chUnit, " "));
		/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		
		return strUnit;
	}

	string GetDACChannelName(int nChannelNo)
	{
		LPCSTR lpcstrName = m_header.sDACChannelName;
		lpcstrName += (nChannelNo * ABF_DACNAMELEN);
		
		char cName[ABF_DACNAMELEN + 1];
		memcpy(cName, (LPSTR)lpcstrName, ABF_DACNAMELEN);
		cName[ABF_DACNAMELEN] = 0;

		/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		//string strName = cName;
		string strName;
		_init_string_from_mbcs(strName, cName);
		/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		strName.TrimRight();
		return strName;
	}
	/// end FIX_MULTI_CHANNEL_WAVEFORM
	/// end MORE_ADD_STIMULUR_OUTPUT_DATA
	/// Hong 11/10/06 MORE_ADD_TAG_TO_PLOT
	/// Hong 12/20/06 SAVE_INFO_AS_TREE
	//bool GetTagsToPlot(vector<string>& vstrTags, vector& vX, bool bSweepMode)
	bool GetTagsToPlot(TreeNode& trTags, bool bSweepMode)
	/// end SAVE_INFO_AS_TREE
	{
		if( (m_header.lTagSectionPtr <= 4) || (m_header.lNumTagEntries < 1) )
			return false;
		
		int nSweepNum = GetSweepNumPerChannel();
		vector<double> dvSweepTimes;
		for( int jj = 1; jj <= nSweepNum; jj++ )
		{
			/// Hong 04/23/09 QA80-13222-P7 FIX_TAG_TIME_IS_WRONG_WHEN_CHECK_HOLDING_DURATION
			// Hong, GetStartTime should be consistent with ABF_ReadTags which does NOT offset with holding duration
			CBoolResetAndRestoreHelper	helper(&m_bUseHoldingDuration);
			/// end FIX_TAG_TIME_IS_WRONG_WHEN_CHECK_HOLDING_DURATION
			double dTime;
			if(GetStartTime(&dTime, -1, jj))
				dvSweepTimes.Add(dTime);
			else
				return false;
		}
		/// 01/05/06 FIX_GAPFREE_MODE_ERROR_TAGS_COORDINATE
		bool bGapfreeMode = false;
		if( ABF_GAPFREEFILE == GetOperationMode() )
			bGapfreeMode = true;
		/// end FIX_GAPFREE_MODE_ERROR_TAGS_COORDINATE
		Tree tr;
		TreeNode trTemp = tr.AddNode("Tags");
		ABFTag Tag;
		string strTag, strComment;
		int nTagTime, nOffSet;
		for( DWORD i = 0; i < (DWORD)m_header.lNumTagEntries; i++ )
		{
		  	if( ABF_ReadTags(m_nFileHandle, &m_header, i, &Tag, 1, NULL) )
		  	{
		  		if(!m_header.fSynchTimeUnit)
		  			/// Hong 12/08/06 UPDATE_TO_VERSION_2 
		  			//nTagTime = (Tag.lTagTime * m_header.fADCSampleInterval) / 1000;
		  			/// Hong 04/20/09 FIX_VERSION_2_SAMPLE_INTERVAL_NOT_CONSISTENT_WITH_VERSION_1
		  			//nTagTime = (Tag.lTagTime * m_header.fADCSequenceInterval) / 1000;
		  			nTagTime = Tag.lTagTime * GetADCSequenceInterval();
		  			/// end FIX_VERSION_2_SAMPLE_INTERVAL_NOT_CONSISTENT_WITH_VERSION_1
		  			/// end UPDATE_TO_VERSION_2
		  		else
		  			nTagTime = Tag.lTagTime * m_header.fSynchTimeUnit / 1000;		
		  		//determine which sweep the tag are
		  		int jj = 1;
		  		/// Hong 01/05/06 FIX_GAPFREE_MODE_ERROR_TAGS_COORDINATE
		  		if( !bGapfreeMode )
		  		{
		  			for(; jj < nSweepNum; jj++)
					{
						if(nTagTime < dvSweepTimes[jj])
							break;
					}
		  		}
		  		/// end FIX_GAPFREE_MODE_ERROR_TAGS_COORDINATE
				if( bSweepMode )
					//nTagTime -= dvSweepTimes[jj - 1];
					nOffSet = nTagTime - dvSweepTimes[jj - 1]; //Hong 12/20/06 SAVE_INFO_AS_TREE
				/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
				//strComment = Tag.sComment;
				_init_string_from_mbcs(strComment, Tag.sComment);
				/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN

				strComment.TrimRight();
				strComment.TrimLeft();
				/// Hong 12/20/06 SAVE_INFO_AS_TREE
			  	//strTag.Format("Tag%lu sw:%d\n%ldms\n%s", i+1, jj, nTagTime, strComment);
				//vstrTags.Add(strTag);
				//vX.Add(nTagTime);	
				int nTagIndex = i+1;
				string strName;
				strName.Format("Tag%d", nTagIndex);
				TreeNode trNode, trTag = trTemp.AddNode(strName);
				
				trNode = trTag.AddNumericNode(jj, "SweepNum");
				trNode.SetAttribute(STR_LABEL_ATTRIB, "Sweep index");
				trNode.Enable = ENABLE_READ_ONLY;
				
				trNode = trTag.AddNumericNode(nTagTime, "TagTime");
				trNode.SetAttribute(STR_LABEL_ATTRIB, "Time of tag");
				trNode.Enable = ENABLE_READ_ONLY;
				
				trNode = trTag.AddNumericNode(nOffSet, "OffSet");
				trNode.SetAttribute(STR_LABEL_ATTRIB, "Time offset in sweep");
				trNode.Enable = ENABLE_READ_ONLY;

				trNode = trTag.AddTextNode(strComment, "Comment");
				trNode.SetAttribute(STR_LABEL_ATTRIB, "Comment");
				trNode.Enable = ENABLE_READ_ONLY;
				/// end SAVE_INFO_AS_TREE
		  	}
		}
		trTags.Replace(trTemp.Clone(), true, true); /// Hong 12/20/06 SAVE_INFO_AS_TREE
		return true;
	}
	/// end MORE_ADD_TAG_TO_PLOT
	
	/// Hong 12/09/06 READ_MATH_CHANNEL
	bool GetMathChannelInfo(string& strName, string& strUnit, string& strFormular)
	{
		if( !m_header.nArithmeticEnable )//Math channel is disable
			return false;
		///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING tell the cache which DLL to use.
		OABF_SetABFVersion(m_header.nABFVersion);
		///end PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		char chName[ABF_ADCNAMELEN + 1];
		ABFH_GetMathChannelName(chName, ABF_ADCNAMELEN);
		chName[ABF_ADCNAMELEN] = 0;
		/// Hong 01/09/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
		//strName = chName;
		_init_string_from_mbcs(strName, chName);
		/// end FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
			
		string strOperator(m_header.sArithmeticOperator, ABF_ARITHMETICOPLEN);
		string strUnitTemp(m_header.sArithmeticUnits, ABF_ARITHMETICUNITSLEN);
		
		strUnit = strUnitTemp;
		
		string strChannelA, strChannelB;
		GetChannelName( m_header.nArithmeticADCNumA, strChannelA);
		GetChannelName( m_header.nArithmeticADCNumB, strChannelB);
		
		if( m_header.nArithmeticExpression )
		{	//Expression #0 (general purpose)
		 	//Result = (K1*A + K2) <op> (K3*B + K4)
			strFormular.Format("Result = (%f*(%s) + %f) %s (%f*(%s) + %f)", m_header.fArithmeticK1, strChannelA, 
				m_header.fArithmeticK2, strOperator, m_header.fArithmeticK3, strChannelB, m_header.fArithmeticK4);
		}
		else
		{	//Expression #1 (ratio dyes)
			//Result = (K1*R + K2) <op> (K3*R + K4)
			//R = (A + K5)/(B + K6)
			string strR;
			strR.Format("((%s) + %f)/((%s) + %f)", strChannelA, m_header.fArithmeticK5, strChannelB, m_header.fArithmeticK6);
			strFormular.Format("Result = (%f*(%s) + %f) %s (%f*(%s) + %f)", m_header.fArithmeticK1, strR, 
				m_header.fArithmeticK2, strOperator, m_header.fArithmeticK3, strR, m_header.fArithmeticK4);
		}
		return TRUE;
		
	}
	
	bool ReadOneSweepMathChannel(int nSweepNo, vector<float>& vData)
	{
		if( !m_header.nArithmeticEnable )//Math channel is disable
			return false;
		if( !checkSweepNo(nSweepNo) )
			return false;
		
		if(SWEEP_OFFSET)
		{
			nSweepNo = convertSweepIndexToSweepNo(nSweepNo);
		}

		int	nCurrentSweepSize;
		
		vData.SetSize(m_nMaxSamples);
		if( !ABF_ReadChannel( m_nFileHandle, &m_header, MATH_CHANNEL, nSweepNo, vData, &nCurrentSweepSize, NULL) ) 
			return false;
		
		vData.SetSize(nCurrentSweepSize);
		
		return true;
	}
	/// end READ_MATH_CHANNEL
	///Sophy 11/26/2013 ORG-9402-S1 PROPER_CLOSE_PCLAMP_FILE_WITH_CHECK
	BOOL	Close()
	{
		///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		//if ( 0 == m_nFileHandle )
		if ( m_nFileHandle < 0 ) // -1
		///end PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
			return FALSE;
		///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING tell the cache which DLL to use.
		OABF_SetABFVersion(m_header.nABFVersion);
		///end PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		int nError;
		if ( !ABF_Close(m_nFileHandle, &nError ) )
			return FALSE;
		///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		//m_nFileHandle = 0;
		m_nFileHandle = -1;
		///end PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		return TRUE;
	}
	///end PROPER_CLOSE_PCLAMP_FILE_WITH_CHECK
protected:
	//Open the data file for the instance of this class
	BOOL	Open()
	{
		int nError;
		m_nMaxSamples = 0;
		DWORD dwMaxEpi = 0;
		m_nDataFormat = ABF_INTEGERDATA;		//// AW 12/01/06 CHECK_FILE_DATA_TYPE
		int 	flags = ABF_DATAFILE;
		m_nFileHandle = -1;	///Sophy 11/22/2014 ORG-9424-P2 PROPER_LOAD_ABF_FILE_WITH_SMART_VERSION_DETECTING
		if( !ABF_ReadOpen(m_strFileNameMBCS, &m_nFileHandle, flags, &m_header, &m_nMaxSamples, &dwMaxEpi, &nError) )
		{
			///Sophy 8/19/2014 ORG-11755-S1 IMPROVE_ERRMSG_WITH_FILE_VERSION_CHECKING
			ASSERT(ABF_EBADPARAMETERS == nError);
			if ( m_header.fFileVersionNumber > ABF_CURRENTVERSION || ABF_EBADPARAMETERS == nError )
			{
				//m_strErrMsg = _L("The file version is higher than the one Origin currently supports. Import terminated.");
				warning_msg_box(_L("The file version is higher than the one Origin currently supports. Import terminated."), false, 'E');
			}
			///end IMPROVE_ERRMSG_WITH_FILE_VERSION_CHECKING
			return false; 
		}
		//// AW 12/01/06 CHECK_FILE_DATA_TYPE
		if ( !ABF_IsABFFile(m_strFileNameMBCS, &m_nDataFormat, &nError) )
			return false;
		//// END CHECK_FILE_DATA_TYPE
			
		return  TRUE;
	}
	
	//Close the data file for the instance of this class
	///Sophy 11/26/2013 ORG-9402-S1 PROPER_CLOSE_PCLAMP_FILE_WITH_CHECK
	//BOOL	Close()
	//{
		//int nError;
		//if( !ABF_Close( m_nFileHandle, &nError ) ) 
			//return false;
	//}
	///end PROPER_CLOSE_PCLAMP_FILE_WITH_CHECK
private:
	BOOL checkChannelNo(int nChannelNo)
	{
		if( nChannelNo >= m_nChannelNum )
			return FALSE;
		else
			return TRUE;
	}
	
	BOOL checkSweepNo(int nSweepNo)
	{
		if( nSweepNo >= m_nSweepNum )
			return FALSE;
		else
			return TRUE;
	}
	
	//In Origin, Sweep No is 0 offset, otherwise in pclamp file Sweep No is 1 offset
	int convertSweepIndexToSweepNo(int nSweepNo)
	{
		if(nSweepNo >= 0 )
			return nSweepNo+1;
		else
			return nSweepNo;
	}
	
	
private:
	string 			m_strFileName;
	string			m_strFileNameMBCS; /// Hong 01/06/2017 ORG-14435-S3 FIX_IMPORT_PCLAMP_FAIL_IN_UNICODE_ORIGIN
	int				m_nFileHandle;
	UINT			m_nMaxSamples;
	/// Hong 04/20/09 USER_ASK_FOR_PUBLIC_ACCESS_OF_HEADER_INFO, http://beta.originlab.com/forum/topic.asp?TOPIC_ID=2844
	//ABFFileHeader	m_header;
	/// end USER_ASK_FOR_PUBLIC_ACCESS_OF_HEADER_INFO
	int				m_nChannelNum;
	int				m_nSweepNum;
	BOOL			m_bValidPClamp;
	string			m_strErrMsg;	///Sophy 8/19/2014 ORG-11755-S1 IMPROVE_ERRMSG_WITH_FILE_VERSION_CHECKING
public:
	int				m_nDataFormat;		//// AW 12/01/06 CHECK_FILE_DATA_TYPE

	BOOL			m_bUseHoldingDuration;		/// Fisher 01/07/09 QA80-12413 ADD_HOLDING_DURATION_TIME_IN_PCLAMP
	/// Hong 04/20/09 USER_ASK_FOR_PUBLIC_ACCESS_OF_HEADER_INFO
	ABFFileHeader	m_header;
	/// end USER_ASK_FOR_PUBLIC_ACCESS_OF_HEADER_INFO
};
#endif//	PCLAMPFILE_H
