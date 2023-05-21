#pragma once
#include <list>

/*class observer {							//se escribe en función del modelo

public:
	observer() {};
	observer(const observer& orig) {};
	virtual void notify(void *) = 0;		//cada observer potencialmente va a hacer algo distinto
	virtual ~observer() {};


};

class subject {

public:
	subject() {}
	subject(const subject& orig) { observers = orig.observers; }

	void attach_obs(observer& o) {
		list <observer&>::iterator it = observers.end();
		observers.insert(it, o);
	}
	void dettach_obs(observer& o) {};

protected:
	void notify_all_obs(void* model) {
		for (observer& o : observers)
			o.notify(model);
	};

private:
	list <observer&> observers;


};*/

