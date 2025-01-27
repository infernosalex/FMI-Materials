window.onload = function () {
    tv = document.querySelector('#tv')
    tv.addEventListener("click", selectMovie);

    const url = 'http://127.0.0.1:5500/resources/zap.json';
    
    var promiseFetch = fetch(url);
    let filme;
    let nrFilme;

    promiseFetch.then((response) => {
        if (!response.ok) {
            throw new Error(`HTTP error: ${response.status}`);
        }
        return response.text();
    })
    .then(function(text) {
        filme = JSON.parse(text);
        // console.log(filme)
        nrFilme = filme.length
    })
    .catch(function (err) {
        alert(err);
    });

    let tvDiv = document.createElement('div')
    tvDiv.className = "tvdiv"
    document.body.append(tvDiv)

    function selectMovie() {
        let index = Math.floor(Math.random() * nrFilme)
        let titlu = filme[index]["title"]
        let date = filme[index]["date"]
        let time = filme[index]["time"]
        let starring = filme[index]["starring"]
        let poster = filme[index]["poster"]
        let rating = filme[index]["rate"]
        
        tvDiv.innerHTML = 
        `<h5>${date}</h5>
         <p>${time} - ${titlu}</p>
         <img src='resources/${poster}' />
         <p class="distributie">${starring} + ${rating}</p>
        `
        
    }
}



