/**********************************************************************
* 版权所有 (C)2016, Zhou Zhaoxiong。
*
* 文件名称： StringContains.c
* 文件标识： 无
* 内容摘要： 测试一个字符串是否是另一个字符串的子串
* 其它说明： 例如, "ABC"是"ABCD"的子串
* 当前版本： V1.0
* 作    者： Zhou Zhaoxiong
* 完成日期： 20160216
*
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>

// 重新定义数据类型
typedef signed   char       INT8;
typedef unsigned short int  UINT16;
typedef          int        INT32;
typedef unsigned int        UINT32;

// 存放字符串中的字符和格式的结构体
typedef struct
{
    INT8   szStrCharArray[101][2];     // 字符串中不相同的字符的存放数组，最大支持100个
    INT32  iStrCharCount;              // 字符串中不相同的字符的个数
} StrInfo_T;

StrInfo_T gtLongerStrInfo  = {0};
StrInfo_T gtShorterStrInfo = {0};


// 函数声明
void GetStrChar(INT8 *pszInputStr, INT32 iProcessFlag);
INT32 JudgeIfContainsStr();


/**********************************************************************
* 功能描述： 主函数
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 0-执行成功   其它-执行失败
* 其它说明： 无
* 修改日期        版本号       修改人          修改内容
* -----------------------------------------------------------------
* 20160216        V1.0     Zhou Zhaoxiong        创建
***********************************************************************/
INT32 main()
{
    INT8   szLongerStr[500]   = {0};
    INT8   szShorterStr[100]  = {0};
    
    UINT32 iContainFlag = 1;     // 包含标志, 1-包含, 0-不包含
    
    printf("Please input the longer string: \n");
    scanf("%s", szLongerStr);
    printf("LongerStr=%s\n", szLongerStr);

    printf("Please input the shorter string: \n");
    scanf("%s", szShorterStr);
    printf("ShorterStr=%s\n", szShorterStr);

    // 如果ShorterStr的长度大于LongerStr, 则直接返回
    if (strlen(szShorterStr) > strlen(szLongerStr))
    {
        printf("%s is longer than %s, please check!\n", szShorterStr, szLongerStr);
        return -1;
    }
    
    // 获取较长的字符串中的不同的字符
    GetStrChar(szLongerStr, 1);

    // 获取较短的字符串中的不同的字符
    GetStrChar(szShorterStr, 2);

    iContainFlag = JudgeIfContainsStr();
    if (iContainFlag == 0)
    {
        printf("%s doesn't contain %s!\n", szLongerStr, szShorterStr);
    }
    else
    {
        printf("%s contains %s!\n", szLongerStr, szShorterStr);
    }
    
    return 0;            
}


/**********************************************************************
* 功能描述： 获取字符串中不相同的字符及其个数
* 输入参数： pszInputStr-输入字符串
             iProcessFlag-处理标志(1:处理长字符串, 2:处理短字符串)
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期          版本号         修改人           修改内容
* ---------------------------------------------------------------
* 20160216          V1.0       Zhou Zhaoxiong        创建
***********************************************************************/
void GetStrChar(INT8 *pszInputStr, INT32 iProcessFlag)
{
    INT32  iCharCount      = 0;                // 字符个数
    INT8   szInputStr[501] = {0};
    INT8   szCharBuf[2]    = {0};              // 存放单个字符的缓存
    INT32  iRepeatFlag     = 0;
    UINT32 iStrPosFlag     = 0;
    UINT32 iLoopFlag       = 0;
    UINT32 iInputStrLen    = 0;

    if (pszInputStr == NULL)
    {
        return;
    }

    iInputStrLen = strlen(pszInputStr);
    if (iInputStrLen >= 500)  // 最大支持100个字母
    {
        return;
    }

    memcpy(szInputStr, pszInputStr, iInputStrLen);

    iCharCount = 0;

    for (iStrPosFlag = 0; iStrPosFlag < iInputStrLen; iStrPosFlag ++)
    {
        iRepeatFlag = 0;
        
        // 判断正要获取的字符是否已经存在了
        memset(szCharBuf, 0x00, sizeof(szCharBuf));
        memcpy(szCharBuf, szInputStr+iStrPosFlag, 1);

        // 若与之前已经加入的字符重复, 则忽略
        for (iLoopFlag = 0; iLoopFlag < iCharCount; iLoopFlag ++)
        {
            if (iProcessFlag == 1)    // 处理长字符串
            {
                if (0 == strncmp(gtLongerStrInfo.szStrCharArray[iLoopFlag], szCharBuf, 1))
                {
                    iRepeatFlag = 1;  // 有重复的, 直接忽略
                    break;
                }
            }
            else                     // 处理短字符串
            {
                if (0 == strncmp(gtShorterStrInfo.szStrCharArray[iLoopFlag], szCharBuf, 1))
                {
                    iRepeatFlag = 1;  // 有重复的, 直接忽略
                    break;
                }
            }
        }

        if (1 == iRepeatFlag)
        {
            continue;
        }

        if (iProcessFlag == 1)    // 处理长字符串
        {
            strncpy(gtLongerStrInfo.szStrCharArray[iCharCount], szCharBuf, 1);
        }
        else                      // 处理短字符串
        {
            strncpy(gtShorterStrInfo.szStrCharArray[iCharCount], szCharBuf, 1);
        }

        iCharCount = iCharCount + 1;
    }

    if (iProcessFlag == 1)    // 处理长字符串
    {
        gtLongerStrInfo.iStrCharCount = iCharCount;
    }
    else                      // 处理短字符串
    {
        gtShorterStrInfo.iStrCharCount = iCharCount;
    }

    return;
}


/**********************************************************************
* 功能描述： 判断长字符串是否包含了短字符串
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 1-包含了 0-没有包含
* 其它说明： 无
* 修改日期          版本号         修改人           修改内容
* ---------------------------------------------------------------
* 20160216          V1.0       Zhou Zhaoxiong        创建
***********************************************************************/
INT32 JudgeIfContainsStr()
{
    UINT32 iLongerLoopFlag    = 0;
    UINT32 iShorterLoopFlag   = 0;
    UINT32 iCharIdenticalFlag = 0;

    // 判断较短的字符串中的字符是否全部都在较长的字符串中的字符中
    for (iShorterLoopFlag = 0; iShorterLoopFlag < gtShorterStrInfo.iStrCharCount; iShorterLoopFlag ++)
    {
        iCharIdenticalFlag = 0;
        for (iLongerLoopFlag = 0; iLongerLoopFlag < gtLongerStrInfo.iStrCharCount; iLongerLoopFlag ++)
        {
            if (strcmp(gtShorterStrInfo.szStrCharArray[iShorterLoopFlag], gtLongerStrInfo.szStrCharArray[iLongerLoopFlag]) == 0)
            {
                iCharIdenticalFlag = 1;    // 字符相同
                break;
            }
        }

        if (iCharIdenticalFlag == 0)     // 表示两个字符串中有不相同的字符
        {
            return 0;
        }
    }

    return 1;
}
