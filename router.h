#ifndef ROUTER_H
#define ROUTER_H
#include <string>
#include <map>
using namespace std;
const int infinito=100000;

class router
{
private:
    string nombre;
    map<string,int>vecinos;
    map<string,int>tabla_costos;
public:
    router();
    router(const string& _nombre);
    string getNombre() const;
    void agregarvecino(const string& nombreVecino,int costo);
    void eliminarvecino(const string& nombreVecino);
    void actualizartabladecostos(const map<string, int>& nuevaTabla);
    map<string,int>gettabladecostos()const;
    map<string,int>getvecinos()const;
    void imprimirvecinos()const;
    void imprimirtabla()const;
};

#endif // ROUTER_H
