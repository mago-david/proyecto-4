#include <iostream>
#include <list>
#include <string>
#include "red.h"
using namespace std;

int main()
{
    red r;
    bool salir=false;
    char opcion;
    string origen,destino,nombre,archivo;
    int costo;
    if(!r.cargardesdearchivo("prueba.txt")){
        return 1;
    }
    while(!salir){
        cout<<endl<<"que quieres hacer? 1.ver la red  2.ver camino entre routers  3.agregar router  4.eliminar router  5.agregar enlace  6.eliminar enlace  7.cargar archivo  0.salir"<<endl;
        cin>>opcion;
        switch(opcion){
        case '1':
            r.imprimirred();
            break;
        case '2':
            cout<<"router origen: ";
            cin>>origen;
            cout<<"router destino: ";
            cin>>destino;
            {
                list<string> camino=r.encontrarcamino(origen,destino);
                if(camino.empty()){
                    cout<<"No hay camino"<<endl;
                }
                else{
                    cout<<"Camino: ";
                    list<string>::iterator i;
                    for(i=camino.begin();i!=camino.end();++i){
                        cout<<*i<<" ";
                    }
                    cout<<endl<<"Costo: "<<r.calcularcostocamino(camino)<<endl;
                }
            }
            break;
        case '3':
            cout<<"nombre del nuevo router: ";
            cin>>nombre;
            r.agregarrouter(nombre);
            break;
        case '4':
            cout<<"nombre del router a eliminar: ";
            cin>>nombre;
            r.eliminarrouter(nombre);
            break;
        case '5':
            cout<<"router a: ";
            cin>>origen;
            cout<<"router b: ";
            cin>>destino;
            cout<<"costo: ";
            cin>>costo;
            r.agregarenlace(origen,destino,costo);
            break;
        case '6':
            cout<<"router a: ";
            cin>>origen;
            cout<<"router b: ";
            cin>>destino;
            r.eliminarenlace(origen,destino);
            break;
        case '7':
            cout<<"nombre del archivo: ";
            cin>>archivo;
            if(r.cargardesdearchivo(archivo)){
                cout<<"red cargada"<<endl;
            }
            break;
        case '0':
            salir=true;
            break;
        default:
            cout<<"opcion no valida"<<endl;
        }
    }
    return 0;
}
