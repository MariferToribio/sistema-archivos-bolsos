///   216623393 LUEVANO MARTINEZ STEVEN
///   216850837 TORIBIO TORRES MARIFER

///   MATERIA: ESTRUCTURAS DE DATOS 2
///   SECCION: D08

///   PROFESOR: GRACIELA LARA LOPEZ

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include "archivo.h"

#define delimR "\n"
#define NombreArchivo "Bolsos.txt"

using namespace std;

int contador = 0;

/*Metodo que inserta un registro en el archivo*/
void Archivo::insertarRegistro(){
        ofstream archivo; /*Declarar archivo en modo salida*/
        /*Cuando se abre el archivo en modo de apertura ios::app, significa que todas las operaciones de salida seran al final del archivo*/
        archivo.open(NombreArchivo, ios::app);

        /*Comprobar si el archivo se pudo abrir*/
        if(!archivo.is_open()){ /*Si el archivo no se pudo abrir, mostrar mensaje de error*/
                cout << " Error al abrir el archivo " << NombreArchivo << endl;
                system("pause");
        }

        else{ /*Caso contrario, entonces realizar el procedimiento correspondiente para insertar registro en el archivo*/

                int longClave(0), longNombre(0), longDescripcion(0); /*Declarar variables de tipo entero para guardar la longitud de cada campo*/
                Bolso bolso(solicitarDatos()); /*Declarar variable de tipo "Bolso" e incializarla con el registro que retorna el metodo solicitarDatos()*/
                longNombre = bolso.nombre.size(); /*Guardar longitud de campo "nombre"*/
                longClave = strlen(bolso.clave); /*Guardar longitud de campo "clave"*/
                longDescripcion = bolso.descripcion.size(); /*Guardar longitud de campo "descripcion"*/

                archivo << longClave << bolso.clave/*Escribir longitud de campo "clave" y el campo "clave" en archivo*/
                        << longNombre << bolso.nombre /*Escribir longitud de campo "nombre" y el campo "nombre" en archivo*/
                        << longDescripcion << bolso.descripcion; /*Escribir longitud de campo "descripcion" y el campo "descripcion" en archivo*/

                archivo.write(delimR, strlen(delimR)); /*Escribir un salto de linea al final del registro*/

                archivo.close(); /*Cerrar archivo*/
                cout << " REGISTRO INSERTADO !!" << endl << endl;
                contador++;
                system("pause");
        }
}

/*Metodo que pide la informacion del bolso, guarda la informacion en el campo correspondiente del registro y retorna dicho registro*/
Archivo::Bolso Archivo::solicitarDatos(){
        Archivo::Bolso bolso;
        string nombre = "", descripcion = "";

        /*Solicitar datos al usuario y guardar la informacion*/
        cout << endl << endl;
        cout << " -----------------------------------" << endl;
        cout << " Ingresa nombre: ";
        getline(cin, nombre);
        cout << " Ingresa descripcion: ";
        getline(cin, descripcion);

        /*Cuando se guardan o concatenan espacios en blanco en los campos, es para que en el momento de escribir el campo en
        el archivo aparezca separado del indicador de longitud del campo mismo o del siguiente indicador de longitud de campo*/
        bolso.nombre = " "; /*Guardar un espacio en blanco en el campo "nombre"*/
        bolso.nombre += nombre; /*Concatenar al campo "nombre" del registro el nombre que el usuario ingreso*/
        bolso.nombre += " "; /*Concatenar espacio en blanco al campo "nombre"*/

        bolso.descripcion = " ";  /*Guardar un espacio en blanco en el campo "descripcion"*/
        bolso.descripcion += descripcion; /*Concatenar al campo "descripcion" del registro la informacion que el usuario ingreso*/

        string clave = " ";/*Guardar un espacio en blanco en variable "clave"*/
        /*Llamar al metodo hacerLlave para que forme la clave(llave primaria) del bolso y guardar dicha clave(llave primaria) en variable "clave" */
        clave += hacerLlave(bolso.nombre);
        clave += " ";/*Concatenar un espacio en blanco a variable "clave"*/

        strcpy(bolso.clave, clave.c_str()); /*Guardar en el campo "clave" la llave primaria del bolso*/

        return bolso; /*Retornar registro de tipo "Bolso"*/
}

