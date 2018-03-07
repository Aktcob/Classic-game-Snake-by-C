#pragma once
#include "Ge.h"

class CSnake
{
private:

public:
	CSnake(void);
	virtual ~CSnake(void);
public:
	CString mm_string;
	int Time;
	int power;
	int m_marks;//分数
	CString m_string;//字符串
	int n;//蛇身长度
	CGe body[600];//蛇身数组
	int direction;//蛇前进方向：1代表向上，2代表向右，3代表向下，4代表向左
public:
	CGe forwardup();//向上前进
	CGe forwardright();//向右前进
	CGe forwarddown();//向下前进
	CGe forwardleft();//向左前进
	bool IsBeanInSnake(int, int);
	bool SnakeEatBean(int, int);
	bool GameLose(CSnake);
	bool IsHeadPengShen(CSnake);

};
