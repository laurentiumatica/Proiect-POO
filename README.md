# Sistem de Gestiune a Inventarului

Program destinat gestionării materialelor, furnizorilor și tranzacțiilor pentru un depozit de materiale de construcții.

---

## Arhitectura proiectului

Proiectul este organizat în fișiere `.h` și `.cpp` separate pentru fiecare clasă, respectând principiile POO: moștenire, polimorfism, încapsulare și abstractizare. Pe lângă acestea, au fost integrate trei design pattern-uri clasice — **Factory**, **Observer** și un container generic de tip **Repository**.

### Ierarhia de clase

```
Transaction (clasă de bază abstractă)
├── PurchaseOrder        — comandă de achiziție de la un furnizor
├── ConsumptionRecord    — consum de materiale pentru un proiect
├── ReturnTransaction    — returnare de materiale cu calcul automat al sumei
└── AdjustmentTransaction — ajustare manuală a cantităților din inventar
```

```
InventoryException (derivată din std::exception)
├── ValidationException          — erori de validare a datelor
├── ResourceNotFoundException    — resurse negăsite (material, furnizor, tranzacție)
└── InsufficientStockException   — stoc insuficient pentru operație
```

```
StockObserver (interfață abstractă de observator)
└── LowStockAlert        — afișează o avertizare când un material scade sub pragul critic
```

---

## Clasele proiectului

### Material

Reprezintă un material din inventar cu ID (`MAT-#####`), nume, unitate de măsură, cantitate, prag critic, preț unitar și categorie.

**Categorii disponibile:** wood, metal, insulation, finishes, others.

**Operații principale:**
- Construcție cu validare completă a tuturor câmpurilor
- Modificarea cantității, pragului critic și prețului unitar
- Comparație între materiale (operatorii `==` și `!=`)
- Citire/afișare prin operatorii `>>` și `<<`

### Provider

Reprezintă un furnizor cu ID (`PRV-#####`), nume, telefon, email, adresă și lista de materiale furnizate.

**Operații principale:**
- Construcție cu validare (format ID, email, telefon de 10 cifre)
- Afișarea materialelor disponibile
- Comparație și interschimbare între furnizori

### Transaction (clasă de bază abstractă)

Clasă abstractă care definește interfața comună pentru toate tipurile de tranzacții. Folosește pattern-ul NVI (Non-Virtual Interface): metoda publică `apply()` apelează metoda virtuală pură `do_apply()`, iar `print()` apelează `do_print()`.

**Clase derivate:**
- **PurchaseOrder** — comandă de achiziție cu status (pending/delivered/cancelled) și ID furnizor. La procesare, adaugă materialele comandate în inventar.
- **ConsumptionRecord** — înregistrare de consum cu nume de proiect și departament. La procesare, scade cantitățile din inventar.
- **ReturnTransaction** — returnare cu ID-ul tranzacției originale și motiv. La procesare, scade cantitățile și calculează suma de rambursat.
- **AdjustmentTransaction** — ajustare cu motiv. La procesare, setează cantitățile la valorile corectate.

Fiecare tranzacție poate fi procesată o singură dată (flag `processed` în clasa de bază).

### TransactionFactory (Factory Pattern)

Clasă utilitară cu metode statice care centralizează crearea tranzacțiilor. Fiecare metodă (`create_purchase_order`, `create_consumption_record`, `create_return_transaction`, `create_adjustment_transaction`) construiește obiectul derivat corespunzător și îl returnează ca `std::unique_ptr<Transaction>`. Astfel, codul din `Inventory` nu depinde direct de constructorii claselor concrete, ci doar de fabrică.

### Repository\<T\> (container generic)

Șablon de clasă (`template<typename T>`) folosit ca depozit tipizat pentru materiale și furnizori în interiorul clasei `Inventory`. Primește la construcție o funcție (`std::function`) care extrage ID-ul unui element, permițând căutare, adăugare și ștergere după ID indiferent de tipul stocat.

**Operații principale:** `add`, `find_by_id` (versiune const și non-const), `remove_by_id`, `clear`, `get_items`, `count`.

### StockObserver / LowStockAlert (Observer Pattern)

`StockObserver` este o interfață abstractă cu metoda virtuală pură `on_low_stock()`. `LowStockAlert` este implementarea concretă: afișează o avertizare formatată atunci când cantitatea unui material scade sub pragul critic. `Inventory` păstrează o listă de observatori și îi notifică automat (`notify_observers`) după procesarea tranzacțiilor care reduc stocul.

### Inventory

Gestionează materialele, furnizorii înregistrați și tranzacțiile inventarului. Materialele și furnizorii sunt stocați intern în câte un `Repository<T>`, iar tranzacțiile într-un `std::vector<std::unique_ptr<Transaction>>`.

