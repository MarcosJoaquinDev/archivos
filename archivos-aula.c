// Realizar un programa que maneje un archivo de longitud desconocida, donde cada
// registro contiene el nombre de un alumno y cuatro notas. Hacerlo con un menú que permita
// crear el archivo, calcular el promedio, mostrarlo, buscar un registro determinado, modificar
// una nota, agregar registros y ordenar el archivo alfabéticamente.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alumno {
    char nombre[20];
    int notas[4];
};

int mostrar_menu();
//void crear_archivo();

int main(){

    int opcion ;
    FILE * arch;                   //FLUJO DEL ARCHIVO
    char archivo_nuevo[15];       // VARIABLE PARA NOMBRAR AL ARCHIVO
    char registro_busqueda[20];  // VARIABLE PARA BUSCAR EL NOMBRE EN UN REGISTRO
    struct alumno x,y;          // ESTRUCTURA PARA MODIFICACIONES EN MEMORIA
    int cantidad, nota = 4, i,j;    // CONTADORES
    float promedio; // ACUMULADOR
    int nota_modificada, numero_nota; // VARIABLE DE LAS BUSQUEDAS DE LAS NOTAS
    char caracter; // CONTADOR PARA TAMAÑO DEL ARCHIVO


   opcion = mostrar_menu();

    while(opcion>0 && opcion< 8){

       //OPCION PARA CRECION DE ARCHIVO
      if (opcion==1){
            fflush(stdin);
            printf("\n\t INGRESE EL NOMBRE DEL ARCHIVO = ");
            gets(archivo_nuevo);

            if ( (arch = fopen(archivo_nuevo, "wb") ) == NULL ){
                printf("error archivo");
                exit(1);
            }
            printf("\n\t INGRESAR CANTIDAD DE ALUMMNOS = ");
            scanf("%d", &cantidad);

            while(cantidad){
            fflush(stdin);
            printf("NOMBRE DEL ALUMNO = ");
            gets(x.nombre);

                for(i=0; i < nota; i++){
                    printf("NOTA %d = ", i+1);
                    scanf("%d", &x.notas[i] );
                }
            fwrite(&x, sizeof(x), 1, arch);
            cantidad--;
            }

            fclose(arch);
        }
        // OPCION PARA SACAR EL PROMEDIO
        if (opcion==2){
            fflush(stdin);
            printf("NOMBRE DEL ARCHIVO QUE DESEA LEER: ");
            gets(archivo_nuevo);

            if ( (arch = fopen(archivo_nuevo, "rb") ) == NULL ){
                printf("error archivo");
                exit(1);
            }
           fread(&x, sizeof(x), 1, arch);
           while(!feof(arch)){
                promedio = 0;
                for(i=0; i<nota; i++ ){
                    promedio=promedio + x.notas[i];
                }
           printf("\n\n");
           printf("EL PROMEDIO DE %s es %.2f \n\n", x.nombre, promedio/nota);
           fread(&x, sizeof(x), 1, arch);
           }

        }
        // OPCION PARA LA BUSQUEDA DE ALGUN REGISTRO
        if (opcion==3){

            fflush(stdin);
            printf("\n\t NOMBRE DEL ARCHIVO QUE DESEA BUSCAR REGISTRO: ");
            gets(archivo_nuevo);

           if ( (arch = fopen(archivo_nuevo, "rb") ) == NULL ){
                printf("error archivo");
                exit(1);
            }
            printf("\n\t NOMBRE DEL ALUMNO = ");
            gets(registro_busqueda);
            fflush(stdin);

            fread(&x, sizeof(x), 1, arch);
            while(!feof(arch)){
                if ( strcmp(registro_busqueda, x.nombre)==0){
                    printf("\n\n\t %-15s %-7s %-7s %-7s %-7s", "ALUMNO","NOTA 1","NOTA 2","NOTA 3","NOTA 4");
                    printf("\n\n\t %-15s   %-7d %-7d %-7d %-7d\n\n",x.nombre, x.notas[0],x.notas[1],x.notas[2], x.notas[3] );
                }
             fread(&x, sizeof(x), 1, arch);
            }
        }
        //MODIFICAR ALGUNA NOTA DE ALGUN ALUMNO
        if (opcion == 4){
            fflush(stdin);
            printf("\n\t NOMBRE DEL ARCHIVO QUE DESEA BUSCAR REGISTRO: ");
            gets(archivo_nuevo);

           if ( (arch = fopen(archivo_nuevo, "r+b") ) == NULL ){
                printf("error archivo");
                exit(1);
            }
            printf("\n\t NOMBRE DEL ALUMNO = ");
            gets(registro_busqueda);
            fflush(stdin);
            printf("\n\t NOTA QUE DESEA MODIFICAR ----> /1/2/3/4/ = ");
            scanf("%d", &numero_nota);

            fread(&x, sizeof(x), 1, arch);
            while(!feof(arch)){
                if ( strcmp(registro_busqueda, x.nombre)==0){
                     printf("\n\tNOTA ACTUAL = %d", x.notas[numero_nota-1]);
                     printf("\n\tNOTA NUEVA = ");
                     scanf("%d",&nota_modificada);
                     x.notas[numero_nota-1]= nota_modificada;
                     fseek(arch, (long)(-1 * sizeof(x)),SEEK_CUR);
                     fwrite(&x, sizeof(x), 1, arch);
                     fseek(arch, 0 ,SEEK_CUR);
                }
              fread(&x, sizeof(x), 1, arch);

            }

            }
         // AGREGAR REGISTROS AL ARCHIVO
         if (opcion == 5 ){

            fflush(stdin);
            printf("NOMBRE DEL ARCHIVO DONDE DESEA AGREGAR REGISTROS: ");
            gets(archivo_nuevo);

            if ( (arch = fopen(archivo_nuevo, "ab") ) == NULL ){
                printf("error archivo");
                exit(1);
            }

            printf("\n\t INGRESAR CANTIDAD DE ALUMMNOS = ");
            scanf("%d", &cantidad);

                while(cantidad){
                fflush(stdin);
                printf("NOMBRE DEL ALUMNO = ");
                gets(x.nombre);

                    for(i=0; i < nota; i++){
                        printf("NOTA %d = ", i+1);
                        scanf("%d", &x.notas[i] );
                    }
                fwrite(&x, sizeof(x), 1, arch);
                cantidad--;
                }
                fclose(arch);
         }
        if (opcion==6){
            fflush(stdin);
            printf("\n\t NOMBRE DEL ARCHIVO QUE DESEA ORDENAR ");
            gets(archivo_nuevo);

            if ( (arch = fopen(archivo_nuevo, "r+b") ) == NULL ){
                printf("error archivo");
                exit(1);
            }
            caracter = getc(arch);

            while( !feof(arch) ){
            caracter = getc(arch);
            cantidad++;
            }
            int N;
            N = cantidad / sizeof(x);

            fread(&x, sizeof(x),1,arch);
            for(i=0; i<N-1; i++){
                for(j=0; j<N-i-1; j++){
                    fseek(arch, j*sizeof(x),SEEK_SET );
                    fread(&x, sizeof(x), 1, arch );
                    fread(&y, sizeof(y), 1, arch);

                    if ( strcmp(x.nombre ,y.nombre ) > 0){
                        fseek(arch, (long)(-2 * sizeof(x)) , SEEK_CUR );
                        fwrite(&y, sizeof(x), 1, arch );
                        fwrite(&x, sizeof(y), 1, arch);
                    }
                }
            }
        }
        if(opcion==7){
            fflush(stdin);
            printf("\n\t NOMBRE DEL ARCHIVO QUE DESEA MOSTRAR ");
            gets(archivo_nuevo);

            if ( (arch = fopen(archivo_nuevo, "rb") ) == NULL ){
                printf("error archivo");
                exit(1);
            }
           printf("\n\n\t %-15s %-7s %-7s %-7s %-7s","NOMBRE","NOTA1","NOTA2","NOTA3","NOTA4");
           fread(&x, sizeof(x),1,arch );
           while(!feof(arch)){
            printf("\n\n\t %-15s %-7d %-7d %-7d %-7d",x.nombre, x.notas[0],x.notas[1],x.notas[2], x.notas[3] );
            fread(&x, sizeof(x),1,arch );
           }

        }

     opcion= mostrar_menu();
    }
}
int mostrar_menu(){
 int opcion;
 printf("\n\t----------------------");
 printf("\n\t|1| CREAR ARCHIVO     ");
 printf("\n\t----------------------");
 printf("\n\t|2| MOSTRAR PROMEDIO  ");
 printf("\n\t----------------------");
 printf("\n\t|3| BUSCAR REGISTRO   ");
 printf("\n\t----------------------");
 printf("\n\t|4| MODIFICAR NOTA    ");
 printf("\n\t----------------------");
 printf("\n\t|5| AGREGAR REGISTROS ");
 printf("\n\t----------------------");
 printf("\n\t|6| ORDENAR REGISTROS ");
 printf("\n\t----------------------");
 printf("\n\t|7| MOSTRAR REGISTROS ");
 printf("\n\t----------------------\n\n");

 scanf("%d", &opcion);
 return opcion;

 }

