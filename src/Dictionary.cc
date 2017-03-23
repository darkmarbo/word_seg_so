﻿#include "stdafx.h"
#include <fstream>
#include <stdio.h>

#include "Dictionary.h"
#include "StringUtil.h"


Dictionary::Dictionary(void): maxLen(0), coreDictPath("dict.txt")
{
	//this->coreDictPath = "resource/dict/core.dic.wordlist";
	cout << "Here, construct dictionary!"<< endl;
	loadDict(this->coreDictPath);
}

Dictionary::Dictionary(string dictPath): maxLen(0)
{
	this->coreDictPath = dictPath;
	loadDict(this->coreDictPath);
}


Dictionary::~Dictionary(void)
{
}

void Dictionary::loadDict(string dictPath)
{
	////locale china("chs"); //use china character
	////wcout.imbue(china);

	////setlocale(LC_ALL, "chs");

	//wifstream dictFile;
	////dictFile.imbue(china);
	//dictFile.open(dictPath, ios::in);
	//if(!dictFile.is_open())
	//{
	//	wcerr<<"Unable to open dictFile: "<<dictPath<<" . now exit!"<<endl;
	//	exit(-1);
	//}
	//wstring line;
	//unsigned int lineNum = 0;
	//while(getline(dictFile, line, L'\n'))
	//{
	//	lineNum += 1;
	//	if(line.length()==0)
	//	{
	//		continue;
	//	}

	//	wstring temp_line = line;

	//	//wcout<<"len="<<line.length()<<", "<<line<<endl;
	//	wcout<<"len="<<temp_line.length()<<", lineNum="<<lineNum<<", line="<<line<<endl;

	//	vector<wstring> res;
	//	util::split(res, line);
	//	if(findword(res[0])==-1)
	//	{
	//		coredict.insert(make_pair(res[0], 1));
	//		if(res[0].length() > maxlen)
	//		{
	//			maxlen = res[0].length();
	//			//wcout<<"len="<<maxlen<<", "<<res[0]<<endl;
	//			//wcout<<"len="<<maxlen<<", linenum="<<linenum<<endl;
	//		}
	//	}
	//}


	cout << "Here, load dict!"<< endl;
	cout << "coreDictPath:\t" << this->coreDictPath << endl;

	const int ENTRY_BUFF_SIZE = 4096;
	char buff[ENTRY_BUFF_SIZE];

	FILE* fp = fopen(dictPath.c_str(), "r");
	UTF8Util::SkipUtf8Bom(fp);

	size_t lineNum = 1;
	while(fgets(buff, ENTRY_BUFF_SIZE, fp))
	{
		const char* inbuff = buff;
		size_t length;

		const char* pbuff = UTF8Util::FindNextInline(inbuff, '\t');
		if(UTF8Util::IsLineEndingOrFileEnding(*pbuff))
		{
		}

		
		length = static_cast<size_t>(pbuff-inbuff);
		string key = UTF8Util::FromSubstr(inbuff, length);
	
		coreDict.insert(make_pair(key, 1));
		size_t key_length = UTF8Util::StrCharLength(key.c_str());
		if(key_length > maxLen)
		{
			maxLen = key_length;
			//cout << key << " \tLen="<<key_length<<endl;
		}

		//cout << key << endl;
		lineNum += 1;

	}

    // todo 添加数字 
    for(int ii=0; ii<100001; ii++)
    {
        char tmp[1024] = {0};
        snprintf(tmp,1024,"%d",ii);
        string key = tmp; 
        coreDict.insert(make_pair(key, 1));
    }

	fclose(fp);
}

int Dictionary::FindWord(string word)
{
	if(coreDict.find(word) != coreDict.end())
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int Dictionary::getMaxLen()
{
	return maxLen;
}
