#ifndef RED_H
#define RED_H
#include <string>
#include <map>
#include <list>
#include "router.h"
using namespace std;

class red
{
private:
    map<string,router>routers;
    void calcularcamino(const string& origen,map<string,int>& dist,map<string,string>& previo)const;
    string mayusculas(const string& texto) const;
public:
    red();
    void agregarrouter(const string& nombre);
    void eliminarrouter(const string& nombre);
    void agregarenlace(const string& a,const string& b,int costo);
    void eliminarenlace(const string& a,const string& b);
    bool cargardesdearchivo(const string& nombrearchivo);
    void actualizartablascostos();
    list<string> encontrarcamino(const string& origen,const string& destino) const;
    int calcularcostocamino(const list<string>& camino) const;
    void imprimirred() const;
};

#endif // RED_H
