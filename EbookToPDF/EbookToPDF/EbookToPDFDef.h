#define DStringBufferSize 256

#define DStrSuccess L"Success"
#define DStrError	L"Error"

#define DStrImagePath "Image\\"

struct TMonitorData
{	
	int iStartX;
	int iStartY;
	int iMonitorWidth;
	int iMonitorHeight;
	wchar_t wcharMonitorName[DStringBufferSize];

	TMonitorData()
	{
		memset(&wcharMonitorName, 0x00, DStringBufferSize);
		iMonitorWidth = 0;
		iMonitorHeight = 0;
	}
};