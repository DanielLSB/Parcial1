#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

using namespace std;
void gotoxy(int x, int y)
{
 HANDLE hcon;
 hcon = GetStdHandle(STD_OUTPUT_HANDLE);
 COORD dwPos;
 dwPos.X = x;
 dwPos.Y = y;
 SetConsoleCursorPosition(hcon,dwPos);
}

const char *nombre_archivo="archivo.dat";
struct Trabajo{
int codigo;
char nombres[50];
char apellidos[50];
char puesto[50];
float sueldo;
float bonificacion;
float total;
};
void abrir();
void ingresar();
void buscar_indice();
void modificar();
void buscar_codigo();
void eliminar();
main(){
	int op;
do{
system("cls");
gotoxy(40,1);cout<<" REGISTRO DE PERSONAL"<<endl;
gotoxy(40,2);cout<<"1. ingreso de datos"<<endl;
gotoxy(40,3);cout<<"2. datos"<<endl;
gotoxy(40,4);cout<<"3. modificar"<<endl;
gotoxy(40,5);cout<<"4. buscar registro"<<endl;
gotoxy(40,6);cout<<"5. eliminar"<<endl;
gotoxy(40,7);cout<<"6. salir"<<endl;
gotoxy(40,8);cout<<"ingrese su opcion"<<endl;
gotoxy(40,9);cin>>op;

     switch(op){
	 
     case 1:
	 ingresar();
	 break;
	 
	 case 2:
	 abrir();
	 break;
	 
	 case 3:
	 modificar();
	 break;
	 
	 case 4:
	 buscar_codigo();
	 break;
	
	case 5:
	eliminar();
    break;
}
}while(op<=5);
}

void ingresar(){
char continuar;
FILE* archivo=fopen(nombre_archivo,"ab");
Trabajo trabajo;
string nombre,apellido,puesto;	
do{
	fflush(stdin);
	system("cls");
cout<<"ingrese el codigo:";
cin>>trabajo.codigo;
cin.ignore();
cout<<"ingrese los nombres:";
getline(cin,nombre);
strcpy(trabajo.nombres,nombre.c_str());
cout<<"ingrese los apellidos:";
getline(cin,apellido);
strcpy(trabajo.apellidos,apellido.c_str());
cout<<"ingrese el puesto:";
getline(cin,puesto);
strcpy(trabajo.puesto,puesto.c_str());
cout<<"ingrese el suedo base:";
cin>>trabajo.sueldo;
cout<<"ingrese bonificaiones:";
cin>>trabajo.bonificacion;
trabajo.total=trabajo.sueldo+trabajo.bonificacion;
cout<<"El sueldo total es: "<<trabajo.total;
cout<<endl;
fwrite(&trabajo,sizeof(Trabajo),1,archivo);

	cout<<"desea agregar otro nombre (s/n):";
	cin>>continuar;
}while(continuar=='s'||continuar=='S');
fclose(archivo);

}

