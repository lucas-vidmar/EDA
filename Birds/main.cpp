#include "allegro.h"
#include "Bird.h"
#include "ParseCmdLine.h"

#define MAXBIRDS 100
#define MAXJIGGLE 2
#define MAXEYE 10


static int parsing(int argc,const char *argv[], char userData[MAXOPTIONS][2][MAXLENGTH]);
int parseCallBack(const char* key, const char* value, void* datosDeUsuario);
static void change(bool increment, double* thing, double limit_t, double limit_b);

double randomNum(double min, double max);

int main(int argc,const char * argv[]) 
{
	char userData[MAXOPTIONS][2][MAXLENGTH] = { {{0}} }; //Arreglo de strings donde se guardan los parametros
	int total_of_birds=7;
	int rand_jiggle_limit=2, eye_sight=10;

	if (int parseCmdLine_Return = parsing(argc, argv, userData) == CB_SUXS)
	{
		for (int i = 0; i < 3; i++) {
			printf("%d",i);
			if (!strcmp(userData[i][0], "birds")) //si es birds
				total_of_birds = atoi(userData[i][1]);
			else if (!strcmp(userData[i][0], "jiggle")) //si es birds
				rand_jiggle_limit = atoi(userData[i][1]);
			else if (!strcmp(userData[i][0], "eyesight")) //si es birds
				eye_sight = atoi(userData[i][1]);
		}

		int mode = 1;
		int key;	
		double jiggle = randomNum(INF_LIMIT, rand_jiggle_limit);		//Keyboard key presed
		ALLEGRO_EVENT_QUEUE *event_queue = NULL;	//Allegro queue for keyboard events
		
		//Allegro and background Initialization. 
		//Queue initalization and register event source
		allegroEssentials_t allegro(WIDTH, HEIGHT);
		background_t fondo(WIDTH, HEIGHT);
		backgroundUpdate(&allegro, &fondo);
		al_flip_display();
		if (!(event_queue = al_create_event_queue()))
		{
			fprintf(stderr, "Creacion de fila de eventos fallida \n");
			al_destroy_event_queue(event_queue);
			return -1;
		}
		al_register_event_source(event_queue, al_get_keyboard_event_source());

		srand(time(NULL));		//Initialization for random number generator
		
		Bird* tweety = (Bird*)malloc(total_of_birds * sizeof(Bird)) ; //Reserve memory for tweeties
		
		for (int i = 0; i < total_of_birds; i++)  //Building tweeties
		{
			if (mode)
			{
				Bird tweety_c (WIDTH, HEIGHT);			//Inicializate a bird with 2 randoms arguments to generate 2 randoms positions
				memcpy((tweety + i), &tweety_c, sizeof(Bird));		//Copy values to ebject value
			}
			else
			{
				Bird tweety_c(DEFAULT_SPEED,WIDTH, HEIGHT);			//Inicializate a bird with 2 randoms arguments to generate 2 randoms positions
				memcpy((tweety + i), &tweety_c, sizeof(Bird));		//Copy values to ebject value
			}

		}

		do
		{
			backgroundUpdate(&allegro, &fondo);
			key = get_keyboard(event_queue);

			if (key == ALLEGRO_KEY_Q)
			{
				for (int i = 0; i < total_of_birds; i++)	//filling position vectors
				{
					tweety[i].speechChange(true); //incrementa
				}
			}
			else if (key == ALLEGRO_KEY_A)
			{
				for (int i = 0; i < total_of_birds; i++)	//filling position vectors
				{
					tweety[i].speechChange(false); //incrementa
				}
			}
			else if (key == ALLEGRO_KEY_W)
			{
				eye_sight++;
			}
			else if (key == ALLEGRO_KEY_S)
			{
				if (eye_sight - 1 > 0)
				{
					eye_sight--;
				}
			}
			else if (key == ALLEGRO_KEY_E)
			{
				if (jiggle + 1 < rand_jiggle_limit) {
					jiggle++;
				}
			}
			else if (key == ALLEGRO_KEY_D)
			{
				if (jiggle - 1 < 0)
				{
					jiggle--;
				}
			}
			else if (key == ALLEGRO_KEY_M)
			{
				for (int i = 0; i < total_of_birds; i++)	//filling position vectors
				{
					tweety[i].setSpeed(DEFAULT_SPEED); //incrementa
				}
			}
			else if (key == ALLEGRO_KEY_N)
			{
				for (int i = 0; i < total_of_birds; i++)	//filling position vectors
				{
					tweety[i].setRandomSpeed(); //incrementa
				}
			}

			for (int i = 0; i < total_of_birds; i++)	//filling position vectors
			{
				objectUpdate(&allegro, &fondo, tweety, i);
			}   
			for (int i = 0; i < total_of_birds; i++)	//filling position vectors
			{
				tweety[i].project(tweety, total_of_birds, eye_sight, jiggle);
				tweety[i].moveBird(WIDTH, HEIGHT);
			}   
		} while (key != ALLEGRO_KEY_ESCAPE);

		al_destroy_event_queue(event_queue);
		endAllegro(&allegro);	//Delete display and allegro features
		free(tweety);   //Free Malloc memory	
	}
	else
	{
		printf("Sintaxis o valores incorrectos\n");
	}

	return 0;
}

