#include <stdio.h>

typedef struct{
	char nombre [20];
	int socket;
} Conectado;
typedef struct{
	Conectado conectados [100];
	int num;
} ListaConectados;

int Pon (ListaConectados *lista, char nombre[20], int socket){
	if(lista->num == 100)
		return -1;	
	else {
		strcpy (lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		return 0;
	}
}

int DameSocket(ListaConectados *lista, char nombre[20]){
	int i=0;
	int encontrado = 0;
	while ((i< lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre, nombre)==0)
			encontrado =1;
		if (!encontrado)
			i=i+1;
	}
	if (encontrado)
		return lista->conectados[i].socket;
	else
		return -1;
}
	
	int DamePosicion(ListaConectados *lista, char nombre[20]){
		int i=0;
		int encontrado = 0;
		while ((i< lista->num) && !encontrado)
		{
			if (strcmp(lista->conectados[i].nombre, nombre)==0)
				encontrado =1;
			if (!encontrado)
				i=i+1;
		}
		if (encontrado)
			return i;
		else
			return -1;
	}
		
	

int Elimina(ListaConectados *lista, char nombre[20]){
	int pos = DamePosicion (lista, nombre);
	if (pos == -1)
		return -1;
	else{
		int i;
		for (i=pos; i<lista->num-1; i++)
		{
			strcpy (lista->conectados[i].nombre, lista->conectados[i+1].nombre);
			lista->conectados[i].socket = lista->conectados[i+1].socket;
		}
		lista->num--;
		return 0;
		
	}
}

void DameConectados (ListaConectados *lista, char conectados[300]){
	sprintf (conectados, "%d", lista->num);
	int i;
	for (i=0; i< lista->num; i++)
		sprintf (conectados, "%s/%s", conectados, lista->conectados[i].nombre);
	
}

void DameSocketUsuarios (ListaConectados *lista, char jugadores [300], char socket){
	char *p =strtok (jugadores, ",");
	while (p!=NULL)
	{
		int pos = DamePosicion(lista, p);
		if (pos!=-1)
		{
			sprintf(socket, "%s, %d", socket, lista->conectados[pos].socket);
			
		}
		p = strtok (NULL, ",");
	}
}



		
		
int main(int argc, char *argv[]) {
	ListaConectados miLista;
	miLista.num=0;
	Pon (&miLista, "Luis", 3);
	Pon (&miLista, "Maria", 4);
	Pon (&miLista, "Carlos", 30);
	int res = Pon (&miLista, "Juan", 5);
	if (res == -1)
		printf("Lista llena. No se puede añadir.\n");
	else
		printf("Añadido bien.\n");
		
	int socket = DameSocket (&miLista, "Pedro");
	if (socket != -1)
		printf ("El socket de Pedro es: %d\n", socket);
	else
		printf("Ese usuario no esta en la lista.\n");
	int pos = DamePosicion (&miLista, "Luis");
	if (socket != -1)
		printf ("El socket de Pedro es: %d\n", miLista.conectados[pos].socket);
	else
		printf("Ese usuario no esta en la lista.\n");
	
	res = Elimina(&miLista, "Luis");
	if(res == -1)
		printf ("No está.\n");
	else
		printf ("Eliminado.\n");
	char misConectados [300];
	DameConectados (&miLista, misConectados);
	printf("Resultado: %s\n", misConectados);
	
	char misJugadores [300];
	DameSocketUsuarios (&miLista, misJugadores, 3);
	printf ("Resultado: %s\n", misJugadores);
	
	char *p = strtok (misConectados, '/');
	printf ("11111\n");
	int n = atoi (p);
	printf ("22222\n");
	int i;
	for (i=0; i<n; i++){
		char nombre [20];
		p = strtok (NULL, '/');
		strcpy (nombre, p);
		printf ("Conectado: %s\n", nombre);
	}

	return 0;
	
}

