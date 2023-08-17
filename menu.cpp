///   216623393 LUEVANO MARTINEZ STEVEN
///   216850837 TORIBIO TORRES MARIFER

///   MATERIA: ESTRUCTURAS DE DATOS 2
///   SECCION: D08

///   PROFESOR: GRACIELA LARA LOPEZ

#include <iostream>

#include "menu.h"
#include "archivo.h"

using namespace std;

/*Metodo que muestra las opciones del menu principal, llama el metodo ejecutarOpcion() y le pasa por parametro la opcion seleccionada*/
void Menu::mostrarMenu(){
        string opcion = "";

        /*Muestra el menu mientras no el usuario no seleccione la opcion 4(Opcion que termina el programa)*/
        do{
                system("cls");
                cout << endl << endl;
                cout << "              M E N U" << endl;
                cout << " -----------------------------------" << endl;
                cout << " 1) Insertar registro" << endl;
                cout << " 2) Mostrar registro por su codigo" << endl;
                cout << " 3) Eliminar registro de manera logica" << endl;
                cout << " 4) Salir" << endl;
                cout << " Digite opcion: "; getline(cin, opcion);

                /*En el caso de que el usuario seleccione una opcion que no esta en el menu, mostrar mensaje de error*/
                if(opcion != "1" and opcion != "2" and opcion != "3" and opcion != "4"){
                        cout << "    Opcion no valida" << endl << endl;
                        system("pause");
                }

                else{ /*Caso contrario, llamar el metodo ejecutarOpcion() y pasarle por parametro la opcion que se selecciono*/
                        ejecutarOpcion(opcion);
                }

        } while(opcion != "4");
}

/*Metodo que recibe como parametro la opcion seleccionada y segun esta sea, realiza lo correspondiente*/
void Menu::ejecutarOpcion(string opcion){
        Archivo archivo; /*Crear objeto de clase "Archivo"*/
        if(opcion == "1"){
                archivo.insertarRegistro(); /*LLamar metodo insertarRegistro()*/
        }

        else if(opcion == "2"){
                archivo.consultar(); /*Llamar metodo consultar()*/
        }

        else if(opcion == "3"){
                archivo.buscarRegistroEliminar(); /*LLamar metodo buscarRegistroEliminar()*/
        }
}
