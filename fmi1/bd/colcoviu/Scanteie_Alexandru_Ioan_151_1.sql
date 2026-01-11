-- Scanteie Alexandru Ioan
-- grupa 151
-- nr 1

-- INSTITUTIE(id#,denumire, nr_departamente,localitate)
-- CURS(id#,id_institutie, denumire,nr_credite)
-- INSCRIERE(id#,id_curs,data_inscriere,nr_zile_curs)
-- TARIF_CURS(id_curs#,data_start#,data_end,tarif)
-- STUDENT(id#,nume,prenume,data_nasterii,localitate_domiciliu,tara,telefon)
-- STUDENT_INSCRIERE(id_inscriere#,id_student#)
-- FACILITATE(id#,denumire)
-- INSTITUTIE_FACILITATE(id_institutie#,id_facilitate#)

--     cerinta 1
-- Sa se afiseaze toate instutiile educationale impreuna cu toate cursurile organizate de aceasta, precum si facilitatile disponibile in acele institutii.
-- se vor afisa doar inscireile efectuate in anul 2023
-- se vor afisa: id_institutie, denumire institutie, numarul de departamente din cadrul institutiei, denumirile facilitatilor disponibile, denumirea cursului si tarifele ascoiate fiecarui curs ( toate tarifele pe care le-a avut)
-- Daca o institutie nu are facilitatati, se va afisa in output, textul "Nu are facilitati"
-- de asemenea, se vor elimina duplicatele
-- se vor afisa Cod institutie,Denumire Institutie, Nr departamente, Denumire facilitate, Denumire Curs, Tarif Curs

SELECT DISTINCT I.ID "Cod Institutie", -- pt a elimina duplicatele
       I.DENUMIRE "Denumire Institutie",
       I.NR_DEPARTAMENTE "Nr Departamente",
       NVL(F.DENUMIRE, 'Nu are facilitati') "Denumire Facilitate",
       C.DENUMIRE "Denumire Curs",
       TC.TARIF "Tarif Curs"
FROM INSTITUTIE I
JOIN CURS C ON I.ID = C.ID_INSTITUTIE
JOIN INSCRIERE I2 ON C.ID = I2.ID_CURS
JOIN TARIF_CURS TC ON C.ID = TC.ID_CURS
LEFT JOIN INSTITUTIE_FACILITATE IF ON I.ID = IF.ID_INSTITUTIE
LEFT JOIN FACILITATE F ON IF.ID_FACILITATE = F.ID
WHERE I2.DATA_INSCRIERE > TO_DATE('2022-12-31','YYYY-MM-DD') and  I2.DATA_INSCRIERE < TO_DATE('2024-01-01','YYYY-MM-DD'); -- prea lenes sa dau extract :))


-- cerinta 2
-- sa se afiseze, pentru fiecare institutie educationala, cursul la care s-au inscris cei mai multi studenti care provin din afara romaniei.
-- tara din care provine un student se va verifica folosind majuscule.
-- pentru fiecare institutie se va afisa un singur curs - acela la care s-au inscris cei mai multi studenti straini.
-- se presupune ca nu exista egalitate intre mai multe cursuri(adica exista un singur maxim pentru fiecare institutie)
-- se voir afisa urmatoarele coloane: id_institutie, denumirea_institutie, codul cursului, denumirea cursului, si o coloana cu numarul total de inscrieri numita "Numar inscrieri"( Numarul de inscireire realizate de studenti din afara Romaniei)


SELECT I.ID "Cod Institutie", I.DENUMIRE "Denumire Institutie", C.ID "Cod Curs", C.DENUMIRE "Denumire Curs", COUNT(SI.ID_STUDENT) "Numar Inscrieri"
FROM INSTITUTIE I
JOIN CURS C ON I.ID = C.ID_INSTITUTIE
JOIN INSCRIERE I2 ON C.ID = I2.ID_CURS
JOIN STUDENT_INSCRIERE SI ON I2.ID = SI.ID_INSCRIERE
JOIN STUDENT S on SI.ID_STUDENT = S.ID
WHERE S.TARA IS NOT NULL AND UPPER(S.TARA) != UPPER('Romania')
GROUP BY I.ID, I.DENUMIRE, C.ID, C.DENUMIRE
HAVING COUNT(SI.ID_STUDENT) = (
    SELECT MAX(NumarInscrieri)
    FROM (
        SELECT COUNT(SI2.ID_STUDENT) AS NumarInscrieri
        FROM INSTITUTIE I2
        JOIN CURS C2 ON I2.ID = C2.ID_INSTITUTIE
        JOIN INSCRIERE I3 ON C2.ID = I3.ID_CURS
        JOIN STUDENT_INSCRIERE SI2 ON I3.ID = SI2.ID_INSCRIERE
        JOIN STUDENT S2 on SI2.ID_STUDENT = S2.ID
        WHERE S2.TARA IS NOT NULL AND UPPER(S2.TARA) != UPPER('Romania')
        GROUP BY I2.ID, C2.ID
    )
);


-- cerinta 3
-- sa se afiseze codurile si denumiirle institutilor educationale care ofera toate facilitatile institutiei cu cei mai putini studenti distincti inscrisi in total la cursurile sale (se presupune ca exista daor o singura astfel de institutie)
-- o institutie poate avea de mai multe ori inscris un anumit student .
-- o sa se numere doar studentii distincti pentru fieacre institutie in parte.
-- institutile afisate pot avea si alte facilitati, dar trebuie sa aiba , obligatoriu, toate facilitatile institutiei cu cei mai putini studenti distincti.
-- se va exclude in rezultate institutia sursa, adica cea cu cei mai putini studenti inscrisi.
-- se vor afisa codul si denumirea institutilor

SELECT I.ID "Cod Institutie", I.DENUMIRE "Denumire Institutie", C.ID "Cod Curs", C.DENUMIRE "Denumire Curs", COUNT(DISTINCT SI.ID_STUDENT) "Numar Inscrieri"
FROM INSTITUTIE I
JOIN CURS C ON I.ID = C.ID_INSTITUTIE
JOIN INSCRIERE I2 ON C.ID = I2.ID_CURS
JOIN STUDENT_INSCRIERE SI ON I2.ID = SI.ID_INSCRIERE
JOIN STUDENT S on SI.ID_STUDENT = S.ID
WHERE S.TARA IS NOT NULL AND UPPER(S.TARA)!=UPPER('Romania')
GROUP BY I.ID, I.DENUMIRE, C.ID, C.DENUMIRE
HAVING COUNT(SI.ID_STUDENT) = (
    SELECT MIN(NumarDistincti)
    FROM (
        SELECT COUNT(DISTINCT SI2.ID_STUDENT) AS NumarDistincti
        FROM INSTITUTIE I2
        JOIN CURS C2 ON I2.ID = C2.ID_INSTITUTIE
        JOIN INSCRIERE I3 ON C2.ID = I3.ID_CURS
        JOIN STUDENT_INSCRIERE SI2 ON I3.ID = SI2.ID_INSCRIERE
        GROUP BY I2.ID, I2.DENUMIRE
    )
);

-- cerinta 4
-- creati tabelul capacitate_curs care sa contina codul cursului, denumirea cursului si o colaana care sa indice capacitatea fiecarui curs.
-- capacitatea e definita ca numarul total de isncrieri ale studentilor prentru acel curs
-- se contorizeaza toate incsrirle, inclusiv situatiile in care acelasi student s-a inscris de mai multe ori.
-- se va crea tabelul cu urmatoarele coloane: cod_curs, nume_curs, capacitate.
-- se vor insera datele conform logicii cerute, prin intermediui uneicereri sql.
-- la final tablul se va sterge
-- COD_CURS NUME_CURS CAPACITATE
-- 1     Baza de Date 3
-- 2 Structuri de date 5 etc..

CREATE TABLE CAPACITATE_CURS AS
SELECT C.ID "Cod Curs", C.DENUMIRE "Denumire Curs", COUNT(SI.ID_STUDENT) "Capacitate"
FROM CURS C
JOIN INSCRIERE I ON C.ID = I.ID_CURS
JOIN STUDENT_INSCRIERE SI on I.ID = SI.ID_INSCRIERE
GROUP BY C.ID, C.DENUMIRE;
DROP TABLE CAPACITATE_CURS
