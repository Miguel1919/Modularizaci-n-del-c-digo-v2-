#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct Producto {
    string nombre;
    string codigo;
    int cantidad;
    double precio;
};

int buscarProducto(const vector<Producto>& inventario, const string& codigo) {
    for (int i = 0; i < (int)inventario.size(); i++) {
        if (inventario[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerEnteroPositivo(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= 0) {
            return valor;
        }
        cout << "  [!] Por favor ingrese un numero entero valido (mayor o igual a cero)." << endl;
        limpiarBuffer();
    }
}

double leerDecimalPositivo(const string& mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= 0.0) {
            return valor;
        }
        cout << "  [!] Por favor ingrese un valor numerico valido (mayor o igual a cero)." << endl;
        limpiarBuffer();
    }
}

void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "        GADGETXPRESS - MENU PRINCIPAL     " << endl;
    cout << "========================================" << endl;
    cout << "  1. Agregar nuevo producto" << endl;
    cout << "  2. Listar todos los productos" << endl;
    cout << "  3. Actualizar cantidad de un producto" << endl;
    cout << "  4. Reporte de bajo inventario" << endl;
    cout << "  5. Salir" << endl;
    cout << "----------------------------------------" << endl;
    cout << "  Seleccione una opcion: ";
}

void agregarProducto(vector<Producto>& inventario) {
    cout << "\n--- AGREGAR NUEVO PRODUCTO ---" << endl;

    Producto nuevo;

    cout << "  Nombre del producto  : ";
    limpiarBuffer();
    getline(cin, nuevo.nombre);

    cout << "  Codigo del producto  : ";
    getline(cin, nuevo.codigo);

    if (buscarProducto(inventario, nuevo.codigo) != -1) {
        cout << "  [!] Error: Ya existe un producto con ese codigo. Operasion cancelada." << endl;
        return;
    }

    nuevo.cantidad = leerEnteroPositivo("  Cantidad inicial    : ");
    nuevo.precio   = leerDecimalPositivo("  Precio unitario ($) : ");

    inventario.push_back(nuevo);
    cout << "  [OK] Producto \"" << nuevo.nombre << "\" agregado exitosamente." << endl;
}

void listarProductos(const vector<Producto>& inventario) {
    cout << "\n--- INVENTARIO COMPLETO ---" << endl;

    if (inventario.empty()) {
        cout << "  El imventario esta vacio." << endl;
        return;
    }

    cout << left
         << setw(12) << "CODIGO"
         << setw(24) << "NOMBRE"
         << setw(12) << "CANTIDAD"
         << setw(12) << "PRECIO"
         << endl;
    cout << string(60, '-') << endl;

    for (const Producto& p : inventario) {
        cout << left
             << setw(12) << p.codigo
             << setw(24) << p.nombre
             << setw(12) << p.cantidad
             << "$" << fixed << setprecision(2) << p.precio
             << endl;
    }
}

void actualizarCantidad(vector<Producto>& inventario) {
    cout << "\n--- ACTUALIZAR CANTIDAD ---" << endl;

    if (inventario.empty()) {
        cout << "  [!] No hay productos en el inventario." << endl;
        return;
    }

    cout << "  Ingrese el codigo del producto: ";
    limpiarBuffer();
    string codigo;
    getline(cin, codigo);

    int indice = buscarProducto(inventario, codigo);

    if (indice == -1) {
        cout << "  [!] Error: No existe ningun producto con ese codigo." << endl;
        return;
    }

    cout << "  Producto encontrado: " << inventario[indice].nombre << endl;
    cout << "  Cantidad actual    : " << inventario[indice].cantidad << endl;

    inventario[indice].cantidad = leerEnteroPositivo("  Nueva cantidad     : ");
    cout << "  [OK] Cantidad actualizada correctamente." << endl;
}

void generarReporteBajoInventario(const vector<Producto>& inventario) {
    const int UMBRAL_BAJO = 5;

    cout << "\n--- REPORTE DE BAJO INVENTARIO (menos de "
         << UMBRAL_BAJO << " unidades) ---" << endl;

    bool hayProductosBajos = false;

    cout << left
         << setw(12) << "CODIGO"
         << setw(24) << "NOMBRE"
         << setw(12) << "CANTIDAD"
         << endl;
    cout << string(48, '-') << endl;

    for (const Producto& p : inventario) {
        if (p.cantidad < UMBRAL_BAJO) {
            cout << left
                 << setw(12) << p.codigo
                 << setw(24) << p.nombre
                 << setw(12) << p.cantidad
                 << endl;
            hayProductosBajos = true;
        }
    }

    if (!hayProductosBajos) {
        cout << "  Todo el inventario esta en niveles optimos." << endl;
    }
}

int main() {
    vector<Producto> inventario;
    int opcion;

    cout << "========================================" << endl;
    cout << "   Bienvenido a GADGETXPRESS v2.0" << endl;
    cout << "   Sistema de Gestion de Inventario" << endl;
    cout << "========================================" << endl;

    do {
        mostrarMenu();
        if (!(cin >> opcion)) {
            cout << "\n  [!] Entrada no balida." << endl;
            limpiarBuffer();
            opcion = 0;
            continue;
        }

        switch (opcion) {
            case 1: agregarProducto(inventario);              break;
            case 2: listarProductos(inventario);              break;
            case 3: actualizarCantidad(inventario);           break;
            case 4: generarReporteBajoInventario(inventario); break;
            case 5: cout << "\nHasta luego. Que tenga un exelente dia!" << endl; break;
            default: cout << "\n  [!] Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 5);

    return 0;
}