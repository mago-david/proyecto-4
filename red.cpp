#include "red.h"
#include <iostream>
#include <fstream>


red::red() {
}
    void red::agregarrouter(const string& nombre){
        if(routers.find(nombre)!=routers.end()){
            cout<<"El router "<<nombre<<" ya existe"<<endl;
            return;
        }
        routers[nombre]=router(nombre);
        actualizartablascostos();
    }
    void red::eliminarrouter(const string& nombre){
        if(routers.find(nombre)==routers.end()){
            cout<<"El router "<<nombre<<" no existe"<<endl;
            return;
        }
        map<string,router>::iterator i;
        for(i=routers.begin();i!=routers.end();++i){
            i->second.eliminarvecino(nombre);
        }
        routers.erase(nombre);
        actualizartablascostos();
    }
    void red::agregarenlace(const string& a, const string& b, int costo){
        if(routers.find(a)==routers.end() || routers.find(b)==routers.end()){
            cout<<"Los dos routers deben existir"<<endl;
            return;
        }
        routers[a].agregarvecino(b,costo);
        routers[b].agregarvecino(a,costo);
        actualizartablascostos();
    }
    void red::eliminarenlace(const string& a, const string& b){
        if(routers.find(a)==routers.end() || routers.find(b)==routers.end()){
            cout<<"Los dos routers deben existir"<<endl;
            return;
        }
        routers[a].eliminarvecino(b);
        routers[b].eliminarvecino(a);
        actualizartablascostos();
    }
    bool red::cargardesdearchivo(const string& nombrearchivo){
        ifstream archivo(nombrearchivo.c_str());
        if(!archivo.is_open()){
            cout<<"No se pudo abrir "<<nombrearchivo<<endl;
            return false;
        }
        routers.clear();
        int cantidadrouters;
        archivo>>cantidadrouters;
        for(int i=0;i<cantidadrouters;i++){
            string nombre;
            archivo>>nombre;
            routers[nombre]=router(nombre);
        }
        int cantidadenlaces;
        archivo>>cantidadenlaces;
        for(int i=0;i<cantidadenlaces;i++){
            string a,b;
            int costo;
            archivo>>a>>b>>costo;
            if(routers.find(a)!=routers.end() && routers.find(b)!=routers.end()){
                routers[a].agregarvecino(b,costo);
                routers[b].agregarvecino(a,costo);
            }
        }
        archivo.close();
        actualizartablascostos();
        return true;
    }
    void red::calcularcamino(const string& origen, map<string,int>& dist,map<string,string>& previo) const{
        map<string,bool> visitado;
        map<string,router>::const_iterator i;
        for(i=routers.begin();i !=routers.end();++i){
            dist[i->first]=infinito;
            visitado[i->first]=false;
        }
        dist[origen]=0;
        for(unsigned int a=0;a<routers.size();a++){
            string actual="";
            int mejor=infinito;
            for(i=routers.begin();i!=routers.end();++i){
                if(!visitado[i->first] && dist[i->first]<mejor){
                    mejor=dist[i->first];
                    actual=i->first;
                }
            }
            if(actual=="") break;
            visitado[actual]=true;
            map<string,router>::const_iterator pos=routers.find(actual);
            map<string,int> vec=pos->second.getvecinos();
            map<string,int>::iterator v;
            for(v=vec.begin();v!=vec.end();++v){
                int nuevo=dist[actual]+v->second;
                if(nuevo<dist[v->first]){
                    dist[v->first]=nuevo;
                    previo[v->first]=actual;
                }
            }
        }
    }
    void red::actualizartablascostos(){
        map<string,router>::iterator it;
        for(it=routers.begin();it!=routers.end();++it){
            map<string,int> dist;
            map<string,string> previo;
            calcularcamino(it->first,dist,previo);
            it->second.actualizartabladecostos(dist);
        }
    }
    list<string> red::encontrarcamino(const string& origen, const string& destino) const{
        list<string> camino;
        if(routers.find(origen)==routers.end() || routers.find(destino)==routers.end()){
            return camino;
        }
        map<string,int> dist;
        map<string,string> previo;
        calcularcamino(origen,dist,previo);
        if(dist[destino]>=infinito){
            return camino;
        }
        string actual=destino;
        camino.push_front(actual);
        while(actual!=origen){
            actual=previo[actual];
            camino.push_front(actual);
        }
        return camino;
    }
    int red::calcularcostocamino(const list<string>& camino) const{
        if(camino.empty()) return -1;
        int total=0;
        list<string>::const_iterator i=camino.begin();
        list<string>::const_iterator siguiente=camino.begin();
        ++siguiente;
        while(siguiente!=camino.end()){
            map<string,router>::const_iterator pos=routers.find(*i);
            if(pos==routers.end()) return -1;
            map<string,int> vec=pos->second.getvecinos();
            map<string,int>::iterator enlace=vec.find(*siguiente);
            if(enlace==vec.end()) return -1;
            total=total+enlace->second;
            ++i;
            ++siguiente;
        }
        return total;
    }
    void red::imprimirred() const{
        map<string,router>::const_iterator i;
        for(i=routers.begin();i!=routers.end();++i){
            i->second.imprimirvecinos();
        }
        cout<<endl;
        for(i=routers.begin();i!=routers.end();++i){
            i->second.imprimirtabla();
        }
    }