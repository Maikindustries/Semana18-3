#include <iostream>
#include "funko.hpp"
#include <iostream> 
#include <sstream> 
#include <cstdlib>

using namespace std;


int main(){

    string nombre,modelo, categoria,coleccion,id, anio;
    string mes,dia,tiempo,ip,falla,flag="1";    
    ListaDL * lista = new ListaDL();
    ifstream datos1;
    datos1.open("PruebasSemana18.txt");
    while(datos1.good()){
        getline(datos1,nombre,',');
        getline(datos1,modelo,',');
        getline(datos1,id,',');
        getline(datos1,anio,',');
        getline(datos1,categoria,',');
        getline(datos1,coleccion,'\n');       
        lista->agregarFinal(nombre,modelo,atoi(id.c_str()),atoi(anio.c_str()),categoria,coleccion);
    }
    cout<<lista->imprimirLista();


    string categ;
    Funko * elemento = lista->getHead();
    ListaCS * listaCS = new ListaCS();
    cout<< "\nCategorias: "<<endl;
    elemento=lista->getHead();
    while(elemento){
        listaCS->agregaCategoria(elemento->getCategoria());
        elemento=elemento->getSiguiente();
    }
    cout<<listaCS->imprimirLista();

}
