#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

class barbero_dormilon
{
public:
    void cortar_pelo(int id_cliente);
    void siguiente_cliente();

private:
    mutex mtx_monitor;
    condition_variable esperar_cliente, esperar_barbero;
    bool barbero_disponible = true;
    int num_clientes_esperando = 0;
};

void barbero_dormilon::cortar_pelo(int id_cliente)
{
    unique_lock<mutex> lck(mtx_monitor);
    if (!barbero_disponible)
    {
        cout << "Cliente " << id_cliente << " esperando su turno." << endl;
        num_clientes_esperando++;
        esperar_cliente.wait(lck);
    }
    cout << "El barbero está cortando el pelo del cliente " << id_cliente << endl;
    barbero_disponible = false;
    cout << "El barbero ha terminado de cortar el pelo al cliente " << id_cliente << endl;
    barbero_disponible = true;
    esperar_barbero.notify_one();
}

void barbero_dormilon::siguiente_cliente()
{
    unique_lock<mutex> lck(mtx_monitor);
    if (num_clientes_esperando == 0)
    {
        cout << "El barbero está durmiendo." << endl;
        esperar_barbero.wait(lck);
    }
    num_clientes_esperando--;
    esperar_cliente.notify_one();
}

barbero_dormilon bd;

void cliente(int id)
{
    while (true)
    {
        bd.cortar_pelo(id);
    }
}

void barbero()
{
    while (true)
    {
        bd.siguiente_cliente();
    }
}

int main()
{
    thread hilo_barbero(barbero);

    thread hilos_clientes[5];
    for (int i = 0; i < 5; i++)
    {
        hilos_clientes[i] = thread(cliente, i + 1);
    }

    for (int i = 0; i < 5; i++)
    {
        hilos_clientes[i].join();
    }

    return 0;
}