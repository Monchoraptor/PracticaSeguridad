#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CLAVE_DEFECTO 10

/* Variables globales */
char *tira_aux={"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};

int main (int argc, char **argv)
{
   char *Alfabeto;
   int clave;
   char *p;
   int longitud_alfabeto;
   int i;
   char caracter;
   int  pos_caracter, pos_nuevo_caracter;

   /* Manejar argumentos */
   if (argc == 1)
      clave = CLAVE_DEFECTO;
   else if (argc == 2)
      clave = atoi(argv[1]);
   if ( (argc > 2) || (clave == 0) ) {
      printf("Uso: \"%s N\" para cifrar con clave=N, o \"%s\" para cifrar con clave=%d\n",argv[0],argv[0],CLAVE_DEFECTO);
      return 1;
   }
   /* Crear alfabeto */
   Alfabeto = strdup(tira_aux);
   /* Calcular la longitud del alfabeto */
   longitud_alfabeto = strlen(Alfabeto);
   /* Poner todas las letras del alfabeto en mayúsculas, por si acaso */
   for (i = 0; i < longitud_alfabeto; i++)
      Alfabeto[i] = toupper(Alfabeto[i]);
   /* Leer los caracteres de la entrada uno por uno */
   while ( (caracter = fgetc(stdin)) != EOF ) {
      /* Convertir carácter a mayúscula si es una letra */
      caracter = toupper(caracter);
      /* Si el carácter es un fin de línea, ponerlo en la salida */
      if (caracter == '\n')
         fputc('\n',stdout);
      /* Si el carácter no está en el alfabeto y no es un salto de línea, poner un blanco */
      else if ( (p = strchr(Alfabeto,caracter)) == NULL )
         fputc(' ',stdout);
      /* Si el carácter está en el alfabeto, encriptarlo */
      else {
         /* Averiguar la posición del carácter en el alfabeto */
         pos_caracter = (int) (p-Alfabeto);
         /* Averiguar la posición del carácter encriptado en el alfabeto */
         pos_nuevo_caracter = (pos_caracter + clave) % longitud_alfabeto;
         // printf("Posición %d; letra: %c (%d) ==> %c (%d)\n",i,buffer[i],pos_letra,Alfabeto[nueva_letra],nueva_letra);
         /* Escribir en la salida estándar el carácter encriptado */
         fputc(Alfabeto[pos_nuevo_caracter],stdout);
      }
   }
   free(Alfabeto);
   return(0);
}

