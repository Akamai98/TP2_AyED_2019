#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>

using namespace std;

string preparar_palabra(string);

int compara_strings(string,string);
int comp_ins = 0, comp_arbol = 0, comp_QS = 0;

//Nodo para palabras
class Nodo_palabra
{
	private:
		string palabra;
		int cantidad_repeticiones;
		Nodo_palabra* hijo_izq;
		Nodo_palabra* hijo_der;
		Nodo_palabra* next_alf;
		Nodo_palabra* next_rep;
	public:
		Nodo_palabra();
		Nodo_palabra(string);
		~Nodo_palabra() {};
		Nodo_palabra* get_hijo_izq() { return this->hijo_izq; }
		Nodo_palabra* get_hijo_der() { return this->hijo_der; }
		Nodo_palabra* get_next_alf() { return this->next_alf; }
		Nodo_palabra* get_next_rep() { return this->next_rep; }
		string get_palabra() { return this->palabra; }
		int get_cantidad_repeticiones() { return this-> cantidad_repeticiones; }
		void set_palabra(string palabra) { this->palabra = palabra; }
		void set_cantidad_repeticiones(int cantidad_repeticiones) { this->cantidad_repeticiones = cantidad_repeticiones; }
		void set_hijo_izq(Nodo_palabra* hijo_izq) { this->hijo_izq = hijo_izq; }
		void set_hijo_der(Nodo_palabra* hijo_der) { this->hijo_der = hijo_der; }
		void set_next_alf(Nodo_palabra* next_alf) { this->next_alf = next_alf; }
		void set_next_rep(Nodo_palabra* next_rep) { this->next_rep = next_rep; }
};

//Constructores del nodo de palabras
Nodo_palabra::Nodo_palabra()
{
	this->hijo_izq = NULL;
	this->hijo_der = NULL;
	this->next_alf = NULL;
	this->next_rep = NULL;

	this->cantidad_repeticiones = 0;
}

Nodo_palabra::Nodo_palabra(string palabra)
{
	this->palabra = palabra;

	this->hijo_izq = NULL;
	this->hijo_der = NULL;
	this->next_alf = NULL;
	this->next_rep = NULL;

	this->cantidad_repeticiones = 0;
}

//Lista de palabras y árbol
class Lista_Arbol_Palabras
{
	private:
		Nodo_palabra* comienzo;
		Nodo_palabra* raiz;
		Nodo_palabra* comienzo_rep;
	    void rid(Nodo_palabra*);
	    void ird(Nodo_palabra*);
	    void idr(Nodo_palabra*);
	    void show(Nodo_palabra*,int);
	public:
		Lista_Arbol_Palabras();
		~Lista_Arbol_Palabras() {};
		Nodo_palabra* get_comienzo() { return this->comienzo; }
		Nodo_palabra* get_raiz() { return this->raiz; }
		Nodo_palabra* get_comienzo_rep() { return this->comienzo_rep; }
		Nodo_palabra* ultimo();
		string get_palabra() { return this->comienzo->get_palabra(); }
		bool esta_vacia() { return this->comienzo->get_next_alf()==NULL; }
		bool esta_palabra(string,Nodo_palabra*&);
		void mostrar_lista();
		void add_palabra(string);
		int cantidad_elementos();
		void rellenar_arreglo(Nodo_palabra* v[]);
	    void IRD() { ird(raiz); }
	    void mostrar_arbol() { show(raiz,0); }
	    void mostrar_rep();
	    void enlazador(Nodo_palabra* v[]);
	    void linkear_reps();
};

//Método de la lista y árbol
Lista_Arbol_Palabras::Lista_Arbol_Palabras()
{
	comienzo = new Nodo_palabra();

	raiz = new Nodo_palabra();
}

void Lista_Arbol_Palabras::linkear_reps()
{
	Nodo_palabra* pivote = this->comienzo;
	
	this->comienzo_rep = pivote;
	
	while(pivote->get_next_alf()!=NULL)
	{
		pivote->set_next_rep(pivote->get_next_alf());
		
		pivote = pivote->get_next_alf();
	}
}

void Lista_Arbol_Palabras::rellenar_arreglo(Nodo_palabra* v[])
{
	Nodo_palabra* pivote = this->comienzo_rep;
	
	for(int i=0; i<this->cantidad_elementos(); i++)
	{
		v[i] = pivote;
		
		pivote = pivote->get_next_rep();
	}
}

int Lista_Arbol_Palabras::cantidad_elementos()
{
	int c = 0;

	Nodo_palabra* pivote = this->comienzo;
	
	while(pivote->get_next_alf()!=NULL)
	{
		c++;

		pivote = pivote->get_next_alf();
	}

	return c;
}

void Lista_Arbol_Palabras::mostrar_rep()
{
	cout << "      PALABRA       |   CANTIDAD DE REPETICIONES" << endl
		 << "----------------------------------------------------" << endl;
	
	Nodo_palabra* pivote = this->comienzo_rep;
	
	while(pivote->get_next_rep()!=NULL)
	{
		cout << setw(20) << left << pivote->get_palabra() << "|" << setw(15) << right << pivote->get_cantidad_repeticiones() << endl;

		pivote = pivote->get_next_rep();
	}
}

