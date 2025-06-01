#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"
#include "ventas.h"
#include "productos.h"

using namespace std;

class ventas_detalle {
protected:
    int idventa = 0;
    int idproducto = 0;
    string cantidad;
    double precio_unitario = 0.0;
public:
    ventas_detalle() {}
    ventas_detalle(int idv, int idp, string cant, double precio) {
        idventa = idv;
        idproducto = idp;
        cantidad = cant;
        precio_unitario = precio;
    }

    // Setters y getters
    void setIdventa(int id) { idventa = id; }
    void setIdproducto(int id) { idproducto = id; }
    void setCantidad(string c) { cantidad = c; }
    void setPrecioUnitario(double p) { precio_unitario = p; }

    int getIdventa() { return idventa; }
    int getIdproducto() { return idproducto; }
    string getCantidad() { return cantidad; }
    double getPrecioUnitario() { return precio_unitario; }

    // CRUD
    void crear() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO ventas_detalle(idventa, idproducto, cantidad, precio_unitario) VALUES (" +
                to_string(idventa) + ", " + to_string(idproducto) + ", '" + cantidad + "', " + to_string(precio_unitario) + ");";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Detalle de venta ingresado correctamente." << endl;
            }
            else {
                cout << "Error al ingresar el detalle de venta." << endl;
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
            string query = "SELECT * FROM ventas_detalle;";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                cout << "idventa\tidproducto\tcantidad\tprecio_unitario" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "\t" << fila[1] << "\t" << fila[2] << "\t" << fila[3] << endl;
                }
            }
            else {
                cout << "Error al consultar ventas_detalle." << endl;
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
            string query = "UPDATE ventas_detalle SET cantidad='" + cantidad +
                "', precio_unitario=" + to_string(precio_unitario) +
                " WHERE idventa=" + to_string(idventa) +
                " AND idproducto=" + to_string(idproducto) + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Detalle de venta actualizado correctamente." << endl;
            }
            else {
                cout << "Error al actualizar el detalle de venta." << endl;
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
            string query = "DELETE FROM ventas_detalle WHERE idventa=" + to_string(idventa) +
                " AND idproducto=" + to_string(idproducto) + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Detalle de venta eliminado correctamente." << endl;
            }
            else {
                cout << "Error al eliminar el detalle de venta." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
        }
        cn.cerrar_conexion();
    }
};