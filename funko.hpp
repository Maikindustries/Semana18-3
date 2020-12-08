#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Funko{
    //Atributos
    private:
        string nombre;
        string modelo;
        int id;
        int anio;
        string categoria;
        string coleccion;
        Funko * siguiente;
        Funko * anterior;
    //Metodos
    public:
        Funko(string nombre, string modelo, int id, int anio, string categoria, string coleccion,Funko * anterior, Funko * siguiente){
            this->nombre=nombre;
            this->modelo=modelo;
            this->id=id;
            this->anio=anio;
            this->categoria=categoria;
            this->coleccion=coleccion;
            this->siguiente=siguiente;
            this->anterior=anterior;
        }

        //Getters y setters
        string getNombre(){return this->nombre;}
        string getModelo(){return this->modelo;}
        int getId(){return this->id;}
        int getAnio(){return this->anio;}
        string getCategoria(){return this->categoria;}
        string getColeccion(){return this->coleccion;}
        Funko * getSiguiente(){return this->siguiente;}
        Funko * getAnterior(){return this->anterior;}

        void setNombre(string nombre){this->nombre=nombre;}
        void setModelo(string modelo){this->modelo=modelo;}
        void setId(int id){this->id=id;}
        void setAnio(int anio){this->anio;}
        void setCategoria(string categoria){this->categoria=categoria;}
        void seColeccion(string coleccion){this->coleccion=coleccion;}
        void setSiguiente(Funko * siguiente){this->siguiente=siguiente;}
        void setAnterior(Funko * anterior){this->anterior=anterior;}
        string imprimirEntrada(){
            return getNombre()+" "+ getModelo()+" "+to_string(getId())+" " + to_string(getAnio())+" "+getCategoria()+" "+getColeccion()+"\n";
        }
};

class ListaDL{
    //Atributos
    Funko * head;
    int tam;
    public:
        Funko * getHead(){return this->head;}
        int getTam(){return this->tam;}
        void setHead(Funko * head){this->head=head;}
        void setTam(int tam){this->tam=tam;}

        ListaDL(){
            this->head=nullptr;
            this->tam=0;
        }

        /*
        Metodo agregarFinal: Agrega un nodo de tipo Bitacora en una lista doblemente ligada.
        Recibe: string de mes, día, tiempo, ip y falla
        Regresa: -
        O(n) tiene que recorrer todo para llegar al final.
        */
        void agregarFinal(string nombre, string modelo, int id, int anio, string categoria, string coleccion){
            Funko * nuevo=new Funko(nombre, modelo, id, anio, categoria, coleccion,nullptr,nullptr);//Crear el nuevo nodo
            Funko * elemento=this->head; // Iniciar el apuntador al nodo elemento en el head de la lista
            if(elemento){//Verificar que la lista no esta vacia
                //Recorrer toda la lista para encontrar el nodo final
                while(elemento->getSiguiente()){
                    elemento=elemento->getSiguiente();
                }
                elemento->setSiguiente(nuevo); //Hacer que el Ãºltimo elemento siguiente apunte al nuevo nodo
                nuevo->setAnterior(elemento);  //Actualizar el nuevo nodo anterior al elemento que era el Ãºltimo
            }else{
                this->head=nuevo; //Si la lista estÃ¡ vacia el nodo nuevo serÃ¡ el nodo del head y el ultimo
            }
            this->tam++;//Actualizamos el tamaÃ±o de la lista
        }
        
        /*
        Metodo imprimirLista: Imprime todos los valores de los nodos dentro de la lista.
        Recibe: -
        Regresa: string de resultado
        O(n) recorre los n elementos de la lista
        */
        string imprimirLista(){
            string resultado="";
            Funko * elemento=this->head;
            while(elemento){
                resultado+=elemento->imprimirEntrada();
                elemento=elemento->getSiguiente();
            }
            return resultado;
        }

};


class Categoria{
    string nombre;
    int numOcurrencias;
    Categoria * siguiente;
    public:
        Categoria(string nombre, int numeroOcurrencias, Categoria *  siguiente){
            this->nombre = nombre;
            this->numOcurrencias = numeroOcurrencias;
            this->siguiente = siguiente;
        }
        Categoria(){
            this->nombre="";
            this->numOcurrencias=0;
            this->siguiente = nullptr;
        }
        
        /*
        Metodo imprimirEntrada: Regresa una linea de strings.
        Recibe: -
        Regresa: string de nombre y número de ocurrencias
        O(N)
        */
        string imprimirEntrada(){
            return getNombre()+": #"+to_string(getNumOcur())+"\n";
        }
        
        string getNombre(){return this->nombre;}
        void setNombre(string nombre){this->nombre=nombre;}
        int getNumOcur(){return this->numOcurrencias;}
        void setNumOcur(int numOcurrencias){this->numOcurrencias=numOcurrencias;}
        Categoria * getSiguiente(){return this->siguiente;}
        void setSiguiente(Categoria * siguiente){this->siguiente=siguiente;}
};

class ListaCS{
    Categoria * last;
    int tam;
    public:
        Categoria * getLast(){return this->last;}
        int getTam(){return this->tam;}
        void setLast(Categoria * last){this->last=last;}
        void setTam(int tam){this->tam=tam;}

        ListaCS(){
            this->last=nullptr;
            this->tam=0;
        }

        void agregarFinal(string nombre, int numOcurrencias){
            if(this->last){ //Lista con elementos
                //Creamos el nuevo nodo apuntado al que era el nodo inicial
                Categoria * nuevo=new Categoria(nombre,numOcurrencias,this->last->getSiguiente());
                //Actualizamos el siguiente del Ãºltimo nodo con el nuevo nodo
                this->last->setSiguiente(nuevo);
                //Actualizamos el apuntador del Ãºltimo al nuevo nodo
                this->last=nuevo;
            }else{ //Lista VacÃ­a
                Categoria * nuevo=new Categoria(nombre,numOcurrencias,nullptr); // Creando el nuevo nodo
                nuevo->setSiguiente(nuevo); // Como solo hay un nodo el apuntador siguiente serÃ¡ asi mismo
                this->last=nuevo; // El nuevo nodo serÃ¡ el Ãºltimo y el primero al mismo tiempo
            }            
            this->tam++; //Actualizamos el tamaÃ±o
        }
        

        string imprimirLista(){ 
            string resultado = "";
            if(this->last){//Verificar si hay elementos en la lista                
                Categoria * elemento=this->last->getSiguiente(); //Iniciar en el primer nodo el recorrido que es al que apunta last siguiente
                do{                
                    resultado+=elemento->imprimirEntrada();
                    elemento=elemento->getSiguiente(); //Recorrer al siguiente elemento
                }while(elemento!=this->last->getSiguiente()); //Detener cuando elemento es nuevamente el primero  
                return resultado;
            }else{
                return "Lista vacia\n";
            }   
        }


        bool agregaCategoria(string ip){
            if(this->last){//Verificar si hay elementos en la lista
                Categoria * elemento=this->last->getSiguiente(); //Iniciar en el primer nodo el recorrido que es al que apunta last siguiente
                do{                    
                    if (elemento->getNombre()==ip){
                        elemento->setNumOcur(elemento->getNumOcur()+1);
                        return true;                        
                    }                    
                    elemento=elemento->getSiguiente(); //Recorrer al siguiente elemento
                }while(elemento!=this->last->getSiguiente()); //Detener cuando elemento es nuevamente el primero  
                this->agregarFinal(ip,1);
            }else{
                this->agregarFinal(ip,1);
                return false;
            }
            return false;      
        }
};