static int parsing(int argc,const char *argv[], char userData[MAXOPTIONS][2][MAXLENGTH]) {

	int total = parseCmdLine(argc, argv, parseCallBack, userData);	//cantidad de opciones y parametros encontrados
	
	if (total == XERROR)
	{
		printf("Data entry error.\n");

		return CB_ERR; //there was an error, abort
	}
	printf("Data entry success.\n");


	printf("\n");
	for (int i = 0; i < (total); i++) //imprime en pantalla las opciones y parametros ingresados
		printf("Key %d: %s \t| Value %d: %s \n", i, userData[i][0], i, userData[i][1]);

	return CB_SUXS;
}

int parseCallBack(const char* key, const char* value, void* datosDeUsuario)
{

	char data[MAXOPTIONS][2][MAXLENGTH] = { {{0}} }; //utilizamos otro arreglo temporaneo para no confundirnos
	memcpy(data, datosDeUsuario, MAXOPTIONS*MAXLENGTH * 2 * (sizeof(char))); //igualamos los arreglos
	int ultimoValor = lastValue(data); //miro el ultimo valor

	if ((ultimoValor) == (MAXOPTIONS - 1))
	{
		printf("Supero el limite de %d opciones/parametros\n", MAXOPTIONS);
		return CB_ERR;
	}

	//checking if key is valid
	if (key != NULL) //es opcion
	{
		if (validKey(key)) //check if key is valid
		{
			strcpy(data[ultimoValor][0], key);
		}
		else //key not valid
			return CB_ERR;
	}

	//checking if value is valid
	if (value != NULL)
	{
		if (validValue(value)) //check if value is valid
		{
			strcpy(data[ultimoValor][1], value);
		}
		else //value not valid
			return CB_ERR;
	}
	else //value cant be null
		return CB_ERR;

	//key and value were ok
	memcpy(datosDeUsuario, data, MAXOPTIONS*MAXLENGTH * 2 * (sizeof(char))); //volvemos a igualar los arreglos

	return CB_SUXS;
}

//recibe true si queres incrementar y un puntero a la variable, el limite superior y el limite inferior
//ya hay defines para velocidad MAX_SPEED y INF_LIMIT, habria que mandar esas cosas
static void change(bool increment, double* thing,double limit_t, double limit_b){
	if (increment) {
		if (*thing + 1 < limit_t) {
			*thing++;
		}
	}
	else {
		if (*thing - 1 > limit_b) {
			*thing--;
		}
	}
}

double randomNum(double min, double max) {
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}
