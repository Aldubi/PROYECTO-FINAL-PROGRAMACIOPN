#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"
using namespace std;

class puestos {
protected:
    string puesto;
    int idpuesto = 0;
public:
    puestos() {}
    puestos(string pue, int idp) {
        puesto = pue;
        idpuesto = idp;
    }

    // Setters y getters
    void setIdpuesto(int id) { idpuesto = id; }
    void setPuesto(string p) { puesto = p; }
    int getIdpuesto() { return idpuesto; }
    string getPuesto() { return puesto; }

    // CRUD
    void crear() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO puestos(puesto) VALUES('" + puesto + "');";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Puesto ingresado correctamente." << endl;
            }
            else {
                cout << "Error al ingresar el puesto." << endl;
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
            string query = "SELECT * FROM puestos;";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                cout << "ID\tPuesto" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "\t" << fila[1] << endl;
                }
            }
            else {
                cout << "Error al consultar puestos." << endl;
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
            string id = to_string(idpuesto);
            string query = "UPDATE puestos SET puesto='" + puesto + "' WHERE idpuesto=" + id + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Puesto actualizado correctamente." << endl;
            }
            else {
                cout << "Error al actualizar el puesto." << endl;
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
            string id = to_string(idpuesto);
            string query = "DELETE FROM puestos WHERE idpuesto=" + id + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Puesto eliminado correctamente." << endl;
            }
            else {
                cout << "Error al eliminar el puesto." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
        }
        cn.cerrar_conexion();
    }
};