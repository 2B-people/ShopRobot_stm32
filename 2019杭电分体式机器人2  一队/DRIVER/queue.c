#include "queue.h"

void initQueue(queue *pque)
{
	pque->front = pque->endline = 0;//清空队列
}
//入队
void enQueue(queue *pque, datatype data) 
{
	//判断队列是否溢出
	if (pque->endline < EN)
	{
		//判断队列是否为空
		if (pque->front == pque->endline)//队头和队尾重合表明没有元素
		{
			//初始化队列
			initQueue(pque);
		}
		pque->data[pque->endline] = data;
		pque->endline += 1;
	}
	else		
	{
		return;
	}

}
//出队
void deQueue(queue *pque)
{
	//判断队列是否为空
	if (pque->front == pque->endline)
	{
		//队列为空
		return;
	}
	else {
		//直接弹出最后一个
		pque->front += 1;
	}
}