**Operații principale:**
- Înregistrarea furnizorilor din catalogul global
- Plasarea comenzilor de achiziție cu materiale de la furnizorii înregistrați
- Înregistrarea consumurilor, returnărilor și ajustărilor
- Procesarea tranzacțiilor (aplicarea efectelor asupra stocului)
- Notificarea observatorilor la atingerea pragului critic de stoc
- Anularea comenzilor de achiziție în status pending
- Căutarea materialelor, furnizorilor și tranzacțiilor după ID
- Afișarea materialelor sortate după nume sau cantitate (fără modificarea ordinii interne)
- Filtrarea materialelor după categorie sau prag critic
- Calcularea costului total al inventarului și a sumei totale a rambursărilor
- Afișarea comenzilor de achiziție sortate după preț total

### Menu (Singleton)

Punctul de intrare în aplicație. Gestionează meniurile interactive și starea aplicației. La inițializare înregistrează un observator `LowStockAlert` pe inventar.

**Submeniuri:**
- **Inventory** — vizualizare și editare detalii inventar (nume, adresă, telefon, email)
- **Materials** — listare, căutare, filtrare pe categorie, materiale critice, sortare după nume/cantitate
- **Providers** — listare furnizori înregistrați/neînregistrați, înregistrare furnizor, căutare după ID
- **Transactions** — plasare comandă, consum, returnare, ajustare, procesare, anulare, listare, căutare
- **Reports** — cost total inventar, total rambursări, comenzi pe furnizor, sortare comenzi după preț
- **Developer Mode** — acces cu parolă pentru administrarea catalogului global de furnizori

---

## Validări implementate

- Formate de ID-uri: `MAT-#####`, `PRV-#####`, `TRN-#####`, `INV-#####`
- Format dată: `DD-MM-YYYY` cu validare de zile per lună și an bisect
- Email și telefon cu expresii regulate
- Unicitate ID-uri la crearea tranzacțiilor și materialelor
- Verificarea stocului disponibil la crearea consumurilor și returnărilor
- Prevenirea procesării multiple a oricărei tranzacții
- Verificarea existenței tranzacției originale la returnări
- Numărul de materiale unice nu poate depăși materialele disponibile

---

## Concepte POO utilizate

- **Moștenire** — `Transaction` cu 4 clase derivate; `InventoryException` cu 3 clase derivate; `StockObserver` cu o clasă derivată
- **Polimorfism** — funcții virtuale pure (`do_apply`, `do_print`, `clone`, `on_low_stock`) apelate prin pointeri de bază (`std::unique_ptr<Transaction>`, `std::unique_ptr<StockObserver>`)
- **NVI (Non-Virtual Interface)** — `apply()` și `print()` publice non-virtuale, `do_apply()` și `do_print()` private virtuale
- **Constructori virtuali** — `clone()` pentru copiere polimorfică
- **Șabloane (templates)** — clasa generică `Repository<T>` parametrizată cu tipul elementelor stocate
- **Smart pointers** — `std::unique_ptr<Transaction>` și `std::unique_ptr<StockObserver>` pentru gestiunea automată a memoriei
- **Copy-and-swap** — în operatorii de atribuire ai claselor `Material`, `Provider` și `Inventory`
- **`dynamic_cast`** — downcast cu sens în `process_transaction()`, `cancel_order()`, `get_inventory_total_refunds()`
- **Excepții proprii** — ierarhie independentă derivată din `std::exception`
- **STL** — `std::vector`, `std::string`, `std::unique_ptr`, `std::function`, `std::ranges::sort`, `std::ranges::find_if`, `std::regex`
- **Funcții și atribute statice** — `get_instance()`, `material_category_to_string()`, `purchase_order_status_to_string()`, metodele fabricii `TransactionFactory`, `print_selected_*()`, `sort_selected_*()`, `DEV_PASSWORD`

### Design pattern-uri

- **Singleton** — clasa `Menu` cu constructor privat și acces prin `get_instance()`
- **Factory** — `TransactionFactory` centralizează crearea celor 4 tipuri de tranzacții
- **Observer** — `StockObserver` / `LowStockAlert` pentru avertizări automate la stoc scăzut
- **Repository** — `Repository<T>` ca depozit generic tipizat pentru materiale și furnizori

---

## Compilare și rulare

```bash
g++ -std=c++20 -Wall -Wextra -o inventory_app main.cpp materials.cpp providers.cpp transactions.cpp inventory.cpp menu.cpp
./inventory_app
```

Alternativ, proiectul include o configurație CMake (`CMakeLists.txt`, standard C++20):

```bash
cmake -S . -B build
cmake --build build
./build/Proiect_1
```

---

## Structura fișierelor

```
main.cpp                — punctul de intrare
menu.h / menu.cpp       — singleton, meniuri interactive, date inițiale
inventory.h / .cpp      — clasa Inventory
materials.h / .cpp      — clasa Material
providers.h / .cpp      — clasa Provider
transactions.h / .cpp   — Transaction + 4 clase derivate
transaction_factory.h   — Factory pentru crearea tranzacțiilor
repository.h            — container generic Repository<T>
stock_observer.h        — Observer: StockObserver + LowStockAlert
exceptions.h            — ierarhia de excepții
utils.h                 — funcții de validare și helper-ul read_string
CMakeLists.txt          — configurația de build CMake
```