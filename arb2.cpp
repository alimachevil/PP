#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct Nodo
{
    int inf;
    Nodo *izq,*der;
    int fe;
}nodo;

//Crear
void insertar(Nodo*&,int,int);
void eliminar(Nodo*&,int,int);
void reestructura1(Nodo*&,int);
void reestructura2(Nodo*&,int);
void borra(Nodo*&,Nodo*&,int);
void preorden(Nodo*&);
void inorden(Nodo *&);
void postorden(Nodo *&);

int main ()
{
    Nodo *R = NULL;
    int clave;
    int  cen;
    int men=0;
    do 
    {
        cout << "---------------------MENU---------------------"<<endl;
        cout << "Opciones: "<<endl;
        cout << "1. Insertar AVL"<<endl;
        cout << "2. Eliminar AVL"<<endl;
        cout << "3. Mostrar preorden"<<endl;
        cout << "4. Mostrar inorden"<<endl;
        cout << "5. Mostrar postorden"<<endl;
        cout << "6. Salir" << endl;
        cout << "Digite su opcion: "; cin >> men;
        switch (men)
        {
        case 1:
            fflush(stdin);
            cout << "Ingrese la clave a insertar: ";
            cin >> clave;
			insertar(R,clave,cen);
            system("pause");
            system("cls");
            break;
        case 2:
            fflush(stdin);
            cout << "Ingrese la clave a eliminar: ";
            cin >> clave;
			eliminar(R,clave,cen);
            system("pause");
            system("cls");
            break;
        case 3:
            fflush(stdin);
			preorden(R);
            system("pause");
            system("cls");
            break;
        case 4:
            fflush(stdin);
			inorden(R);
            system("pause");
            system("cls");
            break;
        case 5:
            fflush(stdin);
			postorden(R);
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    }
    while (men!=6);

    getch();
}

void insertar(Nodo*&R,int clave,int cen)
{
    //tal vez sea necesario declarar R
    if (R!=NULL)
    {
        if (clave<R->inf)
            {
                insertar(R->izq,clave,cen);
                if(cen==1)
                {
                    if (R->fe==1)
                    {
                        R->fe=0;
                        cen=0;
                    }
                    if (R->fe==0)
                    {
                        R->fe=-1;
                    }
                    if (R->fe==-1)
                    {
                        Nodo* R1 = new Nodo();
                        R1=R->izq;
                        if(R1->fe>=0)
                        {
                            Nodo* R2 = new Nodo();
                            R2=R1->der;

                            R->izq=R2->der;
                            R2->der=R;
                            R1->der=R2->izq;
                            R2->izq=R1;
                            
                            if(R2->fe=-1)
                            {
                                R->fe=1;
                            }
                            else
                            {
                                R->fe=0;
                            }

                            if(R2->fe=1)
                            {
                                R1->fe=-1;
                            }
                            else
                            {
                                R1->fe=0;
                            }

                            R=R2;
                        }
                        else
                        {
                            R->izq=R1->der;
                            R1->der=R;
                            R->fe=0;
                            R=R1;
                        }
                        R->fe=0;
                        cen=0;
                    }
                }
            }
            else
            {
                if (clave>R->inf)
                {
                    insertar(R->der,clave,cen);
                    if(cen==1)
                    {
                        if (R->fe==-1)
                        {
                            R->fe=0;
                            cen=0;
                        }
                        if (R->fe==0)
                        {
                            R->fe=1;
                        }
                        if (R->fe==1)
                        {
                            Nodo* R1 = new Nodo();
                            R1=R->der;
                            if(R1->fe<0)
                            {
                                Nodo* R2 = new Nodo();
                                R2=R1->izq;

                                R->der=R2->izq;
                                R2->izq=R;
                                R1->izq=R2->der;
                                R2->der=R1;
                                
                                if(R2->fe=1)
                                {
                                    R->fe=-1;
                                }
                                else
                                {
                                    R->fe=0;
                                }

                                if(R2->fe=-1)
                                {
                                    R1->fe=1;
                                }
                                else
                                {
                                    R1->fe=0;
                                }

                                R=R2;
                            }
                            else
                            {
                                R->der=R1->izq;
                                R1->izq=R;
                                R->fe=0;
                                R=R1;
                            }
                            R->fe=0;
                            cen=0;
                        }
                    }
                }
                else
                {
                    fflush(stdin);
                    cout << "Clave ya existe";
                }
            }
        }
    else
    {
        Nodo* q = new Nodo();
        q->inf=clave;
        q->fe=0;
        R=q;
        q->izq=NULL;
        q->der=NULL;
        cen=1;
    }
}

void eliminar(Nodo*&R,int clave,int cen)
{
    if (R!=NULL)
    {
        if (clave<R->inf)
            {
                eliminar(R->izq,clave,cen);
                reestructura1(R,cen);
            }
            else
            {
                if (clave>R->inf)
                {
                    eliminar(R->der,clave,cen);
                    reestructura2(R,cen);
                }
                else
                {
                    Nodo * q = new Nodo();
                    q=R; 
                    if(q->der==NULL)
                    {
                        R=q->izq;
                        cen=1;
                    }
                    else
                    {
                        if(q->izq==NULL)
                        {
                            R=q->der;
                            cen=1;
                        }
                        else
                        {
                            borra(q->izq,q,cen);
                            reestructura1(R,cen);
                            delete q;
                        }
                    }
                }
            }
        }
    else
    {
        fflush(stdin);
        cout << "Clave no existe";
        getch();
    }
}

void reestructura1(Nodo*&R,int cen)
{
    if (cen==1)
    {
        if(R->fe==-1)
        {
            R->fe=0;
        }
        if(R->fe==0)
        {
            R->fe=1;
            cen=0;
        }
        if(R->fe==1)
        {
            Nodo* R1 = new Nodo();
            R1=R->der;
            if(R1->fe>=0)
            {
                R->der=R1->izq;
                R1->izq=R;
                if(R1->fe==0)
                {
                    R->fe=1;
                    R1->fe=-1;
                    cen=0;
                }
                if(R1->fe==1)
                {
                    R->fe=0;
                    R1->fe=0;
                }
                R=R1;
            }
            else
            {
                Nodo* R2 = new Nodo();
                R2=R1->izq;
                R->der=R2->izq;
                R2->izq=R;
                R1->izq=R2->der;
                R2->der=R1;
                if(R2->fe=1)
                {
                    R->fe=-1;
                }
                else
                {
                    R->fe=0;
                }
                
                if(R2->fe=-1)
                {
                    R1->fe=1;
                }
                else
                {
                    R1->fe=0;
                }
                R=R2;
                R2->fe=0;
            }
        }
    }
}

void reestructura2(Nodo*&R,int cen)
{
    if (cen==1)
    {
        if(R->fe==1)
        {
            R->fe=0;
        }
        if(R->fe==0)
        {
            R->fe=-1;
            cen=0;
        }
        if(R->fe==-1)
        {
            Nodo* R1 = new Nodo();
            R1=R->izq;
            if(R1->fe<0)
            {
                R->izq=R1->der;
                R1->der=R;
                if(R1->fe==0)
                {
                    R->fe=-1;
                    R1->fe=1;
                    cen=0;
                }
                if(R1->fe==1)
                {
                    R->fe=0;
                    R1->fe=0;
                }
                R=R1;
            }
            else
            {
                Nodo* R2 = new Nodo();
                R2=R1->der;
                R->izq=R2->der;
                R2->der=R;
                R1->der=R2->izq;
                R2->izq=R1;
                if(R2->fe=-1)
                {
                    R->fe=1;
                }
                else
                {
                    R->fe=0;
                }
                
                if(R2->fe=1)
                {
                    R1->fe=-1;
                }
                else
                {
                    R1->fe=0;
                }
                R=R2;
                R2->fe=0;
            }
        }
    }
}

void borra(Nodo*&aux,Nodo*&otro,int cen)
{
    if (aux->der!=NULL)
    {
        borra(aux->der,otro,cen);
        reestructura2(aux,cen);
    }
    else
    {
        otro->inf=aux->inf;
        aux=aux->izq;
        cen=1;
    }
}

void preorden(Nodo*&R)
{   
    if(R!=NULL)
    {
        cout << "Nodo: "<< R->inf<< endl;
        preorden(R->izq);
        preorden(R->der);
    }
}

void inorden(Nodo *&R)
{
    if(R!=NULL)
    {
        inorden(R->izq);
        cout << "Nodo : "<<R->inf << endl;
        inorden(R->der);
    }
}

void postorden(Nodo *&R)
{
    if(R!=NULL)
    {
        postorden(R->izq);
        postorden(R->der);
        cout << "Nodo: "<< R->inf << endl;
    }
}