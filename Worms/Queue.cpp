#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue()
{
	for (int i = 0; i < ARRAYLONG; i++)	//coloco en la cola todos elementos vacios
	{
		queue[i] = eventType::Empty;
	}
	pFirstEv = queue;
	pLastEv = pFirstEv;
}


Queue::~Queue()
{
}

void Queue::print(void)
{
	for (int i = 0; i < ARRAYLONG; i++)
		cout << (int)get_queue_ev(i);

	cout << endl;
	return;
}

eventType Queue::get_next_ev() {	//devuelve el siguient evento y pone al puntero al siguiente evento

	if (!isQueueEmpty())
	{
		while(*get_pFirst()==eventType::Empty)
		{ 
			inc_pointer_queue(&pFirstEv);
		}
		eventType pTemp = *(get_pFirst());	//guardo elemento a devolver
		*pFirstEv = eventType::Empty;		//cambio contenido de posicion por elemento vacio
		inc_pointer_queue(&pFirstEv);		//puntero ahora apunta al siguiente elemento
		return pTemp;
	}

	return eventType::Empty;
}



bool Queue::isQueueEmpty()	//determina si la cola esta totalmente vacia
{
	for (int i = 0; i < ARRAYLONG; i++)
		if (get_queue_ev(i) != eventType::Empty)
			return false;

	return true;
}

bool Queue::isQueueFull()	//determina si la cola esta totlamente llena
{
	for (int i = 0; i < ARRAYLONG; i++)
		if (get_queue_ev(i) == eventType::Empty)
			return false;

	return true;
}


void Queue::inc_pointer_queue(eventType** p){

	
	if (isQueueEmpty())
	{
		return;
	}
	
	if (*p == (queue + ARRAYLONG))
	{
		*p = queue;
		return;
	}
	else
	{
		cout << *p << " " ;
		(*p)++;
		cout << *p << endl;
		return;
	}
	

}


void Queue::put_event(eventType event)
{
	if (!isQueueFull())
	{
		inc_pointer_queue(&pLastEv);
		*pLastEv = event;
	}
	return;
}