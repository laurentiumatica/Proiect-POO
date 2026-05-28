# Sistem de Gestiune a Inventarului

Program destinat gestionării materialelor, furnizorilor și tranzacțiilor pentru un depozit de materiale de construcții.

---

## Review: Sistem de Gestiune a Inventarului
 
Proiectul meu implementează un sistem de gestiune a unui depozit de materiale de construcții. Ideea de implementare pleacă de la o problemă concretă în business. Un depozit primește marfă de la furnizori, o consumă pentru diverse proiecte, înregistrează returnări și efectuează ajustări de stoc, iar toate aceste operații trebuie urmărite, validate și raportate. Soluția aleasă implementează fiecare dintre aceste concepte o clasă clar definită: material, furnizor, tranzacție, inventar, și organizează interacțiunea dintre ele printr-o aplicație în terminal cu meniu interactiv. Întregul cod este împărțit în fișiere `.h` și `.cpp` separate pentru fiecare clasă, ceea ce a făcut ca dezvoltarea acestuia să fie mai ușor de gestionat pe parcurs.
 
Ierarhia moștenirilor pleacă de la clasa abstractă `Transaction`, care nu derivă din nimic și care definește interfața comună pentru orice tip de operație asupra stocului. Din ea derivă patru clase: `PurchaseOrder` (comandă de materiale), `ConsumptionRecord` (consum de materiale), `ReturnTransaction` (returnare de materiale) și `AdjustmentTransaction` (ajustarea cantităților materialelor). Polimorfismul nu este folosit decorativ, ci funcțional. `Transaction` declară metodele virtuale pure `do_apply()` și `do_print()`, apelate prin metodele publice non-virtuale `apply()` și `print()`, după modelul NVI. Această separare permite clasei de bază să controleze ce se întâmplă în jurul operațiilor. De exemplu, `apply()` marchează automat tranzacția ca procesată după ce apelează `do_apply()`, fără ca derivatele să poată ocoli acest comportament. Funcția `do_apply()` este, totodată, funcția virtuală specifică temei. Ea nu este o simplă afișare sau citire, ci conține logica reală prin care fiecare tip de tranzacție își produce efectul asupra inventarului, fiecare derivată comportându-se diferit. Pe lângă acest lucru, clasa de bază declară și constructorul pur virtual `clone()`, care obligă fiecare derivată să știe să se copieze polimorfic. Constructorii claselor derivate apelează explicit constructorul clasei de bază `Transaction`, transmițându-i partea comună (id, dată, lista de materiale).
 
Clasa `Inventory` este componenta care deține atributul de tip pointer la bază. Ea păstrează tranzacțiile într-un `std::vector<std::unique_ptr<Transaction>>`. Folosirea smart pointerilor în loc de pointeri clasici elimină grija gestiunii manuale a memoriei și garantează eliberarea corectă a obiectelor derivate, prin destructorul virtual al clasei de bază. Aceeași buclă de procesare și de afișare funcționează identic pentru orice tip de tranzacție, fără implementare separată personalizată. Acolo unde este nevoie de un comportament specific unui subtip, de exemplu pentru a calcula suma totală a rambursărilor, pentru a filtra doar comenzile de materiale sau pentru a verifica dacă o tranzacție care trebuie anulată este într-adevăr o comandă, se folosește `dynamic_cast` cu verificarea rezultatului înainte de orice operație, ceea ce reprezintă un downcast cu sens, nu unul forțat. Tot la nivelul claselor cu stare proprie (`Material`, `Provider`, `Inventory`) este aplicat conceptul de copy-and-swap. Operatorul de atribuire primește parametrul prin valoare și interschimbă membrii cu `std::swap`, ceea ce asigură atribuiri corecte și previne alterarea stării interne în caz de excepții.
 
Tratarea erorilor se bazează pe o ierarhie de excepții. Baza este `InventoryException`, derivată din `std::exception`, iar din ea derivă trei clase pentru categorii de erori distincte: `ValidationException` pentru date invalide, `ResourceNotFoundException` pentru resurse inexistente (material, furnizor sau tranzacție inexistente) și `InsufficientStockException` pentru cazurile în care stocul nu este suficient pentru o operație care este cerută. Cele trei nu sunt variații ale aceleiași erori, ci probleme conceptual diferite, ceea ce respectă cerința de categorii distincte. Excepțiile sunt folosite cu sens, fiind transmise din constructorii claselor și din funcțiile de validare atunci când datele nu sunt corecte și sunt „prinse” mai sus în lanțul de apeluri, astfel încât o eroare la introducerea unui ID greșit nu afectează aplicația, ci produce un mesaj clar de alertă și permite reîncercarea introducerii datelor. Validările sunt centralizate într-un fișier `utils.h` cu funcții care verifică formatele de ID prin expresii regulate, corectitudinea datelor calendaristice (inclusiv zilele lunilor anului și anul bisect), unicitatea identificatorilor și disponibilitatea stocului. Proiectul folosește, de asemenea, funcții și atribute statice, componente STL variate (`std::vector`, `std::string`, `std::unique_ptr`, `std::function`, `std::regex` și algoritmii din `std::ranges`) și aplică `const` cât se poate de des, urmărind totodată implementarea unor funcții de nivel înalt și reducerea getterilor și a setterilor low-level.
 
