const xml = '<?xml version="1.0" encoding="UTF-8"?> <cinemateca>     <film>         <titlu limba="en">The Shawshank Redemption</titlu>         <gen>Drama</gen>         <regizor>Frank Darabont</regizor>         <an>1994</an>         <scenarist>Frank Darabont</scenarist>         <producator>Niki Marvin</producator>         <actori>             <actor rol="principal">Tim Robbins</actor>             <actor rol="principal">Morgan Freeman</actor>         </actori>         <scor>9.3</scor>     </film>      <film>         <titlu limba="en">Inception</titlu>         <gen>Sci-Fi</gen>         <regizor>Christopher Nolan</regizor>         <an>2010</an>         <scenarist>Christopher Nolan</scenarist>         <producator>Emma Thomas</producator>         <actori>             <actor rol="principal">Leonardo DiCaprio</actor>             <actor rol="secundar">Joseph Gordon-Levitt</actor>         </actori>         <scor>8.8</scor>     </film> </cinemateca>';

parser = new DOMParser(); // se creează un analizor XML DOM
xmlDoc = parser.parseFromString(xml, "text/xml"); // se obține un obiect XMLDocument

// Afișați în fișierul HTML, folosind liste neordonate, conținutul obiectului JavaScript nou creat.

let cinemateca = xmlDoc.getElementsByTagName("cinemateca")[0];

let lista = document.createElement("ul");
document.body.appendChild(lista);

let filme = cinemateca.getElementsByTagName("film");
for (let film of filme) {
    let titlu = film.getElementsByTagName("titlu")[0].textContent;
    let gen = film.getElementsByTagName("gen")[0].textContent;
    let regizor = film.getElementsByTagName("regizor")[0].textContent;
    let an = film.getElementsByTagName("an")[0].textContent;
    let scenarist = film.getElementsByTagName("scenarist")[0].textContent;
    let producator = film.getElementsByTagName("producator")[0].textContent;
    let actori = film.getElementsByTagName("actori")[0].getElementsByTagName("actor");
    let scor = film.getElementsByTagName("scor")[0].textContent;

    let listaFilm = document.createElement("li");
    lista.appendChild(listaFilm);

    let detaliiFilm = document.createElement("ul");
    listaFilm.appendChild(detaliiFilm);

    let titluFilm = document.createElement("li");
    titluFilm.textContent = `Titlu: ${titlu}`;
    detaliiFilm.appendChild(titluFilm);

    let genFilm = document.createElement("li");
    genFilm.textContent = `Gen: ${gen}`;
    detaliiFilm.appendChild(genFilm);

    let regizorFilm = document.createElement("li");
    regizorFilm.textContent = `Regizor: ${regizor}`;
    detaliiFilm.appendChild(regizorFilm);

    let anFilm = document.createElement("li");
    anFilm.textContent = `An: ${an}`;
    detaliiFilm.appendChild(anFilm);

    let scenaristFilm = document.createElement("li");
    scenaristFilm.textContent = `Scenarist: ${scenarist}`;
    detaliiFilm.appendChild(scenaristFilm);

    let producatorFilm = document.createElement("li");
    producatorFilm.textContent = `Producator: ${producator}`;
    detaliiFilm.appendChild(producatorFilm);

    let actoriFilm = document.createElement("li");
    actoriFilm.textContent = "Actori:";
    detaliiFilm.appendChild(actoriFilm);

    let listaActori = document.createElement("ul");
    actoriFilm.appendChild(listaActori);

    for (let actor of actori) {
        let actorFilm = document.createElement("li");
        actorFilm.textContent = actor.textContent;
        listaActori.appendChild(actorFilm);
    }

    let scorFilm = document.createElement("li");
    scorFilm.textContent = `Scor: ${scor}`;
    detaliiFilm.appendChild(scorFilm);
}
