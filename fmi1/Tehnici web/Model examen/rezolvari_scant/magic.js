window.onload = function () {
    bila = document.getElementById("ccenter")
    bila.addEventListener("click", answer);

    const url = 'http://127.0.0.1:5500/Model%20examen/rezolvari_scant/magic.json';
    
    var promiseFetch = fetch(url);
    let possanswers;

    promiseFetch.then((response) => {
        if (!response.ok) {
            throw new Error(`HTTP error: ${response.status}`);
        }
        return response.text();
    })

        .then(function (text) {
            possanswers = JSON.parse(text);
        })
        .catch(function (err) {
            alert(err);
        });


    function answer() {
        let max = possanswers.length;
        let ans = Math.floor(Math.random() * max);
        let color = "green";
        if (possanswers[ans].bool == "no")
            color = "red";
        else if (possanswers[ans].bool == "maybe")
            color = "orange";

        bila.style.backgroundColor = color
        bila.innerHTML = ""

        let infodiv = document.getElementById("info");
        infodiv.innerHTML = possanswers[ans].text;
        infodiv.style.color = color;
    }
}