Nodo_palabra* Lista_Arbol_Palabras::ultimo()
{
	Nodo_palabra* pivote = this->comienzo;
	
	while(pivote->get_next_alf()->get_next_alf()!=NULL) pivote = pivote->get_next_alf();

	return pivote;
}

void Lista_Arbol_Palabras::enlazador(Nodo_palabra* v[])
{
	this->comienzo_rep = v[0];

	Nodo_palabra* pivote = this->comienzo_rep;

	for(int i = 1; i<this->cantidad_elementos(); i++)
	{
		pivote->set_next_rep(v[i]);
		
		pivote = pivote->get_next_rep();
	}

	Nodo_palabra* ultimo = new Nodo_palabra();

	pivote->set_next_rep(ultimo);
}

void Lista_Arbol_Palabras::ird(Nodo_palabra* aux)
{
	if(aux!=NULL)
	{
		ird(aux->get_hijo_izq());
	 	
	 	cout << endl << aux->get_palabra();
	  	
	  	ird(aux->get_hijo_der());
	}
}

void Lista_Arbol_Palabras::show(Nodo_palabra* aux, int n)
{
	if(aux!=NULL)
	{
		show(aux->get_hijo_der(),n+1);
		
		for(int i=1; i<=n; i++) cout << "     ";
		
		cout << aux->get_palabra() << endl;	
		
		show(aux->get_hijo_izq(),n+1);
	}
}

void Lista_Arbol_Palabras::mostrar_lista()
{
	cout << "----PALABRAS ALMACENADAS:----" << endl << endl;
	
	Nodo_palabra* pivote = this->comienzo;
	
	while(pivote->get_next_alf()!=NULL)
	{
		cout << pivote->get_palabra() << endl;

		pivote = pivote->get_next_alf();
	}

	cout << endl
		 << "----FIN DE LA LISTA----"
		 << endl << endl;
}

bool Lista_Arbol_Palabras::esta_palabra(string buscada,Nodo_palabra* &puntero)
{
	Nodo_palabra *pivote = this->comienzo;

	string aux_string;

	while(pivote->get_next_alf()!=NULL)
	{
		aux_string = pivote->get_palabra();
		
		if(aux_string.compare(buscada)==0)
		{
			puntero = pivote;

			return true;
		}

		pivote = pivote->get_next_alf();
	}

	return false;
}

void Lista_Arbol_Palabras::add_palabra(string palabra)
{
	if(this->esta_vacia())
	{	
		Nodo_palabra* nuevo_nodo = new Nodo_palabra(palabra);

		nuevo_nodo->set_next_alf(this->comienzo);

		comienzo = nuevo_nodo;
		
		this->raiz = nuevo_nodo;
	}
	
	else
	{		
		Nodo_palabra* nodo_aux;
		Nodo_palabra* pivote = this->comienzo;
		Nodo_palabra* pivote_arbol = this->raiz;
		
		if(esta_palabra(palabra,nodo_aux))
		{
			nodo_aux->set_cantidad_repeticiones(nodo_aux->get_cantidad_repeticiones()+1);

			return;
		}
		
		else
		{
			bool es_primero_en_lista = true, es_ultimo_en_lista = false, arbol_asignado = false, lista_asignada = false;
			
			Nodo_palabra* nuevo_nodo = new Nodo_palabra(palabra);
			Nodo_palabra* anterior = new Nodo_palabra();

			while(true)
			{	
				if(pivote->get_next_alf()->get_next_alf()==NULL) es_ultimo_en_lista=true;
				
				if(arbol_asignado && lista_asignada) return;
				
				if(!lista_asignada)
				{
					comp_ins++;
					
					switch(compara_strings(palabra,pivote->get_palabra()))
					{	
						case 1:
						{
							if(es_primero_en_lista)
							{
								nuevo_nodo->set_next_alf(this->comienzo);
								
								comienzo = nuevo_nodo;
								
								lista_asignada = true;
								
								break;		
							}
							else
							{
								nuevo_nodo->set_next_alf(pivote);

								anterior->set_next_alf(nuevo_nodo);

								lista_asignada = true;
								
								break;	
							}	
						}
						
						case 2:		
						{
							if(es_ultimo_en_lista)
							{
								nuevo_nodo->set_next_alf(pivote->get_next_alf());

								pivote->set_next_alf(nuevo_nodo);
								
								lista_asignada = true;
								
								break;				
							}

							es_primero_en_lista = false;
							
							anterior = pivote;

							pivote = pivote->get_next_alf();
							
							break;
						}
					}
				}

				if(!arbol_asignado)
				{
					comp_arbol++;
					
					switch(compara_strings(palabra,pivote_arbol->get_palabra()))
					{	
						case 1:
						{	
							if(pivote_arbol->get_hijo_izq()==NULL)
							{
								pivote_arbol->set_hijo_izq(nuevo_nodo);

								arbol_asignado = true;
								
								break;		
							}
							else pivote_arbol = pivote_arbol->get_hijo_izq();

							break;
						}
						
						case 2:		
						{
							if(pivote_arbol->get_hijo_der()==NULL)
							{
								pivote_arbol->set_hijo_der(nuevo_nodo);

								arbol_asignado = true;
								
								break;		
							}
							else pivote_arbol = pivote_arbol->get_hijo_der();

							break;
						}
					}
				}
			}
		}
	}
}

