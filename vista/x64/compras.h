#pragma once
#include <iostream>
#include <string>
#include "proveedores.h"
#include "ConexionBD.h"
using namespace std;

class compras : public proveedores {
protected:
    int no_orden_compra = 0;
    string fecha_orden, fechaingreso;
public:
    compras() {}
    compras(int no_orden, int idprov, string fecha_ord, string fecha_ing,
        string prov = "", string nt = "", string dir = "", string tel = "")
        : proveedores(prov, nt, dir, tel, idprov) {
        no_orden_compra = no_orden;
        fecha_orden = fecha_ord;
        fechaingreso = fecha_ing;
    }

    // Setters y getters
    void setNoOrdenCompra(int n) { no_orden_compra = n; }
    void setFechaOrden(string f) { fecha_orden = f; }
    void setFechaIngreso(string f) { fechaingreso = f; }

    int getNoOrdenCompra() { return no_orden_compra; }
    string getFechaOrden() { return fecha_orden; }
    string getFechaIngreso() { return fechaingreso; }

    // CRUD
    void crear() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO compras(no_orden_compra, idproveedore, fecha_orden, fechaingreso) VALUES (" +
                to_string(no_orden_compra) + ", " + to_string(idproveedore) + ", '" + fecha_orden + "', '" + fechaingreso + "');";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Compra ingresada correctamente." << endl;
            }
            else {
                cout << "Error al ingresar la compra." << endl;
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
            string query = "SELECT * FROM compras;";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                cout << "NoOrden\tIdProveedor\tFechaOrden\tFechaIngreso" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "\t" << fila[1] << "\t" << fila[2] << "\t" << fila[3] << endl;
                }
            }
            else {
                cout << "Error al consultar compras." << endl;
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
            string query = "UPDATE compras SET idproveedore=" + to_string(idproveedore) +
                ", fecha_orden='" + fecha_orden +
                "', fechaingreso='" + fechaingreso +
                "' WHERE no_orden_compra=" + to_string(no_orden_compra) + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Compra actualizada correctamente." << endl;
            }
            else {
                cout << "Error al actualizar la compra." << endl;
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
            string query = "DELETE FROM compras WHERE no_orden_compra=" + to_string(no_orden_compra) + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Compra eliminada correctamente." << endl;
            }
            else {
                cout << "Error al eliminar la compra." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
        }
        cn.cerrar_conexion();
    }
};