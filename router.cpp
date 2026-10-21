#include "router.h"
#include <iostream>

router::router(){
    nombre="N/A";
}
router::router(const string& _nombre) {
    nombre=_nombre;
    tabla_costos[nombre]=0;
}

string router::getNombre()const{
    return nombre;
}
map<string,int>router::getvecinos()const{
    return vecinos;
}
void router::agregarvecino(const string& nombrevecino,int costo){
    vecinos[nombrevecino]=costo;
    tabla_costos[nombrevecino]=costo;
}
void router::eliminarvecino(const string& nombrevecino){
    vecinos.erase(nombrevecino);
    tabla_costos.erase(nombrevecino);
}
void router::actualizartabladecostos(const map<string,int>& nuevatabla){
    tabla_costos=nuevatabla;
}
map<string,int>router::gettabladecostos()const{
    return tabla_costos;
}
void router::imprimirvecinos()const{
    cout<<"vecino del router "<<nombre<<"="<<endl;
    if(vecinos.empty()){
        cout<<"no tiene vecinos :,( "<<endl;
    }
    else{
        map<string,int>::const_iterator i;
        for(i=vecinos.begin();i !=vecinos.end();i++){
            cout<<i->first<<"("<<i->second<<")";
        }
        cout<<endl;
    }
}
void router::imprimirtabla()const{
    cout<<"tabla de "<<nombre<<"= ";
    map<string,int>::const_iterator i;
    for(i=tabla_costos.begin();i !=tabla_costos.end();i++){
        cout<<i->first<<"=";
    if (i->second >= infinito){
        cout<<"inf";
    }
    else{
    cout <<i->second;
    cout<<" ";
    }
}
    cout<<endl;
}