/*Metodo que genera la llave primaria del bolso*/
string Archivo::hacerLlave(string nombre){
        int longNombre(nombre.size()), x(0);
        string llave = ""; /*Declarar variable que guardara la llave*/
        srand(time(NULL));
        int num = 0 +rand()%99; /*Generar numero aleatorio entre 0 y 99*/

        for (int i = 0; i <= longNombre and x < 3; i++){
               /*Si el caracter que se esta leyendo es diferente de un espacio en blanco, concatenar dicho caracter a la variable "llave"
                 Incrementando la variable "x" cada vez que se concatene una letra, para que de esa manera solo se concatenen las primeras tres letras del nombre del bolso, por ello la condicion del for dice x < 3*/
               if(nombre[i] != ' '){
                        llave += nombre[i];
                        x++;
               }
        }

        llave += '-'; /*Concatenar un guion medio a variable "llave"*/

        /*Si el numero generado aleatoriamente tiene menos de 2 digitos,
        entonces antes de concatenar a la variable "llave" el numero aleatorio, concatenar un 0.*/
        if(num < 10){
              llave += '0';
              llave += to_string(num);
        }

        /*Caso contrario, simplemente concatenar el numero generado aleatoriamente*/
        else{
              llave += to_string(num);
        }

        return llave; /*Retornar llave primaria de bolso*/
}

/*Metodo que muestra un registro buscado por su clave*/
void Archivo::consultar(){
         ifstream archivo;
        archivo.open(NombreArchivo, ios::in);

        if(!archivo.is_open()){
                cout << " Error al abrir el archivo " << NombreArchivo << endl;
                system("pause");
        }

        else{
                string longTexto = "";
                string asterisco = "";
                cout << endl << endl;
                char claveBus[10];   //Declara una variable a buscar
                int encontrado=0;   //Declara una bandera encontrado
                string aux = " ";   //Declara una variable auxiliar
                string aux2;        //Declara una segunda variable auxiliar
                cout<<" Ingrese la clave buscada: "; //Pide la llave a buscar
                getline(cin, aux2); //Guarda la llave ingresada por el usuario en la segunda variable auxiliar
                aux +=aux2;         //copia lo que hay en la segunda varuable auxiliar en la primera
                aux += " "; //Concatena un espacio en blanco a la primer variable auxiliar
                strcpy(claveBus, aux.c_str());     //Copia lo que hay en la variable auxiliar en la variable claveBus

                while(!archivo.eof()){ /*Mientras no sea fin de archivo*/
                        archivo >> longTexto; /*Lee la informacion correspodiente a la longitud del campo "clave y lo guarda en variable "longTexto"*/
                        asterisco=longTexto;
                        if(longTexto[0]=='*'){
                            longTexto[0]=' ';
                        }
                        int longClave = stoi(longTexto); /*Convierte en entero la longitud leida en archivo  y guarda dicha longitud en variable "longClave"*/
                        char clave[longClave] = ""; /*Crear cadena de caracteres que tiene como tamaño la longitud leida del archivo correspondiente al campo "clave"*/
                        archivo.read((char*)&clave, longClave); /*Leer la cantidad de caracteres que dicta longClave y guarda la informacion leida en variable "clave"*/
                        clave[longClave] = '\0'; /*Despues de leer el campo "clave" del archivo, asignar al final el fin de cadena*/

                        archivo >> longTexto;
                        int longNombre = stoi(longTexto);
                        char nombre[longNombre] = "";
                        archivo.read((char*)&nombre, longNombre);
                        nombre[longNombre] = '\0';

                        archivo >> longTexto;
                        int longDescripcion = stoi(longTexto);
                        char descripcion[longDescripcion] = "";
                        archivo.read((char*)&descripcion, longDescripcion);
                        descripcion[longDescripcion] = '\0';

                        if(archivo.eof()){
                                break;
                        }

                        if(strcmp(clave, claveBus)==0){
                        if(asterisco[0]=='*')
                        {
                                cout<<" REGISTRO BORRADO LOGICAMENTE"<<endl;
                                break;
                        }
                        /*Mostrar registro encontrado*/
                        system("cls");
                        cout << "\n\n     R E G I S T R O    E N C O N T R A D O" << endl;
                        cout << " ------------------------------------------------" << endl;
                        cout << " CLAVE:" << clave << endl;
                        cout << " NOMBRE:" << nombre << endl;
                        cout << " DESCRIPCION:" << descripcion << endl << endl << endl << endl;
                        encontrado++;      //la bandera encontrado ahora vale 1

                        }
                }
                if(encontrado==0){         //si la bandera sigue valiendo 0 entonces no se encontro el registro
                    cout<<"\n NO SE ENCONTRO EL REGISTRO"<<endl;
                }

                system("pause");
                archivo.close();
        }

}

