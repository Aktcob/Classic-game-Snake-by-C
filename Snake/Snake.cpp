#include "StdAfx.h"
#include "Snake.h"

CSnake::CSnake(void)
{
}

CSnake::~CSnake(void)
{
}

CGe CSnake::forwardup()
{
	CGe ret = body[n - 1];
	for (int i = n - 1; i >= 1; i--)
	{
		body[i].i = body[i - 1].i, body[i].j = body[i - 1].j;
	}
	body[0].i--;
	return ret;
}

CGe CSnake::forwardright()
{
	CGe ret = body[n - 1];
	for (int i = n - 1; i >= 1; i--)
	{
		body[i].i = body[i - 1].i, body[i].j = body[i - 1].j;
	}
	body[0].j++;
	return ret;
}

CGe CSnake::forwarddown()
{
	CGe ret = body[n - 1];
	for (int i = n - 1; i >= 1; i--)
	{
		body[i].i = body[i - 1].i, body[i].j = body[i - 1].j;
	}
	body[0].i++;
	return ret;
}

CGe CSnake::forwardleft()
{
	CGe ret = body[n - 1];
	for (int i = n - 1; i >= 1; i--)
	{
		body[i].i = body[i - 1].i, body[i].j = body[i - 1].j;
	}
	body[0].j--;
	return ret;
}
bool  CSnake::IsBeanInSnake(int m, int n)
{
	bool flag = false;
	for (int i = 0; i<n; i++)
	{
		if (m == body[i].i&&n == body[i].j)
		{
			flag = true;
			break;
		}

	}
	return flag;

}

bool CSnake::SnakeEatBean(int m, int n)
{
	bool flag = false;
	if (body[0].i == m&&body[0].j == n)
	{
		flag = true;
		//this->m_marks+=100;
	}
	else
	{
		flag = false;
	}
	return flag;
}

bool CSnake::GameLose(CSnake snake)
{
	if (body[0].i == -1 || body[0].i == 21 || body[0].j == -1 || body[0].j == 31 || IsHeadPengShen(snake) == true)
	{
		return true;
	}
	else
	{
		return false;
	}


}

bool CSnake::IsHeadPengShen(CSnake snake)
{
	bool flag = false;
	for (int i = 1; i<n; i++)
	{
		if (body[0].i == body[i].i&&body[0].j == body[i].j)
		{
			flag = true;
			break;
		}
		if (body[0].i == snake.body[i].i&&body[0].j == snake.body[i].j){
			flag = true;
			break;
		}
	}
	return flag;

}
