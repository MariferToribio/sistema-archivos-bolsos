///   216623393 LUEVANO MARTINEZ STEVEN
///   216850837 TORIBIO TORRES MARIFER

///   MATERIA: ESTRUCTURAS DE DATOS 2
///   SECCION: D08

///   PROFESOR: GRACIELA LARA LOPEZ

#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

class Archivo{
        private:
                /*Estructura de registro de datos de un bolso*/
                struct Bolso{
                        char clave[9];
                        std::string nombre;
                        std::string descripcion;
                };

                Bolso solicitarDatos();
                std::string hacerLlave(std::string);

                void eliminarRegistro(char[]);
                std::string quitarAsterisco(std::string);

        public:
                void insertarRegistro();
                void consultar();
                void buscarRegistroEliminar();
};

#endif // ARCHIVO_H_INCLUDED
