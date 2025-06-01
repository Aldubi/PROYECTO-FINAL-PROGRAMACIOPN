#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"
using namespace std;

class marcas {
protected:
    string marca;
    int idmarcas = 0;
public:
    marcas() {}
    marcas(string mar, int idm) {
        marca = mar;
        idmarcas = idm;
    }

    // Setters y getters
    void setIdmarcas(int id) { idmarcas = id; }
    void setMarca(string m) { marca = m; }
    int getIdmarcas() { return idmarcas; }
    string getMarca() { return marca; }

    // CRUD
    void crear() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO marcas(marca) VALUES('" + marca + "');";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Marca ingresada correctamente." << endl;
            }
            else {
                cout << "Error al ingresar la marca." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
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
            string query = "SELECT * FROM marcas;";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                cout << "ID\tMarca" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "\t" << fila[1] << endl;
                }
            }
            else {
                cout << "Error al consultar marcas." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id = to_string(idmarcas);
            string query = "UPDATE marcas SET marca='" + marca + "' WHERE idmarcas=" + id + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Marca actualizada correctamente." << endl;
            }
            else {
                cout << "Error al actualizar la marca." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id = to_string(idmarcas);
            string query = "DELETE FROM marcas WHERE idmarcas=" + id + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Marca eliminada correctamente." << endl;
            }
            else {
                cout << "Error al eliminar la marca." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
        }
        cn.cerrar_conexion();
    }

    // CRUD MENU
    void crud_marcas() {
        int opcion;
        do {
            cout << "\n--- CRUD MARCAS ---\n";
            cout << "1. Crear marca\n";
            cout << "2. Ver marcas\n";
            cout << "3. Actualizar marca\n";
            cout << "4. Eliminar marca\n";
            cout << "0. Volver al menu principal\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
            case 1: {
                string nueva_marca;
                cout << "Ingrese nombre de la marca: ";
                getline(cin, nueva_marca);
                marcas m(nueva_marca, 0);
                m.crear();
                break;
            }
            case 2: {
                marcas m;
                m.leer();
                break;
            }
            case 3: {
                int id;
                string nueva_marca;
                cout << "Ingrese ID de la marca a actualizar: ";
                cin >> id; cin.ignore();
                cout << "Ingrese el nuevo nombre: ";
                getline(cin, nueva_marca);
                marcas m(nueva_marca, id);
                m.actualizar();
                break;
            }
            case 4: {
                int id;
                cout << "Ingrese ID de la marca a eliminar: ";
                cin >> id; cin.ignore();
                marcas m("", id);
                m.borrar();
                break;
            }
            case 0:
                cout << "Regresando al menu principal...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
            }
        } while (opcion != 0);
    }
};