void abrir(){
	system("cls");
	FILE* archivo=fopen(nombre_archivo,"rb");
	if(!archivo){
		archivo=fopen(nombre_archivo,"w+b");;
	}
	
	Trabajo trabajo;
	int registro=0;
	int cont=3;
	
fread(&trabajo,sizeof(Trabajo),1,archivo);

gotoxy(1,1);cout<<"ID"<<endl;
gotoxy(4,1);cout<<"CODIGO"<<endl;
gotoxy(15,1);cout<<"NOMBRE"<<endl;
gotoxy(39,1);cout<<"APELLIDO"<<endl;
gotoxy(60,1);cout<<"PUESTO"<<endl;
gotoxy(78,1);cout<<"SUELDO B"<<endl;
gotoxy(95,1);cout<<"BONIFICAION"<<endl;
gotoxy(110,1);cout<<"TOTAL"<<endl;
do{

	
gotoxy(1,cont);cout<<registro<<endl;
gotoxy(5,cont);cout<<trabajo.codigo<<endl;
gotoxy(13,cont);cout<<trabajo.nombres<<endl;
gotoxy(37,cont);cout<<trabajo.apellidos<<endl;
gotoxy(60,cont);cout<<trabajo.puesto<<endl;
gotoxy(78,cont);cout<<"Q"<<trabajo.sueldo<<endl;
gotoxy(95,cont);cout<<"Q"<<trabajo.bonificacion<<endl;
gotoxy(110,cont);cout<<"Q"<<trabajo.total<<endl;

	fread(&trabajo,sizeof(Trabajo),1,archivo);
	
registro+=1;
cont+=1;

} while(feof(archivo)==0); 
cout<<endl;
fclose(archivo);	
system("pause");

}
void buscar_codigo(){
	system("cls");
FILE* archivo=fopen(nombre_archivo,"rb");	
int indice=0,pos=0,cod=0;
cout<<"buscar codigo:";
cin>>cod;
Trabajo trabajo;
fread(&trabajo,sizeof(Trabajo),1,archivo);
	do{
		if(trabajo.codigo==cod){
        pos = indice;
		}
		fread(&trabajo,sizeof(Trabajo),1,archivo);
		indice+=1;
	}while(feof(archivo)==0);
	
	fseek(archivo,pos * sizeof(Trabajo),SEEK_SET);
	fread(&trabajo,sizeof(Trabajo),1,archivo);
cout<<"codigo: "<<trabajo.codigo<<endl;
cout<<"nombres:"<<trabajo.nombres<<endl;
cout<<"apellido:"<<trabajo.apellidos<<endl;
cout<<"puesto:"<<trabajo.puesto<<endl;
cout<<"sueldo:"<<trabajo.sueldo<<endl;
cout<<"boficacion:"<<trabajo.bonificacion<<endl;
cout<<"total:"<<trabajo.total<<endl;

fclose(archivo);
system("pause");

}

void modificar(){
	system("cls");
	abrir();
	FILE* archivo=fopen(nombre_archivo,"r+b");
	string nombre,apellido,puesto;
		Trabajo trabajo;
	int id=0;
cout<<"que resistro desea modificar (id):";
cin>>id;
fseek(archivo,id * sizeof(Trabajo),SEEK_SET);
cout<<"ingrese nuevo codigo: ";
cin>>trabajo.codigo;
cin.ignore();
cout<<"ingrese nuevo nombres: ";
getline(cin,nombre);
strcpy(trabajo.nombres,nombre.c_str());	
cout<<"ingrese nuevo apellidos: ";
getline(cin,apellido);
strcpy(trabajo.apellidos,apellido.c_str());
cout<<"ingrese nuevo puesto: ";
getline(cin,puesto);
strcpy(trabajo.puesto,puesto.c_str());
cout<<"ingrese nuevo sueldo: ";
cin>>trabajo.sueldo;
cout<<"ingrese nuevas bonificaciones: ";
cin>>trabajo.bonificacion;
trabajo.total=trabajo.sueldo+trabajo.bonificacion;
cout<<"El nuevo total es: "<<trabajo.total<<endl;
	
fwrite(&trabajo,sizeof(Trabajo ),1,archivo);
fclose(archivo);
system("pause");

}

void eliminar(){
    
    system("cls");
    int pos=0;
    cout<<"\nIngresa el codigo a eliminar: "<<endl;
    cin>>pos;
      
    FILE* archivo = fopen(nombre_archivo, "rb");
	FILE* archivo2 = fopen("auxi.dat", "a+b");
    Trabajo trabajo;
    fread ( &trabajo, sizeof(Trabajo), 1, archivo );

	while (feof( archivo ) == 0){
    
	if (pos == trabajo.codigo){
        cout<<"Registro Eliminado"<<endl;
        cout<<endl;
    } else
        fwrite( &trabajo, sizeof(Trabajo), 1, archivo2 );
    fread ( &trabajo, sizeof(Trabajo), 1, archivo );
    
    }
    fclose(archivo);
    fclose(archivo2);
    remove("archivo.dat");
    rename("auxi.dat","archivo.dat");
    system("pause");

}

