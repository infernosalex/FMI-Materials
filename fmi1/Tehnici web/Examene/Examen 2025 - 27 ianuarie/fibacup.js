window.addEventListener("load", main);
function main() {
    canvasElem = document.getElementById("field"); 
    ctx = canvasElem.getContext("2d");
    drawField();
}

var canvasElem;
var ctx;
function drawField(){
    canvasElem.width = 600;
    canvasElem.height = 400;

    ctx.save();

    ctx.clearRect(0, 0, canvasElem.width, canvasElem.height);

    ctx.fillStyle = "#e9692c";
    ctx.fillRect(0, 0, 600, 400);

    ctx.strokeStyle = "white";
    ctx.lineWidth = 4;

    var path = new Path2D();
    path.moveTo(300, 0);
    path.lineTo(300, 400);
    ctx.stroke(path);

    ctx.strokeRect(0, 150, 75, 100);
    ctx.strokeRect(525, 150, 75, 100);

    // Circle center
    const circle = new Path2D();
    circle.arc(300, 200, 80, 0, 2 * Math.PI);
    ctx.stroke(circle);


    // Circle left
    const circlel = new Path2D();
    circlel.arc(70, 200, 50, 0, 2 * Math.PI);
    ctx.stroke(circlel);    
    
    // Circle right
    const circler = new Path2D();
    circler.arc(530, 200, 50, 0, 2 * Math.PI);
    ctx.stroke(circler);

    // arc left
    const arcl = new Path2D();
    arcl.arc(-50, 200, 200, 0*Math.PI, 2*Math.PI);
    ctx.stroke(arcl);

    // arc right
    const arcr = new Path2D();
    arcr.arc(650, 200, 200, 0*Math.PI, 2*Math.PI);
    ctx.stroke(arcr);  

    ctx.restore();
}

window.onload = function () {
 // modify this
    canvas = document.querySelector(`#field`)
    canvas.addEventListener("click", select);

 // modify this
    const url = `http://127.0.0.1:5501/resources/fibacup.json`;
    
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
        console.log(list[index])
        let home = list[index]["home"]
        let homeflag = list[index]["homeflag"]
        let guest = list[index]["guest"]
        let guestflag = list[index]["guestflag"]
        let date = list[index]["date"]
        let time = list[index]["time"]
        divDesc.innerHTML = 
        `
        <div class="tabela">
            <img src='resources/${homeflag}' class="flag" />
            <img src='resources/${guestflag}' class="flag" />
        </div>
        <p class="info">${date} at ${time}</p>
        `
    }
}


