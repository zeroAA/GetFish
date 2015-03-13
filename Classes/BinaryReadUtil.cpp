//
//  BinaryReadUtil.cpp
//  Zengine
//
//  Created by zs on 15-2-19.
//
//

#include "BinaryReadUtil.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

BinaryReadUtil * BinaryReadUtil::create(const char * filePath)
{
	BinaryReadUtil *pRet = new BinaryReadUtil();
	if(pRet && pRet->init(filePath))
	{
		pRet->autorelease();
		return pRet;
	}
    
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool BinaryReadUtil::init(const char * filePath)
{
	std::string path = filePath;
	path = CCFileUtils::sharedFileUtils()->fullPathForFilename(path.c_str());
	
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	readFile = gzopen(path.c_str(),"rb");
	return readFile != NULL;
#else //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	fileData = NULL;
	fileLength = 0;
	fileCursor = 0;
    
	unsigned char* tempFileData = NULL;
	unsigned long tempFileLength = 0;
	tempFileData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &tempFileLength);
    
    if (!tempFileData) {
        CCLOG("tp : NULL");
    }
    
    
    if (tempFileData)
    {
        
        
//        //用libz进行解压缩
//        fileLength = ZipUtils::ccInflateMemory(tempFileData, tempFileLength, &fileData);
//        CC_SAFE_DELETE_ARRAY(tempFileData);

        fileData =tempFileData;
        fileLength =tempFileLength;
        fileCursor = 0;
        
        if (fileLength == 0)
        {
            CCLog("[BinaryReadUtil] warning: file length zero! file:%s", path.c_str());
        }
        return true;
    }
    else
    {
        return false;
    }
#endif
}

void BinaryReadUtil::close()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if(readFile){
		gzclose(readFile);
	}
#else //if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	CC_SAFE_DELETE_ARRAY(fileData);
#endif
	release();
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

int BinaryReadUtil::readInt(void)
{
	const int bufferLen = sizeof(int);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen] = {0};
        int len;
        len = gzread(readFile,buf, bufferLen);
        
        int res = 0;
        for (int i = 0 ;i < len; i++)
        {
            res<<= 8;
            res += (buf[i]&0xff);
        }
        
        return res;
    }
    return 0;
}
#else //if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
int BinaryReadUtil::readInt(void)
{
	const int bufferLen = sizeof(int);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen] = {0};
        int len;
        
        memcpy(buf, fileData+fileCursor, bufferLen);
        fileCursor += bufferLen;
        len = bufferLen;
        
        int res = 0;
        for (int i = 0 ;i < len; i++)
        {
            res <<= 8;
            res += (buf[i]&0xff);
        }
        
        return res;
    }
    
    return 0;
}
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
short BinaryReadUtil::readShort(void)
{
	const int bufferLen = sizeof(short);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        len = gzread(readFile,buf, bufferLen);
        
        short res = 0;
        for (int i = 0 ;i < len; i++)
        {
            res <<= 8;
            res += (buf[i] & 0xff);
        }
        return res;
    }
    return 0;
}
#else //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
short BinaryReadUtil::readShort(void)
{
	const int bufferLen = sizeof(short);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        
        memcpy(buf, fileData+fileCursor, bufferLen);
        fileCursor += bufferLen;
        len = bufferLen;
        
        short res = 0;
        for (int i = 0 ;i < len; i++)
        {
            res <<= 8;
            res += (buf[i] & 0xff);
        }
        return res;
    }
    return 0;
}
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

long BinaryReadUtil::readLong(void)
{
	const int bufferLen = sizeof(long);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        len = gzread(readFile,buf, bufferLen);
        
        long res = 0;
        for (int i = 0; i < len ; i++)
        {
            res <<= 8;
            res += (buf[i] & 0xff);
        }
        return res;
    }
    return 0;
}
#else //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
long BinaryReadUtil::readLong(void)
{
	const int bufferLen = sizeof(long);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        
        memcpy(buf, fileData+fileCursor, bufferLen);
        fileCursor += bufferLen;
        len = bufferLen;
        
        long res = 0;
        for (int i = 0; i < len ; i++)
        {
            res <<= 8;
            res += (buf[i] & 0xff);
        }
        return res;
    }
    return 0;
}
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
bool BinaryReadUtil::readBoolean(void)
{
	const int bufferLen = sizeof(bool);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        len = gzread(readFile,buf, bufferLen);
        
        bool res = false;
        res = (buf[0] != 0);
        return res;
    }
    return false;
}
#else //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
bool BinaryReadUtil::readBoolean(void)
{
	const int bufferLen = sizeof(bool);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        
        memcpy(buf, fileData+fileCursor, bufferLen);
        fileCursor += bufferLen;
        len = bufferLen;
        
        bool res = false;
        res = (buf[0] != 0);
        return res;
    }
    return false;
}
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
char BinaryReadUtil::readByte(void)
{
	const int bufferLen = sizeof(char);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        len = gzread(readFile,buf, bufferLen);
        
        char res = 0;
        
        res = buf[0];
        
        return res;
    }
    return 0;
}
#else //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
signed char BinaryReadUtil::readByte(void)
{
	const int bufferLen = sizeof(char);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        
        memcpy(buf, fileData+fileCursor, bufferLen);
        fileCursor += bufferLen;
        len = bufferLen;
        
        char res = 0;
        
        res = buf[0];
        
        return res;
    }
    return 0;
}
#endif

