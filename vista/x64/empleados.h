#pragma once
#include "puestos.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>
using namespace std;

class empleados : puestos {
private:
    string nombres, apellidos, direccion, telefono, dpi, fecha_nacimiento, fecha_inicio_labores, fechaingreso;
    int idempleado = 0;
    int genero = 0;

    void pedir_datos_empleado() {
        cout << "Ingrese nombres: ";
        getline(cin, nombres);
        cout << "Ingrese apellidos: ";
        getline(cin, apellidos);
        cout << "Ingrese dirección: ";
        getline(cin, direccion);
        cout << "Ingrese teléfono: ";
        getline(cin, telefono);
        cout << "Ingrese DPI (sin guiones): ";
        getline(cin, dpi);
        cout << "Ingrese género (0 = Femenino, 1 = Masculino): ";
        cin >> genero;
        cin.ignore();
        cout << "Ingrese fecha de nacimiento (YYYY-MM-DD): ";
        getline(cin, fecha_nacimiento);
        cout << "Ingrese ID del puesto: ";
        cin >> idpuesto;
        cin.ignore();
        cout << "Ingrese fecha de inicio de labores (YYYY-MM-DD): ";
        getline(cin, fecha_inicio_labores);
        cout << "Ingrese fecha de ingreso (YYYY-MM-DD): ";
        getline(cin, fechaingreso);
    }

public:
    empleados() {}
    empleados(string pues, int idp, string nom, string ape, string dir, string tel, string dp, int gen, string fn, string fil, string fi)
        : puestos(pues, idp) {
        nombres = nom;
        apellidos = ape;
        direccion = dir;
        telefono = tel;
        dpi = dp;
        genero = gen;
        fecha_nacimiento = fn;
        fecha_inicio_labores = fil;
        fechaingreso = fi;
    }

    void setIdempleado(int e) { idempleado = e; }
    void setNombres(string n) { nombres = n; }
    void setApellidos(string a) { apellidos = a; }
    void setDireccion(string d) { direccion = d; }
    void setTelefono(string t) { telefono = t; }
    void setDpi(string dp) { dpi = dp; }
    void setGenero(int g) { genero = g; }
    void setFecha_nacimiento(string fn) { fecha_nacimiento = fn; }
    void setFecha_inicio_labores(string fil) { fecha_inicio_labores = fil; }
    void setFechaingreso(string fi) { fechaingreso = fi; }
    void setIdpuesto(int idp) { idpuesto = idp; }
    void setPuesto(string p) { puesto = p; }

    int getIdempleado() { return idempleado; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getDireccion() { return direccion; }
    string getTelefono() { return telefono; }
    string getDpi() { return dpi; }
    int getGenero() { return genero; }
    string getFecha_nacimiento() { return fecha_nacimiento; }
    string getFecha_inicio_labores() { return fecha_inicio_labores; }
    string getFechaingreso() { return fechaingreso; }
    int getIdpuesto() { return idpuesto; }
    string getPuesto() { return puesto; }

    void crear() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string p = to_string(idpuesto);
            string g = to_string(genero);
            string consulta = "INSERT INTO empleados(nombres,apellidos,direccion,telefono,dpi,genero,fecha_nacimiento,idpuesto,fecha_inicio_labores,fechaingreso) VALUES ('" +
                nombres + "','" + apellidos + "','" + direccion + "','" + telefono + "','" + dpi + "'," + g + ", '" + fecha_nacimiento + "'," + p + ", '" + fecha_inicio_labores + "','" + fechaingreso + "');";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            cout << (!q_estado ? "Ingreso de datos exitoso..." : "xxxx Consulta fallida xxxx") << endl;
        }
        else {
            cout << "xxxx Conexion fallida xxxx" << endl;
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado = 0;
        ConexionBD cn;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConector()) {
            cout << "-------- Datos del empleado --------" << endl;
            string consulta = "SELECT * FROM empleados;";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "," << fila[1] << "," << fila[2] << "," << fila[3] << "," << fila[4] << "," << fila[5] << "," << fila[6] << "," << fila[7] << "," << fila[8] << "," << fila[9] << "," << fila[10] << endl;
                }
            }
            else {
                cout << "xxxx Consulta fallida xxxx" << endl;
            }
        }
        else {
            cout << "xxx Fallo en la conexion xxx" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string p = to_string(idpuesto);
            string g = to_string(genero);
            string id = to_string(idempleado);
            string consulta = "UPDATE empleados SET nombres='" + nombres +
                "', apellidos='" + apellidos +
                "', direccion='" + direccion +
                "', telefono='" + telefono +
                "', dpi='" + dpi +
                "', genero=" + g +
                ", fecha_nacimiento='" + fecha_nacimiento +
                "', idpuesto=" + p +
                ", fecha_inicio_labores='" + fecha_inicio_labores +
                "', fechaingreso='" + fechaingreso +
                "' WHERE idempleado=" + id + ";";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            cout << (!q_estado ? "Actualización exitosa..." : "xxxx Error en la actualización xxxx") << endl;
        }
        else {
            cout << "xxxx Conexion fallida xxxx" << endl;
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id = to_string(idempleado);
            string consulta = "DELETE FROM empleados WHERE idempleado=" + id + ";";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            cout << (!q_estado ? "Eliminación exitosa..." : "xxxx Error al eliminar xxxx") << endl;
        }
        else {
            cout << "xxxx Conexion fallida xxxx" << endl;
        }
        cn.cerrar_conexion();
    }

    void crud_empleados() {
        int opcion = 0;
        do {
            system("cls");
            cout << "\n====== CRUD EMPLEADOS ======\n";
            cout << "1. Crear empleado\n";
            cout << "2. Leer empleados\n";
            cout << "3. Actualizar empleado\n";
            cout << "4. Eliminar empleado\n";
            cout << "0. Salir\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
            case 1:
                pedir_datos_empleado();
                crear();
                break;
            case 2:
                leer();
                break;
            case 3:
                cout << "Ingrese ID del empleado a actualizar: ";
                cin >> idempleado;
                cin.ignore();
                pedir_datos_empleado();
                actualizar();
                break;
            case 4:
                cout << "Ingrese ID del empleado a eliminar: ";
                cin >> idempleado;
                cin.ignore();
                borrar();
                break;
            case 0:
                cout << "Saliendo del CRUD...\n";
                break;
            default:
                cout << "Opción inválida.\n";
                break;
            }
            system("pause");
        } while (opcion != 0);
    }
};
