#pragma once
#include <iostream>
#include <string>
#include "compras.h"
#include "productos.h"
#include "ConexionBD.h"
using namespace std;

class compras_detalle : public compras, public productos {
protected:
    int idcompra = 0;
    int idproducto = 0;
    int cantidad = 0;
    double precio_costo_unitario = 0.0;
public:
    compras_detalle() {}
    compras_detalle(int idc, int idp, int cant, double precio) {
        idcompra = idc;
        idproducto = idp;
        cantidad = cant;
        precio_costo_unitario = precio;
    }

    // Setters y getters
    void setIdcompra(int id) { idcompra = id; }
    void setIdproducto(int id) { idproducto = id; }
    void setCantidad(int c) { cantidad = c; }
    void setPrecioCostoUnitario(double p) { precio_costo_unitario = p; }

    int getIdcompra() { return idcompra; }
    int getIdproducto() { return idproducto; }
    int getCantidad() { return cantidad; }
    double getPrecioCostoUnitario() { return precio_costo_unitario; }

    // CRUD
    void crear() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO compras_detalle(idcompra, idproducto, cantidad, precio_costo_unitario) VALUES (" +
                to_string(idcompra) + ", " + to_string(idproducto) + ", " + to_string(cantidad) + ", " + to_string(precio_costo_unitario) + ");";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Detalle de compra ingresado correctamente." << endl;
            }
            else {
                cout << "Error al ingresar el detalle de compra." << endl;
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
            string query = "SELECT * FROM compras_detalle;";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                cout << "idcompra\tidproducto\tcantidad\tprecio_costo_unitario" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "\t" << fila[1] << "\t" << fila[2] << "\t" << fila[3] << endl;
                }
            }
            else {
                cout << "Error al consultar compras_detalle." << endl;
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
            string query = "UPDATE compras_detalle SET cantidad=" + to_string(cantidad) +
                ", precio_costo_unitario=" + to_string(precio_costo_unitario) +
                " WHERE idcompra=" + to_string(idcompra) +
                " AND idproducto=" + to_string(idproducto) + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Detalle de compra actualizado correctamente." << endl;
            }
            else {
                cout << "Error al actualizar el detalle de compra." << endl;
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
            string query = "DELETE FROM compras_detalle WHERE idcompra=" + to_string(idcompra) +
                " AND idproducto=" + to_string(idproducto) + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Detalle de compra eliminado correctamente." << endl;
            }
            else {
                cout << "Error al eliminar el detalle de compra." << endl;
            }
        }
        else {
            cout << "Error de conexion." << endl;
        }
        cn.cerrar_conexion();
    }
};