/*Metodo que antes de realizar el borrado logico, comprueba la existencia de un registro con la clave que el usuario ingreso*/
void Archivo::buscarRegistroEliminar(){
        ifstream archivo; /*Declarar archivo en modo entrada*/
        archivo.open(NombreArchivo, ios::in);

        /*Comprobar si el archivo se pudo abrir*/
        if(!archivo.is_open()){ /*Si el archivo no se pudo abrir, mostrar mensaje de error*/
                cout << " Error al abrir el archivo " << NombreArchivo << endl;
                system("pause");
        }

        else{/*Caso contrario*/
                string llaveB = ""; /*Declarar variable que guardara la clave del registro a eliminar que el usuario ingreso*/
                string longTexto = ""; /*Declarar variable que guardara la longitud del campo*/

                /*Solicitar clave al usuario y guardar dicha clave en la variable "llaveB"*/
                cout << "\n Ingresa clave: "; getline(cin, llaveB);

                string llave = " "; /*Guardar espacio en blanco*/
                llave += llaveB; /*Concatenar llave que ingreso el usuario*/
                llave += " "; /* Concatenar espacio en blanco*/

                char llaveBuscar[10] = "";
                strcpy(llaveBuscar, llave.c_str()); /*Copiar en variable "llaveBuscar" el contenido de variable "llave"*/
                /*Esta variable es la que se compara directamente con el campo "clave" que se lee del archivo*/

                bool registroEncontrado(false), asterisco(false), registroBorradoLogico(false);
                archivo.seekg(0, ios::beg);
                int numCampo(1);

                /*Mientras no sea fin de archivo y mientras no se haya encontrado aun el registro que se quiere eliminar con la llave que se busca*/
                while(!archivo.eof() and registroEncontrado == false){
                                while(numCampo < 4){ /*Leer los 3 campos del registro*/
                                        archivo >> longTexto; /*Leer longitud del campo*/

                                        if(numCampo == 1){
                                                if(longTexto[0] == '*'){ /*Si el primer caracter de la informacion que corresponde a la longitud es un asterisco*/
                                                        longTexto = quitarAsterisco(longTexto); /*Quitar asterisco de variable "longTexto" para poder leer el campo "clave"*/
                                                        asterisco = true; /*Cuando sucede esto, es por si llega a suceder que este registro que ya esta logicamente borrado tiene como campo "clave" la misma llave del registro que se quiere eliminar,
                                                        Por lo tanto no se puede borrar, por que no existiria este registro (esta borrado logicamente)*/
                                                }
                                        }

                                        int longCampo = stoi(longTexto); /*Convierte en entero la longitud leida en archivo y guarda dicha longitud en variable "longCampo"*/
                                        char campo[longCampo] = ""; /*Crear cadena de caracteres de tamaño la longitud correspondiente al campo leidO del archivo*/
                                        archivo.read((char*)&campo, longCampo); /*Leer la cantidad de caracteres que dicta longCampo y lo guarda en "campo"*/
                                        campo[longCampo] = '\0'; /*Asignar el fin de cadena*/

                                        if(numCampo == 1){
                                                if(strcmp(campo, llaveBuscar) == 0){ /*Comparar llave de registro que se quiere eliminar y campo "clave" del registro que se esta leyendo del archivo*/
                                                        if(asterisco == false){ /*No es un registro que esta borrado logicamente, por lo tanto, si se puede eliminar*/
                                                                registroEncontrado = true; /*Se encontro el registro que se quiere eliminar*/
                                                        }

                                                        else{
                                                                registroBorradoLogico = true;
                                                        }
                                                }
                                        }

                                        if(asterisco == true){
                                                asterisco =  false;
                                        }

                                        numCampo++;
                                }

                                numCampo = 1; /*Para leer siguiente registro*/
                }

                archivo.close(); /*Cerrar archivo*/

                /*No se encontro registro con la llave que el usuario ingreso*/
                if(registroEncontrado == false and registroBorradoLogico != true){
                        cout << "\n\n No se encontro registro" << endl;
                }

                /*Es un registro que se encuentra borrado logicamente*/
                else if(registroBorradoLogico == true){
                        cout << "\n\n Registro borrado" << endl;
                }

                else if(registroEncontrado != false and registroBorradoLogico != true){
                        eliminarRegistro(llaveBuscar); /*LLamar metodo eliminarRegistro() y pasarle por parametro, llave de registro a eliminar*/
                        cout << " REGISTRO ELIMINADO !!" << endl;
                }
                system("pause");

        }
}

