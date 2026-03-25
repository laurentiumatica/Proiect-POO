# Sistem de Gestiune a Inventarului

Program destinat gestionării materialelor, furnizorilor și comenzilor pentru un depozit de materiale.

## Clasele Proiectului

### Clasa Material
Reprezintă un material din inventar cu ID, nume, unitate de măsură, cantitate, prag critic, preț unitar și categorie.

**Operații principale:**
* Obține/setează informațiile materialului (ID, nume, unitate de măsură, cantitate, prag critic, preț unitar, categorie).
* Verifică dacă materialul este sub pragul critic.

### Clasa Provider
Reprezintă un furnizor cu ID, nume, telefon, email, adresă, lista de materiale furnizate și discount.

**Operații principale:**
* Obține/setează informațiile furnizorului (ID, nume, contact, adresă, materiale, discount).

### Clasa Order
Reprezintă o comandă cu ID, ID furnizor, lista de materiale, cantități, preț total, dată și status.

**Operații principale:**
* Obține/setează informațiile comenzii (ID, furnizor, materiale, cantități, preț total, dată, status).
* Verifică statusul comenzii (pending, delivered, cancelled).

### Clasa Inventory
Gestionează materialele, furnizorii și comenzile inventarului.

**Operații principale:**
* Obține/setează informațiile inventarului (ID, nume, adresă, telefon, email).
* Adaugă materiale noi.
* Adaugă furnizori noi.
* Adaugă comenzi noi.
* Caută materiale, furnizori sau comenzi după ID.
* Calculează valoarea totală a inventarului.
* Sortează materialele după nume sau cantitate.
* Sortează comenzile după prețul total.
* Filtrează comenzile după furnizor.
* Obține materialele critice sau sortate după categorie.
* Consumă materiale din stoc.
* Primește comenzi și actualizează stocurile.

---

## Funcționalități principale

* Crearea de materiale cu parametri personalizați (wood, metal, insulation, finishes, others).
* Crearea de furnizori cu informații de contact și discount-uri.
* Adăugarea comenzilor de la furnizori cu liste de materiale și cantități.
* Verificarea stocurilor și identificarea materialelor aflate sub pragul critic.
* Gestionarea mai multor inventare cu capacități diferite.
* Vizualizarea informațiilor complete ale materialelor, furnizorilor și comenzilor.
* Calcularea valorii totale a inventarului.
* Sortarea și filtrarea datelor pentru analiză.

---

## Note tehnice

* Categoriile de materiale sunt: wood, metal, insulation, finishes, others.
* Statusurile comenzilor sunt: pending, delivered, cancelled, unknown.
* Eligibilitatea pentru comenzi se bazează pe capacitățile inventarului.
* Gestiunea memoriei: programul folosește alocare dinamică de memorie pentru string-uri și tablouri.