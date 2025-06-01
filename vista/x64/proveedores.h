#include "empleados.h"
#include <iostream>
#include "proveedores.h"
using namespace std;

void crud_proveedores() {
    proveedores prov;
    int subop;
    do {
        cout << "\n--- CRUD PROVEEDORES ---\n";
        cout << "1. Crear\n";
        cout << "2. Leer\n";
        cout << "3. Actualizar\n";
        cout << "4. Borrar\n";
        cout << "0. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> subop;
        cin.ignore();

        switch (subop) {
        case 1: {
            string proveedor, nit, direccion, telefono;
            cout << "Ingrese proveedor: "; getline(cin, proveedor);
            cout << "Ingrese NIT: "; getline(cin, nit);
            cout << "Ingrese direccion: "; getline(cin, direccion);
            cout << "Ingrese telefono: "; getline(cin, telefono);
            proveedores nuevo(proveedor, nit, direccion, telefono, 0);
            nuevo.crear();
            break;
        }
        case 2: {
            proveedores p;
            p.leer();
            break;
        }
        case 3: {
            int id;
            string proveedor, nit, direccion, telefono;
            cout << "Ingrese ID del proveedor a actualizar: "; cin >> id; cin.ignore();
            cout << "Nuevo proveedor: "; getline(cin, proveedor);
            cout << "Nuevo NIT: "; getline(cin, nit);
            cout << "Nueva direccion: "; getline(cin, direccion);
            cout << "Nuevo telefono: "; getline(cin, telefono);
            proveedores actualizado(proveedor, nit, direccion, telefono, id);
            actualizado.actualizar();
            break;
        }
        case 4: {
            int id;
            cout << "Ingrese ID del proveedor a eliminar: "; cin >> id; cin.ignore();
            proveedores eliminar("", "", "", "", id);
            eliminar.borrar();
            break;
        }
        case 0: break;
        default: cout << "Opcion no valida.\n";
        }
    } while (subop != 0);
}

int main() {
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. CRUD Empleados\n";
        cout << "2. CRUD Proveedores\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            empleados emp;
            emp.crud_empleados();
            break;
        }
        case 2: {
            crud_proveedores();
            break;
        }
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);

    return 0;
}