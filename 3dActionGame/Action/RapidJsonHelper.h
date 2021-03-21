#pragma once

#include "document.h"
#include "filereadstream.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


/*
@fn  jsonファイルのオープン
@param _inputDocument rapidJsonオブジェクト
@param _inFileName オープンしたいJsonファイルパス
return ファイルを開くことができたか
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName);

/*
@fn  Doc内にそのメンバーは存在するか？
@param _inDocument rapidJsonオブジェクト
@param _memberName メンバ名
@return Documentにメンバ名が含まれていたかどうか
*/
bool IsExistMember(const rapidjson::Document& _inDoc, const char* _memberName);

/*
@fn そのメンバーが存在し、かつ値が一致するか？
@param _inDocument ドキュメント
@param _menberName メンバー名
@param _matchValue 調べたいメンバー名にマッチする値
@return  memberNameに対応する値がmatchValueだったときのみtrueを返す
*/
bool IsExistMemberAndValue(const rapidjson::Document& _inDoc, const char* _memberName, const char* _matchValue);

/*
@param _inDocument
@param _menberName
@return Document内にメンバ名が含まれるか
*/
bool IsExistArrayName(const rapidjson::Document& _inDoc, const char* _memberName);


// Value値を強制的にFloat値として取得
float ForceGetFloat(const rapidjson::Value& _val);