/*Metodo que realiza el borrado logico del registro correspondiente y recibe como parametro la llave del registro a borrar*/
void Archivo::eliminarRegistro(char llaveBuscar[]){
        ifstream archivo; /*Declarar archivo en modo entrada*/
        archivo.open(NombreArchivo, ios::in);

        ofstream archivoAuxiliar; /*Declara el archivo auxiliar en modo salida*/
        archivoAuxiliar.open("Auxiliar.txt", ios::app); /*Modo de apertura donde todas las operaciones de salida seran al final del archivo*/

        /*Comprobar si el archivo se pudo abrir*/
        if(!archivo.is_open()){ /*Si el archivo no se pudo abrir, mostrar mensaje de error*/
                cout << " Error al abrir el archivo " << NombreArchivo << endl;
                system("pause");
        }

        else{/*Caso contrario*/
                string longTexto = ""; /*Declarar variable que guardara la longitud del campo*/
                bool registroEncontrado(false);
                bool asterisco(false);

                archivo.seekg(0, ios::beg);

                while(!archivo.eof()){ /*Mientras no sea fin de archivo*/

                        ///LEER CAMPO CLAVE
                        archivo >> longTexto; /*Lee longitud del campo "clave" y lo guarda en variable "longTexto"*/

                        if(longTexto[0] == '*'){ /*Si el primer caracter de la informacion que corresponde a la longitud es un asterisco*/
                                longTexto = quitarAsterisco(longTexto); /*Quitar asterisco de variable "longTexto" para poder leer el campo "clave"*/
                                asterisco = true;
                        }

                        int longClave = stoi(longTexto); /*Convierte en entero la longitud leida en archivo y guarda la longitud*/
                        char clave[longClave] = "";  /*Crear cadena de caracteres de tamaño la longitud leida del archivo correspondiente al campo "clave"*/
                        archivo.read((char*)&clave, longClave); /*Leer la cantidad de caracteres que dicta longClave y guardarlo en "clave"*/
                        clave[longClave] = '\0'; /*Asignar el fin de cadena*/

                        if(strcmp(clave, llaveBuscar) == 0){ /*Comparar llave de registro que se quiere eliminar y campo "clave" el registro que esta leyendo del archivo*/
                                registroEncontrado = true; /*Se encontro el registro que se quiere eliminar*/
                        }

                        ///LEER CAMPO NOMBRE
                        archivo >> longTexto; /*Lee longitud del campo "nombre" y lo guarda en variable "longTexto"*/
                        int longNombre = stoi(longTexto); /*Convierte en entero la longitud leida en archivo y guarda la longitud*/
                        char nombre[longNombre] = ""; /*Crear cadena de caracteres de tamaño la longitud leida del archivo correspondiente al campo "nombre"*/
                        archivo.read((char*)&nombre, longNombre); /*Leer la cantidad de caracteres que dicta longNombre y guardarlo en "nombre"*/
                        nombre[longNombre] = '\0'; /*Asignar el fin de cadena*/

                        ///LEER CAMPO DESCRIPCION
                        archivo >> longTexto; /*Lee la longitud del campo "descripcion" y lo guarda en variable "longTexto"*/
                        int longDescripcion = stoi(longTexto); /*Convierte en entero la longitud leida en archivo y guarda la longitud"*/
                        char descripcion[longDescripcion] = ""; /*Crear cadena de caracteres de tamaño la longitud leida del archivo correspondiente al campo "descripcion"*/
                        archivo.read((char*)&descripcion, longDescripcion); /*Leer la cantidad de caracteres que dicta longDescripcion y guardarlo en "descripcion"*/
                        descripcion[longDescripcion] = '\0'; /*Asignar el fin de cadena*/

                        if(archivo.eof()){
                                break;
                        }

                        if(registroEncontrado == false){ /*No es el registro que se quiere borrar logicamente*/
                                if(asterisco == true){ /*Este registro que se esta leyendo esta borrado logicamente*/
                                        char asteriscoCaracter = '*';
                                        archivoAuxiliar << asteriscoCaracter; /*Antes de escribir el registro, escribir en el archivo auxiliar un asterisco*/
                                }

                        }

                        if(registroEncontrado == true){ /*Este es el registro que se quiere borrar logicamente*/
                                char asteriscoCaracter = '*';
                                archivoAuxiliar << asteriscoCaracter; /*Antes de escribir el registro, escribir un asterisco en el archivo auxiliar*/
                                registroEncontrado = false; /*Ya se borro logicamente el registro con la llave que el usuario ingreso*/
                        }

                        /*Escribir campos con sus correspondientes indicadores de longitud en el archivo auxiliar*/
                        archivoAuxiliar << longClave << clave << longNombre << nombre << longDescripcion << descripcion;
                        archivoAuxiliar.write(delimR, strlen(delimR)); /*Escribir en el archivo auxiliar un salto de linea al final del registro*/

                        if(asterisco == true){ /*Regresar "asterisco" a su valor inicial, por si llega a suceder que haya mas registros en el archivo borrados logicamente*/
                                asterisco = false;
                        }

                }

                archivoAuxiliar.close(); /*Cerrar archivo auxiliar*/
                archivo.close(); /*Cerrar archivo*/
                remove(NombreArchivo); /*Eliminar archivo fisico "Bolsos.txt"*/
                rename("Auxiliar.txt", NombreArchivo); /*Cambiarle el nombre al archivo fisico "Auxiliar.txt"*/
        }
}

/*Metodo que recibe como parametro la longitud del campo con un asterisco y su funcion es quitarle dicho asterisco a la longitud
y retorna el valor entero que hace referencia a la longitud del campo*/
string Archivo::quitarAsterisco(string longEnTexto){
        int longitudDeTexto = longEnTexto.length();
        string longTextoNuevo = "";

        for(int i = 0; i <= longitudDeTexto; i++){
                if(longEnTexto[i] != '*'){
                        longTextoNuevo += longEnTexto[i];
                }
        }

        return longTextoNuevo;
}
