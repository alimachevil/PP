#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <limits> // Para usar los valores máximos y mínimos de los tipos de datos

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
float promedio_claves(Nodo *R);

int main()
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
    } while (op != 5);

    // Llamar a la función promedio_claves e imprimir el resultado
    float promedio = promedio_claves(R);
    cout << "El promedio entre la clave menor y la clave mayor es: " << promedio << endl;

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

// Implementación de la función promedio_claves
float promedio_claves(Nodo *R)
{
    if (R == NULL)
    {
        // Si el árbol está vacío, devolvemos un valor inválido
        // Puedes elegir cómo manejar este caso según tus necesidades
        return numeric_limits<float>::quiet_NaN();
    }

    // Encontrar la clave menor
    Nodo *temp = R;
    while (temp->izq != NULL)
    {
        temp = temp->izq;
    }
    int clave_menor = temp->num;

    // Encontrar la clave mayor
    temp = R;
    while (temp->der != NULL)
    {
        temp = temp->der;
    }
    int clave_mayor = temp->num;

    // Calcular el promedio
    float promedio = (clave_menor + clave_mayor) / 2.0;
    return promedio;
}
