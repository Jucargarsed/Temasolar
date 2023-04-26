#include <stdio.h>
#include <cmath>
// define constantes
#define Ms 1.989E30
#define UA 1.496E11
#define G 6.67430E-11
#define N 9

//funciones de cambio de unidad
void cambiolong(double longitud[]){
    for (int i = 0; i < N; i++)
    {
        longitud[i]=longitud[i]/UA;
    }
    return;
    
}

void cambiomasas(double masas[]){
    for (int i = 0; i < N; i++)
    {
        masas[i]=masas[i]/Ms;
    }
    return;
}

void cambiovelocidad(double Velocidad[]){
    double c;
    c=1/(UA*sqrt((G*Ms/(pow(UA,3)))));
     for (int i = 0; i < N; i++)
    {
        Velocidad[i]=Velocidad[i]*c;
    }
    return;
}

void calcAceleracion(double posicionX[],double posicionY[], double masas[],double aceleracionX[], double aceleracionY[]){
    double sumaX, sumaY, modulo, numeradorX, numeradorY;
    numeradorX=0.0;
    numeradorY=0.0;
    for (int i = 0; i < N; i++)
    {
        sumaX=0.0;
        sumaY=0.0;
        //inicializamos sumas a 0, para que no se sobre escriban
             for (int j = 0; j < N; j++)
        {
             if (j!=i)
        {
          numeradorX=posicionX[i]-posicionX[j];
          numeradorY=posicionY[i]-posicionY[j];
          modulo=sqrt(pow(numeradorX,2)+pow(numeradorY,2));
          //calculamos cada termino de la aceleracion
            sumaX=sumaX-masas[j]*numeradorX/(modulo*modulo*modulo);
            sumaY=sumaY-masas[j]*numeradorY/(modulo*modulo*modulo);
            
        }
        }
        //printf("%lf\t%lf\t", aceleracionX[i],aceleracionY[i]);
        //printf("\n");
        aceleracionX[i]=sumaX;
        aceleracionY[i]=sumaY;
        
    }
    // printf("\n");
    return;
}

void calcWvector(double velocidad[], double aceleracion[], double Wvector[], double h){
    for (int i = 0; i < N; i++)
    {
        Wvector[i]=velocidad[i]+h*aceleracion[i]/2.0;
    }
    
    return;
}


double Tcinetica(double velocidadX[],double velocidadY[], double masas[]){
    double T=0.0;
    for (int i = 0; i < N; i++)
    {
        T=T+masas[i]*(pow(velocidadX[i],2)+pow(velocidadY[i],2));
    }
    
    return T/2.0;
}

double calculoPotenc(double posicionX[], double posicionY[], double masas[]){

    double PotencialP=0.0;
    double PotencialT=0.0;
    double separacionX=0;
    double separacionY=0;

    for (int i = 0; i < N; i++)
    {
        PotencialP=0.0;
        for (int j = 0; j < N; j++)
        {
            if(j!=i){
                //el numerador de cada interaccion con un planeta

            separacionX=posicionX[i]-posicionX[j];
            separacionY=posicionY[i]-posicionY[j];

            PotencialP=PotencialP+masas[j]/sqrt(separacionX*separacionX+separacionY*separacionY);
        }
        }
        //suma al total
        PotencialT=PotencialT+PotencialP*masas[i];
        
    }
    return -PotencialT;
}

void calculoPeriodo(double posicionY[], double Periodo[], double t){
   for (int i = 0; i < N; i++)
   {
     if (posicionY[i]<0 && Periodo[i]==0)
    {
        Periodo[i]=2*t;
    }
   }
   return ;
   
    
} 

