//
//  ShellManage.cpp
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#include "ShellManage.h"
#include "Shell.h"


ShellManage::ShellManage()
{
    
}

ShellManage::~ShellManage()
{
    
}

bool ShellManage::init()
{
    if(!ActorManage::init()) {
        return  false;
    }
    
    return true;
}

void ShellManage::addShell(const char *name, CCPoint pos,std::vector<int> item,int openTime,int closeTime)
{
//    Shell* shell = Shell::create(name, pos, itemID);
    
//    addActor(shell);
}