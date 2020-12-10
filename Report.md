# Tagok

| Név | Github azonosito  | Javasolt relatív érdemjegy | Becsült óra | Indoklás  | 
| --- | ---- | --- | ------------------ | --------- |
| Almási Szabolcs | @AlmasiSzabolcs | +1 | 55 | A csapat összetartó ereje volt. Ő hajtotta csapatot, hogy időben kész legyünk a feladatokkal. Ezen kívül maga is ügyesen megoldotta a rá eső feladatokat és problémákat. |
| Beszedics Tamás | @beszedics | 0 | 50 | A rábízott feladatokat alaposan és időben megoldotta, A használt szoftverfejlesztési eszközöket érti és alkalmazni tudja. A csapat megbeszéléseken mindig részt vett. |
| Élő Kristóf Lajos | @kristofelo | 0 | 50 | A rábízott feladatokat időben megoldotta, A használt szoftverfejlesztési eszközöket érti és alkalmazni is tudja. A csapat megbeszéléseken mindig részt vett. PR-eknél értékelte a társcsapat munkáját. |


# Videók

 - [Gameplay](/videos/gameplay.mp4)
 - [CodeBaseDefense](/videos/codebasedefense.mp4)

# Befejezett feladatok

| Feladat | Merge ideje a határidóhöz (nap) | Change request körök | Reviewer | 
| ------- | ------------------------------- | -------------------- | -------- |
| Feladat 1 | +1 | 1 | @oliverosz | 
| Feladat 2 | +3 | 0 | @vizvezetek |
| jsonparser | +11 | 1 | @wajzy |
| levelup | 0 | 5 | @oliverosz |
| attackspeed | -5 | 0 | @vizvezetek |
| documentation | -1 | 0 | @kristofelo / @thethreevision - @poloczmate, @radvanszkyl |
| unittest | -2 | 0 | @beszedics, @AlmasiSzabolcs / @thethreevision - @poloczmate, @borbelytomii |
| makefile | -2 | 2 | @hegyhati |
| refactor | 0 | 0 | @hegyhati |
| docker | -3 | 0 | @hegyhati |
| jsonpimp | Merge: 11.21 | 0 | @kristofelo / @thethreevision - @poloczmate, @borbelytomii |
| map | Merge: 11.24 | 0 | @kristofelo / @thethreevision - @borbelytomii, @radvanszkyl |
| game | Merge: 12.09 | 0 | @thethreevision - @borbelytomii |
| defense | Merge: 11.23 | 0 | @AlmasiSzabolcs, @kristofelo / @thethreevision - @borbelytomii |
| damage | Merge: 11.26 | 0 | @beszedics / @thethreevision - @borbelytomii, @radvanszkyl  |
| markedmap | nem készült el | - | - |
| preparedgame | nem készült el | - | -
| light radius | nem készült el | - | - |
| rendering | nem készült el | - | - |

# Unit tesztek

| Osztály | Publikus metódusok száma | Unit tesztelt metódusok száma | Unit tesztek száma |
| --- | --- | --- | --- |
| `Hero` | 4 | 5 | 7 |
| `Monster` | 9 | 6 | 10 | 
| `JSON` | 5 | 3 | 6 | 
| `Map` | 2 | 0 | 0 | 
| `Game` | 8 | 0 | 0 | 

# Kód dokumentáció

| Teljesen dokumentált osztályok | Részben dokumentált osztályok | Nem dokumentált osztályok |
| --- | --- | --- | 
| `Hero` |  |  |  
| `JSON` |
| `Monster` |
| `Damage` |
| `Map` |
| `Game` |

# Mindenféle számok

 - Összes cpp kódsor : 572
 - Egyéb kódsor : 
    * 76 (python)
    * 148 (gtest)
    * 51 (Makefile)
    * 2579 (doxconf)
    * 26 (Dockerfile)
    * 61 (yml)
 - cppcheck
   - warning : 0
   - style : 14
   - performance : 6
   - unusedFunction : 0
   - missingInclude : 0
 
# Implicit megtanult dolgok
Olyanok, amik nem a tárgy anyaga, de muszáj/hasznos volt elsajátítani:
 - `alapvető python scripting`
 - `std::variant`
 - `sor végi eltérő karakterek szerepe különböző operációs rendszerek között (LF vs CRLF)`

# Feedback (optional)
Git, Dockert használunk máshol is, így ez hasznos volt, valamint szerencsésnek találtuk, hogy egy újonnan megjelenő eszközt a Github Actions-t tudtuk használni, ami úgy látszik, hogy eléggé elterjedt már most.

Az online videók mindenképpen hasznosak voltak, mert így többször vissza tudtuk nézni.

# Üzenet a jövőbe (optional)