bool BinaryReadUtil::readBool(void)
{
    return readByte() != 0;
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
float BinaryReadUtil::readFloat(void)
{
	const int bufferLen = sizeof(float);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        len = gzread(readFile,buf, bufferLen);
        
        for(int i = 0 ; i < len/2 ; i++)
        {
            char temp = buf[i];
            buf[i] = buf[len -i -1];
            buf[len - i - 1] = temp;
        }
        
        float res = 0.0f;
        memcpy(&res, buf, bufferLen);
        return res;
    }
    return 0;
}
#else //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
float BinaryReadUtil::readFloat(void)
{
	const int bufferLen = sizeof(float);
    if (checkSize(bufferLen))
    {
        char buf[bufferLen];
        int len;
        
        memcpy(buf, fileData+fileCursor, bufferLen);
        fileCursor += bufferLen;
        len = bufferLen;
        
        for(int i = 0 ; i < len/2 ; i++)
        {
            char temp = buf[i];
            buf[i] = buf[len -i -1];
            buf[len - i - 1] = temp;
        }
        
        float res = 0.0f;
        memcpy(&res, buf, bufferLen);
        return res;
    }
    return 0;
}
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

bool BinaryReadUtil::readUtf(std::string &out)
{
	const int utfLen = readShort();
    if (checkSize(utfLen))
    {
        const int bufferLen = 1024;
        char buf[bufferLen];
        int have = 0;
        int len = 0;
        
        do
        {
            if(len <= utfLen - bufferLen){
                have = gzread(readFile,buf,bufferLen);
                out.append(buf,have);
                if(have != bufferLen){
                    CCLOG("Read utf from inputstream error: Not enough bytes!");
                    return false;
                }
                len += have;
            }else{
                have = gzread(readFile,buf, utfLen - len);
                out.append(buf,have);
                if(have != (utfLen -len))
                {
                    CCLOG("Read utf from inputstream error: Not enough bytes!");
                    return false;
                }
                len += have;
                break;
            }
        } while (true);
        
        if(len != utfLen)
        {
            CCLOG("Read utf from inputstream error: Not enough bytes!");
        }
        return true;
    }
    return false;
}

string BinaryReadUtil::readUtf()
{
    string out = "";
	const int utfLen = readShort();
    if (checkSize(utfLen))
    {
        const int bufferLen = 1024;
        char buf[bufferLen];
        int have = 0;
        int len = 0;
        
        do
        {
            if(len <= utfLen - bufferLen){
                have = gzread(readFile,buf,bufferLen);
                out.append(buf,have);
                if(have != bufferLen){
                    CCLOG("Read utf from inputstream error: Not enough bytes!");
                    return false;
                }
                len += have;
            }else{
                have = gzread(readFile,buf, utfLen - len);
                out.append(buf,have);
                if(have != (utfLen -len))
                {
                    CCLOG("Read utf from inputstream error: Not enough bytes!");
                    return false;
                }
                len += have;
                break;
            }
        } while (true);
        
        if(len != utfLen)
        {
            CCLOG("Read utf from inputstream error: Not enough bytes!");
        }
        return out;
    }
    return "";
}
#else //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
bool BinaryReadUtil::readUtf(std::string &out)
{
	const int utfLen = readShort();
    if (checkSize(utfLen))
    {
        const int bufferLen = 1024;
        char buf[bufferLen];
        int have = 0;
        int len = 0;
        
        do
        {
            if (len <= utfLen - bufferLen)
            {
                memcpy(buf, fileData+fileCursor, bufferLen);
                fileCursor += bufferLen;
                have = bufferLen;
                
                out.append(buf, have);
                if (have != bufferLen)
                {
                    return false;
                }
                len += have;
            }
            else
            {
                memcpy(buf, fileData+fileCursor, utfLen - len);
                fileCursor += utfLen - len;
                have = utfLen - len;
                
                out.append(buf,have);
                if (have != (utfLen -len))
                {
                    //				CCLOG("Read utf from inputstream error: Not enough bytes!");
                    return false;
                }
                len += have;
                break;
            }
        } while (true);
        
        if(len != utfLen)
        {
            //		CCLOG("Read utf from inputstream error: Not enough bytes!");
        }
        return true;
    }
    return false;
}

string BinaryReadUtil::readUtf()
{
    string out = "";
	const int utfLen = readShort();
    if (checkSize(utfLen))
    {
        const int bufferLen = 1024;
        char buf[bufferLen];
        int have = 0;
        int len = 0;
        
        do
        {
            if (len <= utfLen - bufferLen)
            {
                memcpy(buf, fileData+fileCursor, bufferLen);
                fileCursor += bufferLen;
                have = bufferLen;
                
                out.append(buf, have);
                if (have != bufferLen)
                {
                    return false;
                }
                len += have;
            }
            else
            {
                memcpy(buf, fileData+fileCursor, utfLen - len);
                fileCursor += utfLen - len;
                have = utfLen - len;
                
                out.append(buf,have);
                if (have != (utfLen -len))
                {
                    //				CCLOG("Read utf from inputstream error: Not enough bytes!");
                    return false;
                }
                len += have;
                break;
            }
        } while (true);
        
        if(len != utfLen)
        {
            //		CCLOG("Read utf from inputstream error: Not enough bytes!");
        }
        return out;
    }
    return "";
}

#endif

void BinaryReadUtil::readBytes(unsigned char * data, int length)
{
    if (checkSize(length))
    {
        memcpy(data, fileData+fileCursor, length);
        fileCursor += length;
    }
}

// readUtf crash sometimes, I'll check this latter
bool BinaryReadUtil::checkSize(int size)
{
    return  fileCursor + size <= fileLength;
}
