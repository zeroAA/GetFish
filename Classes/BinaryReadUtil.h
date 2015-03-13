//
//  BinaryReadUtil.h
//  Zengine
//
//  Created by zs on 15-2-19.
//
//

#ifndef _BINARY_READ_UTIL_
#define _BINARY_READ_UTIL_

#include "platform/CCFileUtils.h"
#include "support/zip_support/ZipUtils.h"
#include <zlib.h>
#include "cocos2d.h"
using namespace std;

class BinaryReadUtil :public cocos2d::CCObject
{
public:
	static BinaryReadUtil * create(const char * filePath);
	void close(void);

	int readInt(void);
	short readShort(void);
	long readLong(void);
	bool readBoolean(void);
	signed char readByte(void);
    bool readBool(void);
	float readFloat(void);
	bool readUtf(std::string &out);
    string readUtf();
    void readBytes(unsigned char * data, int length);
    
    unsigned long getFileLength() { return fileLength; }

protected:
    bool checkSize(int size);
    
private:
	bool init(const char * filePath);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	gzFile readFile;
#else //if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	unsigned char* fileData;
	unsigned long fileLength;
	unsigned long fileCursor;
#endif
};

#endif