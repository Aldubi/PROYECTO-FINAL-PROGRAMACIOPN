#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "ConexionBD.h"
using namespace std;

class clientes {
protected:
    string nombres, apellidos, nit, telefono, correo_electronico, fechaingreso;
    int id_cliente = 0;
    int genero = 0;

public:
    clientes() {}
    clientes(string nom, string ape, string nt, int gen, string tel, string ce, string fi, int idc) {
        nombres = nom;
        apellidos = ape;
        nit = nt;
        genero = gen;
        telefono = tel;
        correo_electronico = ce;
        fechaingreso = fi;
        id_cliente = idc;
    }

    // Setters y Getters
    void setIdCliente(int id) { id_cliente = id; }
    void setNombres(string n) { nombres = n; }
    void setApellidos(string a) { apellidos = a; }
    void setNit(string n) { nit = n; }
    void setGenero(int g) { genero = g; }
    void setTelefono(string t) { telefono = t; }
    void setCorreo(string c) { correo_electronico = c; }
    void setFechaIngreso(string f) { fechaingreso = f; }

    int getIdCliente() { return id_cliente; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getNit() { return nit; }
    int getGenero() { return genero; }
    string getTelefono() { return telefono; }
    string getCorreo() { return correo_electronico; }
    string getFechaIngreso() { return fechaingreso; }

    // Validación de NIT sin guion
    bool validarNit(string nit) {
        // Convertir a mayúsculas
        for (auto& c : nit) c = toupper(c);

        // Consumidor final
        if (nit == "CF" || nit == "C/F") return true;

        // Remover guion si lo tuviera
        nit.erase(remove(nit.begin(), nit.end(), '-'), nit.end());

        if (nit.length() < 2 || nit.length() > 9) return false;

        char digito = nit[nit.length() - 1];
        if (!isdigit(digito) && digito != 'K') return false;

        int suma = 0;
        size_t factor = nit.length() - 2;

        for (size_t i = 0; i < nit.length() - 1; ++i) {
            if (!isdigit(nit[i])) return false;
            suma += (nit[i] - '0') * static_cast<int>(factor--);
        }

        int verificador = (11 - (suma % 11)) % 11;
        char esperado = (verificador == 10) ? 'K' : ('0' + verificador);

        return toupper(digito) == esperado;
    }

    // CRUD
    void crear() {
        nit.erase(remove(nit.begin(), nit.end(), '-'), nit.end());
        if (!validarNit(nit)) {
            cout << "NIT inválido. No se puede registrar el cliente." << endl;
            return;
        }

        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fechaingreso) VALUES ('" +
                nombres + "','" + apellidos + "','" + nit + "'," + to_string(genero) + ",'" + telefono + "','" + correo_electronico + "','" + fechaingreso + "');";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Cliente ingresado correctamente." << endl;
            }
            else {
                cout << "Error al ingresar el cliente." << endl;
            }
        }
        else {
            cout << "Error de conexión." << endl;
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
            string query = "SELECT * FROM clientes;";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                cout << "ID\tNombres\tApellidos\tNIT\tGenero\tTelefono\tCorreo\tFechaIngreso" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << "\t" << fila[1] << "\t" << fila[2] << "\t" << fila[3] << "\t" << fila[4]
                        << "\t" << fila[5] << "\t" << fila[6] << "\t" << fila[7] << endl;
                }
            }
            else {
                cout << "Error al consultar clientes." << endl;
            }
        }
        else {
            cout << "Error de conexión." << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        nit.erase(remove(nit.begin(), nit.end(), '-'), nit.end());
        if (!validarNit(nit)) {
            cout << "NIT inválido. No se puede actualizar el cliente." << endl;
            return;
        }

        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id = to_string(id_cliente);
            string query = "UPDATE clientes SET nombres='" + nombres +
                "', apellidos='" + apellidos +
                "', nit='" + nit +
                "', genero=" + to_string(genero) +
                ", telefono='" + telefono +
                "', correo_electronico='" + correo_electronico +
                "', fechaingreso='" + fechaingreso +
                "' WHERE id_cliente=" + id + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Cliente actualizado correctamente." << endl;
            }
            else {
                cout << "Error al actualizar el cliente." << endl;
            }
        }
        else {
            cout << "Error de conexión." << endl;
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id = to_string(id_cliente);
            string query = "DELETE FROM clientes WHERE id_cliente=" + id + ";";
            const char* c = query.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "Cliente eliminado correctamente." << endl;
            }
            else {
                cout << "Error al eliminar el cliente." << endl;
            }
        }
        else {
            cout << "Error de conexión." << endl;
        }
        cn.cerrar_conexion();
    }

    void buscarPorNit(string nit_buscar) {
        nit_buscar.erase(remove(nit_buscar.begin(), nit_buscar.end(), '-'), nit_buscar.end());
        ConexionBD cn;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        bool encontrado = false;
        if (cn.getConector()) {
            string query = "SELECT nombres, apellidos FROM clientes WHERE nit='" + nit_buscar + "';";
            const char* c = query.c_str();
            if (!mysql_query(cn.getConector(), c)) {
                resultado = mysql_store_result(cn.getConector());
                if ((fila = mysql_fetch_row(resultado))) {
                    cout << "Cliente encontrado: " << fila[0] << " " << fila[1] << endl;
                    encontrado = true;
                }
            }
        }
        cn.cerrar_conexion();

        if (!encontrado) {
            cout << "NIT no encontrado. Registrando nuevo cliente..." << endl;
            crear();
        }
    }
};