int main(){
    double posicionX[N];
    double posicionY[N];
    double masas[N];
    double velocidadY[N];
    double velocidadX[N];
    double Periodo[N]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double aceleracionX[N]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double aceleracionY[N]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double WvectorY[N]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double WvectorX[N]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double h=0.2;
    double t=0.0;
    double T, P,U;

//leen ficheros
 FILE *fposicion;
    fposicion = fopen("posiciones2.txt", "r");
    //FILE *archivo2;
    //archivo2 = fopen("nombre_archivo2.txt", "r");
for (int i = 0; i < N; i++) {
    fscanf(fposicion, "%lf,%lf", &posicionX[i], &posicionY[i]);
    //fscanf(archivo2, "%lf\t", &vectorsegundo[i]);
}
   
fclose(fposicion);

 FILE *fvelocidad;
    fvelocidad = fopen("velocidades2.txt", "r");
    //FILE *archivo2;
    //archivo2 = fopen("nombre_archivo2.txt", "r");
for (int i = 0; i < N; i++) {
    fscanf(fvelocidad, "%lf,%lf", &velocidadX[i], &velocidadY[i]);
    //fscanf(archivo2, "%lf\t", &vectorsegundo[i]);
}
   

fclose(fvelocidad);

//fclose(archivo2);
FILE *fmasas;
    fmasas = fopen("masas2.txt", "r");
    //FILE *archivo2;
    //archivo2 = fopen("nombre_archivo2.txt", "r");
for (int i = 0; i < N; i++) {
    fscanf(fmasas, "%lf", &masas[i]);
    //fscanf(archivo2, "%lf\t", &vectorsegundo[i]);
}
   

fclose(fmasas);





    cambiolong(posicionX);
    cambiolong(posicionY);
    cambiovelocidad(velocidadY);
    cambiomasas(masas);
  //calculamos la aceleracion

    calcAceleracion(posicionX,posicionY,masas,aceleracionX,aceleracionY);

   
    
    //abre el fichero donde se van a escribir los datos
    FILE *salidaX;
    FILE *salidaY;

     if ((salidaX = fopen("LaPOSICIONX2.txt", "a")) == NULL) 
    {
        printf("error");
    }
    

   while (t<50.0)
   {
     //imprimos los valores en los ficheros
    salidaX=fopen("LaPOSICIONX2.txt", "a");
    //salidaY=fopen("LaPOSICIONY2.txt", "a");
    salidaY=fopen("EnergiaU.txt", "a");

    for (int k = 0; k < N; k++)
    {
        fprintf(salidaX, "%lf,%lf\n", posicionX[k],posicionY[k]);
        //fprintf(salidaY,"%lf\t", posicionY[k]);
        //decimos que de ultimas meta salto de linea
    }
        fprintf(salidaX, "\n");
        //fprintf(salidaY,"\n");

        //calculamos el periodo
        calculoPeriodo(posicionY, Periodo, t);


        //calculamos la nueva iteracion r(t+h)=r(t)+hw(t)
        calcWvector(velocidadX,aceleracionX,WvectorX,h);
        calcWvector(velocidadY,aceleracionY,WvectorY,h);

        T=Tcinetica(velocidadX,velocidadY,masas);
        P=calculoPotenc(posicionX,posicionY,masas);
        U=T+P;
        
        fprintf(salidaY, "%lf\n", U);
        

        for (int i = 0; i < N; i++)
        {
            posicionX[i]=posicionX[i]+h*WvectorX[i];
            posicionY[i]=posicionY[i]+h*WvectorY[i];
        }
    
        //se recalcula la aceleracion con las nuevas posiciones

        calcAceleracion(posicionX,posicionY,masas,aceleracionX,aceleracionY);

        //nueva vector velocidad 
        for (int i = 0; i < N; i++)
        {
            velocidadX[i]=WvectorX[i]+h*aceleracionX[i]/2.0;
            velocidadY[i]=WvectorY[i]+h*aceleracionY[i]/2.0;
        }

        
   
    t=t+h;
   }
   
     fclose(salidaX);
     fclose(salidaY);
    //fclose(salidaY);

    //si quiero mas precision en los periodos, pongo un paso h más pequeño
    for (int i = 0; i < N; i++)
    {
        printf("%lf\t", Periodo[i]);
    }
    
    
    
    return 0;
}