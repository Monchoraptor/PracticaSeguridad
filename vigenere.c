#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Variables globales */
char *tira_aux={"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};

int main (int argc, char **argv)
{
   char *Alfabeto;
   char *clave;
   int  *pos_clave;
   int  longitud_clave;
   int  iclave, i;
   int  longitud_alfabeto;
   char caracter;
   int  pos_caracter, pos_nuevo_caracter;
   char *p;

   /* Manejar argumentos */
   if (argc == 2) {
      clave = strdup(argv[1]);
      longitud_clave = strlen(clave);
         }
   if ( (argc != 2)) {
      printf("Uso: \"%s clave\" donde \"clave\" es una tira de caracteres compuesta exclusivamente por letras mayúsculas\n",argv[0]);
      return 1;
   }
   /* Crear alfabeto */
   Alfabeto = strdup(tira_aux);

   /* Calcular la longitud del alfabeto */
   longitud_alfabeto = strlen(Alfabeto);

   /* Poner todas las letras del alfabeto en mayusculas, por si acaso */
   for (i = 0; i < longitud_alfabeto; i++)
      Alfabeto[i] = toupper(Alfabeto[i]);

   /* Calcular las posiciones de los elementos de la clave en el alfabeto, y guardarlas en un vector */
   pos_clave = malloc(strlen(clave) * sizeof (int));
   for (i = 0; i < longitud_clave; i++)
      pos_clave[i] = (int) (strchr(Alfabeto,clave[i]) - Alfabeto);

   /* Comenzar la encriptacion por el primer caracter de la clave */
   iclave = 0;

   /* Leer los caracteres de la entrada uno por uno */
   while ( (caracter = fgetc(stdin)) != EOF ) {
      
	/* Convertir caracter a mayuscula si es una letra */
      caracter = toupper(caracter);
      
	/* Si el caracter es un fin de li­nea, ponerlo en la salida */
      if (caracter == '\n')
         fputc('\n',stdout);
      
	/* Si el caracter no esta en el alfabeto y no es un salto de li­nea, poner un blanco */
      else if ( (p = strchr(Alfabeto,caracter)) == NULL )
         fputc(' ',stdout);
      
	/* Si el caracter esta en el alfabeto, encriptarlo */
      else {
         /* Averiguar la posicion del caracter en el alfabeto */
         pos_caracter = (int) (p-Alfabeto);
  
         /* Averiguar la posicion del caracter encriptado en el alfabeto */
          pos_nuevo_caracter = (pos_caracter + pos_clave[iclave]) % longitud_alfabeto;
   
         // printf("Posicion %d; letra: %c (%d) ==> %c (%d)\n",i,buffer[i],pos_letra,Alfabeto[nueva_letra],nueva_letra);
         /* Escribir en la salida estÃ¡ndar el carÃ¡cter encriptado */
         fputc(Alfabeto[pos_nuevo_caracter],stdout);
     
         /* Pasar al siguiente caracter de la clave */
         iclave = (iclave + 1) % longitud_clave;
      }
   }
   free(pos_clave);
   free(Alfabeto);
   return(0);
}

