#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

//Nodo
struct Nodo
{
    int num;
    Nodo* der;
	Nodo* izq;
}nodo;

//Opciones
int op,op1;
int nivel_pre=1;
int nivel_in=1;
int nivel_post=1;

//Crear
void crear_i(Nodo*&);
void preorden(Nodo*&);
void inorden(Nodo *&);
void postorden(Nodo *&);

int main ()
{
    //Cabeza
    Nodo *R = NULL;
    
    do
    {
        cout << "----------------------------------------- MENU -----------------------------------------------" << endl;
        cout << "1. Crear Arbol" << endl;
        cout << "2. Recorrer Preorden" << endl;
        cout << "3. Recorrer Inorden"<<endl;
        cout << "4. Recorrer Postorden"<< endl;
        cout << "5. Salir" << endl;	
        cout << "Ingrese opcion: "; cin >> op;
        system("cls");
        if(op==1)
        {
        	fflush(stdin);
            crear_i(R);
            system("pause");
            system("cls");
        }
        else if(op==2)
        {   
            fflush(stdin);
			preorden(R);
            system("pause");
            system("cls");
        }
		else if (op==3)
		{
			fflush(stdin);
			inorden(R);
            system("pause");
            system("cls");
		}
		else if (op==4)
		{
			fflush(stdin);
			postorden(R);
            system("pause");
            system("cls");
		}
    } while (op!=5);   
    
    return 0;
}

void crear_i(Nodo*& R)
{
    R = new Nodo();
	fflush(stdin);
	cout << "Ingrese entero: "; cin >> R->num;
	cout << "\nTiene rama izquierda?" << endl;
	cout << "1. Si" << endl;
	cout << "2. No" << endl;
	cout << "Ingrese su opcion: "; cin >> op;
    if(op==1)
    {
        Nodo* x = new Nodo();
        R->izq=x;
        crear_i(R->izq);
    }
    else
    {
        R->izq=NULL;
    }
    cout << "Tiene rama derecha?" << endl;
    cout << "1. Si"<< endl;
    cout << "2. No"<<endl;
    cout << "Ingrese su opcion "; cin >> op1;
    if(op1==1)
    {
        Nodo* x = new Nodo();
        R->der=x;
        crear_i(R->der);
    }
    else
    {
        R->der=NULL;
    }
}

void preorden(Nodo*& R)
{   
    if(R!=NULL)
    {
        cout << "Nodo: "<< R->num << endl;
        preorden(R->izq);
        preorden(R->der);
    }
}

void inorden(Nodo *&R)
{
    if(R!=NULL)
    {
        inorden(R->izq);
        cout << "Nodo : "<<R->num << endl;
        inorden(R->der);
    }
}

void postorden(Nodo *&R)
{
    if(R!=NULL)
    {
        postorden(R->izq);
        postorden(R->der);
        cout << "Nodo: "<< R->num << endl;
    }
}
