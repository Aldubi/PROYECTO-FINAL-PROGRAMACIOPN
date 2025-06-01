#pragma once
#include "marcas.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>
using namespace std;

class productos : public marcas {
private:
    string producto, descripcion, imagen, fecha_ingreso;
    double precio_costo = 0.0, precio_venta = 0.0;
    int idproducto = 0, idmarcas = 0, existencia = 0;

public:
    productos() {}
    productos(string mar, int idm, string prod, string des, string img, double pc, double pv, int idp, int exi)
        : marcas(mar, idm) {
        producto = prod;
        descripcion = des;
        imagen = img;
        precio_costo = pc;
        precio_venta = pv;
        idproducto = idp;
        existencia = exi;
    }

    // Setters
    void setIdproducto(int p) { idproducto = p; }
    void setProducto(string pr) { producto = pr; }
    void setDescripcion(string d) { descripcion = d; }
    void setImagen(string g) { imagen = g; }
    void setFechaingreso(string f) { fecha_ingreso = f; }
    void setPreciocosto(double pc) { precio_costo = pc; }
    void setPrecioventa(double pv) { precio_venta = pv; }
    void setIdmarcas(int idm) { idmarcas = idm; }
    void setExistencia(int exi) { existencia = exi; }

    // Getters
    int getIdproducto() const { return idproducto; }
    string getProducto() { return producto; }
    string getDescripcion() { return descripcion; }
    string getImagen() { return imagen; }
    string getFechaingreso() { return fecha_ingreso; }
    double getPreciocosto() const { return precio_costo; }
    double getPrecioventa() const { return precio_venta; }
    int getIdmarca() const { return idmarcas; }
    int getExistencia() const { return existencia; }

    void crear() const {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string m = to_string(idmarcas);
            string p = to_string(idproducto);
            string e = to_string(existencia);
            string consulta = "INSERT INTO productos(idproducto,producto,idmarca,descripcion,imagen,precio_costo,precio_venta,existencia,fecha_ingreso) VALUES (" +
                p + ",'" + producto + "'," + m + ",'" + descripcion + "','" + imagen + "'," +
                to_string(precio_costo) + "," + to_string(precio_venta) + "," + e + ",'" + fecha_ingreso + "');";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Ingreso de datos exitoso..." << endl;
            }
            else {
                cout << "xxxx Consulta fallida xxxx" << endl;
            }
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
            cout << "Datos de los productos" << endl;
            string consulta = "SELECT * FROM productos;";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "," << fila[1] << "," << fila[2] << "," << fila[3] << "," << fila[4]
                        << "," << fila[5] << "," << fila[6] << "," << fila[7] << "," << fila[8] << endl;
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
            string m = to_string(idmarcas);
            string p = to_string(idproducto);
            string e = to_string(existencia);
            string consulta = "UPDATE productos SET producto='" + producto +
                "', idmarca=" + m +
                ", descripcion='" + descripcion +
                "', imagen='" + imagen +
                "', precio_costo=" + to_string(precio_costo) +
                ", precio_venta=" + to_string(precio_venta) +
                ", existencia=" + e +
                ", fecha_ingreso='" + fecha_ingreso +
                "' WHERE idproducto=" + p + ";";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Actualización exitosa..." << endl;
            }
            else {
                cout << "xxxx Error en la actualización xxxx" << endl;
            }
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
            string p = to_string(idproducto);
            string consulta = "DELETE FROM productos WHERE idproducto=" + p + ";";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Eliminación exitosa..." << endl;
            }
            else {
                cout << "xxxx Error al eliminar xxxx" << endl;
            }
        }
        else {
            cout << "xxxx Conexion fallida xxxx" << endl;
        }
        cn.cerrar_conexion();
    }

    // CRUD completo con menú
    void crud_productos() {
        int opcion;
        do {
            system("cls"); // usa system("clear"); en Linux/Mac
            cout << "----- CRUD PRODUCTOS -----\n";
            cout << "1. Crear producto\n";
            cout << "2. Leer productos\n";
            cout << "3. Actualizar producto\n";
            cout << "4. Borrar producto\n";
            cout << "0. Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
            case 1: {
                cout << "Ingrese ID del producto: ";
                cin >> idproducto;
                cin.ignore();
                cout << "Nombre del producto: ";
                getline(cin, producto);
                cout << "Descripcion: ";
                getline(cin, descripcion);
                cout << "Imagen (ruta): ";
                getline(cin, imagen);
                cout << "Precio costo: ";
                cin >> precio_costo;
                cout << "Precio venta: ";
                cin >> precio_venta;
                cout << "Existencia: ";
                cin >> existencia;
                cout << "ID de marca: ";
                cin >> idmarcas;
                cin.ignore();
                cout << "Fecha ingreso (YYYY-MM-DD): ";
                getline(cin, fecha_ingreso);
                crear();
                system("pause");
                break;
            }
            case 2:
                leer();
                system("pause");
                break;
            case 3: {
                cout << "Ingrese ID del producto a actualizar: ";
                cin >> idproducto;
                cin.ignore();
                cout << "Nuevo nombre del producto: ";
                getline(cin, producto);
                cout << "Nueva descripcion: ";
                getline(cin, descripcion);
                cout << "Nueva imagen (ruta): ";
                getline(cin, imagen);
                cout << "Nuevo precio costo: ";
                cin >> precio_costo;
                cout << "Nuevo precio venta: ";
                cin >> precio_venta;
                cout << "Nueva existencia: ";
                cin >> existencia;
                cout << "Nuevo ID de marca: ";
                cin >> idmarcas;
                cin.ignore();
                cout << "Nueva fecha ingreso (YYYY-MM-DD): ";
                getline(cin, fecha_ingreso);
                actualizar();
                system("pause");
                break;
            }
            case 4: {
                cout << "Ingrese ID del producto a eliminar: ";
                cin >> idproducto;
                borrar();
                system("pause");
                break;
            }
            case 0:
                cout << "Saliendo del CRUD de productos...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
            }
        } while (opcion != 0);
    }
};
