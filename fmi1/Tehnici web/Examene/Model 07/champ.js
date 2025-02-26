window.onload = function () {
    field = document.querySelector('#field')
    field.addEventListener("click", selectGame);

    const url = 'http://127.0.0.1:5500/resources/champ.json';
    
    var promiseFetch = fetch(url);
    let meciuri;
    let nrMeciuri;

    promiseFetch.then((response) => {
        if (!response.ok) {
            throw new Error(`HTTP error: ${response.status}`);
        }
        return response.text();
    })
    .then(function(text) {
        meciuri = JSON.parse(text);
        meciuri = meciuri.matches
        // console.log(meciuri)
        nrMeciuri = meciuri.length
    })
    .catch(function (err) {
        alert(err);
    });

    let meci = document.createElement('meci')
    meci.className = "meci"
    document.body.append(meci)

    function selectGame() {
        let index = Math.floor(Math.random() * nrMeciuri)
        let date = meciuri[index]["date"]
        let time = meciuri[index]["time"]
        let homeTeam = meciuri[index]["homeTeam"]
        let guestTeam = meciuri[index]["guestTeam"]
        let homeflag = meciuri[index]["homeflag"]
        let guestflag = meciuri[index]["guestflag"]
        let country_where = meciuri[index]["country_where"]
        
        meci.innerHTML = 
        `
         <img src='${homeflag}' class="flag" />
        <img src='${guestflag}' class="flag" />
        <p>${homeTeam} vs ${guestTeam}</p>
         <p>on ${country_where} National    Stadium on ${date}, ${time}</p>
        `
        
    }
}


function drawField(){
    canvasElem.width = 600;
    canvasElem.height = 400;

    ctx.save();

    ctx.clearRect(0, 0, canvasElem.width, canvasElem.height);

    ctx.fillStyle = "green";
    ctx.fillRect(0, 0, 600, 400);

    ctx.strokeStyle = "white";
    ctx.lineWidth = 4;

    var path = new Path2D();
    path.moveTo(300, 20);
    path.lineTo(300, 380);
    ctx.stroke(path);

    ctx.strokeRect(20, 20, 600 - 40, 400 - 40);
    ctx.strokeRect(20, 125, 50, 150);
    ctx.strokeRect(530, 125, 50, 150);

    const circle = new Path2D();
    circle.arc(300, 200, 30, 0, 2 * Math.PI);
    ctx.stroke(circle);

    ctx.restore();
}