//Funciones aparte
void quick_sort(Nodo_palabra* v[], int primero, int ultimo)
{
	int i,j;

	Nodo_palabra* k;
	Nodo_palabra* tmp;

	i = primero;
	j = ultimo-1;

	k = v[(i+j)/2];

	while(i<=j)
	{
		while(v[i]->get_cantidad_repeticiones()>k->get_cantidad_repeticiones())
		{
			i++;

			comp_QS++;	
		} 
		while(v[j]->get_cantidad_repeticiones()<k->get_cantidad_repeticiones())
		{
			j--;

			comp_QS++;	
		} 
		
		if(i<=j)
		{
			tmp = v[i];

			v[i] = v[j];
			v[j] = tmp;

			i++;
			j--;
		}
	}

	if(primero<j) quick_sort(v,primero,j);

	if(i<ultimo) quick_sort(v,i,ultimo);
}

void generar_txt(Lista_Arbol_Palabras* LAP)
{
	ofstream archivo;

	archivo.open("Salida.txt",ios::out);

	if(archivo.fail())
	{
		cout << "ERROR AL CREAR EL ARCHIVO .txt" << endl;

		system("PAUSE");

		exit(1);
	}

	archivo << "----PALABRAS ALMACENADAS ORDENADAS ALFABETICAMENTE----" << endl;
	
	Nodo_palabra* pivote = LAP->get_comienzo();

	while(pivote->get_next_alf()!=NULL)
	{
		archivo << pivote->get_palabra() << endl;

		pivote = pivote->get_next_alf();
	}

	pivote = LAP->get_comienzo_rep();

	archivo << endl << "----PALABRAS ALMACENADAS ORDENADAS POR CANTIDAD DE REPETICIONES----" << endl
			<< endl << "      PALABRA       |   CANTIDAD DE REPETICIONES"     << endl
		 			<< "----------------------------------------------------" << endl << endl;

	while(pivote->get_next_rep()!=NULL)
	{
		archivo << setw(20) << left <<pivote->get_palabra() << "|" << setw(15) << pivote->get_cantidad_repeticiones() << endl;
		
		pivote = pivote->get_next_rep();
	}

	archivo << endl << "COMPARACIONES POR INSERCION: " << comp_ins << endl
		 	<< "COMPARACIONES ARBOL BINARIO: " << comp_arbol << endl
			<< "COMPARACIONES QUICK SORT: " << comp_QS <<endl;

	archivo.close();
}

int compara_strings(string entrante, string enlista)
{
	int hasta, por_caracteres;

	if(entrante.length()>enlista.length()) 
	{
		hasta = enlista.length();

		por_caracteres = 2;
	}
	else 
	{
		hasta = entrante.length();

		por_caracteres = 1;
	}

	for(int i=0; i<hasta; i++)
	{
		if(entrante.at(i)<enlista.at(i)) return 1;

		if(entrante.at(i)>enlista.at(i)) return 2;
	}

	return por_caracteres;
}

string preparar_palabra(string palabra)
{
	for(int i=0; i<palabra.length(); i++)
	{
		if(palabra.at(i)>=65 && palabra.at(i)<=90) palabra.at(i) = palabra.at(i) + 32;
		
		if(palabra.at(i)>=32 && palabra.at(i)<=64) palabra.erase(i,1);
	}

	return palabra;
}

void ordenador(Lista_Arbol_Palabras* LAP)
{
	ifstream txtFile;

	string palabra;

	txtFile.open("text.txt",ios::in);

	if(txtFile.fail())
	{
		cout << "ERROR AL LEER EL ARCHIVO .txt" << endl;

		system("PAUSE");

		exit(1);
	}

	while(!txtFile.eof())
	{
		getline(txtFile,palabra,' ');
		
		palabra = preparar_palabra(palabra);
		
		LAP->add_palabra(palabra);
	}
}

int main()
{
	Lista_Arbol_Palabras* LAP = new Lista_Arbol_Palabras();
	
	ordenador(LAP);
	
	LAP->mostrar_lista();
	LAP->mostrar_arbol();
	LAP->linkear_reps();
	LAP->mostrar_rep();

	Nodo_palabra* v[LAP->cantidad_elementos()];
	
	LAP->rellenar_arreglo(v);
	
	for(int i=0;i<3;i++) quick_sort(v,0,LAP->cantidad_elementos());
    
    LAP->enlazador(v);
    LAP->mostrar_rep();
    
    generar_txt(LAP);

	system("PAUSE");
	
	return EXIT_SUCCESS;
}