Față de proiectele anterioare, varianta actuală a adăugat exact elementele cerute de Tema 3 în structura deja existentă. Cea mai vizibilă schimbare este introducerea celor două design patternuri (factory și observer). **Factory** a fost adăugat prin clasa `TransactionFactory`, cu metode statice care centralizează crearea celor patru tipuri de tranzacții și le returnează ca `std::unique_ptr<Transaction>`. Astfel, codul din `Inventory` nu mai depinde direct de constructorii claselor, ci doar de „fabrică”, iar o eventuală schimbare în modul de construire a unei tranzacții rămâne izolată într-un singur loc. **Singleton** (care a fost implementat încă de la Tema 2) a fost aplicat clasei `Menu`, punctul de intrare al aplicației. Constructorul este privat, accesul se face exclusiv prin metoda statică `get_instance()`, iar constructorii de copiere și de mutare sunt explicit șterși, ceea ce garantează că există o singură instanță a meniului pe toată durata rulării programului. **Observer** a fost adăugat prin interfața abstractă `StockObserver` și implementarea concretă `LowStockAlert`. Inventarul păstrează o listă de observers și îi anunță automat, prin `notify_observers()`, atunci când cantitatea unui material scade sub pragul critic asociat acestuia, ceea ce separă complet logica alertelor de logica procesării de tranzacții.
 
Tot ca element de noutate, a fost introdusă o clasă șablon. `Repository<T>` este parametrizată cu tipul elementelor stocate și primește la construcție o funcție `std::function` care extrage ID-ul unui element, ceea ce îi permite să asigure căutare, adăugare și ștergere după ID, indiferent de tipul de date. Clasa este instanțiată de două ori în interiorul lui `Inventory`: `Repository<Material>` și `Repository<Provider>`. Înainte de introducerea șablonului, aceeași logică de container ar fi trebuit scrisă de două ori, o dată pentru materiale și încă o dată pentru furnizori. Generalizarea face ca, dacă în viitor ar apărea un nou tip de entitate care trebuie stocată și căutată după ID, să se poată refolosi `Repository` fără nicio modificare adusă codului.
 
O altă modificare pe care am făcut-o este legată de opțiunea „Developer Mode” din meniul principal. Similar versiunii anterioare a proiectului, catalogul de furnizori și materiale distribuite de aceștia era hardcodat, însă pentru Milestone 2 plănuiam și posibilitatea introducerii unor noi date de la tastatură în timpul folosirii aplicației de gestiune a inventarului. Pentru a reduce complexitatea proiectului și a separa rolul efectiv al proiectului de alte elemente adiționale care păreau totuși interesante, am ales ca pentru varianta finală a acestuia datele să rămână hardocate și să renunț la ideea de a crea noi materiale și furnizori. În plus, această decizie aduce avantaje precum pornirea aplicației dintr-o stare validă, deoarece catalogul nu mai poate fi alterat cu date inconsistente în timpul rulării. În al doilea rând, datele de referință au fost separate clar de datele operaționale. Catalogul de materiale și de furnizori este stabil, iar utilizatorul rămâne responsabil doar de partea dinamică a aplicației, adică plasarea comenzilor, consumurile, returnările și ajustările de stoc. Acest lucru se potrivește și cu logica reală a unui depozit, unde lista de materiale și de furnizori se schimbă rar, în timp ce tranzacțiile sunt cele care variază des.
 
În concluzie, proiectul meu acoperă integral cerințele temelor și implementează o aplicație funcțională cu o structură clară și ușor de extins. Față de versiunile anterioare, această etapă a adus cele patru design patternuri, clasa șablon Repository<T> cu cele două instanțieri ale sale și fixarea în cod a catalogului de materiale și furnizori, prin renunțarea la posibilitatea de a-l extinde din „Developer Mode” și păstrarea acestui mod doar pentru vizualizarea datelor „globale”. Moștenirea, polimorfismul prin pointeri la clasa de bază și separarea responsabilităților fac codul ușor de dezvoltat și schimbat. Adăugarea unui nou tip de tranzacție, a unei noi excepții sau a unui nou observer ar cere modificări minime în codul pe care l-am scris, ceea ce a fost, de fapt, scopul principal al întregii implementări.

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
