#ifndef QRENCODER_H
#define QRENCODER_H
//
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

//
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// 
#define QR_VRESION_S	0 
#define QR_VRESION_M	1 
#define QR_VRESION_L	2 

#define MAX_ALLCODEWORD	 3706 
#define MAX_DATACODEWORD 2956 
#define MAX_CODEBLOCK	  153 
#define MAX_MODULESIZE	  177 

#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		
	int ncAllCodeWord;	
	int ncDataCodeWord;	

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////

typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   
	int ncAllCodeWord; 

	int ncDataCodeWord[4];	

	int ncAlignPoint;	
	int nAlignPoint[6];	

	RS_BLOCKINFO RS_BlockInfo1[4]; 
	RS_BLOCKINFO RS_BlockInfo2[4]; 

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////

class QrEncoder
{
public:
	QrEncoder();
	~QrEncoder();


public:
	int symbleSize() const;
	unsigned char at(int x, int y);

	int level() const;
	int version() const;
	bool autoExtent() const;
	int maskingNo() const;
private:
	int  m_nLevel;
	int  m_nVersion;
	bool m_bAutoExtent;
	int  m_nMaskingNo;

	int m_nSymbleSize;
	unsigned char m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]

	int m_ncDataCodeWordBit; 
	unsigned char m_byDataCodeWord[MAX_DATACODEWORD]; 

	int m_ncDataBlock;
	unsigned char m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; 
	unsigned char m_byAllCodeWord[MAX_ALLCODEWORD]; 
	unsigned char m_byRSWork[MAX_CODEBLOCK]; 

public:
	bool encodeData(int nLevel, int nVersion, bool bAutoExtent, int nMaskingNo, char* lpsSource, int ncSource = 0);

private:
	int encodeVersion(int nVersion, char* lpsSource, int ncLength);
	bool encodeSourceData(char* lpsSource, int ncLength, int nVerGroup);

	int bitLength(unsigned char nMode, int ncData, int nVerGroup);

	int setBitStream(int nIndex, unsigned short wData, int ncData);

	bool isNumeralData(unsigned char c);
	bool isAlphabetData(unsigned char c);
	bool isKanjiData(unsigned char c1, unsigned char c2);

	unsigned char alphabetToBinaly(unsigned char c);
	unsigned short kanjiToBinaly(unsigned short wc);

	void rsCodeWord(unsigned char * lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

private:
	void formatModule();

	void setFunctionModule();
	void setFinderPattern(int x, int y);
	void setAlignmentPattern(int x, int y);
	void setVersionPattern();
	void setCodeWordPattern();
	void setMaskingPattern(int nPatternNo);
	void setFormatInfoPattern(int nPatternNo);
	int countPenalty();
};


#endif // QRENCODER_H
