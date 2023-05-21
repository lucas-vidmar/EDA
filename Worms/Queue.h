#pragma once
#include "EventGenerator.h"
#define ARRAYLONG 10



class Queue
{
	public:
	Queue();
	~Queue();


	/*----------Funciones de la cola----------*/
	eventType get_next_ev();			//Devuelve evento de la cola
	void put_event(eventType event);	//pone un evento en la cola		un eventType seria eventType::Walking
	bool isQueueEmpty();				//pregunta si la cola esta vacia
	bool isQueueFull();					//pregunta si la cola esta llena
	/*-----------------------------------------*/

	
	void print(void);

	private:
	eventType queue[ARRAYLONG];		//Cola de eventos, puede almacenar hasta 1000 eventos
	eventType * pFirstEv;
	eventType * pLastEv;
	eventType * get_pFirst() { return pFirstEv; };
	eventType * get_pLast() { return pLastEv; };
	eventType get_queue_ev(int i) { return queue[i]; };
	void inc_pointer_queue(eventType** p);


};

