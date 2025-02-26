window.onload = function () {
    let name_of_file
    let canvasID

    canvas = document.querySelector(`#${canvasID}`)
    canvas.addEventListener("click", select);

    const url = `http://127.0.0.1:5500/resources/${name_of_file}.json`;
    
    var promiseFetch = fetch(url);
    let list;
    let nrlist;

    promiseFetch.then((response) => {
        if (!response.ok) {
            throw new Error(`HTTP error: ${response.status}`);
        }
        return response.text();
    })
    .then(function(text) {
        list = JSON.parse(text);
        nrlist = list.length
    })
    .catch(function (err) {
        alert(err);
    });

    let divDesc = document.createElement('div')
    divDesc.className = "divDesc"
    document.body.append(divDesc)

    function select() {
        let index = Math.floor(Math.random() * nrlist)
        let titlu = list[index]["title"]
        let date = list[index]["date"]
        let time = list[index]["time"]
        let starring = list[index]["starring"]
        let poster = list[index]["poster"]
        let rating = list[index]["rate"]
        
        divDesc.innerHTML = 
        `<h5>${date}</h5>
         <p>${time} - ${titlu}</p>
         <img src='resources/${poster}' />
         <p class="distributie">${starring} + ${rating}</p>
        `
        
    }
}



